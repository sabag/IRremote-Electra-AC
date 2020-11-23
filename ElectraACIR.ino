/*
  modified sketch to reverse engineer the Electra AC codes.
  the purpose of this sketch is to read the IR codes and find out which AC command is it

  this is a fork of IRRecvDemo with copying the IRremote code and modifying it to decode manchester encoding

  I am using the ESP32 DEVKIT V1 with Ir receiver connected to pin D15 (which is next to the 3v3 and GND

  this sketch is used as a debuger and developing sketch for reading the electra AC remote, 
  the full sketch is at IR_Electra_ESP_V2
*/

#include "IRremote.h"



#pragma pack(1)
typedef union OrangeElectraCode {
  uint64_t num;
  struct {
    uint64_t zeros1 : 1;
    uint64_t ones1 : 1;
    uint64_t zeros2 : 16;
    uint64_t sleep : 1;
    uint64_t temperature : 4;
    uint64_t zeros3 : 2;
    uint64_t swing : 1;
    uint64_t zeros4 : 2;
    uint64_t fan : 2;
    uint64_t mode : 3;
    uint64_t power : 1;
  };
} ElectraUnion;
#pragma pack()





int RECV_PIN = 15;

IRrecv irrecv(RECV_PIN);

decode_results results;

OrangeElectraCode code;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  irrecv.enableIRIn();


}


void loop() {

  if (irrecv.decode(&results)) {

    if (results.decode_type == ELECTRA_MANCHESTER) {

      Serial.print("Code      : 0x");
      Serial.print(uint64ToString(results.value));
      Serial.print(" (");
      Serial.print(results.bits, DEC);
      Serial.println(" bits)");
      dumpCode(&results);

      dumpElectraValues(&results);
    }

    irrecv.resume();
  }
}


void dumpElectraValues(decode_results *results) {
  code.num = results->value;

  Serial.print("power: "); Serial.println((int)code.power);
  Serial.print("mode: ");
  Serial.print((int)code.mode);
  switch (code.mode) {
    case 1: Serial.println(" Cool"); break;
    case 2: Serial.println(" Heat"); break;
    case 5: Serial.println(" Fan"); break;
    case 4: Serial.println(" Dry"); break;
    case 3: Serial.println(" Auto"); break;
    default: Serial.println(" ?");break;
  }

  Serial.print("fan: ");
  Serial.print((int)code.fan);
  switch (code.fan) {
    case 0: Serial.println(" Low"); break;
    case 1: Serial.println(" Medium"); break;
    case 2: Serial.println(" High"); break;
    case 3:  Serial.println(" Auto"); break;
    default: Serial.println(" ?");break;
  }

  Serial.print("temperature: "); Serial.println((int) code.temperature + 15);
}


void dumpCode(decode_results *results) {

  Serial.print("rawData[");                // array name
  Serial.print(results->rawlen - 1, DEC);  // array size
  Serial.print("] = {");                   // Start declaration

  // Dump data
  for (unsigned int i = 1; i < results->rawlen; i++) {
    Serial.print(results->rawbuf[i] * MICROS_PER_TICK, DEC);
    if (i < results->rawlen - 1)
      Serial.print(","); // ',' not needed on last one
    if (!(i & 1))
      Serial.print(" ");
  }

  // End declaration
  Serial.println("};");

}


String uint64ToString(uint64_t input) {
  String result = "";
  uint8_t base = 16;

  do {
    char c = input % base;
    input /= base;

    if (c < 10)
      c +='0';
    else
      c += 'A' - 10;
    result = c + result;
  } while (input);
  return result;
}
