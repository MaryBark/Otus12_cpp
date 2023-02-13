#cmake_minimum_required(VERSION 3.5)

#project(otus12_mapping LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_executable(otus12_mapping main.cpp
#    mapper.h mapper.cpp
#    reducer.h reducer.cpp
#    sorter.h sorter.cpp
#    splitter.h splitter.cpp)

cmake_minimum_required(VERSION 3.2)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
   project(otus12_mapping VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
   project(otus12_mapping VERSION 0.0.1)
endif()

find_package(GTest REQUIRED)
find_package(Boost REQUIRED)

#set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
#file(GLOB HEADER_FILES ${INCLUDE_DIR}/*.h)
#add_executable(Otus_cpp_11 ${HEADER_FILES} main.cpp)
add_executable(otus12_mapping main.cpp
    mapper.h mapper.cpp
        reducer.h reducer.cpp
        sorter.h sorter.cpp
        splitter.h splitter.cpp
        test_main.cpp)


set_target_properties(otus12_mapping PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES "${Boost_INCLUDE_DIR};${INCLUDE_DIR}"
)

enable_testing()
add_executable(otus12_mapping_tests ${HEADER_FILES} test_main.cpp)

set_target_properties(otus12_mapping_tests PROPERTIES INCLUDE_DIRECTORIES ${GTEST_INCLUDE_DIRS} )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        set_target_properties(otus12_mapping PROPERTIES COMPILE_OPTIONS -W3)
        target_link_libraries(otus12_mapping ${Boost_LIBRARIES} )
        target_link_libraries(otus12_mapping_tests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
else()
        set_target_properties(otus12_mapping PROPERTIES COMPILE_OPTIONS -Wpedantic -Wall -Wextra)
        target_link_libraries(otus12_mapping pthread ${Boost_LIBRARIES} )
        target_link_libraries(otus12_mapping_tests pthread ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
endif()


add_test(test_symmetric_difference	otus12_mapping_tests)
add_test(test_intersection		otus12_mapping_tests)
add_test(test_output			otus12_mapping_tests)
add_test(test_commands			otus12_mapping_tests)
add_test(test_command_errors		otus12_mapping_tests)

install(TARGETS otus12_mapping RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT Alttaira@yandex.ru)

include (CPack)

