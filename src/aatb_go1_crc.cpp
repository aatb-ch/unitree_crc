// AATB / Thibault Brevet
// compute CRC with CRC32 for Go1 motor commands

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include "crc/crc32.h"

int main() {

  // from Ian's capture
  // feee001500ffff00000020421000ff7f805ce97f14000004050000000000b02833b2
  // fe ee 00 15 00 ff ff 00 00 00 20 42 10 00 ff 7f 80 5c e9 7f 14 00 00 04 05 00 00 00 00 00 b0 28 33 b2
  // desired CRC is b0 28 33 b2

  uint8_t s[30];

    s[0] = 0xFE; // header 1
    s[1] = 0xEE; // header 2
    s[2] = 0x00; // motor ID
    s[3] = 0x15;
    s[4] = 0x00; // ?
    s[5] = 0xFF; // 0xff
    s[6] = 0xFF;
    s[7] = 0x00;
    s[8] = 0x00; // 0
    s[9] = 0x00;
    s[10] = 0x20;
    s[11] = 0x42;
    s[12] = 0x10; // target tau ?
    s[13] = 0x00;
    s[14] = 0xFF; // 0x7fff
    s[15] = 0x7F;
    s[16] = 0x80; // 0x7fe95c80 normally at 0x10
    s[17] = 0x5C; // 
    s[18] = 0xE9; // 
    s[19] = 0x7F; // 
    s[20] = 0x14; // target q ?
    s[21] = 0x00;
    s[22] = 0x00; // target v ?
    s[23] = 0x04;
    s[24] = 0x05; // bVar1
    s[25] = 0x00;
    s[26] = 0x00;
    s[27] = 0x00;
    s[28] = 0x00;
    s[29] = 0x00;

    /*
    These are from decompiled Go2 basic_service,
    likely leftover from Go1/B1 arch, doesnt match exactly

    SetMotor_cmd[cmdStartAddr + 0] = 0xeefe
    SetMotor_cmd[cmdStartAddr + 2] = param_2 // motor id
    SetMotor_cmd[cmdStartAddr + 4] = cVar2
    SetMotor_cmd[cmdStartAddr + 5] = 0xff
    SetMotor_cmd[cmdStartAddr + 8] = 0
    SetMotor_cmd[cmdStartAddr + 0x10] = 0x7fe95c80
    SetMotor_cmd[cmdStartAddr + 0xc // 12] = (short)(int)((float)iVar9 * fVar16 * (1.0 / fVar11) * 256.0)
    SetMotor_cmd[cmdStartAddr + 0xe // ] = uVar4 = 0x7fff
    SetMotor_cmd[cmdStartAddr + 0x14] = (short)(int)((fVar13 / (fVar11 * fVar11)) * 0.03834952 * 2048.0);
    SetMotor_cmd[cmdStartAddr + 0x16] = (short)(int)((fVar12 / (fVar11 * fVar11)) * 100.0 * 1024.0);
    SetMotor_cmd[cmdStartAddr + 0x18] = bVar1
    SetMotor_cmd[cmdStartAddr + 0x1e] = uVar5 // computed CRC
    */

    printf("Go1 payload is: ");
    for (int i=0; i<30; i++){
      printf("%02x", s[i]);
    }
    std::cout << std::endl;

    // cast uint8 to uint32 pointer
    uint32_t* ptr_s;
    ptr_s = (uint32_t *) &s;

    // get the CRC, somehow it only uses 28 bytes (7x4)
    // this was also found in the decompiled binary of go2 basic_service
    uint32_t crc = crc32_core(ptr_s, 7);

    printf("computed CRC is: %02x ", (crc >> (8*0)) & 0xff);
    printf("%02x ", (crc >> (8*1)) & 0xff);
    printf("%02x ", (crc >> (8*2)) & 0xff);
    printf("%02x", (crc >> (8*3)) & 0xff);
    std::cout << std::endl;

    printf("captured CRC is: b0 28 33 b2");
    std::cout << std::endl;
}
