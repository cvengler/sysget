# sysget

### A front-end for every package manager<br>
sysget is a bridge that lets you use one syntax to every package manager on every unix-based operating system.<br>
You probably all know the problem when you are on a new distro and don't know anything about the package manager. With sysget you just need to remember one syntax for every package manager.<br>
The syntax is mostly same with apt-get so it should be easy to use. <br>
### Supported package managers:
* apt-get
* xbps
* dnf
* yum
* zypper
* eopkg
* pacman
* emerge
* pkg
* chromebrew
* homebrew
* nix
* snap
* npm
* flatpak (See notice)
* slapt-get
* pip3

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
### Add your own package manager
sysget also has the ability that you can add your own paackage manager.<br>
Simply create the file /etc/sysget_custom and then write **8** lines into it.<br>
One line for one command.<br>
The order is: search, install, remove, autoremove, update, upgrade, upgrade_pkg, clean
### Flatpak notice
Flatpak works different than other package managers.<br>
If you want to install a package you need to provide the remote name or the URL of a .flatpakref<br>
**For Example:**<br>
```
sysget install flathub org.gimp.GIMP
```
or
```
sysget install https://flathub.org/repo/appstream/org.gimp.GIMP.flatpakref
```
to install GIMP

###### Credits
[TermGet](https://github.com/termget/termget)
