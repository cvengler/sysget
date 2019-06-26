// Copyright (c) 2018-2019 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
// file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
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

// Default path for config files
std::string ConfigPath = "/etc/sysget/sysget";
std::string CustomPath = "/etc/sysget/custom";
std::string ArgsPath = "/etc/sysget/args";

std::string version = "2.2";

const char *HelpMsg =
	"Help of sysget" + version + "\n"
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
	"About sysget " + version  + "\n"
	"Copyright (C) 2018-2019 Emil Engler et al.\n"
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


// Default syntax operations
std::vector<std::string> SearchCmds = {"search", "--search"};
std::vector<std::string> InstallCmds = {"install", "--install"};
std::vector<std::string> RemoveCmds = {"remove", "--remove"};
std::vector<std::string> AutoremoveCmds = {"autoremove", "--autoremove"};
std::vector<std::string> UpdateCmds = {"update", "--update"};
std::vector<std::string> UpgradeCmds = {"upgrade", "--upgrade"};
std::vector<std::string> CleanCmds = {"clean", "--clean"};
std::vector<std::string> SetCmds = {"set", "--set"};
std::vector<std::string> HelpCmds = {"help", "--help"};
std::vector<std::string> AboutCmds = {"about", "--about"};
std::vector<std::string> VersionCmds = {"version", "--version"};

int main(int argc, char* argv[]) {
	std::vector<std::string> PackageManagerList = GetPackageManagerList();

	// Get the path if the user has changed it with an enviroment variable
	char* EnvConfigPath = getenv("SYSGET_CONFIG_PATH");
	char* EnvCustomPath = getenv("SYSGET_CUSTOM_PATH");
	char* EnvArgsPath = getenv("SYSGET_ARGS_PATH");

	// Check if the enviroment variables aren't empty
	if(EnvConfigPath != NULL) {
		ConfigPath = std::string(EnvConfigPath);
	}

	if(EnvCustomPath != NULL) {
		CustomPath = std::string(EnvCustomPath);
	}

	if(EnvArgsPath != NULL) {
		ArgsPath = std::string(EnvArgsPath);
	}
	
	// Create a config file if the config file does not exists
	if(!file_exists(ConfigPath.c_str())) {
		std::cout << "Please choose a package manager: " << std::endl;

		for(unsigned int i = 0; i < PackageManagerList.size(); i++) {
			std::cout << (i+1) << ". " << PackageManagerList[i] << std::endl;
		}

		std::cout << std::endl;

		// Now lets listen for the input
		std::string input;
		std::cin >> input;
		// Convert the input to an int to see if it is valid
		unsigned int InputInt;
		try {
			InputInt = stoi(input);
		}
		catch(std::exception&) {
			std::cerr << "You need to enter a number" << std::endl;
			exit(1);
		}

		// Create config files

		// Finally check if the input is valid
		if(InputInt > PackageManagerList.size() || InputInt <= 0) {
			std::cerr << "Input is out of range" << std::endl;
			exit(1);
		}

		// We need to reduce the input by 1 because arrays start at 0
		CreateConf(ConfigPath, PackageManagerList[InputInt -1] + "\n");

	}

	// Get the name of the package manager from the config file
	std::string pm_config = GetPackageManager(ConfigPath);

	if(pm_config == "ERROR") {
		std::cerr << "Your config is broken please restart the program to create a new one" << std::endl;
		if(remove(ConfigPath.c_str()) != 0) {
			std::cerr << "Error while deleting broken config file, are you root?" << std::endl;
		}
		exit(1);
	}

	PackageManager pm;
	std::string execcmd;	// Will be appended with packages

	// If the user declares his own package manager
	if(file_exists(CustomPath.c_str())) {
		pm.customPM(CustomPath);
	}

	// If sysget_config does not exists use defaults
	else {
		pm.init(pm_config);
	}

	// If the user declares his own input commands
	if(file_exists(ArgsPath.c_str())) {
		std::vector<std::string> c_args;	// If the user changes the layout of sysget
		c_args = CustomArgs(ArgsPath);
		SearchCmds.push_back(c_args[0]);
		InstallCmds.push_back(c_args[1]);
		RemoveCmds.push_back(c_args[2]);
		AutoremoveCmds.push_back(c_args[3]);
		UpdateCmds.push_back(c_args[4]);
		UpgradeCmds.push_back(c_args[5]);
		CleanCmds.push_back(c_args[6]);
		SetCmds.push_back(c_args[7]);
		HelpCmds.push_back(c_args[8]);
		AboutCmds.push_back(c_args[9]);
	}

	// Now parse the console arguments
	// If the user enters no operation
	if(argc < 2) {
		std::cerr << "Error you need an operation." << std::endl << "Try sysget help" << std::endl;
		exit(1);
	}

	// Lets set argv[1] to cmd for a more handy usage
	std::string cmd = argv[1];

	if(VectorContains(cmd, SearchCmds)) {
		// If the user enters no search query
		if(argc < 3) {
			std::cerr << "Error, no search query provided" << std::endl;
			exit(1);
		}
		checkcmd(pm.search);
		system(std::string(pm.search + argv[2]).c_str());
	}

	else if(VectorContains(cmd, InstallCmds)) {
		// If the user enters no package to install
		if(argc < 3) {
			std::cerr << "Error, no package for the installation provided" << std::endl;
			exit(1);
		}

		for(int i = 2; i < argc; i++) {
			checkcmd(pm.install);
			execcmd = execcmd + argv[i] + " ";
		}

		system(std::string(pm.install + execcmd).c_str());
	}

	else if(VectorContains(cmd, RemoveCmds)) {
		// If the user enters no package to remove
		if(argc < 3) {
			std::cerr << "Error, no package for the removal provided" << std::endl;
			exit(1);
		}

		for(int i = 2; i < argc; i++) {
			checkcmd(pm.uninstall);
			execcmd = execcmd + argv[i] + " ";
		}

		system(std::string(pm.uninstall + execcmd).c_str());
	}

	// FYI: checkcmd will check if your package manager supports this feature

	// Autoremove will remove orpahns
	else if(VectorContains(cmd, AutoremoveCmds)) {
		checkcmd(pm.autoremove);
		system(pm.autoremove.c_str());
	}

	// Update will only refresh the database
	else if(VectorContains(cmd, UpdateCmds)) {
		checkcmd(pm.update);
		system(pm.update.c_str());
	}

	// Upgrading will not update the database
	else if(VectorContains(cmd, UpgradeCmds)) {
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

			system(std::string(pm.upgrade_pkg + execcmd).c_str());
		}
	}

	// Clean will clean the download cache
	else if(VectorContains(cmd, CleanCmds)) {
		checkcmd(pm.clean);
		system(pm.clean.c_str());
	}

	// Set will change the package manager
	else if(VectorContains(cmd, SetCmds)) {
		if(argc < 3) {
			std::cerr << "Error, no new package manager provided" << std::endl;
			exit(1);
		}

		if(remove(ConfigPath.c_str()) != 0) {
			std::cerr << "Error while deleting config file, are you root ?" << std::endl;
			exit(1);
		}

		else {
			CreateConf(ConfigPath, std::string(argv[2]) + "\n");
			std::cout << "Package manager changed to " << argv[2] << std::endl;
		}
	}

	// Help
	else if(VectorContains(cmd, HelpCmds)) {
		std::cout << HelpMsg;
	}

	// About
	else if(VectorContains(cmd, AboutCmds)) {
		std::cout << AboutMsg;
	}

	else if(VectorContains(cmd, VersionCmds) {
		std::cout << version << std::endl;
	}

	else {
		std::cerr << "Unknown operation '" << cmd << "'. Try sysget help" << std::endl;
		exit(1);
	}
}
