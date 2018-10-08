#include "utils.hpp"

bool file_exists(const char *filename) {
	ifstream file(filename);
	return (bool)file;
}

string read_conf(string filename) {
	string line;
	string packageManager;
	ifstream file(filename);

	if(file.is_open()) {
		while(getline(file, line)) {
			if(line == "apt" || line == "apt-get") {
				packageManager = "apt-get";
			}

			else if(line == "xbps") {
				packageManager = "xbps";
			}

			else if(line == "dnf") {
				packageManager = "dnf";
			}

			else if(line == "yum") {
				packageManager = "yum";
			}

			else if(line == "zypper") {
				packageManager = "zypper";
			}

			else if(line == "eopkg") {
				packageManager = "eopkg";
			}

			else if(line == "pacman") {
				packageManager = "pacman";
			}

			else if(line == "emerge") {
				packageManager = "emerge";
			}

			else if(line == "pkg") {
				packageManager = "pkg";
			}

			else if(line == "chromebrew") {
				packageManager = "chromebrew";
			}

			else if(line == "homebrew") {
				packageManager = "homebrew";
			}

			else if(line == "nix") {
				packageManager = "nix";
			}

			else if(line == "snap") {
				packageManager = "snap";
			}

			else {
				packageManager = "ERROR";
			}
		}
	}

	else {
		cout << "Unable to open config file" << endl;
		exit(1);
	}

	return packageManager;
}

int create_conf(string filename, string packagemanager) {
	system("mkdir -p /usr/local/share/sysget");
	ofstream file(filename);
	if(file.is_open()) {
		file << packagemanager;
	}
	else {
		cout << "Unable to create config, are you root ?" << endl;
		exit(1);
	}
	return 0;
}