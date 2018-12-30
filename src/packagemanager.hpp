#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H
#include <string>
#include <vector>
#include <fstream>
using namespace std;

/*
NOTE: If a string begins with an "exit=" it means that it is not availible. Everything after the '=' is the error message
NOTE: Spaces are VERY important because we need them to append other strings to them
*/

struct PackageManager {
	string search, install, uninstall, autoremove, update, upgrade, upgrade_pkg, clean;
	void init(string pm);
	void customPM(string filename);
};
#endif