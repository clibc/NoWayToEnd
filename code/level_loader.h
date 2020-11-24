#pragma once
#include <fstream>
#include <string>

struct level
{
    // NOTE(62bit): Input
    char *file_path;

    // NOTE(62bit): Output
    int cells[99];
};

static void load_level(level &lvl)
{
    int index = 0;
    std::string line;
    std::ifstream _fStream;
    _fStream = std::ifstream(lvl.file_path);

    if (_fStream)
    {

        while (!_fStream.eof())
        {
            std::getline(_fStream, line, ',');
            lvl.cells[index] = std::stoi(line);
            ++index;
        }
    }
    else
    {
        debug("failed to open level file");
    }
}
