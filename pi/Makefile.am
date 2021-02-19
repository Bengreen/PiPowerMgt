AUTOMAKE_OPTIONS = foreign
# SUBDIRS = bentemp

AM_CFLAGS = --pedantic -Wall -O2
AM_LDFLAGS =


bin_PROGRAMS = i2ctest slavetest

i2ctest_SOURCES = i2ctest.cpp

slavetest_SOURCES = slavetest.cpp
slavetest_LDFLAGS = -lpigpio

#rpi_gateway_CPPFLAGS = -I$(top_srcdir)/Arduino/SendTo_RFM69 -I$(top_srcdir)/RFM69 -I$(top_srcdir)/dummy
#rpi_gateway_SOURCES = rpi_gateway.cpp
