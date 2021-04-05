AUTOMAKE_OPTIONS = foreign
# SUBDIRS = bentemp

ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = --pedantic -Wall -O2
AM_LDFLAGS =


bin_PROGRAMS = i2ctest slavetest wdactions_libtest
lib_LTLIBRARIES = libwdactions.la


libwdactions_la_SOURCES = wdactions.cpp
libwdactions_la_LDFLAGS = -version-info 0:0:0



wdactions_libtest_CPPFLAGS = -I$(srcdir)/..
wdactions_libtest_SOURCES = wdactions_libtest.cpp
wdactions_libtest_LDADD = libwdactions.la

i2ctest_SOURCES = i2ctest.cpp

slavetest_SOURCES = slavetest.cpp
slavetest_LDFLAGS = -lpigpio



#rpi_gateway_CPPFLAGS = -I$(top_srcdir)/Arduino/SendTo_RFM69 -I$(top_srcdir)/RFM69 -I$(top_srcdir)/dummy
#rpi_gateway_SOURCES = rpi_gateway.cpp
