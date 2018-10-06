#include "remove.h"

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

int remove(string packagemanager, string package) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get remove " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-remove " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf erase " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "yum") {
		cmd = "yum remove " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper remove " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg remove " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Rs " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge -C " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg delete " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew remove " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew uninstall " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "nix") {
		cmd = "nix-env -e " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "snap") {
		cmd = "snap remove " + package;
		system(cmd.c_str());
	}
}

int autoremove(string packagemanager) {
	//This will try to remove orphans
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get autoremove";
		system(cmd.c_str());
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-remove -o";
		system(cmd.c_str());
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf autoremove";
		system(cmd.c_str());
	}

	else if(packagemanager == "yum") {
		cmd = "yum autoremove";
		system(cmd.c_str());
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper rm -u";
		system(cmd.c_str());
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg remove-orphans";
		system(cmd.c_str());
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Rns $(pacman -Qtdq)";
		system(cmd.c_str());
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge --depclean -a";
		system(cmd.c_str());
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg autoremove";
		system(cmd.c_str());
	}

	else if(packagemanager == "chromebrew") {
		cout << "Chromebrew does not support this :(" << endl;
		exit(1);
	}

	else if(packagemanager == "homebrew") {
		cout << "Homebrew does this automatically" << endl;
		exit(0);
	}

	else if(packagemanager == "nix") {
		cmd = "nix-collect-garbage -d";
		system(cmd.c_str());
	}

	else if(packagemanager == "snap") {
		cout << "A snap doesn't have orphans" << endl;
		exit(0);
	}
}