#include <vector>
#include "utils.hpp"
#include "search.hpp"
#include "install.hpp"
#include "remove.hpp"
#include "update.hpp"
#include "clean.hpp"

#define CONFIG_PATH "/usr/local/share/sysget/config.txt"

using namespace std;

int main(int argc, char *argv[]) {
	// First check if the config file exists
	string pm;
	string command;

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
		
		// Now lets listen for input, returned with enter
		string input;
		cin >> input;

		// Create config files
		vector<string> package_manager_list = { "apt-get", "xbps", "dnf", "yum", "zypper", "eopkg", "pacman", "emerge", "pkg", "chromebrew", "homebrew", "nix", "snap", "npm" };	//Thanks dwbrite

		// Convert the input into an int
		int input_int = stoi(input);

		// Check if input is valid
		if(input_int > package_manager_list.size() || input_int <= 0) {
			cout << "Invalid input" << endl;
			exit(1);
		}

		// We need to reduce the input with 1 because arrays start at 0
		create_conf(CONFIG_PATH, package_manager_list[input_int - 1] + "\n");
		return 0;
	}

	pm = read_conf(CONFIG_PATH);
	// If read_conf detects something invalid, the return will be ERROR
	if(pm == "ERROR") {
		cout << "Broken config, please restart to generate a new one" << endl;
		if(remove(CONFIG_PATH) != 0) {
			cout << "Error while deleting broken config file, are you root?" << endl;
		}

		exit(1);
	}

	// If user enters no operation
	if(argc < 2) {
		cout << "Error, you need an operation" << endl;
		exit(1);
	}
	
	command = argv[1];

	if(command == "search") {
		if(argc < 3) {
			// If users enters no search parameter
			cout << "Error, no search parameter" << endl;
			exit(1);
		}

		search(pm, string(argv[2]));
	}

	else if(command == "install") {
		if(argc < 3) {
			// If user enters no package to install
			cout << "Error, no package to install" << endl;
			exit(1);
		}

		install(pm, string(argv[2]));
	}

	else if(command == "remove") {
		if(argc < 3) {
			//If user enters no package to remove
			cout << "Error, no package to remove" << endl;
			exit(1);
		}

		remove(pm, string(argv[2]));
	}

	else if(command == "autoremove") {
		autoremove(pm);
	}

	// Update will only refresh the database
	else if(command == "update") {
		update(pm);
	}

	// Upgrading will not update the database
	else if(command == "upgrade") {
		if(argc < 3) {
			upgrade(pm);
		}

		else {
			upgrade_pkg(pm, string(argv[2]));
		}
	}

	// Clean will clean the download cache
	else if(command == "clean") {
		clean(pm);
	}

	// Set will change the package manager
	else if(command == "set") {
		if(argc < 3) {
			cout << "Error, no package manager provided" << endl;
			exit(1);
		}

		if(remove(CONFIG_PATH) != 0) {
			cout << "Error while deleting the config file, are you root ?" << endl;
			exit(1);
		}

		else {
			create_conf(CONFIG_PATH, string(argv[2]) + "\n");
			cout << "Package manager changed to " << string(argv[2]) << endl;
		}

	}

	// Help
	else if(command == "help" || command == "?") {
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
		cout << endl; // IDEA: clean this up a little, convert to one string
	}

	else {
		cout << "Unknown operation, try sysget help" << endl;
		exit(1);
	}
	return 0;
}
