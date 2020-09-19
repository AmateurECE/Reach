///////////////////////////////////////////////////////////////////////////////
// NAME:            AudioPlayer.hpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Plays PCM Audio data.
//
// CREATED:         09/19/2020
//
// LAST EDITED:     09/19/2020
////

#ifndef __ET_AUDIOPLAYER__
#define __ET_AUDIOPLAYER__

#include <memory>

#include <namespace.hpp>

// Forward declaration for compiler
namespace emscripten { class val; }

struct ReachCodec::AudioBufferMetadata
{
  unsigned int numberOfChannels;
  unsigned int blockSize;
  unsigned int sampleRate;
};

class ReachCodec::AudioPlayer
{
public:
  AudioPlayer();
  void play();
  void pause();
  void enqueue(AudioBufferMetadata metadata, const int32_t* const pcm[]);

private:
  std::shared_ptr<emscripten::val> m_audioContext;
};

#endif // __ET_AUDIOPLAYER__

///////////////////////////////////////////////////////////////////////////////
