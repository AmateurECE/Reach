///////////////////////////////////////////////////////////////////////////////
// NAME:            EmscriptenBindings.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Binding declarations for Embind.
//
// CREATED:         09/19/2020
//
// LAST EDITED:     09/19/2020
////

#include <emscripten/bind.h>

#include <AudioPlayer.hpp>
#include <AudioStreamDecoder.hpp>
#include <BufferedAudioStreamWriter.hpp>
#include <Interfaces/Decoder.hpp>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(AudioStreamDecoder) {
  class_<ReachCodec::AudioPlayer>("AudioPlayer")
    .constructor<>()
    .function("play", &ReachCodec::AudioPlayer::play)
    .function("pause", &ReachCodec::AudioPlayer::pause)
    ;

  class_<ReachCodec::BufferedAudioStreamWriter>("BufferedAudioStreamWriter")
    .constructor<size_t, ReachCodec::AudioPlayer>()
    ;

  class_<ReachCodec::AudioStreamDecoder>("AudioStreamDecoder")
    .constructor<ReachCodec::BufferedAudioStreamWriter>()
    .function("reset", &ReachCodec::AudioStreamDecoder::reset)
    .function("decodeChunk", &ReachCodec::AudioStreamDecoder::decodeChunk)
    ;
}

///////////////////////////////////////////////////////////////////////////////
