/*
* Copyright (c) 2018-2020 Emil Engler et al.
* Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
* file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "packagemanager.h"

packagemanager_t pm_init(const char* pm)
{
    packagemanager_t ret = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
    if(strcmp(pm, "apt") == 0)
    {
        ret.search = "apt search ";
        ret.install = "apt install ";
        ret.uninstall = "apt purge ";
        ret.autoremove = "apt purge --autoremove";
        ret.update = "apt update";
        ret.upgrade = "apt upgrade";
        ret.upgrade_pkg = "apt upgrade ";
        ret.clean = "apt clean";
        return ret;
    }
    else if(strcmp(pm, "xbps") == 0)
    {
        ret.search = "xbps-query -Rs ";
        ret.install = "xbps-install ";
        ret.uninstall = "xbps-remove ";
        ret.autoremove = "xbps-remove -o";
        ret.update = "xbps-install -S";
        ret.upgrade = "xbps-install -Su";
        ret.upgrade_pkg = "xbps-install -u ";
        ret.clean = "xbps-remove -O";
        return ret;
    }
    else if(strcmp(pm, "dnf") == 0)
    {
        ret.search = "dnf search ";
        ret.install = "dnf install ";
        ret.uninstall = "dnf erase ";
        ret.autoremove = "dnf autoremove";
        ret.update = "dnf clean expire-cache && sudo dnf check-update";
        ret.upgrade = "dnf update";
        ret.upgrade_pkg = "dnf upgrade ";
        ret.clean = "dnf clean all";
        return ret;
    }
    else if(strcmp(pm, "yum") == 0)
    {
        ret.search = "yum search ";
        ret.install = "yum install ";
        ret.uninstall = "yum erase ";
        ret.autoremove = "yum autoremove";
        ret.update = "yum check-update";
        ret.upgrade = "yum update";
        ret.upgrade_pkg = "yum update ";
        ret.clean = "yum clean all";
        return ret;
    }
    else if(strcmp(pm, "zypper") == 0)
    {
        ret.search = "zypper search ";
        ret.install = "zypper install ";
        ret.uninstall = "zypper remove ";
        ret.autoremove = "zypper rm -u";
        ret.update = "zypper refresh zypper ref";
        ret.upgrade = "zypper up";
        ret.upgrade_pkg = "zypper in ";
        ret.clean = "zypper clean";
        return ret;
    }
    else if(strcmp(pm, "eopkg") == 0)
    {
        ret.search = "eopkg search ";
        ret.install = "eopkg install ";
        ret.uninstall = "eopkg remove ";
        ret.autoremove = "eopkg remove-orphans";
        ret.update = "eopkg ur";
        ret.upgrade = "eopkg upgrade";
        ret.upgrade_pkg = "eopkg upgrade ";
        ret.clean = "eopkg delete-cache";
        return ret;
    }
    else if(strcmp(pm, "pacman") == 0)
    {
        ret.search = "pacman -Ss ";
        ret.install = "pacman -S ";
        ret.uninstall = "pacman -Rs ";
        ret.autoremove = "pacman -Rns $(pacman -Qtdq)";
        ret.update = "pacman -Syy";
        ret.upgrade = "pacman -Syu";
        ret.upgrade_pkg = "pacman -S ";
        ret.clean = "pacman -Sc";
        return ret;
    }
    else if(strcmp(pm, "emerge") == 0)
    {
        ret.search = "emerge -S ";
        ret.install = "emerge --ask ";
        ret.uninstall = "emerge -C ";
        ret.autoremove = "emerge --depclean -a";
        ret.update = "layman -f";
        ret.upgrade = "emerge --ask -u world && emerge --ask -uDN world";
        ret.upgrade_pkg = "emerge -avDuN ";
        ret.clean = "eclean distfiles";
        return ret;
    }
    else if(strcmp(pm, "pkg") == 0)
    {
        ret.search = "pkg search ";
        ret.install = "pkg install ";
        ret.uninstall = "pkg delete ";
        ret.autoremove = "pkg autoremove";
        ret.update = "pkg update";
        ret.upgrade = "pkg upgrade";
        ret.upgrade_pkg = "pkg -f install ";
        ret.clean = "pkg clean";
        return ret;
    }
    else if(strcmp(pm, "pkg_mgr") == 0)
    {
        ret.search = "pkg_info ";
        ret.install = "pkg_add ";
        ret.uninstall = "pkg_delete ";
        ret.autoremove = "pkg_delete -a";
        ret.upgrade = "pkg_add -u";
        ret.upgrade_pkg = "pkg_add -u ";
        ret.clean = "pkg_delete -a";
        return ret;
    }
    else if(strcmp(pm , "homebrew") == 0)
    {
        ret.search = "brew search ";
        ret.install = "brew install ";
        ret.uninstall = "brew uninstall ";
        ret.update = "brew update";
        ret.upgrade = "brew upgrade";
        ret.upgrade_pkg = "brew upgrade ";
        ret.clean = NULL;
        return ret;
    }
    else if(strcmp(pm, "nix") == 0)
    {
        ret.search = "nix search ";
        ret.install = "nix-env -i ";
        ret.uninstall = "nix-env -e ";
        ret.autoremove = "nix-collect-garbage -d";
        ret.update = "nix-channel --update nixpkgs";
        ret.upgrade = "nix-env -u '*'";
        ret.upgrade_pkg = "nix-env -u ";
        ret.clean = NULL;
        return ret;
    }
    else if(strcmp(pm, "snap") == 0)
    {
        ret.search = "snap find ";
        ret.install = "snap install ";
        ret.uninstall = "snap remove ";
        ret.upgrade = "snap refresh";
        ret.upgrade_pkg = "snap refresh ";
        ret.clean = "npm cache clean --force";
        return ret;
    }
    else if(strcmp(pm, "npm") == 0)
    {
        ret.search = "npm search ";
        ret.install = "npm install -g ";
        ret.uninstall = "np, uninstall -g ";
        ret.autoremove = "npm prune";
        ret.upgrade = "npm update -g";
        ret.upgrade_pkg = "npm update -g ";
        ret.clean = "npm cache clean --force";
        return ret;
    }
    else if(strcmp(pm, "flatpak") == 0)
    {
        ret.search = "flatpak search ";
        ret.install = "flatpak install ";
        ret.uninstall = "flatpak uninstall ";
        ret.autoremove = "flatpak uninstall --unused";
        ret.upgrade = "flatpak update";
        ret.upgrade_pkg = "flatpak update ";
        return ret;
    }
    else if(strcmp(pm, "slapt-get") == 0)
    {
        ret.search = "slapt-get --search ";
        ret.install = "slapt-get --install ";
        ret.uninstall = "slapt-get --remove ";
        ret.autoremove = "slapt-get --autoremove";
        ret.update = "slapt-get --update";
        ret.upgrade = "slapt-get --upgrade";
        ret.upgrade_pkg = "slapt-get --upgrade ";
        ret.clean = "slapt-get --clean && slapt-get --autoclean && slapt-get --remove-obsolete && slapt-get --remove";
        return ret;
    }
    else if(strcmp(pm, "pip3") == 0)
    {
        ret.search = "pip3 search ";
        ret.install = "pip3 install ";
        ret.uninstall = "pip3 uninstall ";
        return ret;
    }
    else if(strcmp(pm, "guix") == 0)
    {
        ret.search = "guix package -s ";
        ret.install = "guix package -i ";
        ret.uninstall = "guix package -r ";
        ret.upgrade = "guix package -u";
        ret.upgrade_pkg = "guix package -u ";
        ret.clean = "guix gc";
        return ret;
    }
    else if(strcmp(pm, "gem") == 0)
    {
        ret.search = "gem search ^";
        ret.install = "gem install ";
        ret.uninstall = "gem uninstall ";
        ret.upgrade = "gem update";
        ret.upgrade_pkg = "gem update ";
        ret.clean = "exit=RubyGems does not support this";
        return ret;
    }
    else if(strcmp(pm, "port") == 0)
    {
        ret.search = "port search ";
        ret.install = "port install ";
        ret.uninstall = "port uninstall ";
        ret.autoremove = "port reclaim";
        ret.update = "port sync";
        ret.upgrade = "port upgrade outdated";
        ret.upgrade_pkg = "port upgrade ";
        return ret;
    }
    return ret;
}
