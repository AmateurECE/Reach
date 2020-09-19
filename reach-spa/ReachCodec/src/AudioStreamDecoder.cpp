///////////////////////////////////////////////////////////////////////////////
// NAME:            AudioStreamDecoder.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements a Stream Decoder for Audio files in C++.
//
// CREATED:         09/09/2020
//
// LAST EDITED:     09/19/2020
////

#include <vector>
#include <stdint.h>

#include <AudioStreamDecoder.hpp>
#include <DecoderFactory.hpp>
#include <Interfaces/Decoder.hpp>

using namespace emscripten;
using namespace ReachCodec;

AudioStreamDecoder::AudioStreamDecoder()
  : m_decoder{nullptr}
{}

void AudioStreamDecoder::reset()
{
  m_decoder = nullptr;
}

val AudioStreamDecoder::decodeChunk(val byteBuffer, bool endOfStream)
{
  std::vector<uint8_t> byteData = vecFromJSArray<uint8_t>(byteBuffer);
  if (nullptr == m_decoder) {
    uint8_t magicBytes[4] = {byteData[0], byteData[1], byteData[2],
                             byteData[3]};
    m_decoder = DecoderFactory::makeDecoder(magicBytes);
  }

  return m_decoder->decodeChunk(byteData, endOfStream);
}

EMSCRIPTEN_BINDINGS(AudioStreamDecoder) {
  class_<AudioStreamDecoder>("AudioStreamDecoder")
    .constructor<>()
    .function("reset", &AudioStreamDecoder::reset)
    .function("decodeChunk", &AudioStreamDecoder::decodeChunk)
    ;
}

///////////////////////////////////////////////////////////////////////////////
