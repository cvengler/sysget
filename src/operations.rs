// Copyright 2018 Emil Engler <emilstud2015@gmail.com>. All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

use package_managers::*;

#[derive(Copy, Clone, PartialEq, Eq, EnumString, Display, Debug, AsStaticStr)]
#[strum(serialize_all = "snake_case")]
pub enum Operation {
    AutoRemove,
    Clean,
    Install,
    Remove,
    Search,
    Update,
    Upgrade,
    UpgradePkg,
    Help,
}
impl Operation {
    pub fn needs_operands(&self) -> bool {
        use Operation::*;
        match *self {
            UpgradePkg | Install | Search | Remove => true,
            AutoRemove | Upgrade | Update | Clean | Help => false,
        }
    }
    pub fn command_for(&self, pm: &PackageManager) -> Option<&'static str> {
        use Operation::*;
        use PackageManager::*;
        match (*pm, *self) {
            (Apt, AutoRemove) => Some("apt-get autoremove"),
            (Apt, Clean) => Some("apt-get autoclean && apt-get clean"),
            (Apt, Install) => Some("apt-get install"),
            (Apt, Remove) => Some("apt-get remove"),
            (Apt, Search) => Some("apt-cache search"),
            (Apt, Update) => Some("apt-get update"),
            (Apt, Upgrade) => Some("apt-get upgrade"),
            (Apt, UpgradePkg) => Some("apt-get install --only-upgrade"),
            (Xbps, AutoRemove) => Some("xbps-remove -o"),
            (Xbps, Clean) => Some("xbps-remove -O"),
            (Xbps, Install) => Some("xbps-install"),
            (Xbps, Remove) => Some("xbps-remove"),
            (Xbps, Search) => Some("xbps-query -Rs"),
            (Xbps, Update) => Some("xbps-install -S"),
            (Xbps, Upgrade) => Some("xbps-install -Su"),
            (Xbps, UpgradePkg) => Some("xbps-install -u"),
            (Dnf, AutoRemove) => Some("dnf autoremove"),
            (Dnf, Clean) => Some("dnf clean all"),
            (Dnf, Install) => Some("dnf install"),
            (Dnf, Remove) => Some("dnf erase"),
            (Dnf, Search) => Some("dnf search"),
            (Dnf, Update) => Some("dnf clean expire-cache &&& dnf check-update"),
            (Dnf, Upgrade) => Some("dnf update"),
            (Dnf, UpgradePkg) => Some("dnf upgrade"),
            (Yum, AutoRemove) => Some("yum autoremove"),
            (Yum, Clean) => Some("yum clean all"),
            (Yum, Install) => Some("yun install"),
            (Yum, Remove) => Some("yum remove"),
            (Yum, Search) => Some("yum search"),
            (Yum, Update) => Some("yum check-update"),
            (Yum, Upgrade) => Some("yum update"),
            (Yum, UpgradePkg) => Some("yum update"),
            (Zypper, AutoRemove) => Some("zypper rm -u"),
            (Zypper, Clean) => Some("zypper clean"),
            (Zypper, Install) => Some("zypper install"),
            (Zypper, Remove) => Some("zypper remove"),
            (Zypper, Search) => Some("zypper search"),
            (Zypper, Update) => Some("zypper ref"),
            (Zypper, Upgrade) => Some("zypper up"),
            (Zypper, UpgradePkg) => Some("zypper in"),
            (Eopkg, AutoRemove) => Some("eopkg remove-orphans"),
            (Eopkg, Clean) => Some("eopkg delete-cache"),
            (Eopkg, Install) => Some("eopkg install"),
            (Eopkg, Remove) => Some("eopkg remove"),
            (Eopkg, Search) => Some("eopkg search"),
            (Eopkg, Update) => Some("eopkg ur"),
            (Eopkg, Upgrade) => Some("eopkg up"),
            (Eopkg, UpgradePkg) => Some("eopkg up"),
            (Pacman, AutoRemove) => Some("pacman -Rns $(pacman -Qtdq)"),
            (Pacman, Clean) => Some("pacman -Sc"),
            (Pacman, Install) => Some("pacman -S"),
            (Pacman, Remove) => Some("pacman -Rs"),
            (Pacman, Search) => Some("pacman -Ss"),
            (Pacman, Update) => Some("pacman -Syy"),
            (Pacman, Upgrade) => Some("pacman -Syu"),
            (Pacman, UpgradePkg) => Some("pacman -S"),
            (Emerge, AutoRemove) => Some("emerge --depclean -a"),
            (Emerge, Clean) => Some("eclean distfiles"),
            (Emerge, Install) => Some("emerge"),
            (Emerge, Remove) => Some("emerge -C"),
            (Emerge, Search) => Some("emerge -S"),
            (Emerge, Update) => Some("layman -f"),
            (Emerge, Upgrade) => Some("emerge -u world ** emerge -uDN world"),
            (Emerge, UpgradePkg) => Some("emerge -avDuN"),
            (Pkg, AutoRemove) => Some("pkg autoremove"),
            (Pkg, Clean) => Some("pkg clean"),
            (Pkg, Install) => Some("pkg install"),
            (Pkg, Remove) => Some("pkg delete"),
            (Pkg, Search) => Some("pkg search"),
            (Pkg, Update) => Some("pkg update"),
            (Pkg, Upgrade) => Some("pkg upgrade"),
            (Pkg, UpgradePkg) => Some("pkg -f install"),
            (Chromebrew, AutoRemove) => None,
            (Chromebrew, Clean) => None,
            (Chromebrew, Install) => Some("crew install"),
            (Chromebrew, Remove) => Some("crew remove"),
            (Chromebrew, Search) => Some("crew search"),
            (Chromebrew, Update) => None,
            (Chromebrew, Upgrade) => Some("crew upgrade"),
            (Chromebrew, UpgradePkg) => Some("crew upgrade"),
            (Homebrew, AutoRemove) => Some("echo Homebrew does this automatically"),
            (Homebrew, Clean) => Some("echo Homebrew does this automatically"),
            (Homebrew, Install) => Some("brew install"),
            (Homebrew, Remove) => Some("brew uninstall"),
            (Homebrew, Search) => Some("brew search"),
            (Homebrew, Update) => Some("brew update"),
            (Homebrew, Upgrade) => Some("brew upgrade"),
            (Homebrew, UpgradePkg) => Some("brew upgrade"),
            (Nix, AutoRemove) => Some("nix-collect-garbage -d"),
            (Nix, Clean) => None,
            (Nix, Install) => Some("nix-env -i"),
            (Nix, Remove) => Some("nix-env -e"),
            (Nix, Search) => Some("nix search"),
            (Nix, Update) => Some("nix-channel --update nixpkgs"),
            (Nix, Upgrade) => Some("nix-env -u '*'"),
            (Nix, UpgradePkg) => Some("nix-env -u"),
            (Snap, AutoRemove) => Some("echo A snap doesn't have orphans"),
            (Snap, Clean) => Some("echo Snap does this automatically after some time"),
            (Snap, Install) => Some("snap install"),
            (Snap, Remove) => Some("snap remove"),
            (Snap, Search) => Some("snap find"),
            (Snap, Update) => None,
            (Snap, Upgrade) => Some("snap refresh"),
            (Snap, UpgradePkg) => None,
            (_, Help) => None,
        }
    }
}
