#include "search.hpp"

/* Order
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
*/

int search(string packagemanager, string query) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-cache search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-query -Rs " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "yum") {
		cmd = "yum search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Ss " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge -S " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "nix") {
		cmd = "nix search " + query;
		system(cmd.c_str());
	}

	else if(packagemanager == "snap") {
		cmd = "snap find " + query;
		system(cmd.c_str());
	}
	return 0;
}