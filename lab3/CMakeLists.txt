cmake_minimum_required(VERSION 3.15)
project(lab3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(PLATFORM_DIR windows)
else()
    set(PLATFORM_DIR posix)
endif()

set(PLATFORM_SOURCES
    ${PLATFORM_DIR}/clock/get_local.c
    ${PLATFORM_DIR}/clock/get_monotonic_ms.c
    
    ${PLATFORM_DIR}/thread/create.c
    ${PLATFORM_DIR}/thread/join.c
    ${PLATFORM_DIR}/thread/sleep_ms.c
    
    ${PLATFORM_DIR}/logger_append.c
    
    ${PLATFORM_DIR}/counter/open.c
    ${PLATFORM_DIR}/counter/close.c
    ${PLATFORM_DIR}/counter/lock.c
    ${PLATFORM_DIR}/counter/unlock.c
    
    ${PLATFORM_DIR}/leader/open.c
    ${PLATFORM_DIR}/leader/try_acquire.c
    ${PLATFORM_DIR}/leader/release.c
    ${PLATFORM_DIR}/leader/close.c
    
    ${PLATFORM_DIR}/process/get_id.c
    ${PLATFORM_DIR}/process/get_self_path.c
    ${PLATFORM_DIR}/process/spawn.c
    ${PLATFORM_DIR}/process/is_running.c
    ${PLATFORM_DIR}/process/close.c
)

set(COMMON_SOURCES
    main.c

    src/logger/init.c
    src/logger/write.c
    src/logger/write_start.c
    src/logger/write_counter.c
    src/logger/write_exit.c
    src/logger/write_busy.c
    src/logger/write_error.c
    
    src/counter/get.c
    src/counter/set.c
    src/counter/add.c
    src/counter/mul.c
    src/counter/div.c

    src/app/parse_mode.c
    src/app/spawn_copy.c
    src/app/timer_worker.c
    src/app/cli_loop.c
    src/app/run_main.c
    src/app/run_copy1.c
    src/app/run_copy2.c
)

add_executable(lab3
    main.c
    ${PLATFORM_SOURCES}
    ${COMMON_SOURCES}
)

target_include_directories(lab3 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(WIN32)
    target_compile_definitions(lab3 PRIVATE _WIN32_WINNT=0x0600)
else()
    find_package(Threads REQUIRED)
    target_compile_definitions(lab3 PRIVATE _POSIX_C_SOURCE=200809L)
    target_link_libraries(lab3 PRIVATE Threads::Threads rt)
endif()