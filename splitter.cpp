#include "splitter.h"
#include <iostream>

Splitter::Splitter(std::string filename, int countMaps) :
    _file(filename),
    _countMaps(countMaps)
{
    if (!_file.good())
    {
        throw std::ifstream::failure("Problems with file " + filename);
    }
}

std::vector<std::iostream::pos_type> Splitter::split()
{
    _file.seekg(0, std::ios_base::end);
    auto pos_end = _file.tellg();
    auto part = pos_end / _countMaps;
    std::vector<std::iostream::pos_type> borders;
    borders.reserve(_countMaps);
    _file.seekg(part, std::ios_base::beg);
    auto pos = part;
    while ((pos < pos_end) && (pos >= 0))
    {
        _file.seekg(pos, std::ios_base::beg);
        char symbol(0);
        while (symbol != '\n' && !_file.fail())
            _file.read(&symbol, 1);

        pos = _file.tellg();

        if (pos >= 0)
        {
            borders.push_back(pos);
            pos += part;
        }
    }
    borders.push_back(pos_end);
    return borders;
}
