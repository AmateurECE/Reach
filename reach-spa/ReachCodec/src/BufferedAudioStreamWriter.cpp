///////////////////////////////////////////////////////////////////////////////
// NAME:            BufferedAudioStreamWriter.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Buffers PCM audio data on its way to the audio device.
//
// CREATED:         09/19/2020
//
// LAST EDITED:     09/19/2020
////

#include <stdlib.h>
#include <stdint.h>
#include <emscripten/bind.h>

#include <BufferedAudioStreamWriter.hpp>

using namespace emscripten;

ReachCodec::BufferedAudioStreamWriter
::BufferedAudioStreamWriter(size_t, ReachCodec::AudioPlayer audioDevice)
  : m_audioDevice{audioDevice}
{}

void ReachCodec::BufferedAudioStreamWriter
::write(AudioBufferMetadata metadata,
  const int32_t* const pcm[])
{
  // TODO: Implement actual buffering here
  m_audioDevice.enqueue(metadata, pcm);
}

///////////////////////////////////////////////////////////////////////////////
