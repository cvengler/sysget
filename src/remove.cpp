#include "remove.hpp"

int remove(string packagemanager, string package) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get remove ";
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-remove ";
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf erase ";
	}

	else if(packagemanager == "yum") {
		cmd = "yum remove ";
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper remove ";
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg remove ";
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Rs ";
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge -C ";
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg delete ";
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew remove ";
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew uninstall ";
	}

	else if(packagemanager == "nix") {
		cmd = "nix-env -e ";
	}

	else if(packagemanager == "snap") {
		cmd = "snap remove ";
	}

	else if(packagemanager == "npm") {
		cmd = "npm uninstall -g ";
	}
	
	cmd += package;
	system(cmd.c_str());

	return 0;
}

int autoremove(string packagemanager) {
	//This will try to remove orphans
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get autoremove";
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-remove -o";
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf autoremove";
	}

	else if(packagemanager == "yum") {
		cmd = "yum autoremove";
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper rm -u";
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg remove-orphans";
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Rns $(pacman -Qtdq)";
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge --depclean -a";
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg autoremove";
	}

	else if(packagemanager == "chromebrew") {
		cout << "Chromebrew does not support this :(" << endl;
		exit(1);
	}

	else if(packagemanager == "homebrew") {
		cout << "Homebrew does this automatically" << endl;
	}

	else if(packagemanager == "nix") {
		cmd = "nix-collect-garbage -d";
	}

	else if(packagemanager == "snap") {
		cout << "A snap doesn't have orphans" << endl;
	}

	else if(packagemanager == "npm") {
		cmd = "npm prune";
	}

	system(cmd.c_str());

	return 0;
}