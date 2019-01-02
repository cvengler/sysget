// Copyright (c) 2018-2019 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
// file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool file_exists(const char *filename);
vector<string> GetPackageManagerList();
string GetPackageManager(string filename);
void CreateConf(string filename, string packagemanager);
void checkcmd(string cmd);
vector<string> CustomArgs(string path);
bool VectorContains(string s, vector<string> v);
#endif