///////////////////////////////////////////////////////////////////////////////
// NAME:            flac.hpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Basic wrapper for the FLAC library
//
// CREATED:         08/30/2020
//
// LAST EDITED:     08/30/2020
////

#ifndef flac_hpp
#define flac_hpp

class Decoder {
public:
  Decoder(std::string filename);
  ~Decoder();

  std::vector<std::string> getTags() const;

private:
  std::vector<std::string> m_tags;
};

#endif /* flac_hpp */

///////////////////////////////////////////////////////////////////////////////
