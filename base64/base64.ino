#include <libb64/cencode.h>
#include <libb64/cdecode.h>
void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Base64 example");

}

void loop()
{

  // read from port 1, send to port 0:
  if (Serial.available()) {

    unsigned long serialcur = millis();
    String inputstr = Serial.readString();
    unsigned long time_seri = millis() - serialcur;
    Serial.print("Serial time taken:");
    Serial.println(time_seri);
    //    converting string to char array
    int inputLen = inputstr.length();
    char *input = new char[inputLen];
    inputstr.toCharArray(input, inputLen);
    //    char input[] = "nuja";
    //    int inputLen = sizeof(input);
    Serial.print("Input Str:");
    Serial.println(input);
    Serial.print("Input length:");
    Serial.println(inputLen);
    ///////////////////////
    unsigned long cur = millis();
    int epected_encode_legth = base64_encode_expected_len(inputLen);
    char *encoded = new char[epected_encode_legth];
    base64_encode_chars(input, inputLen, encoded);
    unsigned long time1 = millis() - cur;
    Serial.print("Encoded:");
    Serial.println(encoded);
    Serial.print("Encoded time taken:");
    Serial.println(time1);

    ////////////////////decodeing part////////////
    cur = millis();
    int epected_decode_legth = base64_decode_expected_len(epected_encode_legth); //epected_encode_legth it is the size of the encoded char
    char *decoded = new char[epected_decode_legth];
    base64_decode_chars(encoded, epected_encode_legth, decoded);
    unsigned long time2 = millis() - cur;
    Serial.print("Decoded:");
    Serial.println(decoded);
    Serial.print("Decoded time taken:");
    Serial.println(time2);
  }

}
