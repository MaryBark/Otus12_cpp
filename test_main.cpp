#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "mapper.h"
#include "reducer.h"
#include "sorter.h"
#include "splitter.h"


TEST(mapreduce, ok)
{
    testing::internal::CaptureStdout();
    int countMaps = 1;
    int countReducers = 1;
    std::string filepath = "../test_map_reduce";

    Splitter splitter(filepath, countMaps);
    auto borders = splitter.split();

    Mapper mapper(filepath, countMaps);
    auto vecResult = mapper.map(borders);

    Sorter sorter;
    auto sortedResults = sorter.mergeSort(vecResult);

    Reducer reducer(sortedResults, countReducers);
    reducer.reduce();

    std::string output = testing::internal::GetCapturedStdout();
    std::string expected_output = "Minimum prefix: 5\n";
    ASSERT_EQ(output, expected_output);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
