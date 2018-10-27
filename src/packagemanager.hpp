#include <string>
using namespace std;

/*
NOTE: If a string begins with an "exit=" it means that it is not availible. Everything after the '=' is the error message
NOTE: Spaces are VERY important because we need them to append other strings to them
*/

struct PackageManager {
	string search;		//Search in the repos for a package
	string install;		//Install a package
	string remove;		//Remove a package
	string autoremove;	//Remove orphans
	string update;		//Update database
	string upgrade;		//Upgrade all packages
	string upgrade_pkg;	//Upgrade a specific package, if this isn't possible => reinstall
	string clean;		//Clean the cache of the package manager
	void init(string pm);
};