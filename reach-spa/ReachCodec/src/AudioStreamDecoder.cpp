///////////////////////////////////////////////////////////////////////////////
// NAME:            AudioStreamDecoder.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements a Stream Decoder for Audio files in C++.
//
// CREATED:         09/09/2020
//
// LAST EDITED:     09/15/2020
////

#include <vector>
#include <stdint.h>

#include <AudioStreamDecoder.hpp>
#include <DecoderFactory.hpp>
#include <Interfaces/Decoder.hpp>
// #include <FLAC++/decoder.h>

using namespace emscripten;
using namespace ReachCodec;

AudioStreamDecoder::AudioStreamDecoder()
  : m_decoder{nullptr}
{}

void AudioStreamDecoder::reset()
{
  m_decoder = nullptr;
}

val AudioStreamDecoder::decodeChunk(val byteBuffer)
{
  std::vector<uint8_t> byteData = vecFromJSArray<uint8_t>(byteBuffer);
  uint8_t magicBytes[4] = {byteData[0], byteData[1], byteData[2], byteData[3]};
  if (nullptr == m_decoder) {
    m_decoder = DecoderFactory::makeDecoder(magicBytes);
  }

  return m_decoder->decodeChunk(byteData);
}

EMSCRIPTEN_BINDINGS(AudioStreamDecoder) {
  class_<AudioStreamDecoder>("AudioStreamDecoder")
    .constructor<>()
    .function("reset", &AudioStreamDecoder::reset)
    .function("decodeChunk", &AudioStreamDecoder::decodeChunk)
    ;
}

///////////////////////////////////////////////////////////////////////////////
