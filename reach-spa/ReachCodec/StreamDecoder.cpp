///////////////////////////////////////////////////////////////////////////////
// NAME:            StreamDecoder.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Implements a Stream Decoder for FLAC files in C++.
//
// CREATED:         09/09/2020
//
// LAST EDITED:     09/09/2020
////

#include <emscripten.h>
#include <emscripten/bind.h>
// #include <FLAC++/decoder.h>

using namespace emscripten;

class StreamDecoder {
public:
  StreamDecoder() = default;
  std::string getMessage() const {
    return s_message;
  }

private:
  static const std::string s_message;
};

const std::string StreamDecoder::s_message = "Hello from C++!";

EMSCRIPTEN_BINDINGS(StreamDecoder) {
  class_<StreamDecoder>("StreamDecoder")
    .constructor<>()
    .function("getMessage", &StreamDecoder::getMessage)
    ;
}

///////////////////////////////////////////////////////////////////////////////
