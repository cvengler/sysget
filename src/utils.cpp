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

// Check if an item exists twice in the file
void CheckCustomArgs(vector<string> args) {
	vector<string> already_known;
	for(int i = 0; i < args.size(); i++) {
		already_known.push_back(args[i]);
	}

	for(int i = 0; i < already_known.size(); i++) {
		if(std::find(already_known.begin(), already_known.end(), args[i]) != already_known.end()) {
			cout << "The same item in the sysget_args file twice is forbidden" << endl;
			exit(1);
		}
		else {
			// Valid if the index is the same
			if(args[i] == already_known[i]) {
				continue;
			}

			else {
				cout << "The same item in the sysget_args file is twice is forbidden" << endl;
				exit(1);
			}
		}
	}
}

// Set the vector to the default commands
vector<string> DefaultArgs() {
	vector<string> defaultargs;
	defaultargs.push_back("search");
	defaultargs.push_back("install");
	defaultargs.push_back("remove");
	defaultargs.push_back("autoremove");
	defaultargs.push_back("update");
	defaultargs.push_back("upgrade");
	defaultargs.push_back("clean");
	defaultargs.push_back("set");
	defaultargs.push_back("help");
	defaultargs.push_back("about");
	return defaultargs;
}