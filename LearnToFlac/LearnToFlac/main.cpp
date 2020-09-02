///////////////////////////////////////////////////////////////////////////////
// NAME:            main.cpp
//
// AUTHOR:          Ethan D. Twardy <edtwardy@mtu.edu>
//
// DESCRIPTION:     Main file for the project.
//
// CREATED:         08/30/2020
//
// LAST EDITED:     09/02/2020
////

#include <iostream>
#include <vector>
#include <FLAC/stream_decoder.h>

const char* FILENAME = "/Users/ethantwardy/Git/WebApplication/Reach/"
  "dreamland.flac";

void CheckStatus(FLAC__bool status, const char* message)
{
  if (!status) {
    std::cerr << message << "\n";
    exit(1);
  }
}

void CheckStatus(FLAC__StreamDecoderInitStatus status, const char* message)
{
  if (FLAC__STREAM_DECODER_INIT_STATUS_OK != status) {
    std::cerr << message << ". Got: " << status <<  "\n";
    exit(1);
  }
}

FLAC__StreamDecoderWriteStatus
writeCallback(const FLAC__StreamDecoder* decoder, const FLAC__Frame* frame,
    const FLAC__int32* const buffer[], void*)
{
  return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void metadataCallback(const FLAC__StreamDecoder* decoder,
    const FLAC__StreamMetadata* metadata, void*)
{
  if (FLAC__METADATA_TYPE_VORBIS_COMMENT != metadata->type) {
    return;
  }

  auto numberOfTags = metadata->data.vorbis_comment.num_comments;
  auto* tags = metadata->data.vorbis_comment.comments;
  std::vector<std::string> comments;
  for (FLAC__uint32 i = 0; i < numberOfTags; i++) {
    comments.push_back(std::string((const char*)(tags->entry)));
    ++tags;
  }
}

void errorCallback(const FLAC__StreamDecoder* decoder,
    FLAC__StreamDecoderErrorStatus status, void*)
{}

int main(int argc, const char * argv[]) {
  std::cout << "Beginning decoding...\n";

  FLAC__StreamDecoder* decoder = FLAC__stream_decoder_new();
  FLAC__bool status = FLAC__stream_decoder_set_metadata_respond_all(decoder);
  CheckStatus(status, "Could not direct the decoder to pass metadata");

  auto initStatus = FLAC__stream_decoder_init_file(decoder, FILENAME,
      writeCallback, metadataCallback, errorCallback, nullptr);
  CheckStatus(initStatus, "Could not initialize decoder");

  status = FLAC__stream_decoder_process_until_end_of_metadata(decoder);
  CheckStatus(status, "Error in decoding metadata!");

  std::cerr << "Got to here!\n";
}

///////////////////////////////////////////////////////////////////////////////
