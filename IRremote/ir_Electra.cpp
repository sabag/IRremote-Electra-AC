#include "IRremote.h"

#if (DECODE_ELECTRA_AC)

static const unsigned int baseUnitTime = 992;
static const uint8_t numBits = 34;
static const unsigned int MARGIN = 150;

bool IRrecv::decodeElectra(decode_results *results) {

  // Require at least 12 samples to prevent triggering on noise
  if (results->rawlen < 12) {
    return false;
  }

  std::vector<char> stream;

  //
  // scan the pairs and add space (0) and then mark (1) according to the modulo
  //
  for (unsigned int i = 1; i < results->rawlen - 1; i += 2) {
    unsigned int a = ( results->rawbuf[i] * MICROS_PER_TICK + MARGIN ) / baseUnitTime;
    unsigned int b = ( results->rawbuf[i + 1] * MICROS_PER_TICK + MARGIN ) / baseUnitTime;

    while (a > 0) {
      stream.push_back('0');
      a--;
    }
    while (b > 0) {
      stream.push_back('1');
      b--;
    }
  }

  // verify header
  std::string header(stream.begin(), stream.begin() + 6);
  if (header == "000111") {
    //    DBG_PRINTLN("found header of 000111");

    // find the header of the next repeatition
    uint8_t offset = 6;
    for (; offset < stream.size() - 6; offset++) {
      std::string header(stream.begin() + offset, stream.begin() + offset + 6);
      if (header == "000111") {
        //        DBG_PRINTLN("found next header of 000111");
        break;
      }
    }

    if (offset + 6 >= stream.size()) {
      DBG_PRINTLN("next header not found, ignore");
      return false;
    }

    /*
    for (std::vector<char>::iterator it = stream.begin() ; it != stream.begin() + offset + 6; ++it) {
      Serial.print(*it);
    }
    Serial.println();
    */

    // run on the sub vector , from offset 6 to the offset found at break
    int shift = numBits - 1;
    results->value = 0;
    for (int index = 6; index < offset; index += 2) {
      char s = stream[index];
      char m = stream[index + 1];

      if (s == '1' && m == '0') {
        results->value = ((uint64_t)1L << shift) | results->value;
      }
      shift--;
    }

    results->bits = numBits;
    results->decode_type = ELECTRA_MANCHESTER;

    return true;
  }

  return false;
}


#endif
