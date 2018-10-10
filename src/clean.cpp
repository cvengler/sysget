#include "clean.hpp"

int clean(string packagemanager) {
	string cmd;
	
	if(packagemanager == "apt-get") {
		cmd = "apt-get autoclean && apt-get clean";
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-remove -O";
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf clean all";
	}

	else if(packagemanager == "yum") {
		cmd = "yum clean all";
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper clean";
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg delete-cache";
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Sc";
	}

	else if(packagemanager == "emerge") {
		cmd = "eclean distfiles";
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg clean";
	}

	else if(packagemanager == "chromebrew") {
		cout << "Not availible on chromebrew" << endl;
		exit(1);
	}

	else if(packagemanager == "homebrew") {
		cout << "Homebrew does this automatically" << endl;
	}

	else if(packagemanager == "nix") {
		exit(1);
	}

	else if(packagemanager == "snap") {
		cout << "snapd does this automatically after some time" << endl;
	}

	else if(packagemanager == "npm") {
		cmd = "npm cache clean --force";
	}

	system(cmd.c_str());
	
	return 0;
}