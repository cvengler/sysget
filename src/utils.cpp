#include "utils.h"

int clear() {
	system("clear");
}

bool file_exists(const char *filename) {
	ifstream file(filename);
	return (bool)file;
}

string read_conf(string filename) {
	string line;
	ifstream file(filename);

	if(file.is_open()) {
		while(getline(file, line)) {
			if(line == "apt" || line == "apt-get") {
				return "apt-get";
			}

			else if(line == "xbps") {
				return "xbps";
			}

			else if(line == "dnf") {
				return "dnf";
			}

			else if(line == "yum") {
				return "yum";
			}

			else if(line == "zypper") {
				return "zypper";
			}

			else if(line == "eopkg") {
				return "eopkg";
			}

			else if(line == "pacman") {
				return "pacman";
			}

			else if(line == "emerge") {
				return "emerge";
			}

			else if(line == "pkg") {
				return "pkg";
			}

			else if(line == "chromebrew") {
				return "chromebrew";
			}

			else if(line == "homebrew") {
				return "homebrew";
			}

			else if(line == "nix") {
				return "nix";
			}

			else if(line == "snap") {
				return "snap";
			}

			else {
				return "ERROR";
			}
		}
	}

	else {
		cout << "Unable to open config file" << endl;
		exit(1);
	}
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
}