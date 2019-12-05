// Copyright (c) 2018-2019 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
// file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
#include "utils.hpp"

bool sysget::file_exists(const char *filename) {
	std::ifstream file(filename);
	return (bool)file;
}

std::vector<std::string> sysget::GetPackageManagerList() {
	std::vector<std::string> PackageManagerList = { "apt", "xbps", "dnf", "yum", "zypper", "eopkg", "pacman", "emerge", "pkg", "pkg_mgr", "chromebrew", "homebrew", "nix", "snap", "npm", "flatpak", "slapt-get", "pip3", "guix", "gem", "port" };
	return PackageManagerList;
}

std::string sysget::GetPackageManager(std::string filename) {
	std::string line;
	std::string packagemanager;
	std::ifstream file(filename);

	std::vector<std::string> PackageManagerList = sysget::GetPackageManagerList();

	if(file.is_open()) {
		while(getline(file, line)) {
			// If the package manager is valid
			if(std::find(PackageManagerList.begin(), PackageManagerList.end(), line) != PackageManagerList.end()) {
				return line;
			}

			else {
				return "ERROR";
			}
		}
	}

	else {
		std::cout << sysget::JsonSTR(lang["openconferr"]) << std::endl;
		exit(1);
	}
	// clang on macOS will return a warning if a non-void function has no return
	return "ERROR";
}

void sysget::CreateConf(std::string filename, std::string packagemanager) {
	system("mkdir -p /etc/sysget");
	std::ofstream file(filename);
	if(file.is_open()) {
		file << packagemanager;
	}

	else {
		std::cout << sysget::JsonSTR(lang["assignpkgmanager"]) << std::endl;
		exit(1);
	}
}

// Allows user to change the syntax of sysget
std::vector<std::string> sysget::CustomArgs(std::string path) {
	std::ifstream file(path);
	std::string line;
	std::vector<std::string> args;
	int number_of_lines = 0;
	if(file.is_open()) {
		while(getline(file, line)) {
			number_of_lines++;
			args.push_back(line);
		}

		if(number_of_lines != 10) {
			std::cerr << sysget::JsonSTR(lang["invalidsysget_args"]) << std::endl;
			exit(1);
		}

		else {
			return args;
		}

	}
	return args;
}

// Check if an item exists in a vector
bool sysget::VectorContains(std::string s, std::vector<std::string> v) {
	return std::find(v.begin(), v.end(), s) != v.end();
}
