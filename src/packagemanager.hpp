// Copyright (c) 2018-2019 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the
// accompanying file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
/*
NOTE: If a string begins with an "exit=" it means that it is not availible.
Everything after the '=' is the error message NOTE: Spaces are VERY important
because we need them to append other strings to them
*/

struct CustomPackageManager;

struct PackageManager {
  virtual std::string name() = 0;
  virtual std::string search(std::string arg) {
    return name() + " search " + arg;
  }
  virtual std::string install(std::string arg) {
    return name() + " install " + arg;
  }
  virtual std::string uninstall(std::string arg) {
    return name() + " uninstall " + arg;
  }
  virtual std::string autoremove() { return name() + " autoremove"; }
  virtual std::string update() { return name() + " update"; }
  virtual std::string upgrade() { return name() + " upgrade"; }
  virtual std::string upgradePkg(std::string arg) {
    return name() + " upgrade " + arg;
  }
  virtual std::string clean() { return name() + " clean"; }
  static CustomPackageManager *customPM(std::string filename);
};

struct CustomPackageManager : public PackageManager {
  CustomPackageManager(std::string name, std::string search,
                       std::string install, std::string uninstall,
                       std::string autoremove, std::string update,
                       std::string upgrade, std::string upgrade_pkg,
                       std::string clean)
      : name_(name), search_(search), install_(install), uninstall_(uninstall),
        autoremove_(autoremove), update_(update), upgrade_(upgrade),
        upgrade_pkg_(upgrade_pkg), clean_(clean) {}

  // Check will check if the user-supplied string contains an exit message
  std::string checkcmd(std::string cmd) {
    size_t errorfind = cmd.find("exit=");
    if (errorfind != std::string::npos) {
      std::string errormsg = cmd.substr(5);
      std::cerr << errormsg << std::endl;
      ::exit(1);
    }
    return cmd;
  }
  std::string name() { return checkcmd(name_); }
  std::string search(std::string arg) { return checkcmd(search_) + " " + arg; }
  std::string install(std::string arg) {
    return checkcmd(install_) + " " + arg;
  }
  std::string uninstall(std::string arg) {
    return checkcmd(uninstall_) + " " + arg;
  }
  std::string autoremove() { return checkcmd(autoremove_); }
  std::string update() { return checkcmd(update_); }
  std::string upgrade() { return checkcmd(upgrade_); }
  std::string upgradePkg(std::string arg) {
    return checkcmd(upgrade_pkg_) + " " + arg;
  }
  std::string clean() { return checkcmd(clean_); }

private:
  std::string name_;
  std::string search_;
  std::string install_;
  std::string uninstall_;
  std::string autoremove_;
  std::string update_;
  std::string upgrade_;
  std::string upgrade_pkg_;
  std::string clean_;
};

struct AptPackageManager : public PackageManager {
  std::string name() { return "apt"; }

  std::string uninstall(std::string arg) { return "apt purge " + arg; }
  std::string autoremove() { return "apt purge --autoremove"; }
  std::string clean() { return "apt autoclean && apt clean"; }
};

struct XbpsPackageManager : public PackageManager {
  std::string name() { return "xbps"; }

  std::string search(std::string arg) { return "xbps-query -Rs " + arg; }
  std::string install(std::string arg) { return "xbps-install " + arg; }
  std::string uninstall(std::string arg) { return "xbps-remove " + arg; }
  std::string autoremove() { return "xbps-remove -o"; }
  std::string update() { return "xbps-install -S"; }
  std::string upgrade() { return "xbps-install -Su"; }
  std::string upgradePkg(std::string arg) { return "xbps-install -u " + arg; }
  std::string clean() { return "xbps-remove -O "; }
};

struct DnfPackageManager : public PackageManager {
  std::string name() { return "dnf"; }

  std::string uninstall(std::string arg) { return "dnf erase " + arg; }
  std::string update() {
    return "dnf clean expire-cache && sudo dnf check-update";
  }
  std::string upgrade() { return "dnf update"; }
  std::string clean() { return "dnf clean all"; }
};

struct YumPackageManager : public PackageManager {
  std::string name() { return "yum"; }

  std::string uninstall(std::string arg) { return "yum erase " + arg; }
  std::string update() { return "yum check-update"; }
  std::string upgrade() { return "yum update"; }
  std::string clean() { return "yum clean all"; }
};

struct ZypperPackageManager : public PackageManager {
  std::string name() { return "zypper"; }

  std::string uninstall(std::string arg) { return "zypper remove " + arg; }
  std::string autoremove() { return "zypper rm -u"; }
  std::string update() { return "zypper refresh zypper ref"; }
  std::string upgrade() { return "zypper up"; }
  std::string upgradePkg(std::string arg) { return "zypper in " + arg; }
};

struct EopkgManager : public PackageManager {
  std::string name() { return "eopkg"; }

  std::string uninstall(std::string arg) { return "eopkg remove " + arg; }
  std::string autoremove() { return "eopkg remove-orphans"; }
  std::string update() { return "eopkg ur"; }
  std::string clean() { return "eopkg delete-cache"; }
};

struct PacmanManager : public PackageManager {
    std::string name() { return "pacman"; }

    std::string search(std::string arg) { return "pacman -Ss " + arg; }
    std::string install(std::string arg) { return "pacman -S " + arg; }
    std::string uninstall(std::string arg) { return "pacman -Rs " + arg; }
    std::string autoremove() { return "pacman -Rns $(pacman -Qtdq)"; }
    std::string update() { return "pacman -Syy"; }
    std::string upgrade() { return "pacman -Syu"; }
    std::string upgradePkg(std::string arg) { return install(arg); }
    std::string clean() { return "pacman -Sc"; }
};

#endif
