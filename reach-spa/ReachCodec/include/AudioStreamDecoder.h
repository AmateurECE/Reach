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
// LAST EDITED:     09/13/2020
////

#ifndef __ET_AUDIOSTREAMDECODER__
#define __ET_AUDIOSTREAMDECODER__

#include <emscripten.h>
#include <emscripten/bind.h>

namespace ReachCodec {
class AudioStreamDecoder {
public:
  AudioStreamDecoder() = default;

  emscripten::val decodeChunk(emscripten::val chunkBuffer);
  void reset();
};
}

#endif // __ET_AUDIOSTREAMDECODER__

///////////////////////////////////////////////////////////////////////////////
