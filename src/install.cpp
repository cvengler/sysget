#include "install.hpp"

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

int install(string packagemanager, string package) {
	string cmd;
	
	if(packagemanager == "apt-get") {
		cmd = "apt-get install ";
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-install ";
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf install ";
	}

	else if(packagemanager == "yum") {
		cmd = "yum install ";
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper install ";
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg install ";
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -S ";
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge ";
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg install ";
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew install ";
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew install ";
	}

	else if(packagemanager == "nix") {
		cmd = "nix-env -i ";
	}

	else if(packagemanager == "snap") {
		cmd = "snap install ";
	}

	else if(packagemanager == "npm") {
		cmd = "npm install -g ";
	}

	cmd += package;
	system(cmd.c_str());
	
	return 0;
}