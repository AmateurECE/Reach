///////////////////////////////////////////////////////////////////////////////
// NAME:            FlacDecoder.hpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Interface for a FLAC decoder.
//
// CREATED:         09/15/2020
//
// LAST EDITED:     09/15/2020
////

#ifndef __ET_FLACDECODER__
#define __ET_FLACDECODER__

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
  virtual emscripten::val decodeChunk(std::vector<uint8_t> byteData) final
    override;

private:
  class StreamDecoderImpl;

  std::unique_ptr<StreamDecoderImpl> m_decoder;
};

//
// Derived Stream Decoder class
//
class ReachCodec::Decoders::FlacDecoder::StreamDecoderImpl
  : public FLAC::Decoder::Stream
{
protected:
  virtual ::FLAC__StreamDecoderReadStatus read_callback(FLAC__byte buffer[],
    size_t *bytes) final override;
  virtual ::FLAC__StreamDecoderWriteStatus write_callback(const ::FLAC__Frame*
    frame, const FLAC__int32 * const buffer[]) final override;
  virtual void error_callback(::FLAC__StreamDecoderErrorStatus status) final
    override;
};

#endif // __ET_FLACDECODER__

///////////////////////////////////////////////////////////////////////////////
