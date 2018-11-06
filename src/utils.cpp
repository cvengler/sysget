#include "utils.hpp"

bool file_exists(const char *filename) {
	ifstream file(filename);
	return (bool)file;
}

string get_package_manager(string filename) {
	string line;
	string packagemanager;
	ifstream file(filename);

	vector<string> package_manager_list = { "apt-get", "xbps", "dnf", "yum", "zypper", "eopkg", "pacman", "emerge", "pkg", "chromebrew", "homebrew", "nix", "snap", "npm", "flatpak" };

	if(file.is_open()) {
		while(getline(file, line)) {
			//If the package manager is valid
			if(std::find(package_manager_list.begin(), package_manager_list.end(), line) != package_manager_list.end()) {
				return line;
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

void create_conf(string filename, string packagemanager) {
	system("mkdir -p /usr/share/sysget");
	ofstream file(filename);
	if(file.is_open()) {
		file << packagemanager;
                file.close();
	}

	else {
		cout << "Unable to assign package manager, are you root ?" << endl;
		exit(1);
	}
}

//Check will check if the string contains an exit message
void checkcmd(string cmd) {
	size_t errorfind = cmd.find("exit=");
	if(errorfind != string::npos) {
		string errormsg = cmd.substr(5);
		cout << errormsg << endl;
		exit(1);
	}
}
