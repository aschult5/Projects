AUTOMAKE_OPTIONS = foreign
AM_CXXFLAGS = --pedantic -Wall -Werror

lib_LTLIBRARIES = libinventory.la
libinventory_la_SOURCES = src/inventory.cpp src/inventory.hpp src/product.hpp

check_PROGRAMS = gtest
gtest_SOURCES = test/gtest.cpp
gtest_LDADD = libinventory.la
gtest_CPPFLAGS = "-Isrc"
gtest_LDFLAGS = "-lgtest -lgtest_main -lpthread"

TESTS = gtest
