AUTOMAKE_OPTIONS = foreign
AM_CXXFLAGS = --pedantic -Wall -Werror

bin_PROGRAMS = download
download_SOURCES = src/main.cpp src/download.cpp
download_CPPFLAGS = "-Isrc"

check_PROGRAMS = gtest
gtest_SOURCES = test/gtest.cpp src/download.cpp
gtest_CPPFLAGS = "-Isrc"
gtest_LDFLAGS = "-lgtest -lgtest_main -lpthread"

TESTS = gtest
