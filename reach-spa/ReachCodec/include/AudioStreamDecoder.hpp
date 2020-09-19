///////////////////////////////////////////////////////////////////////////////
// NAME:            AudioStreamDecoder.h
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Public interface for the AudioStreamDecoder class, which
//                  has emscripten bindings and is publicly available via the
//                  JavaScript API.
//
// CREATED:         09/13/2020
//
// LAST EDITED:     09/19/2020
////

#ifndef __ET_AUDIOSTREAMDECODER__
#define __ET_AUDIOSTREAMDECODER__

#include <namespace.hpp>
#include <BufferedAudioStreamWriter.hpp>

class ReachCodec::AudioStreamDecoder {
public:
  AudioStreamDecoder(BufferedAudioStreamWriter writer);

  void decodeChunk(emscripten::val chunkBuffer, bool endOfStream);
  void reset();

private:
  std::unique_ptr<Interfaces::Decoder> m_decoder;
  BufferedAudioStreamWriter m_writer;
};

#endif // __ET_AUDIOSTREAMDECODER__

///////////////////////////////////////////////////////////////////////////////
