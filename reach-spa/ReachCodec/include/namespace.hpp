///////////////////////////////////////////////////////////////////////////////
// NAME:            namespace.hpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Namespace declarations for the project
//
// CREATED:         09/15/2020
//
// LAST EDITED:     09/15/2020
////

#ifndef __ET_NAMESPACE__
#define __ET_NAMESPACE__

namespace ReachCodec {
  namespace Interfaces {
    class Decoder;
  }

  namespace Decoders {
    class FlacDecoder;
  }

  class AudioStreamDecoder;
  class DecoderFactory;
}

#endif // __ET_NAMESPACE__

///////////////////////////////////////////////////////////////////////////////
