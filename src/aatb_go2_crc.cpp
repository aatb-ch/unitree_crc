// AATB / Thibault Brevet
// compute CRC with CRC-CCITT for Go2 motor commands

#include <unistd.h>
#include <stdio.h>
#include <cstdint>
#include "crc/crc_ccitt.h"
#include "unitreeMotor/unitreeMotor.h"

int main() {

  MotorCmd cmd;

  cmd.motorType = MotorType::GO_M8010_6;
  cmd.mode = queryMotorMode(MotorType::GO_M8010_6,MotorMode::BRAKE);
  cmd.id   = 0;
  cmd.kp   = 0.0;
  cmd.kd   = 0.0;
  cmd.q    = 0.0;
  cmd.dq   = 0.0;
  cmd.tau  = 0.0;

  // MotorCmd needs to process the data and format it into a Go2-specific format
  cmd.modify_data(&cmd);
  // grab the raw array of data
  uint8_t* data = cmd.get_motor_send_data();

  // print it out, this wont work on Go2 motors,
  // only on the standalone actuator sold for $$$$
  for (int i=0; i<17; i++){
    std::cout << std::endl;
    printf("%02x ", data[i]);
  }
  std::cout << std::endl;

  // build captured payload
  uint8_t s[15];

  s[0] = 0xFE;
  s[1] = 0xEE;
  
  for (int i=0; i<13; i++) {
    s[i+2] = 0x00;
  }

  s[2] = 0x11;
  s[13] = 0xB4;

  // captured Go2 payload and crc:
  // FEEE1100000000000000000000B40037C1

  printf("captured payload is: ");
  for (int i=0; i<15; i++){
    printf("%02x ", s[i]);
  }
  std::cout << std::endl;

  // grab pointer
  uint8_t* ptr_s;
  ptr_s = (uint8_t *) &s;

  // pass pointer along with magic CRC start value
  // this was found in the decompiled basic_service binary
  uint16_t crc = crc_ccitt(0x2cbb, ptr_s, 15);

  printf("computed CRC is: ");
  printf("%02x", (crc >> (8*0)) & 0xff);
  printf("%02x", (crc >> (8*1)) & 0xff);
  std::cout << std::endl;
}
