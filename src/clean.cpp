#include "clean.hpp"

int clean(string packagemanager) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get autoclean && apt-get clean";
		system(cmd.c_str());
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-remove -O";
		system(cmd.c_str());
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf clean all";
		system(cmd.c_str());
	}

	else if(packagemanager == "yum") {
		cmd = "yum clean all";
		system(cmd.c_str());
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper clean";
		system(cmd.c_str());
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg delete-cache";
		system(cmd.c_str());
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Sc";
		system(cmd.c_str());
	}

	else if(packagemanager == "emerge") {
		cmd = "eclean distfiles";
		system(cmd.c_str());
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg clean";
		system(cmd.c_str());
	}

	else if(packagemanager == "chromebrew") {
		cout << "Not availible on chromebrew" << endl;
		exit(1);
	}

	else if(packagemanager == "homebrew") {
		cout << "Homebrew does this automatically" << endl;
		exit(0);
	}

	else if(packagemanager == "nix") {
		exit(1);
	}

	else if(packagemanager == "snap") {
		cout << "snapd does this automatically after some time" << endl;
		exit(0);
	}

	else if(packagemanager == "npm") {
		cmd = "npm cache clean --force";
		system(cmd.c_str());
	}
	return 0;
}