#include "reducer.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using typeResultContainer = std::vector<std::string>;
using typeResultContainerPtr = std::shared_ptr<typeResultContainer>;

Reducer::Reducer(typeResultContainer sortedResults, int countReducers) :
    _sortedResults(sortedResults),
    _countReducers(countReducers)
{}

void reduceFunction(typeResultContainerPtr& input, std::shared_ptr<std::ofstream> out)
{
    if (input->empty())
        return;
    (void) out;
    size_t minimumPrefix(1);
    std::string current("");
    for (std::string prefix : *input)
    {
        if (minimumPrefix <= prefix.length())
        {
            if (current == prefix)
            {
                minimumPrefix = prefix.length() + 1;
            }
            else
            {
                current = prefix;
            }
        }
    }
    std::cout << "Minimum prefix: " << minimumPrefix << std::endl;
}

void Reducer::reduce()
{
    std::vector<typeResultContainerPtr> tasks;
    for (auto num = 0; num < _countReducers; ++num)
        tasks.push_back(std::make_shared<typeResultContainer>());

    std::for_each(_sortedResults.begin(), _sortedResults.end(), [this, &tasks](auto line) {
        unsigned char key(getKey(line, _countReducers));
        tasks[key]->push_back(line);
    });

    std::list<reducerTask> reducers;
    for (auto numTask = 0;
         (numTask < _countReducers);
         ++numTask)
    {

        std::string fileOutName("reducer_" + std::to_string(numTask + 1) + ".out");

        reducerTask newTask;
        newTask.fileOut = std::make_shared<std::ofstream>(fileOutName);
        newTask.threadTask = std::make_shared<std::thread>(
            reduceFunction,
            std::ref(tasks[numTask]),
            newTask.fileOut);
        reducers.push_back(newTask);
    }

    std::for_each(reducers.begin(), reducers.end(), [](auto task) {
        task.threadTask->join();
    });
    reducers.clear();
}

unsigned char Reducer::getKey(std::string value, int countReducers)
{
    std::hash<std::string> hash_fn;
    if (value.empty())
        return 0;
    else
        return hash_fn(value) % countReducers;
}
