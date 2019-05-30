# sysget

[![Build Status](https://travis-ci.org/emilengler/sysget.svg?branch=master)](https://travis-ci.org/emilengler/sysget)
### A front-end for every package manager<br>
sysget is a bridge that lets you use one syntax to every package manager on every unix-based operating system.<br>
You probably all know the problem when you are on a new distro and don't know anything about the package manager. With sysget you just need to remember one syntax for every package manager.<br>
The syntax is mostly same with apt-get so it should be easy to use.<br>
### Supported package managers:
* apt
* apt-get (Legacy)
* xbps
* dnf
* yum
* zypper
* eopkg
* pacman
* emerge
* pkg
* pkg_mgr
* chromebrew
* homebrew
* nix
* snap
* npm
* flatpak
* slapt-get
* pip3
* GNU guix
* Ruby gems
* MacPorts
* Your own package manager (See Add your own package manager)

### Features
* search for packages
* install packages
* remove packages
* remove orphans
* clear package manager cache
* update database
* upgrade system
* upgrade single package

### How to install
Please take a look at the docs/ folder.<br>
In a nutshell:<br>
```make && sudo make install```<br>
No dependencies needed

### Example
To search for a package
```
sysget search <search query>
```
To install a package
```
sysget install <package name>
```
To remove a package
```
sysget remove <package name>
```
To update the database
```
sysget update
```
To upgrade the system
```
sysget upgrade
```
To upgrade a specific package
```
sysget upgrade <package name>
```
To remove orphans
```
sysget autoremove
```
To clean the cache of the package manager
```
sysget clean
```
### Environment Variables
| Environment Variable | Function                                                            |
|----------------------|---------------------------------------------------------------------|
| SYSGET_CONFIG_PATH   | Ability to change the path of the sysget config file                |
| SYSGET_CUSTOM_PATH   | Ability to change the path of the file for a custom package manager |
| SYSGET_ARGS_PATH     | Ability to change the path of the for custom arguments              |
### Configuration files
The file where the package manager is stored is located at `/etc/sysget/sysget`<br>
The *optional* file where a custom package manager is stored at `/etc/sysget/custom`<br>
### Add your own package manager
sysget also has the ability that you can add your own paackage manager.<br>
Simply create the file /etc/sysget_custom and then write **8** lines into it.<br>
One line for one command.<br>
The order is: search, install, remove, autoremove, update, upgrade, upgrade_pkg, clean
### Change the sysget syntax
Similar to adding your own package manager you can also modify the syntax of sysget. For example you can give sysget the pacman syntax<br>
Simply create the file `/etc/sysget/args` and add 10 lines to it.
The order is: search, install, remove, autoremove, update, upgrade, clean, set, help, about<br>
However there are some rules:<br>
* The file needs to have 10 lines
* The same item twice is forbidden
###### Credits
[TermGet](https://github.com/termget/termget)
