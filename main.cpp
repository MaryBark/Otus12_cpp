#include "mapper.h"
#include "reducer.h"
#include "sorter.h"
#include "splitter.h"


#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    //  Получаем и проверяем входные параметры
    if (argc != 4)
    {
        std::cout << "Wrong arguments. Usage: map_reduce <src> <mnum> <rnum>" << std::endl;
        return -1;
    };

    int countMaps = std::stoi(argv[2]);
    if (countMaps <= 0)
    {
        std::cout << "mnum should be > 0" << std::endl;
        return -3;
    }

    int countReducers = std::stoi(argv[3]);
    if (countReducers <= 0)
    {
        std::cout << "rnum should be > 0" << std::endl;
        return -4;
    }

    //  Делаем разбиение файла на части
    Splitter splitter(std::string(argv[1]), countMaps);
    auto borders = splitter.split();

    //  Формируем задачи для мапперов

    Mapper mapper(std::string(argv[1]), countMaps);
    auto vecResult = mapper.map(borders);

    Sorter sorter;
    auto sortedResults = sorter.mergeSort(vecResult);

    Reducer reducer(sortedResults, countReducers);
    reducer.reduce();

    return 0;
}
