#include "sorter.h"

typeResultContainer Sorter::mergeSort(std::vector<typeResultContainerPtr> inputs)
{
    typeResultContainer result;

    std::for_each(inputs.begin(), inputs.end(), [&result](auto mapper_result) {
        std::copy(mapper_result->begin(), mapper_result->end(), std::back_inserter(result));
    });
    std::sort(result.begin(), result.end());
    return result;
}
