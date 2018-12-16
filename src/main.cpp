#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "packagemanager.hpp"
#include "utils.hpp"

// Use secure_getenv when compiling for Linux
#ifdef __linux__
	#define getenv secure_getenv
#endif

char ConfigPath[255] = "/etc/sysget";	// Needs to be NOT const so it can be changed if an enviroment variable set
char CustomPath[255] = "/etc/sysget_custom";
char ArgsPath[255] = "/etc/sysget_args";
const char *HelpMsg =
	"Help of sysget\n"
	"sysget [OPTION] [PACKAGE(S)]\n"
	"\n"
	"search [QUERY]\t\t\tsearch for a package in the resporitories\n"
	"install [PACKAGE] [PACKAGE]\tinstall a package from the repos\n"
	"remove [PACKAGE] [PACKAGE]\tremoves a package\n"
	"autoremove\t\t\tremoves not needed packages (orphans)\n"
	"update\t\t\t\tupdate the database\n"
	"upgrade\t\t\t\tdo a system upgrade\n"
	"upgrade [PACKAGE] [PACKAGE]\tupgrade a specific package\n"
	"clean\t\t\t\tclean the download cache\n"
	"set [NEW MANAGER]\t\tset a new package manager\n"
	"help\t\t\t\topen this help page\n"
	"about\t\t\t\tview legal informations\n\n";

const char *AboutMsg =
	"About sysget\n"
	"Copyright (C) 2018 Emil Engler et al.\n"
	"http://sysget.emilengler.com\n"
	"\n"
	"This program is free software: you can redistribute it and/or modify\n"
	"it under the terms of the GNU General Public License as published by\n"
	"the Free Software Foundation, either version 3 of the License, or\n"
	"(at your option) any later version.\n"
	"\n"
	"This program is distributed in the hope that it will be useful,\n"
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
	"GNU General Public License for more details.\n"
	"\n"
	"You should have received a copy of the GNU General Public License\n"
	"along with this program.  If not, see <http://www.gnu.org/licenses/>.\n";


using namespace std;

int main(int argc, char* argv[]) {
	vector<string> PackageManagerList = GetPackageManagerList();

	// Get the path if the user has changed it with an enviroment variable
	char* EnvConfigPath = getenv("SYSGET_CONFIG_PATH");
	char* EnvCustomPath = getenv("SYSGET_CUSTOM_PATH");
	char* EnvArgsPath = getenv("SYSGET_ARGS_PATH");

	// Check if the enviroment variables aren't empty
	if(EnvConfigPath != NULL) {
		strcpy(ConfigPath, EnvConfigPath);
	}

	if(EnvCustomPath != NULL) {
		strcpy(CustomPath, EnvCustomPath);
	}

	if(EnvArgsPath != NULL) {
		strcpy(ArgsPath, EnvCustomPath);
	}
	
	// Create a config file if the config file does not exists
	if(!file_exists(ConfigPath)) {
		cout << "Please choose a package manager: " << endl;

		for(int i = 0; i < PackageManagerList.size(); i++) {
			cout << (i+1) << ". " << PackageManagerList[i] << endl;
		}

		cout << endl;

		// Now lets listen for the input
		string input;
		cin >> input;
		// Convert the input to an int to see if it is valid
		int input_int = stoi(input);

		// Create config files

		// Finally check if the input is valid
		if(input_int > PackageManagerList.size() || input_int <= 0) {
			cout << "Invalid input" << endl;
			exit(1);
		}

		// Flatpak notice
		if(input_int == 15) {
			cout << "\e[1;33m" << "NOTICE: " << "\e[0m" << "You need to provide a flatpak repository or a '.flatpakref' while installing flatpaks over sysget" << endl;
		}

		// We need to reduce the input by 1 because arrays start at 0
		CreateConf(ConfigPath, PackageManagerList[input_int -1] + "\n");

	}

	// Get the name of the package manager from the config file
	string pm_config = GetPackageManager(ConfigPath);

	if(pm_config == "ERROR") {
		cout << "Your config is broken please restart the program to create a new one" << endl;
		if(remove(ConfigPath) != 0) {
			cout << "Error while deleting broken config file, are you root?" << endl;
		}
		exit(1);
	}

	PackageManager pm;
	string execcmd;	// Will be appended with packages
	vector<string> c_args;	// If the user changes the layout of sysget

	// If the user declares his own package manager
	if(file_exists(CustomPath)) {
		pm.customPM(CustomPath);
	}

	// If sysget_config does not exists use defaults
	else {
		pm.init(pm_config);
	}

	// If the user declares his own input commands
	if(file_exists(ArgsPath)) {
		c_args = CustomArgs(ArgsPath);
		CheckCustomArgs(c_args);
	}

	// If the user doesn't set them to the defaults
	else {
		// Set them to the default args to avoid memory errors
		c_args = DefaultArgs();
	}

	// Now parse the console arguments
	// If the user enters no operation
	if(argc < 2) {
		cout << "Error you need an operation." << endl << "Try sysget help" << endl;
		exit(1);
	}

	// Lets set argv[1] to cmd for a more handy usage
	string cmd = argv[1];

	if(cmd == "search" || cmd == c_args[0]) {
		// If the user enters no search query
		if(argc < 3) {
			cout << "Error, no search query provided" << endl;
			exit(1);
		}
		checkcmd(pm.search);
		system(string(pm.search + argv[2]).c_str());
	}

	else if(cmd == "install" || cmd == c_args[1]) {
		// If the user enters no package to install
		if(argc < 3) {
			cout << "Error, no package for the installation provided" << endl;
			exit(1);
		}

		for(int i = 2; i < argc; i++) {
			checkcmd(pm.install);
			execcmd = execcmd + argv[i] + " ";
		}

		system(string(pm.install + execcmd).c_str());
	}

	else if(cmd == "remove" || cmd == c_args[2]) {
		// If the user enters no package to remove
		if(argc < 3) {
			cout << "Error, no package for the removal provided" << endl;
			exit(1);
		}

		for(int i = 2; i < argc; i++) {
			checkcmd(pm.uninstall);
			execcmd = execcmd + argv[i] + " ";
		}

		system(string(pm.uninstall + execcmd).c_str());
	}

	// FYI: checkcmd will check if your package manager supports this feature

	// Autoremove will remove orpahns
	else if(cmd == "autoremove" || cmd == c_args[3]) {
		checkcmd(pm.autoremove);
		system(pm.autoremove.c_str());
	}

	// Update will only refresh the database
	else if(cmd == "update" || cmd == c_args[4]) {
		checkcmd(pm.update);
		system(pm.update.c_str());
	}

	// Upgrading will not update the database
	else if(cmd == "upgrade" || cmd == c_args[5]) {
		if(argc < 3) {
			checkcmd(pm.upgrade);
			system(pm.upgrade.c_str());
		}

		// Upgrade specifc package
		else {
			for(int i = 2; i < argc; i++) {
				checkcmd(pm.upgrade_pkg);
				execcmd = execcmd + argv[i] + " ";
			}

			system(string(pm.upgrade_pkg + execcmd).c_str());
		}
	}

	// Clean will clean the download cache
	else if(cmd == "clean" || cmd == c_args[6]) {
		checkcmd(pm.clean);
		system(pm.clean.c_str());
	}

	// Set will change the package manager
	else if(cmd == "set" || cmd == c_args[7]) {
		if(argc < 3) {
			cout << "Error, no new package manager provided" << endl;
			exit(1);
		}

		if(remove(ConfigPath) != 0) {
			cout << "Error while deleting config file, are you root ?" << endl;
			exit(1);
		}

		else {
			CreateConf(ConfigPath, string(argv[2]) + "\n");
			cout << "Package manager changed to " << argv[2] << endl;
		}
	}

	// Help
	else if(cmd == "help" || cmd == c_args[8]) {
		cout << HelpMsg;
	}

	// About
	else if(cmd == "about" || cmd == c_args[9]) {
		cout << AboutMsg;
	}

	else {
		cout << "Unknown operation '" << cmd << "'. Try sysget help" << endl;
		exit(1);
	}
}
