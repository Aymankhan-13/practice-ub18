# *****************************************************
#    Copyright 2022 Videonetics Technology Pvt Ltd
# *****************************************************

cmake_minimum_required (VERSION 3.20)

find_package(Poco REQUIRED Util)

add_executable(sample_cpp
    src/main.cpp
)

target_compile_features(sample_cpp
    PRIVATE cxx_std_17
)
target_link_libraries(sample_cpp
    PRIVATE Poco::Util
)

set_property(TARGET sample_cpp PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
