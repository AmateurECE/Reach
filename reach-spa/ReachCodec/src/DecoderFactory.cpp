///////////////////////////////////////////////////////////////////////////////
// NAME:            DecoderFactory.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implementation of the DecoderFactory
//
// CREATED:         09/15/2020
//
// LAST EDITED:     09/15/2020
////

#include <stdexcept>

#include <DecoderFactory.hpp>
#include <Decoders/FlacDecoder.hpp>

using namespace ReachCodec;

std::unique_ptr<Interfaces::Decoder>
DecoderFactory::makeDecoder(uint8_t magicBytes[4])
{
  std::string magicWord{reinterpret_cast<char*>(magicBytes), 4};
  if ("fLaC" == magicWord) {
    return std::make_unique<Decoders::FlacDecoder>();
  }

  throw std::invalid_argument("Magic bytes not recognized: " + magicWord);
}

///////////////////////////////////////////////////////////////////////////////
