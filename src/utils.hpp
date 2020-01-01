// Copyright (c) 2018-2020 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
// file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "main.hpp"

namespace sysget
{
    bool file_exists(const char *filename);
    std::vector<std::string> GetPackageManagerList();
    std::string GetPackageManager(std::string filename);
    void CreateConf(std::string filename, std::string packagemanager);
    void checkcmd(std::string cmd);
    std::vector<std::string> CustomArgs(std::string path);
    bool VectorContains(std::string s, std::vector<std::string> v);
}
#endif