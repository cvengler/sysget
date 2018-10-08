#include "update.hpp"

//Updates the database
int update(string packagemanager) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get update";
		system(cmd.c_str());
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-install -S";
		system(cmd.c_str());
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf clean expire-cache && sudo dnf check-update";
		system(cmd.c_str());
	}

	else if(packagemanager == "yum") {
		cmd = "yum check-update";
		system(cmd.c_str());
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper refresh zypper ref";
		system(cmd.c_str());
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg ur";
		system(cmd.c_str());
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Syy";
		system(cmd.c_str());
	}

	else if(packagemanager == "emerge") {
		cmd = "layman -f";
		system(cmd.c_str());
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg update";
		system(cmd.c_str());
	}

	else if(packagemanager == "chromebrew") {
		cout << "Chromebrew does not support this :(" << endl;
		exit(1);
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew update";
		system(cmd.c_str());
	}

	else if(packagemanager == "nix") {
		cmd = "nix-channel --update nixpkgs";
		system(cmd.c_str());
	}

	else if(packagemanager == "snap") {
		cout << "snapd does not support this, you may want to upgrade ?" << endl;
		exit(1);
	}
	return 0;
}

//Upgrades all packages
int upgrade(string packagemanager) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get upgrade";
		system(cmd.c_str());
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-install -Su";
		system(cmd.c_str());
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf update";
		system(cmd.c_str());
	}

	else if(packagemanager == "yum") {
		cmd = "yum update";
		system(cmd.c_str());
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper up";
		system(cmd.c_str());
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg upgrade";
		system(cmd.c_str());
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -Su";
		system(cmd.c_str());
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge -u world && emerge -uDN world";
		system(cmd.c_str());
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg upgrade";
		system(cmd.c_str());
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew upgrade";
		system(cmd.c_str());
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew upgrade";
		system(cmd.c_str());
	}

	else if(packagemanager == "nix") {
		cmd = "nix-env -u '*'";
		system(cmd.c_str());
	}

	else if(packagemanager == "snap") {
		cmd = "snap refresh";
		system(cmd.c_str());
	}
	return 0;
}

//Upgrades only one package
//Some package managers does not offer this so we need to reinstall the package
int upgrade_pkg(string packagemanager, string package) {
	string cmd;
	if(packagemanager == "apt-get") {
		cmd = "apt-get install --only-upgrade " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "xbps") {
		cmd = "xbps-install -u " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "dnf") {
		cmd = "dnf upgrade " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "yum") {
		cmd = "yum update " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "zypper") {
		cmd = "zypper in " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "eopkg") {
		cmd = "eopkg up " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "pacman") {
		cmd = "pacman -S " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "emerge") {
		cmd = "emerge -avDuN " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "pkg") {
		cmd = "pkg -f install " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "chromebrew") {
		cmd = "crew upgrade " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "homebrew") {
		cmd = "brew upgrade " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "nix") {
		cmd = "nix-env -u " + package;
		system(cmd.c_str());
	}

	else if(packagemanager == "snap") {
		cmd = "snap refresh " + package;
		system(cmd.c_str());
	}
	return 0;
}