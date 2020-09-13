///////////////////////////////////////////////////////////////////////////////
// NAME:            AudioStreamDecoder.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements a Stream Decoder for Audio files in C++.
//
// CREATED:         09/09/2020
//
// LAST EDITED:     09/13/2020
////

#include <AudioStreamDecoder.h>
// #include <FLAC++/decoder.h>

using namespace emscripten;
using namespace ReachCodec;

void AudioStreamDecoder::reset()
{}

val AudioStreamDecoder::decodeChunk(val)
{
  return val::array();
}

EMSCRIPTEN_BINDINGS(AudioStreamDecoder) {
  class_<AudioStreamDecoder>("AudioStreamDecoder")
    .constructor<>()
    .function("reset", &AudioStreamDecoder::reset)
    .function("decodeChunk", &AudioStreamDecoder::decodeChunk)
    ;
}

///////////////////////////////////////////////////////////////////////////////
