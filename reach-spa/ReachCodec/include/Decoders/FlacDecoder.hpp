///////////////////////////////////////////////////////////////////////////////
// NAME:            FlacDecoder.hpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Interface for a FLAC decoder.
//
// CREATED:         09/15/2020
//
// LAST EDITED:     09/18/2020
////

#ifndef __ET_FLACDECODER__
#define __ET_FLACDECODER__

#include <stdlib.h>
#include <emscripten/fiber.h>
#include <FLAC++/decoder.h>

#include <namespace.hpp>
#include <Interfaces/Decoder.hpp>

//
// Public decoder interface
//
class ReachCodec::Decoders::FlacDecoder : public Interfaces::Decoder
{
public:
  FlacDecoder();
  virtual ~FlacDecoder() {}
  virtual emscripten::val decodeChunk(std::vector<uint8_t> byteData,
    bool endOfStream) final override;

private:
  class StreamDecoderImpl;

  // Unfortunately, this object needs to be huge, since it holds three
  // independent execution stacks.
  std::shared_ptr<emscripten_fiber_t> m_mainFiber;
  std::shared_ptr<char> m_mainAsyncStack;
  static const constexpr size_t s_mainAsyncStackSize = 131072;

  std::shared_ptr<emscripten_fiber_t> m_decodeFiber;
  std::shared_ptr<char> m_decodeCStack;
  std::shared_ptr<char> m_decodeAsyncStack;
  static const constexpr size_t s_decodeCStackSize = 131072;
  static const constexpr size_t s_decodeAsyncStackSize = 131072;

  std::shared_ptr<StreamDecoderImpl> m_decoder;
};

//
// Derived Stream Decoder class
//
class ReachCodec::Decoders::FlacDecoder::StreamDecoderImpl
  : public FLAC::Decoder::Stream
{
public:
  StreamDecoderImpl(std::shared_ptr<emscripten_fiber_t> mainFiber,
    std::shared_ptr<emscripten_fiber_t> thisFiber);
  void addNewData(std::vector<uint8_t> newBytes);
  std::vector<std::vector<int32_t>>& getOutput();
  void clearOutput();
  void setEndOfStreamFlag();

protected:
  virtual ::FLAC__StreamDecoderReadStatus read_callback(FLAC__byte buffer[],
    size_t *bytes) final override;
  virtual ::FLAC__StreamDecoderWriteStatus write_callback(const ::FLAC__Frame*
    frame, const FLAC__int32 * const buffer[]) final override;
  virtual void error_callback(::FLAC__StreamDecoderErrorStatus status) final
    override;

private:
  std::vector<uint8_t> m_bytes;
  std::vector<std::vector<int32_t>> m_output;
  std::shared_ptr<emscripten_fiber_t> m_mainFiber;
  std::shared_ptr<emscripten_fiber_t> m_thisFiber;
  bool m_endOfStream;
};

#endif // __ET_FLACDECODER__

///////////////////////////////////////////////////////////////////////////////
