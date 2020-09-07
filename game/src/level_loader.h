#pragma once
#include "gameDefines.h"
#include <fstream>
#include <vector>
#include <string>

static void LoadLevel(const char *filepath, std::vector<int> &blocks)
{
    std::string line;
    std::ifstream _fStream;
    _fStream = std::ifstream(filepath);

    if (_fStream.is_open())
    {
        if (_fStream)
        {

            while (!_fStream.eof())
            {
                std::getline(_fStream, line, ',');
                blocks.push_back(std::stoi(line));
            }
        }
        else
        {
            DEBUG("failed to open level file");
        }
    }
    else
        DEBUG("level_loader.h:failed to open level file");
}