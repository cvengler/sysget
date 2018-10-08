#include <iostream>

using namespace std;

//Update will update the database only
int update(string packagemanager);
//Upgrade will update all packages without the database
int upgrade(string packagemanager);
//Upgrade a specifc package
int upgrade_pkg(string packagemanager, string package);