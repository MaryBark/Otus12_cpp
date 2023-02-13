#ifndef REDUCER_H
#define REDUCER_H

#pragma once

#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>


using typeResultContainer = std::vector<std::string>;

//  Структура задачи для редюсера
struct reducerTask
{
    std::shared_ptr<std::thread> threadTask;
    std::shared_ptr<std::ofstream> fileOut;
};

class Reducer
{
public:
    Reducer() = delete;
    Reducer(typeResultContainer sortedResults, int countReducers);

    void reduce();

private:
    unsigned char getKey(std::string value, int countReducers);
    std::list<reducerTask> _reducers;
    typeResultContainer _sortedResults;
    int _countReducers;
};


#endif // REDUCER_H
