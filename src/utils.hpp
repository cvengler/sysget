#include <iostream>
#include <fstream>

using namespace std;

bool file_exists(const char *filename);
string read_conf(string filename);
int create_conf(string filename, string packagemanager);