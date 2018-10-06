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

#[derive(Clone, Copy, EnumString, EnumIter, Debug, AsStaticStr)]
#[strum(serialize_all = "snake_case")]
pub enum PackageManager {
    #[strum(serialize = "apt", serialize = "apt-get")]
    Apt,
    Xbps,
    Dnf,
    Yum,
    Zypper,
    Eopkg,
    Pacman,
    Emerge,
    Pkg,
    Chromebrew,
    Homebrew,
    Nix,
    Snap,
}
impl PackageManager {
    pub fn distribution(&self) -> &'static str {
        use self::PackageManager::*;
        match *self {
            Apt => "Debian",
            Xbps => "Void",
            Dnf => "Fedora",
            Yum => "Legacy fedora",
            Zypper => "OpenSUSE",
            Eopkg => "Solus",
            Pacman => "Arch",
            Emerge => "Gentoo",
            Pkg => "FreeBSD",
            Chromebrew => "ChromeOS",
            Homebrew => "MacOS",
            Nix => "NixOS",
            Snap => "Independent",
        }
    }
}
