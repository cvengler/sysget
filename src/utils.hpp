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
void CheckCustomArgs(vector<string> args);
vector<string> DefaultArgs();