# Unitree CRC for Go1/Go2 motors

Based off captured frames on the rs-485 bus of Go1/Go2/G1 motors.

1. [clone unitree_actuator_sdk ](https://github.com/unitreerobotics/unitree_actuator_sdk.git)

2. Copy both .cpp files from the `/src` folder into the sdk `/example` folder

3. add to the CMakeList.txt:

```
add_executable(aatb_go1_crc example/aatb_go1_crc.cpp)
target_link_libraries(aatb_go1_crc ${EXTRA_LIBS})

add_executable(aatb_go2_crc example/aatb_go2_crc.cpp)
target_link_libraries(aatb_go2_crc ${EXTRA_LIBS})

add_executable(aatb_g1_crc example/aatb_g1_crc.cpp)
target_link_libraries(aatb_g1_crc ${EXTRA_LIBS})
```

4. compile as usual:

```
mkdir build
cd build
cmake ..
make
```

5. run either `./aatb_go1_crc` or `./aatb_go2_crc` from the `/build` folder.

Hats off to https://github.com/imcnanie for the Go1 motor dumps, Go2 motor dumps by yours truly.
