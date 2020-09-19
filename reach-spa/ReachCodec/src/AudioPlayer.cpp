///////////////////////////////////////////////////////////////////////////////
// NAME:            AudioPlayer.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Plays PCM Audio data.
//
// CREATED:         09/19/2020
//
// LAST EDITED:     09/19/2020
////

#include <emscripten/bind.h>
#include <iostream>

#include <AudioPlayer.hpp>

using namespace emscripten;

ReachCodec::AudioPlayer::AudioPlayer()
  : m_audioContext{nullptr}
{
  auto allocator =
    []() {
      val AudioContext = val::global("AudioContext");
      if (!AudioContext.as<bool>()) {
        AudioContext = val::global("webkitAudioContext");
      }

      return AudioContext.new_();
    };
  // TODO: latencyHint: 'interactive'
  m_audioContext = std::make_shared<val>(allocator());
}

void ReachCodec::AudioPlayer::play()
{}

void ReachCodec::AudioPlayer::pause()
{}

void ReachCodec::AudioPlayer::enqueue(AudioBufferMetadata metadata,
  const int32_t* const pcm[])
{
  // const int length = metadata.numberOfChannels * metadata.blockSize;
  // val audioSource = m_audioContext->call<val>("createBufferSource");
  // val audioBuffer = m_audioContext->call<val>("createBuffer",
  //   metadata.numberOfChannels, length, metadata.sampleRate);
  std::string message = "Int32Array(" + std::to_string(metadata.blockSize)
    + "){";
  for (unsigned i = 0; i < (metadata.blockSize > 10? 10 : metadata.blockSize);
       ++i) {
    message += std::to_string(pcm[0][i]) + ", ";
  }

  message += "...}\n";
  std::cout << message;
}

///////////////////////////////////////////////////////////////////////////////
