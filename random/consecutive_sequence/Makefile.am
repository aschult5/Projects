AUTOMAKE_OPTIONS = foreign
AM_CXXFLAGS = --pedantic -Wall -Werror

check_PROGRAMS = gtest
gtest_SOURCES = test/gtest.cpp src/sequence.cpp
gtest_CPPFLAGS = "-Isrc"
gtest_LDFLAGS = "-lgtest -lgtest_main -lpthread"

TESTS = gtest
