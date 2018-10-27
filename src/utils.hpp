#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool file_exists(const char *filename);
string get_package_manager(string filename);
int create_conf(string filename, string packagemanager);
int checkcmd(string cmd);