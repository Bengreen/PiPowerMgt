install these

    yum install autoconf libtool


https://learn.sparkfun.com/tutorials/raspberry-pi-spi-and-i2c-tutorial/all


Raspberry PI S2i Slave Mode
Slave mode is available on the RPi4 on GPI10,GPI11
Created a C program to work on slave interface.
Issues:
1. It seems to require a 'hot' loop to be in place to respond .. but may be possible to jsut do it via the buffer and therefore not have a hot loop.
2. Reads and writes are implemented as seperate actions.
3. Reads and writes as seperate actions may not work well in a multi-master mode where we cannot guarantee linkage between read+write.