#pragma once
#include <fstream>
#include <string>

struct level
{
    char *file_path;
    int cells[100];
};

static void load_level(level &lvl, const char *filepath)
{
    int index = 0;
    std::string line;
    std::ifstream _fStream;
    _fStream = std::ifstream(filepath);

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
