#include <iostream>
#include <vector>
#include "utils.h"
#include "search.h"
#include "install.h"
#include "remove.h"
#include "update.h"
#include "clean.h"

using namespace std;

int main(int argc, char *argv[]) {
	//First check if the config file exists
	string pm;

	if(file_exists("/usr/local/share/sysget/config.txt") == false) {
		cout << "Please choose a package manager: " << endl << endl;
		cout << "1. apt-get (Debian)" << endl;
		cout << "2. xbps (Void)" << endl;
		cout << "3. dnf (Fedora)" << endl;
		cout << "4. yum (Legacy fedora)" << endl;
		cout << "5. zypper (OpenSUSE)" << endl;
		cout << "6. eopkg (Solus)" << endl;
		cout << "7. pacman (Arch)" << endl;
		cout << "8. emerge (Gentoo)" << endl;
		cout << "9. pkg (FreeBSD)" << endl;
		cout << "10. chromebrew (ChromeOS)" << endl;
		cout << "11. homebrew (Mac OS)" << endl;
		cout << "12. nix (Nix OS)" << endl << endl;

		string input;
		cin >> input;

		//Create config files
		vector<string> package_manager_list = { "apt-get", "xbps", "dnf", "yum", "zypper", "eopkg", "pacman", "emerge", "pkg", "chromebrew", "homebrew", "nix" };	//Thanks dwbrite

		//Convert the input into an int
		int input_int = stoi(input);

		//Check if input is valid
		if(input_int >= package_manager_list.size() || input_int <= 0) {
			cout << "Invalid input" << endl;
			exit(1);
		}

		//We need to reduce the input with 1 because arrays start at 0
		create_conf("/usr/local/share/sysget/config.txt", package_manager_list[input_int - 1] + "\n");
		exit(0);
	}

	pm = read_conf("/usr/local/share/sysget/config.txt");
	//If read_conf detects something invalid, the return will be ERROR
	if(pm == "ERROR") {
		cout << "Broken config" << endl;
		system("rm /usr/local/share/sysget/config.txt");
		exit(1);
	}

	//If user enters no operation
	if(argc < 2) {
		cout << "Error, you need an operation" << endl;
		exit(1);
	}

	if(string(argv[1]) == "search") {
		if(argc < 3) {
			//If users enters no search parameter
			cout << "Error, no search parameter" << endl;
			exit(1);
		}

		search(pm, string(argv[2]));
	}

	else if(string(argv[1]) == "install") {
		if(argc < 3) {
			//If user enters no package to install
			cout << "Error, no package to install" << endl;
			exit(1);
		}

		install(pm, string(argv[2]));
	}

	else if(string(argv[1]) == "remove") {
		if(argc < 3) {
			//If user enters no package to remove
			cout << "Error, no package to remove" << endl;
			exit(1);
		}

		remove(pm, string(argv[2]));
	}

	else if(string(argv[1]) == "autoremove") {
		autoremove(pm);
	}

	//Update will only refresh the database
	else if(string(argv[1]) == "update") {
		update(pm);
	}

	//Upgrading will not update the database
	else if(string(argv[1]) == "upgrade") {
		if(argc < 3) {
			upgrade(pm);
		}

		else {
			upgrade_pkg(pm, string(argv[2]));
		}
	}

	//Clean wiĺl clean the download cache
	else if(string(argv[1]) == "clean") {
		clean(pm);
	}

	//Help
	else if(string(argv[1]) == "help") {
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
		cout << endl;
	}

	else {
		cout << "Unknown operation, try sysget help" << endl;
		exit(1);
	}

}