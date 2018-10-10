#include "search.hpp"

int search(string packagemanager, string query) {
	string cmd;
	
	if(packagemanager == "apt-get") {
		cmd = "apt-cache search ";
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-query -Rs ";
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf search ";
	}

	else if(packagemanager == "yum") {
		cmd = "yum search ";
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper search ";
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg search ";
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Ss ";
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge -S ";
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg search ";
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew search ";
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew search ";
	}

	else if(packagemanager == "nix") {
		cmd = "nix search ";
	}

	else if(packagemanager == "snap") {
		cmd = "snap find ";
	}

	else if(packagemanager == "npm") {
		cmd = "npm search ";
	}

	cmd += query;
	system(cmd.c_str());
	
	return 0;
}