#include <iostream>
#include <fstream>

using namespace std;

int search(string packagemanager, string query);
bool file_exists(const char *filename);
string read_conf(string filename);
int create_conf(string filename, string packagemanager);