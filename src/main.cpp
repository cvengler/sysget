#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "packagemanager.hpp"
#include "utils.hpp"

char CONFIG_PATH[255] = "/etc/sysget";	// Needs to be NOT const so it can be changed if an enviroment variable set
char CUSTOM_PATH[255] = "/etc/sysget_custom";

using namespace std;

int main(int argc, char* argv[]) {
	vector<string> package_manager_list = { "apt-get", "xbps", "dnf", "yum", "zypper", "eopkg", "pacman", "emerge", "pkg", "chromebrew", "homebrew", "nix", "snap", "npm", "flatpak", "slapt-get" };

	// Get the path if the user has changed it with an enviroment variable
	char* env_config_path = getenv("SYSGET_CONFIG_PATH");
	char* env_custom_path = getenv("SYSGET_CUSTOM_PATH");

	// Check if the enviroment variables aren't empty
	if(env_config_path != NULL) {
		strcpy(CONFIG_PATH, env_config_path);
	}

	if(env_custom_path != NULL) {
		strcpy(CUSTOM_PATH, env_custom_path);
	}
	
	// Create a config file if the config file does not exists
	if(!file_exists(CONFIG_PATH)) {
		cout << "Please choose a package manager: " << endl;

		for(int i = 0; i < package_manager_list.size(); i++) {
			cout << (i+1) << ". " << package_manager_list[i] << endl;
		}

		cout << endl;

		// Now lets listen for the input
		string input;
		cin >> input;
		// Convert the input to an int to see if it is valid
		int input_int = stoi(input);

		// Create config files

		// Finally check if the input is valid
		if(input_int > package_manager_list.size() || input_int <= 0) {
			cout << "Invalid input" << endl;
			exit(1);
		}

		// Flatpak notice
		if(input_int == 15) {
			cout << "\e[1;33m" << "NOTICE: " << "\e[0m" << "You need to provide a flatpak repository or a '.flatpakref' while installing flatpaks over sysget" << endl;
		}

		// We need to reduce the input by 1 because arrays start at 0
		create_conf(CONFIG_PATH, package_manager_list[input_int -1] + "\n");

	}

	// Get the name of the package manager from the config file
	string pm_config = get_package_manager(CONFIG_PATH);

	if(pm_config == "ERROR") {
		cout << "Your config is broken please restart the program to create a new one" << endl;
		if(remove(CONFIG_PATH) != 0) {
			cout << "Error while deleting broken config file, are you root?" << endl;
		}
		exit(1);
	}

	PackageManager pm;
	string execcmd;

	// If the user declares his own package manager
	if(file_exists(CUSTOM_PATH)) {
		pm.customPM(CUSTOM_PATH);
	}

	// If sysget_config does not exists use defaults
	else {
		pm.init(pm_config);
	}

	// Now parse the console arguments
	// If the user enters no operation
	if(argc < 2) {
		cout << "Error you need an operation." << endl << "Try sysget help" << endl;
		exit(1);
	}

	// Lets set argv[1] to cmd for a more handy usage
	string cmd = argv[1];

	if(cmd == "search") {
		// If the user enters no search query
		if(argc < 3) {
			cout << "Error, no search query provided" << endl;
			exit(1);
		}
		checkcmd(pm.search);
		system(string(pm.search + argv[2]).c_str());
	}

	else if(cmd == "install") {
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

	else if(cmd == "remove") {
		// If the user enters no package to remove
		if(argc < 3) {
			cout << "Error, no package for the removal provided" << endl;
			exit(1);
		}

		for(int i = 2; i < argc; i++) {
			checkcmd(pm.remove);
			execcmd = execcmd + argv[i] + " ";
		}

		system(string(pm.remove + execcmd).c_str());
	}

	// FYI: checkcmd will check if your package manager supports this feature

	// Autoremove will remove orpahns
	else if(cmd == "autoremove") {
		checkcmd(pm.autoremove);
		system(pm.autoremove.c_str());
	}

	// Update will only refresh the database
	else if(cmd == "update") {
		checkcmd(pm.update);
		system(pm.update.c_str());
	}

	// Upgrading will not update the database
	else if(cmd == "upgrade") {
		if(argc < 3) {
			checkcmd(pm.upgrade);
			system(pm.upgrade.c_str());
		}

		else {
			for(int i = 2; i < argc; i++) {
				checkcmd(pm.upgrade_pkg);
				execcmd = execcmd + argv[i] + " ";
			}

			system(string(pm.upgrade_pkg + execcmd).c_str());
		}
	}

	// Clean will clean the download cache
	else if(cmd == "clean") {
		checkcmd(pm.clean);
		system(pm.clean.c_str());
	}

	// Set will change the package manager
	else if(cmd == "set") {
		if(argc < 3) {
			cout << "Error, no new package manager provided" << endl;
			exit(1);
		}

		if(remove(CONFIG_PATH) != 0) {
			cout << "Error while deleting config file, are you root ?" << endl;
			exit(1);
		}

		else {
			create_conf(CONFIG_PATH, string(argv[2]) + "\n");
			cout << "Package manager changed to " << argv[2] << endl;
		}
	}

	// Help
	else if(cmd == "help") {
		cout << "Help of sysget" << endl;
		cout << "sysget [OPTION] [PACKAGE(S)]" << endl;
		cout << endl;
		cout << "search [QUERY]\t\t\tsearch for a package in the resporitories" << endl;
		cout << "install [PACKAGE] [PACKAGE]\tinstall a package from the repos" << endl;
		cout << "remove [PACKAGE] [PACKAGE]\tremoves a package" << endl;
		cout << "autoremove\t\t\tremoves not needed packages (orphans)" << endl;
		cout << "update\t\t\t\tupdate the database" << endl;
		cout << "upgrade\t\t\t\tdo a system upgrade" << endl;
		cout << "upgrade [PACKAGE] [PACKAGE]\tupgrade a specific package" << endl;
		cout << "clean\t\t\t\tclean the download cache" << endl;
		cout << "set [NEW MANAGER]\t\tset a new package manager" << endl;
		cout << endl;
	}

	else {
		cout << "Unknown operation '" << cmd << "'. Try sysget help" << endl;
		exit(1);
	}
}
