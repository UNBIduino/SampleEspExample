/**
   Library used: https://github.com/spaniakos/AES

*/

#include <AES.h>

AES aes ;

byte *key = (unsigned char*)"0123456789010123";
byte *mykey = (unsigned char*)"0123456789010123";

byte plain[] = "Hello World!!!!!";
int plainLength = sizeof(plain) - 1; // don't count the trailing /0 of the string !
int padedLength = plainLength + N_BLOCK - plainLength % N_BLOCK;

//real iv = iv x2 ex: 01234567 = 0123456701234567
unsigned long long int my_iv = 36753562;

void setup ()
{
  Serial.begin (115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  delay(500);
  Serial.println("\n===testing mode\n") ;

  //  otfly_test () ;
  //  otfly_test256 () ;

  prekey_test ();
}

void loop ()
{
  delay(2000);
}

void prekey (int bits)
{
  aes.iv_inc();
  byte iv [N_BLOCK] ;
  byte real_iv [N_BLOCK] ;
  byte plain_p[padedLength];
  byte cipher [padedLength] ;
  byte check [padedLength] ;
  unsigned long ms = micros ();
  aes.set_IV(my_iv);
  aes.get_IV(iv);
  ///Copy the iv to another array as it get consume during the process
  memcpy(real_iv, iv, N_BLOCK);
  //////////////////////
  aes.do_aes_encrypt(plain, plainLength, cipher, key, bits, iv);
  Serial.print("Encryption took: ");
  Serial.println(micros() - ms);
  ms = micros ();
  aes.set_IV(my_iv);
  aes.get_IV(iv);
  aes.do_aes_decrypt(cipher, padedLength, check, key, bits, iv);
  Serial.print("Decryption took: ");
  Serial.println(micros() - ms);
  Serial.println("\n\nPLAIN :");
  aes.printArray(plain, (bool)true);
  Serial.println("\nCIPHER:");
  aes.printArray(cipher, (bool)false);
  Serial.println("\nCHECK :");
  aes.printArray(check, (bool)true);
  Serial.println("\nkey   :");
  aes.printArray(mykey, 16);
  Serial.println("\nFalse IV    :");
  aes.printArray(iv, 16);
  Serial.println("\nTrue IV    :");
  aes.printArray(real_iv, 16);
  Serial.println("\nCypher   :");
  aes.printArray(cipher, padedLength);
  Serial.println("\n============================================================\n");
}

void prekey_test ()
{
  prekey (128) ;
}
