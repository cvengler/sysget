#include "install.hpp"

int install(string packagemanager, string package) {
	string cmd;
	
	// The following if statements check our package manager and use that as the command
	
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
		cmd = "emerge --ask ";
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

	cmd += package; // Appends package name to end of string
	system(cmd.c_str()); // runs string as command
	
	return 0;
}
