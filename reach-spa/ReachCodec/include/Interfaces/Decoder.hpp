///////////////////////////////////////////////////////////////////////////////
// NAME:            Decoder.hpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Interface for Decoders of all kinds
//
// CREATED:         09/15/2020
//
// LAST EDITED:     09/19/2020
////

#ifndef __ET_DECODER_HPP__
#define __ET_DECODER_HPP__

#include <namespace.hpp>

class ReachCodec::Interfaces::Decoder
{
public:
  virtual ~Decoder() {};
  virtual void decodeChunk(std::vector<uint8_t> byteData,
    bool endOfStream) = 0;
};

#endif // __ET_DECODER_HPP__

///////////////////////////////////////////////////////////////////////////////
