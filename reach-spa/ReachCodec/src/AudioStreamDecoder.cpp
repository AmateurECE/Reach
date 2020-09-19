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
#include <emscripten/bind.h>

#include <AudioStreamDecoder.hpp>
#include <DecoderFactory.hpp>
#include <Interfaces/Decoder.hpp>

using namespace emscripten;
using namespace ReachCodec;

AudioStreamDecoder::AudioStreamDecoder(BufferedAudioStreamWriter writer)
  : m_decoder{nullptr}, m_writer{writer}
{}

void AudioStreamDecoder::reset()
{
  m_decoder = nullptr;
}

void AudioStreamDecoder::decodeChunk(val byteBuffer, bool endOfStream)
{
  std::vector<uint8_t> byteData = vecFromJSArray<uint8_t>(byteBuffer);
  if (nullptr == m_decoder) {
    uint8_t magicBytes[4] = {byteData[0], byteData[1], byteData[2],
                             byteData[3]};
    m_decoder = DecoderFactory::makeDecoder(magicBytes, m_writer);
  }

  m_decoder->decodeChunk(byteData, endOfStream);
}

///////////////////////////////////////////////////////////////////////////////
