# Unitree CRC for Go1/Go2 motors

Based off captured frames on the rs-485 bus of Go1/Go2 motors.

[clone `unitree_actuator_sdk` ](https://github.com/unitreerobotics/unitree_actuator_sdk.git)

Copy both .cpp files in the examples folder, add to the CMakeList:

'''
add_executable(aatb_go1_crc example/aatb_go1_crc.cpp)
target_link_libraries(aatb_go1_crc ${EXTRA_LIBS})

add_executable(aatb_go2_crc example/aatb_go2_crc.cpp)
target_link_libraries(aatb_go2_crc ${EXTRA_LIBS})
'''

compile as usual:

'''
mkdir build
cd build
cmake ..
make
'''

run either './aatb_go1_crc' or './aatb_go2_crc'.

Hats off to https://github.com/imcnanie for the Go1 motor dump.