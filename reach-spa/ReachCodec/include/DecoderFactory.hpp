///////////////////////////////////////////////////////////////////////////////
// NAME:            DecoderFactory.hpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Factory for decoder implementations.
//
// CREATED:         09/15/2020
//
// LAST EDITED:     09/19/2020
////

#ifndef __ET_DECODERFACTORY__
#define __ET_DECODERFACTORY__

#include <memory>

#include <namespace.hpp>
#include <BufferedAudioStreamWriter.hpp>

class ReachCodec::DecoderFactory
{
public:
  static std::unique_ptr<Interfaces::Decoder> makeDecoder(uint8_t magic[4],
    BufferedAudioStreamWriter writer);
};

#endif // __ET_DECODERFACTORY__

///////////////////////////////////////////////////////////////////////////////
