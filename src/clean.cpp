#include "clean.hpp"

// We return an exit code 1 if the package manager does not support this
int clean(string packagemanager) {
	string cmd;
	
	// Following if statements check if our package manager is equal to string and if true, set cmd to command
	
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

	system(cmd.c_str()); // runs command
	
	return 0;
}
