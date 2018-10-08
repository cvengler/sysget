#include "update.hpp"

//Updates the database
int update(string packagemanager) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get update";
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-install -S";
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf clean expire-cache && sudo dnf check-update";
	}

	else if(packagemanager == "yum") {
		cmd = "yum check-update";
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper refresh zypper ref";
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg ur";
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Syy";
	}

	else if(packagemanager == "emerge") {
		cmd = "layman -f";
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg update";
	}

	else if(packagemanager == "chromebrew") {
		cout << "Chromebrew does not support this :(" << endl;
		exit(1);
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew update";
	}

	else if(packagemanager == "nix") {
		cmd = "nix-channel --update nixpkgs";
	}

	else if(packagemanager == "snap") {
		cout << "snapd does not support this, you may want to upgrade ?" << endl;
		exit(1);
	}

	else if(packagemanager == "npm") {
		cout << "npm does not support this, you may want to upgrade ?" << endl;
		exit(1);
	}

	system(cmd.c_str());
	return 0;
}

//Upgrades all packages
int upgrade(string packagemanager) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get upgrade";
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-install -Su";
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf update";
	}

	else if(packagemanager == "yum") {
		cmd = "yum update";
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper up";
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg upgrade";
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Su";
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge -u world && emerge -uDN world";
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg upgrade";
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew upgrade";
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew upgrade";
	}

	else if(packagemanager == "nix") {
		cmd = "nix-env -u '*'";
	}

	else if(packagemanager == "snap") {
		cmd = "snap refresh";
	}

	else if(packagemanager == "npm") {
		cmd = "npm update -g";
	}

	system(cmd.c_str());

	return 0;
}

//Upgrades only one package
//Some package managers does not offer this so we need to reinstall the package
int upgrade_pkg(string packagemanager, string package) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get install --only-upgrade ";
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-install -u ";
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf upgrade ";
	}

	else if(packagemanager == "yum") {
		cmd = "yum update ";
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper in ";
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg up ";
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -S ";
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge -avDuN ";
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg -f install ";
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew upgrade ";
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew upgrade ";
	}

	else if(packagemanager == "nix") {
		cmd = "nix-env -u ";
	}

	else if(packagemanager == "snap") {
		cmd = "snap refresh ";
	}

	else if(packagemanager == "npm") {
		cmd = "npm update -g ";
	}

	cmd += package;
	system(cmd.c_str());
	
	return 0;
}