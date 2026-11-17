cmake_minimum_required(VERSION 3.17)
project(${RunCMake_TEST} CXX)

if(RunCMake_TEST STREQUAL "Extractor")
  add_executable(msbuild-extractor-tool extractor.cxx)
  file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/extractor-$<CONFIG>.cmake"
    CONTENT "set(extractor_dir [==[$<TARGET_FILE_DIR:msbuild-extractor-tool>]==])\n")
else()
  add_library(first STATIC first.cxx)
  add_library(second STATIC second.cxx)
  add_library(broken STATIC EXCLUDE_FROM_ALL broken.cxx)
endif()
