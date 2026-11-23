cmake_minimum_required(VERSION 3.15)
project(lab2 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(LIB_SOURCES
        windows/process_run.c
        windows/process_wait.c
    )
else()
    set(LIB_SOURCES
        posix/process_run.c
        posix/process_wait.c
    )
endif()

add_library(process_runner STATIC ${LIB_SOURCES})

target_include_directories(process_runner PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_executable(lab2 main.c)
target_link_libraries(lab2 PRIVATE process_runner)

install(TARGETS process_runner
    ARCHIVE DESTINATION lib
)
install(FILES include/process_runner.h
    DESTINATION include
)