///////////////////////////////////////////////////////////////////////////////
// NAME:            FlacDecoder.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implementation of the FLAC decoder.
//
// CREATED:         09/15/2020
//
// LAST EDITED:     09/19/2020
////

#include <Decoders/FlacDecoder.hpp>

using namespace emscripten;
using namespace ReachCodec::Decoders;

// TODO: Abstract emscripten_fiber_* calls to an Adaptor class
//   in order to decouple the logic from the fiber implementation? E.g. allow
//   easy porting to new environments in the future.

//
// Public decoder interface
//
FlacDecoder::FlacDecoder()
  : // Memory related to main fiber
    m_mainFiber{std::make_shared<emscripten_fiber_t>()},
    m_mainAsyncStack{new char[s_mainAsyncStackSize],
                     std::default_delete<char[]>()},

    // Memory related to decode fiber
    m_decodeFiber{std::make_shared<emscripten_fiber_t>()},
    m_decodeCStack{new char[s_decodeCStackSize],
                   std::default_delete<char[]>()},
    m_decodeAsyncStack{new char[s_decodeAsyncStackSize],
                       std::default_delete<char[]>()},

    // Decoder
    m_decoder{std::make_shared<StreamDecoderImpl>(m_mainFiber, m_decodeFiber)}
{
  // Initialize the main fiber
  emscripten_fiber_init_from_current_context(m_mainFiber.get(),
    m_mainAsyncStack.get(), s_mainAsyncStackSize);

  // Initialize decode fiber
  auto decodeFiberEntry =
    [](void* arg) {
      auto decoder = static_cast<FLAC::Decoder::Stream*>(arg);
      decoder->process_until_end_of_stream();
    };
  emscripten_fiber_init(m_decodeFiber.get(), decodeFiberEntry, m_decoder.get(),
    m_decodeCStack.get(), s_decodeCStackSize, m_decodeAsyncStack.get(),
    s_decodeAsyncStackSize);

  // Actual setup for the decoder.
  // TODO: Register for metadata callbacks here.
  m_decoder->init();

  // Swap to decode fiber to initiate decoding. The fiber returns to this
  // constructor on the first call to the read_callback.
  emscripten_fiber_swap(m_mainFiber.get(), m_decodeFiber.get());
}

val FlacDecoder::decodeChunk(std::vector<uint8_t> bytes, bool endOfStream)
{
  // Start by clearing the output vector. It could contain residual data from
  // a previous call to decodeChunk().
  m_decoder->clearOutput();

  // Copy new data in, swap to decode fiber. Potentially set end_of_stream.
  m_decoder->addNewData(bytes);
  if (endOfStream) {
    m_decoder->setEndOfStreamFlag();
  }
  emscripten_fiber_swap(m_mainFiber.get(), m_decodeFiber.get());

  val output = val::array();
  std::vector<std::vector<int32_t>>& outputVector = m_decoder->getOutput();
  for (unsigned long i = 0; i < outputVector.size(); i++) {
    output.call<void>("push", val(typed_memory_view(outputVector[i].size(),
          outputVector[i].data())));
  }

  return output;
}

//
// Derived Stream Decoder class
//
FlacDecoder::StreamDecoderImpl
::StreamDecoderImpl(std::shared_ptr<emscripten_fiber_t> mainFiber,
  std::shared_ptr<emscripten_fiber_t> thisFiber)
  : m_mainFiber{mainFiber}, m_thisFiber{thisFiber}, m_endOfStream{false}
{}

void FlacDecoder::StreamDecoderImpl::addNewData(std::vector<uint8_t> newBytes)
{
  std::copy(newBytes.begin(), newBytes.end(), std::back_inserter(m_bytes));
}

std::vector<std::vector<int32_t>>& FlacDecoder::StreamDecoderImpl::getOutput()
{
  return m_output;
}

void FlacDecoder::StreamDecoderImpl::clearOutput()
{
  m_output.clear();
}

void FlacDecoder::StreamDecoderImpl::setEndOfStreamFlag()
{
  m_endOfStream = true;
}

//
// FLAC Callbacks
//
::FLAC__StreamDecoderReadStatus
FlacDecoder::StreamDecoderImpl::read_callback(FLAC__byte buffer[],
  size_t* bytes)
{
  // If there's no data to copy, switch back to the main fiber.
  if (m_bytes.empty()) {
    if (m_endOfStream) {
      return ::FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
    }
    emscripten_fiber_swap(m_thisFiber.get(), m_mainFiber.get());
  }

  // Otherwise, move the data into the array.
  auto endElement = m_bytes.size() > (*bytes)? m_bytes.begin() + (*bytes)
    : m_bytes.end();
  std::copy(m_bytes.begin(), endElement, buffer);
  m_bytes.erase(m_bytes.begin(), endElement);
  return ::FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
}

::FLAC__StreamDecoderWriteStatus
FlacDecoder::StreamDecoderImpl::write_callback(const ::FLAC__Frame* frame,
  const FLAC__int32* const buffer[])
{
  const unsigned int numberOfChannels = frame->header.channels;

  // TODO: Once we begin handling metadata, move this to the metadata_callback.
  if (m_output.empty()) {
    for (unsigned int i = 0; i < numberOfChannels; i++) {
      m_output.push_back(std::vector<int32_t>());
    }
  }

  // Copy the decoded frames into the output vector.
  for (unsigned int i = 0; i < numberOfChannels; ++i) {
    std::copy(buffer[i], buffer[i] + frame->header.blocksize,
      std::back_inserter(m_output[i]));
  }
  return ::FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void FlacDecoder::StreamDecoderImpl
::error_callback(::FLAC__StreamDecoderErrorStatus)
{
  // Really not sure what to do here, but we have to provide an implementation.
}

///////////////////////////////////////////////////////////////////////////////
