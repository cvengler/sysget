# sysget
### A front-end for every package manager

sysget is a bridge that let you use one syntax to every package manager on every operating system.

You probably all know the problem when you are on a new distro and don't know anything about the package manager. With sysget you just need to remember one syntax for every package manager

The syntax is mostly same with apt-get so it should be easy to use

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

```
cargo build --release && install -Dm755 target/release/sysget /usr/local/bin/sysget
```

### Example
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
###### Credits
[TermGet](https://github.com/termget/termget)
