#ifndef MAPPER_H
#define MAPPER_H

#pragma once

#include <fstream>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

//class mapper
//{
//public:
//    mapper();
//};


using typeResultContainer = std::vector<std::string>;
using typeResultContainerPtr = std::shared_ptr<typeResultContainer>;


struct mapTask
{
    std::shared_ptr<std::thread> threadTask;
    typeResultContainerPtr ptrResult;
};

class Mapper
{
public:
    Mapper() = delete;
    Mapper(std::string filename, int countMaps);

    std::vector<typeResultContainerPtr> map(std::vector<std::iostream::pos_type> borders);

private:
    std::ifstream _file;
    int _countMaps;
};


#endif // MAPPER_H
