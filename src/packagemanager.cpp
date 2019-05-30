// Copyright (c) 2018-2019 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
// file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
#include "packagemanager.hpp"

// This is the constructor
void PackageManager::init(string pm) {

	if(pm == "apt") {
		// apt
		search = "apt search ";
		install = "apt install ";
		uninstall = "apt purge ";
		autoremove = "apt purge --autoremove";
		update = "apt update";
		upgrade = "apt upgrade";
		upgrade_pkg = "apt upgrade ";
		clean = "apt autoclean && apt clean";
	}
	
	else if(pm == "apt-get") {
		// apt-get
		search = "apt-cache search ";
		install = "apt-get install ";
		uninstall = "apt-get purge ";
		autoremove = "apt-get purge --autoremove";
		update = "apt-get update";
		upgrade = "apt-get upgrade";
		upgrade_pkg = "apt-get upgrade ";
		clean = "apt-get autoclean && apt-get clean";
	}

	else if(pm == "xbps") {
		// xbps
		search = "xbps-query -Rs ";
		install = "xbps-install ";
		uninstall = "xbps-remove ";
		autoremove = "xbps-remove -o";
		update = "xbps-install -S";
		upgrade = "xbps-install -Su";
		upgrade_pkg = "xbps-install -u ";
		clean = "xbps-remove -O";
	}

	else if(pm == "dnf") {
		// dnf
		search = "dnf search ";
		install = "dnf install ";
		uninstall = "dnf erase ";
		autoremove = "dnf autoremove";
		update = "dnf clean expire-cache && sudo dnf check-update";
		upgrade = "dnf update";
		upgrade_pkg = "dnf upgrade ";
		clean = "dnf clean all";
	}

	else if(pm == "yum") {
		// yum
		search = "yum search ";
		install = "yum install ";
		uninstall = "yum erase ";
		autoremove = "yum autoremove";
		update = "yum check-update";
		upgrade = "yum update";
		upgrade_pkg = "yum update ";
		clean = "yum clean all";
	}

	else if(pm == "zypper") {
		// zypper
		search = "zypper search ";
		install = "zypper install ";
		uninstall = "zypper remove ";
		autoremove = "zypper rm -u";
		update = "zypper refresh zypper ref";
		upgrade = "zypper up";
		upgrade_pkg = "zypper in ";
		clean = "zypper clean";
	}

	else if(pm == "eopkg") {
		// eopkg
		search = "eopkg search ";
		install = "eopkg install ";
		uninstall = "eopkg remove ";
		autoremove = "eopkg remove-orphans";
		update = "eopkg ur";
		upgrade = "eopkg upgrade";
		upgrade_pkg = "eopkg upgrade ";
		clean = "eopkg delete-cache";
	}

	else if(pm == "pacman") {
		// pacman
		search = "pacman -Ss ";
		install = "pacman -S ";
		uninstall = "pacman -Rs ";
		autoremove = "pacman -Rns $(pacman -Qtdq)";
		update = "pacman -Syy";
		upgrade = "pacman -Syu";
		upgrade_pkg = "pacman -S ";
		clean = "pacman -Sc";
	}

	else if(pm == "emerge") {
		// emerge / portage
		search = "emerge -S ";
		install = "emerge --ask ";
		uninstall = "emerge -C ";
		autoremove = "emerge --depclean -a";
		update = "layman -f";
		upgrade = "emerge --ask -u world && emerge --ask -uDN world";
		upgrade_pkg = "emerge -avDuN";
		clean = "eclean distfiles";
	}

	else if(pm == "pkg") {
		// pkg (FreeBSD)
		search = "pkg search ";
		install = "pkg install ";
		uninstall = "pkg delete ";
		autoremove = "pkg autoremove";
		update = "pkg update";
		upgrade = "pkg upgrade";
		upgrade_pkg = "pkg -f install ";
		clean = "pkg clean";
	}
	else if(pm == "pkg_mgr") {
		// pkg_mgr (OpenBSD)
		search = "";
		install = "pkg_add ";
		uninstall = "pkg_delete ";
		autoremove = "pkg_delete -a";
		update = "exit=pkg_mgr does not support this, you may want to upgrade ?";
		upgrade = "pkg_add -u";
		upgrade_pkg = "pkg_add -u ";
		clean = "pkg_delete -a";
	}

	else if(pm == "chromebrew") {
		// chromebrew
		search = "crew search ";
		install = "crew install ";
		uninstall = "crew remove ";
		autoremove = "exit=Chromebrew does not support this";
		update = "exit=Chromebrew does not support this";
		upgrade = "crew upgrade";
		upgrade_pkg = "crew upgrade ";
		clean = "exit=Chromebrew does not support this";
	}

	else if(pm == "homebrew") {
		// homebrew
		search = "brew search ";
		install = "brew install ";
		uninstall = "brew uninstall ";
		autoremove = "exit=Homebrew does this automatically";
		update = "brew update";
		upgrade = "brew upgrade";
		upgrade_pkg = "brew upgrade ";
		clean = "exit=Homebrew does this automatically";
	}

	else if(pm == "nix") {
		// nix
		search = "nix search ";
		install = "nix-env -i ";
		uninstall = "nix-env -e ";
		autoremove = "nix-collect-garbage -d";
		update = "nix-channel --update nixpkgs";
		upgrade = "nix-env -u '*'";
		upgrade_pkg = "nix-env -u ";
		clean = "exit= ";
	}

	else if(pm == "snap") {
		// snap(d)
		search = "snap find ";
		install = "snap install ";
		uninstall = "snap remove ";
		autoremove = "exit=A snap doesn't have orphans";
		update = "exit=snapd does not support this, you may want to upgrade ?";
		upgrade = "snap refresh";
		upgrade_pkg = "snap refresh ";
		clean = "exit=snapd does this automatically after some time";
	}

	else if(pm == "npm") {
		// npm (Global)
		search = "npm search ";
		install = "npm install -g ";
		uninstall = "npm uninstall -g ";
		autoremove = "npm prune";
		update = "exit=npm does not support this, you may want to upgrade ?";
		upgrade = "npm update -g";
		upgrade_pkg = "npm update -g ";
		clean = "npm cache clean --force";
	}
	
	else if(pm == "flatpak") {
		// flatpak (You should checkout the README)
		search = "flatpak search ";
		install = "flatpak install ";
		uninstall = "flatpak uninstall ";
		autoremove = "flatpak uninstall --unused";
		update = "exit=Flatpak does not support this, you may want to upgrade ?";
		upgrade = "flatpak update";
		upgrade_pkg = "flatpak update ";
		clean = "exit=flatpak does not support this";
	}

	else if(pm == "slapt-get") {
		// slapt-get (Slackware)
		search = "slapt-get --search ";
		install = "slapt-get --install ";
		uninstall = "slapt-get --remove ";
		autoremove = "slapt-get --autoremove";	// Hope it works
		update = "slapt-get --update";
		upgrade = "slapt-get --upgrade";
		upgrade_pkg = "slapt-get --upgrade ";	// Hope it works
		clean = "slapt-get --clean && slapt-get --autoclean && slapt-get --remove-obsolete && slapt-get --remove";
	}

	else if(pm == "pip3") {
		// pip3 (python3)
		search = "pip3 search ";
		install = "pip3 install ";
		uninstall = "pip3 uninstall ";
		autoremove = "exit=pip3 does not support this";
		update = "exit=pip3 does not support this";
		upgrade = "exit=pip3 does not support this";
		upgrade_pkg = "pip3 install --upgrade ";
		clean = "exit=pip3 does not support this";
	}

	else if(pm == "guix") {
		// guix
		search = "guix package -s ";
		install = "guix package -i ";
		uninstall = "guix package -r ";
		autoremove = "exit=guix does not support this";
		update = "exit=guix does not support this, you may want to upgrade ?";
		upgrade = "guix package -u";
		upgrade_pkg = "guix package -u ";
		clean = "guix gc";
	}

	else if(pm == "gem") {
		// RubyGems
		search = "gem search ^";
		install = "gem install ";
		uninstall = "gem uninstall ";
		autoremove = "exit=RubyGems does not support this";
		update = "exit=RubyGems does not support this, you may want to upgrade";
		upgrade = "gem update";
		upgrade_pkg = "gem update ";
		clean = "exit=RubyGems does not support this";
	}

	else if(pm == "port") {
		// MacPorts
		search = "port search ";
		install = "port install ";
		uninstall = "port uninstall ";
		autoremove = "port reclaim";
		update = "port sync";
		upgrade = "port upgrade outdated";
		upgrade_pkg = "port upgrade ";
		clean = "exit=MacPorts only supports this per-package";
	}

}

void PackageManager::customPM(string filename) {
	ifstream file(filename);
	string line;
	vector<string> commands;
	int number_of_lines = 0;
	if(file.is_open()) {
		while(getline(file ,line)) {
			commands.push_back(line);
			number_of_lines++;
		}

		if(number_of_lines != 8) {
			search = "exit=Invalid custom file";
			install = "exit=Invalid custom file";
			uninstall = "exit=Invalid custom file";
			autoremove = "exit=Invalid custom file";
			update = "exit=Invalid custom file";
			upgrade = "exit=Invalid custom file";
			upgrade_pkg = "exit=Invalid custom file";
			clean = "exit=Invalid custom file";
		}
		
		else {
			search = commands[0];
			install = commands[1];
			uninstall = commands[2];
			autoremove = commands[3];
			update = commands[4];
			upgrade = commands[5];
			upgrade_pkg = commands[6];
			clean = commands[7];
		}
	}
}
