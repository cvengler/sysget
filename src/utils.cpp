#include "utils.hpp"

bool file_exists(const char *filename) {
	ifstream file(filename);
	return (bool)file;
}

vector<string> GetPackageManagerList() {
	vector<string> PackageManagerList = { "apt-get", "xbps", "dnf", "yum", "zypper", "eopkg", "pacman", "emerge", "pkg", "chromebrew", "homebrew", "nix", "snap", "npm", "flatpak", "slapt-get", "pip3" };
	return PackageManagerList;
}

string GetPackageManager(string filename) {
	string line;
	string packagemanager;
	ifstream file(filename);

	vector<string> PackageManagerList = GetPackageManagerList();

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
		cout << "Unable to open config file" << endl;
		exit(1);
	}
	// clang on macOS will return a warning if a non-void function has no return
	return "ERROR";
}

void CreateConf(string filename, string packagemanager) {
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

// Check will check if the string contains an exit message
void checkcmd(string cmd) {
	size_t errorfind = cmd.find("exit=");
	if(errorfind != string::npos) {
		string errormsg = cmd.substr(5);
		cout << errormsg << endl;
		exit(1);
	}
}

// Allows user to change the syntax of sysget
vector<string> CustomArgs(string path) {
	ifstream file(path);
	string line;
	vector<string> args;
	int number_of_lines = 0;
	if(file.is_open()) {
		while(getline(file, line)) {
			number_of_lines++;
			args.push_back(line);
		}

		if(number_of_lines != 10) {
			file.close();
			cout << "Invalid sysget_args file" << endl;
			exit(1);
		}

		else {
			file.close();
			return args;
		}

	}
}

// Check if an item exists in a vector
// Could be useful in future
bool VectorContains(string s, vector<string> v) {
	if(std::find(v.begin(), v.end(), s) != v.end()) {
		return true;
	}

	else {
		return false;
	}

	// If the vector is empty
	if(v.empty()) {
		return false;
	}

	return false;
}