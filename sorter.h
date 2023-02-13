#ifndef SORTER_H
#define SORTER_H

#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>



using typeResultContainer = std::vector<std::string>;
using typeResultContainerPtr = std::shared_ptr<typeResultContainer>;

class Sorter
{
public:
    Sorter() = default;

    typeResultContainer mergeSort(std::vector<typeResultContainerPtr> inputs);
};


#endif // SORTER_H
