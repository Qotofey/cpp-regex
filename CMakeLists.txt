cmake_minimum_required(VERSION 3.10)

project(calc)
set(CMAKE_CXX_STANDARD 17)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

conan_basic_setup()

add_executable(
    ${PROJECT_NAME} 
    main.cpp
    src/textcalc.cpp
)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})


enable_testing()
add_executable(
    calc_test
    src/textcalc.cpp
    tests/unit/test.cpp
)
target_link_libraries(calc_test ${CONAN_LIBS})
add_test(NAME calc_test COMMAND calc_test)