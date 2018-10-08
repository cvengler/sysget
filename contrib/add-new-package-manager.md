# Add a new package manager
There are tons of package managers out there. It would be great if you could add one too.

### Steps to add a package manager
1. Add the package manager to the README
2. Add the package manager to the list of availible package managers inside *main.cpp*
3. Append the name of the package manager to the end of the vector package_manager_list which is in *main.cpp*
4. Add the commands to the functions
	* search (For searching packages)				search.cpp
	* install (For installing packages)				install.cpp
	* remove (For removing packages)				remove.cpp
	* autoremove (For removing orphans)				remove.cpp
	* update (For updating the database)			update.cpp
	* upgrade (For upgrading all packages)			update.cpp
	* upgrade_pkg (For upgrading a specifc package)	update.cpp
	* clean (For cleaning the cache)				clean.cpp

5. Add the package manager to the read_conf string inside *utils.cpp*