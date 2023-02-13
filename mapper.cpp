#include "mapper.h"

#include <cstring>
#include <iostream>

std::mutex mutexFile;


void read(std::ifstream& fileIn,
          std::iostream::pos_type startPos,
          std::iostream::pos_type stopPos,
          typeResultContainerPtr result)
{
    try
    {
        size_t length(stopPos - startPos);
        std::vector<char> buffer;
        buffer.resize(length + 1);


        std::lock_guard<std::mutex> lock(mutexFile);
        {
            fileIn.seekg(startPos, std::ios_base::beg);
            fileIn.read(buffer.data(), length);
        }
        buffer[length] = 0;


        char* ptrBuffer(buffer.data());
        char* ptrLine(nullptr);

        ptrLine = strtok(ptrBuffer, "\n");
        while (ptrLine != nullptr)
        {
            std::string line(ptrLine);
            for (size_t idx = 1; idx < line.length(); ++idx)
            {
                result->push_back(line.substr(0, idx));
            }
            ptrLine = strtok(nullptr, "\n");
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Error in mapper. " << e.what() << std::endl;
    }
}

Mapper::Mapper(std::string filename, int countMaps) :
    _file(filename),
    _countMaps(countMaps)
{
    if (!_file.good())
    {
        throw std::ifstream::failure("Problems with file " + filename);
    }
}

std::vector<typeResultContainerPtr> Mapper::map(std::vector<std::iostream::pos_type> borders)
{
    std::list<mapTask> tasks;

    std::iostream::pos_type begin(0), end(0);
    auto iterBorder = borders.cbegin();

    for (auto numTask = 0;
         (numTask < _countMaps) && (iterBorder != borders.cend());
         ++numTask, ++iterBorder)
    {
        end = *iterBorder;
        mapTask newTask;
        newTask.ptrResult = std::make_shared<typeResultContainer>();
        newTask.threadTask = std::make_shared<std::thread>(
            read,
            std::ref(_file),
            begin,
            end,
            newTask.ptrResult);
        tasks.push_back(newTask);
        begin = end;
    }

    //  Ожидаем окончания работы мапперов и сортируем результат
    std::vector<typeResultContainerPtr> vecResult;
    std::for_each(tasks.begin(), tasks.end(), [&vecResult](auto task) {
        task.threadTask->join();
        typeResultContainerPtr result(task.ptrResult);
        std::sort(result->begin(),
                  result->end());
        vecResult.push_back(result);
    });
    return vecResult;
}
