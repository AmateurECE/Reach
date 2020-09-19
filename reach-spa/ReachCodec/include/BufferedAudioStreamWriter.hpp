///////////////////////////////////////////////////////////////////////////////
// NAME:            BufferedAudioStreamWriter.hpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Buffers PCM data on its way to the Audio Device.
//
// CREATED:         09/19/2020
//
// LAST EDITED:     09/19/2020
////

#ifndef __ET_BUFFEREDAUDIOSTREAMWRITER__
#define __ET_BUFFEREDAUDIOSTREAMWRITER__

#include <namespace.hpp>
#include <AudioPlayer.hpp>

class ReachCodec::BufferedAudioStreamWriter
{
public:
  BufferedAudioStreamWriter(size_t bufferSize, AudioPlayer audioDevice);
  void write(AudioBufferMetadata metadata,
    const int32_t* const pcm[]);

private:
  AudioPlayer m_audioDevice;
};

#endif // __ET_BUFFEREDAUDIOSTREAMWRITER__

///////////////////////////////////////////////////////////////////////////////
