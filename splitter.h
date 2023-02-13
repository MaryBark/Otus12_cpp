#ifndef SPLITTER_H
#define SPLITTER_H

#pragma once

#include <fstream>
#include <string>
#include <vector>


class Splitter
{
public:
    Splitter() = delete;
    Splitter(std::string filename, int countMaps);

    std::vector<std::iostream::pos_type> split();

private:
    std::ifstream _file;
    int _countMaps;
};


#endif // SPLITTER_H
