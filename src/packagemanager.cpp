// Copyright (c) 2018-2019 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the
// accompanying file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
#include "packagemanager.hpp"

// This is the constructor
// void PackageManager::init(std::string pm) {
//   else if (pm == "emerge") {
//     // emerge / portage
//     search = "emerge -S ";
//     install = "emerge --ask ";
//     uninstall = "emerge -C ";
//     autoremove = "emerge --depclean -a";
//     update = "layman -f";
//     upgrade = "emerge --ask -u world && emerge --ask -uDN world";
//     upgrade_pkg = "emerge -avDuN";
//     clean = "eclean distfiles";
//   }
//
//   else if (pm == "pkg") {
//     // pkg (FreeBSD)
//     search = "pkg search ";
//     install = "pkg install ";
//     uninstall = "pkg delete ";
//     autoremove = "pkg autoremove";
//     update = "pkg update";
//     upgrade = "pkg upgrade";
//     upgrade_pkg = "pkg -f install ";
//     clean = "pkg clean";
//   }
//   else if (pm == "pkg_mgr") {
//     // pkg_mgr (OpenBSD)
//     search = "";
//     install = "pkg_add ";
//     uninstall = "pkg_delete ";
//     autoremove = "pkg_delete -a";
//     update = "exit=pkg_mgr does not support this, you may want to upgrade ?";
//     upgrade = "pkg_add -u";
//     upgrade_pkg = "pkg_add -u ";
//     clean = "pkg_delete -a";
//   }
//
//   else if (pm == "chromebrew") {
//     // chromebrew
//     search = "crew search ";
//     install = "crew install ";
//     uninstall = "crew remove ";
//     autoremove = "exit=Chromebrew does not support this";
//     update = "exit=Chromebrew does not support this";
//     upgrade = "crew upgrade";
//     upgrade_pkg = "crew upgrade ";
//     clean = "exit=Chromebrew does not support this";
//   }
//
//   else if (pm == "homebrew") {
//     // homebrew
//     search = "brew search ";
//     install = "brew install ";
//     uninstall = "brew uninstall ";
//     autoremove = "exit=Homebrew does this automatically";
//     update = "brew update";
//     upgrade = "brew upgrade";
//     upgrade_pkg = "brew upgrade ";
//     clean = "exit=Homebrew does this automatically";
//   }
//
//   else if (pm == "nix") {
//     // nix
//     search = "nix search ";
//     install = "nix-env -i ";
//     uninstall = "nix-env -e ";
//     autoremove = "nix-collect-garbage -d";
//     update = "nix-channel --update nixpkgs";
//     upgrade = "nix-env -u '*'";
//     upgrade_pkg = "nix-env -u ";
//     clean = "exit= ";
//   }
//
//   else if (pm == "snap") {
//     // snap(d)
//     search = "snap find ";
//     install = "snap install ";
//     uninstall = "snap remove ";
//     autoremove = "exit=A snap doesn't have orphans";
//     update = "exit=snapd does not support this, you may want to upgrade ?";
//     upgrade = "snap refresh";
//     upgrade_pkg = "snap refresh ";
//     clean = "exit=snapd does this automatically after some time";
//   }
//
//   else if (pm == "npm") {
//     // npm (Global)
//     search = "npm search ";
//     install = "npm install -g ";
//     uninstall = "npm uninstall -g ";
//     autoremove = "npm prune";
//     update = "exit=npm does not support this, you may want to upgrade ?";
//     upgrade = "npm update -g";
//     upgrade_pkg = "npm update -g ";
//     clean = "npm cache clean --force";
//   }
//
//   else if (pm == "flatpak") {
//     // flatpak (You should checkout the README)
//     search = "flatpak search ";
//     install = "flatpak install ";
//     uninstall = "flatpak uninstall ";
//     autoremove = "flatpak uninstall --unused";
//     update = "exit=Flatpak does not support this, you may want to upgrade ?";
//     upgrade = "flatpak update";
//     upgrade_pkg = "flatpak update ";
//     clean = "exit=flatpak does not support this";
//   }
//
//   else if (pm == "slapt-get") {
//     // slapt-get (Slackware)
//     search = "slapt-get --search ";
//     install = "slapt-get --install ";
//     uninstall = "slapt-get --remove ";
//     autoremove = "slapt-get --autoremove"; // Hope it works
//     update = "slapt-get --update";
//     upgrade = "slapt-get --upgrade";
//     upgrade_pkg = "slapt-get --upgrade "; // Hope it works
//     clean = "slapt-get --clean && slapt-get --autoclean && slapt-get "
//             "--remove-obsolete && slapt-get --remove";
//   }
//
//   else if (pm == "pip3") {
//     // pip3 (python3)
//     search = "pip3 search ";
//     install = "pip3 install ";
//     uninstall = "pip3 uninstall ";
//     autoremove = "exit=pip3 does not support this";
//     update = "exit=pip3 does not support this";
//     upgrade = "exit=pip3 does not support this";
//     upgrade_pkg = "pip3 install --upgrade ";
//     clean = "exit=pip3 does not support this";
//   }
//
//   else if (pm == "guix") {
//     // guix
//     search = "guix package -s ";
//     install = "guix package -i ";
//     uninstall = "guix package -r ";
//     autoremove = "exit=guix does not support this";
//     update = "exit=guix does not support this, you may want to upgrade ?";
//     upgrade = "guix package -u";
//     upgrade_pkg = "guix package -u ";
//     clean = "guix gc";
//   }
//
//   else if (pm == "gem") {
//     // RubyGems
//     search = "gem search ^";
//     install = "gem install ";
//     uninstall = "gem uninstall ";
//     autoremove = "exit=RubyGems does not support this";
//     update = "exit=RubyGems does not support this, you may want to upgrade";
//     upgrade = "gem update";
//     upgrade_pkg = "gem update ";
//     clean = "exit=RubyGems does not support this";
//   }
//
//   else if (pm == "port") {
//     // MacPorts
//     search = "port search ";
//     install = "port install ";
//     uninstall = "port uninstall ";
//     autoremove = "port reclaim";
//     update = "port sync";
//     upgrade = "port upgrade outdated";
//     upgrade_pkg = "port upgrade ";
//     clean = "exit=MacPorts only supports this per-package";
//   }
// }

CustomPackageManager *PackageManager::customPM(std::string filename) {
  std::ifstream file(filename);
  std::string line;
  std::vector<std::string> commands;
  int number_of_lines = 0;
  if (!file.is_open()) {
    return nullptr;
  }
  while (getline(file, line)) {
    commands.push_back(line);
    number_of_lines++;
  }

  if (number_of_lines != 8) {
    return nullptr;
  }
  return new CustomPackageManager(filename, commands[0], commands[1],
                                  commands[2], commands[3], commands[4],
                                  commands[5], commands[6], commands[7]);
}
