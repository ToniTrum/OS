cmake_minimum_required(VERSION 3.15)

project(lab2 C)

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
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

# Тестовая утилита
add_executable(lab2 main.c)
target_link_libraries(lab2 PRIVATE process_runner)