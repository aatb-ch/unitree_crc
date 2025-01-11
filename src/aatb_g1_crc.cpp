// AATB / Thibault Brevet
// compute CRC32 for G1 motor commands

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include "crc/crc32.h"

int main() {

  // from Rob G
  // 0xFE 0xEE 0x90 0x9A 0x00 0x00 0x00 0x00 0x70 0xBF 0x05 0x00 0xC2 0x01 0x0A 0x00 0xD1 0xF2 0x28 0x4A
  // desired CRC 0xD1 0xF2 0x28 0x4A

  uint8_t s[16];

    s[0] = 0xFE; // header 1
    s[1] = 0xEE; // header 2
    s[2] = 0x90;
    s[3] = 0x9A;
    s[4] = 0x00;
    s[5] = 0x00;
    s[6] = 0x00;
    s[7] = 0x00;
    s[8] = 0x70;
    s[9] = 0xBF;
    s[10] = 0x05;
    s[11] = 0x00;
    s[12] = 0xC2;
    s[13] = 0x01;
    s[14] = 0x0A;
    s[15] = 0x00;

    printf("G1 payload is: ");
    for (int i=0; i<16; i++){
      printf("%02x", s[i]);
    }
    std::cout << std::endl;

    // cast from uint8 to uint32 pointer
    uint32_t* ptr_s;
    ptr_s = (uint32_t *) &s;

    // get the CRC, somehow it uses 4 bytes (4x4)
    uint32_t crc = crc32_core(ptr_s, 4);

    printf("computed CRC is: %02x ", (crc >> (8*0)) & 0xff);
    printf("%02x ", (crc >> (8*1)) & 0xff);
    printf("%02x ", (crc >> (8*2)) & 0xff);
    printf("%02x", (crc >> (8*3)) & 0xff);
    std::cout << std::endl;

    printf("captured CRC is: d1 f2 28 4a");
    std::cout << std::endl;
}
