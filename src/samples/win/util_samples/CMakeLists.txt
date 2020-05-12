project(util_samples C CXX ASM)

find_package(EelUtils REQUIRED)

include_directories(${EelUtils_INCLUDE_DIR})

add_executable(io_stream_sample io_stream_sample.cc ${EelUtils_SOURCES})

target_compile_features(io_stream_sample PRIVATE cxx_std_17)

