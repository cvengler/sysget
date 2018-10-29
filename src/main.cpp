#include <iostream>
#include <vector>
#include <string>
#include "packagemanager.hpp"
#include "utils.hpp"

#define CONFIG_PATH "/usr/share/sysget/config.txt"

using namespace std;

int main(int argc, char* argv[]) {
	//Create a config file if the config file does not exists
	if(!file_exists(CONFIG_PATH)) {
		cout << "Please choose a package manager: " << endl << endl;
		cout << "1. apt-get (Debian)" << endl;
		cout << "2. xbps (Void)" << endl;
		cout << "3. dnf (Fedora)" << endl;
		cout << "4. yum (Enterprise Linux/Legacy Fedora)" << endl;
		cout << "5. zypper (OpenSUSE)" << endl;
		cout << "6. eopkg (Solus)" << endl;
		cout << "7. pacman (Arch)" << endl;
		cout << "8. emerge (Gentoo)" << endl;
		cout << "9. pkg (FreeBSD)" << endl;
		cout << "10. chromebrew (ChromeOS)" << endl;
		cout << "11. homebrew (Mac OS)" << endl;
		cout << "12. nix (Nix OS)" << endl;
		cout << "13. snap (Independent)" << endl;
		cout << "14. npm (Javascript, Global)" << endl << endl;

		//Now lets listen for the input
		vector<string> package_manager_list = { "apt-get", "xbps", "dnf", "yum", "zypper", "eopkg", "pacman", "emerge", "pkg", "chromebrew", "homebrew", "nix", "snap", "npm" };	//We use this to check if the input is valid
		string input;
		cin >> input;
		//Convert the input to an int to see if it is valid
		int input_int = stoi(input);

		// Create config files

		//Finally check if the input is valid
		if(input_int > package_manager_list.size() || input_int <= 0) {
			cout << "Invalid input" << endl;
			exit(1);
		}

		// We need to reduce the input by 1 because arrays start at 0
		create_conf(CONFIG_PATH, package_manager_list[input_int -1] + "\n");
		return 0;

	}

	//Get the name of the package manager from the config file
	string pm_config = get_package_manager(CONFIG_PATH);

	if(pm_config == "ERROR") {
		cout << "Your config is broken please restart the program to create a new one" << endl;
		if(remove(CONFIG_PATH) != 0) {
			cout << "Error while deleting broken config file, are you root?" << endl;
		}
		exit(1);
	}

	PackageManager pm;
	pm.init(pm_config);

	//Now parse the args
	//If the user enters no operation
	if(argc < 2) {
		cout << "Error you need an operation." << endl << "Try sysget help" << endl;
		exit(1);
	}

	//Lets set argv[1] to cmd for a more handy usage
	string cmd = argv[1];

	if(cmd == "search") {
		//If the user enters no search query
		if(argc < 3) {
			cout << "Error, no search query" << endl;
			exit(1);
		}
		checkcmd(pm.search);
		system(string(pm.search + argv[2]).c_str());
	}

	else if(cmd == "install") {
		//If the user enters no package to install
		if(argc < 3) {
			cout << "Error, no package to install provided" << endl;
			exit(1);
		}

		checkcmd(pm.install);
		system(string(pm.install + argv[2]).c_str());
	}

	else if(cmd == "remove") {
		//If the user enters no package to remove
		if(argc < 3) {
			cout << "Error, no package to remove provided" << endl;
			exit(1);
		}

		checkcmd(pm.remove);
		system(string(pm.remove + argv[2]).c_str());
	}

	//FYI: checkcmd will check if your package manager supports this feature

	//Autoremove will remove orpahns
	else if(cmd == "autoremove") {
		checkcmd(pm.autoremove);
		system(pm.autoremove.c_str());
	}

	//Update will only refresh the database
	else if(cmd == "update") {
		checkcmd(pm.update);
		system(pm.update.c_str());
	}

	//Upgrading will not update the database
	else if(cmd == "upgrade") {
		if(argc < 3) {
			checkcmd(pm.upgrade);
			system(pm.upgrade.c_str());
		}

		else {
			checkcmd(pm.upgrade_pkg);
			system(string(pm.upgrade_pkg + argv[2]).c_str());
		}
	}

	//Clean will clean the download cache
	else if(cmd == "clean") {
		checkcmd(pm.clean);
		system(pm.clean.c_str());
	}

	//Set will change the package manager
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

	//Help
	else if(cmd == "help") {
		cout << "Help of sysget" << endl;
		cout << "sysget [OPTION] [ARGUMENT]" << endl;
		cout << endl;
		cout << "search [query]\t\tsearch for a package in the resporitories" << endl;
		cout << "install [package]\tinstall a package from the repos" << endl;
		cout << "remove [package]\tremoves a package" << endl;
		cout << "autoremove\t\tremoves not needed packages (orphans)" << endl;
		cout << "update\t\t\tupdate the database" << endl;
		cout << "upgrade\t\t\tdo a system upgrade" << endl;
		cout << "upgrade [package]\tupgrade a specific package" << endl;
		cout << "clean\t\t\tclean the download cache" << endl;
		cout << "set [NEW MANAGER]\tset a new package manager" << endl;
		cout << endl;
	}

	else {
		cout << "Unknown operation, try sysget help" << endl;
		exit(1);
	}
}