///////////////////////////////////////////////////////////////////////////////
// NAME:            FlacDecoder.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implementation of the FLAC decoder.
//
// CREATED:         09/15/2020
//
// LAST EDITED:     09/15/2020
////

#include <Decoders/FlacDecoder.hpp>

using namespace emscripten;
using namespace ReachCodec::Decoders;

//
// Public decoder interface
//
FlacDecoder::FlacDecoder()
  : m_decoder{std::make_unique<StreamDecoderImpl>()}
{}

val FlacDecoder::decodeChunk(std::vector<uint8_t> bytes)
{
  return val::array();
}

//
// Derived Stream Decoder class
//
::FLAC__StreamDecoderReadStatus
FlacDecoder::StreamDecoderImpl::read_callback(FLAC__byte buffer[],
  size_t *bytes)
{
  return ::FLAC__STREAM_DECODER_READ_STATUS_ABORT;
}

::FLAC__StreamDecoderWriteStatus
FlacDecoder::StreamDecoderImpl::write_callback(const ::FLAC__Frame* frame,
  const FLAC__int32 * const buffer[])
{
  return ::FLAC__STREAM_DECODER_WRITE_STATUS_ABORT;
}

void FlacDecoder::StreamDecoderImpl
::error_callback(::FLAC__StreamDecoderErrorStatus status)
{}

///////////////////////////////////////////////////////////////////////////////
