project(util_samples C CXX ASM)

find_package(EelUtil REQUIRED)

include_directories(${CMSIS_INCLUDE_DIRS}
        ${EelUtil_INCLUDE_DIR})

add_executable(io_stream_sample io_stream_sample.cc ${EelUtil_SOURCES})

target_compile_features(io_stream_sample PRIVATE cxx_std_17)

