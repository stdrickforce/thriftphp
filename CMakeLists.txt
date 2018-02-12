project(thriftphp)
cmake_minimum_required(VERSION 2.4)

if (DEFINED PHP_CONFIG)
    set(PHP_CONFIG ${PHP_CONFIG})
else ()
    set(PHP_CONFIG "php-config")
endif ()

set(CMAKE_SHARED_MODULE_PREFIX)

set(PHP_CONFIG "/usr/local/Cellar/php70/7.0.27_19/bin/php-config")
set(PHP "/usr/local/Cellar/php70/7.0.27_19/bin/php")

add_definitions(-DPHP_ATOM_INC)
add_definitions(-DHAVE_CONFIG_H)

execute_process(
    COMMAND ${PHP_CONFIG} --include-dir
    OUTPUT_VARIABLE PHP_INCLUDE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${PHP_CONFIG} --extension-dir
    OUTPUT_VARIABLE PHP_EXTENSION_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${PHP_CONFIG} --php-binary
    OUTPUT_VARIABLE PHP_BINARY
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND ${PHP_CONFIG} --ldflags
    OUTPUT_VARIABLE ${PHP_LDFLAGS}
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

message("PHP_INCLUDE_DIR: ${PHP_INCLUDE_DIR}")

link_directories(${PHP_LDFLAGS})

include_directories(
    ${PHP_INCLUDE_DIR}
    ${PHP_INCLUDE_DIR}/Zend
    ${PHP_INCLUDE_DIR}/main
    ${PHP_INCLUDE_DIR}/TSRM
)
include_directories(include)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-g -O2")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O2")

if (APPLE)
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
    message(DPHP_ATOM_INC${CMAKE_MODULE_LINKER_FLAGS})
endif ()

set(
    parser
    src/parser/Program.cpp
    src/parser/Program.h
)
add_library(libparser STATIC ${parser})

set(
    SOURCE_FILES
    src/thriftphp.cc
    src/thriftphp/init.cc
    src/thriftphp/init.h
)

add_library(thriftphp MODULE ${SOURCE_FILES})
target_link_libraries(thriftphp libparser)
install(TARGETS thriftphp DESTINATION ${PHP_EXTENSION_DIR})

add_custom_target(
    ${PROJECT_NAME}_install
    "${CMAKE_COMMAND}" --build "${CMAKE_BINARY_DIR}" --target install && ${PHP_BINARY} ${PROJECT_SOURCE_DIR}/example/x.php
    DEPENDS thriftphp
    COMMENT "Installing ${PROJECT_NAME}"
)
