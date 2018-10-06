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

use failure::{self, Fallible};
use operations::*;
use package_managers::*;
use shlex;
use std;
use std::io::{Read, Write};
use strum::AsStaticRef;
use strum::IntoEnumIterator;

pub static USAGE: &str = "Help of sysget
sysget [OPTION] [ARGUMENT]

search [query]\t\tsearch for a package in the resporitories
install [package]\tinstall a package from the repos
remove [package]\tremoves a package
autoremove\t\tremoves not needed packages (orphans)
update\t\t\tupdate the database
upgrade\t\t\tdo a system upgrade
upgrade [package]\tupgrade a specific package
clean\t\t\tclean the download cache
";

pub fn system<'a>(s: impl AsRef<std::ffi::OsStr>, i: Vec<&'a str>) -> Fallible<()> {
    let (arg0, arg1): (&'static str, &'static str) = if cfg!(target_os = "windows") {
        ("cmd", "/C")
    } else {
        ("sh", "-c")
    };

    let mut s = s.as_ref().to_os_string();
    let mut t = String::new();
    for x in i {
        t += " ";
        t += &shlex::quote(x.as_ref());
    }
    s.push(std::ffi::OsString::from(t));
    ensure!(
        std::process::Command::new(arg0)
            .arg(arg1)
            .arg(&s)
            .status()?
            .success(),
        "{:?} failed",
        s
    );
    Ok(())
}
impl PackageManager {
    fn from_file(p: impl AsRef<std::path::Path>) -> Fallible<PackageManager> {
        let mut ret = String::new();
        std::fs::File::open(p)?.read_to_string(&mut ret)?;
        Ok(ret.parse()?)
    }
    fn from_interaction() -> Fallible<PackageManager> {
        let package_managers = PackageManager::iter().collect::<Vec<_>>();
        println!("Please choose a package manager: \n");
        for (i, p) in package_managers.iter().enumerate() {
            println!("{}. {} ({})", i, p.as_static(), p.distribution());
        }
        let x: usize = {
            print!("> ");
            let mut s = String::new();
            std::io::stdin().read_line(&mut s)?;
            s.trim().parse()?
        };
        package_managers
            .get(x - 1)
            .cloned()
            .ok_or(failure::err_msg(format!("Invalid input: {:?}", x)))
    }
    pub fn from_file_or_interact(p: impl AsRef<std::path::Path>) -> Fallible<PackageManager> {
        if std::fs::File::open(&p).is_ok() {
            PackageManager::from_file(p)
        } else {
            Ok({
                let this = PackageManager::from_interaction()?;
                this.to_file(p)?;
                this
            })
        }
    }
    fn to_file(&self, p: impl AsRef<std::path::Path>) -> Fallible<()> {
        Ok(std::fs::OpenOptions::new()
            .write(true)
            .create(true)
            .open(p)?
            .write_fmt(format_args!("{}\n", self.as_static()))?)
    }
    pub fn operate(&self, o: Operation, s: Vec<&str>) -> Fallible<()> {
        if o == Operation::Help {
            println!("{}", USAGE);
            Ok(())
        } else {
            let err_msg = failure::err_msg(format!(
                "{} not implemented for {}",
                o.as_static(),
                self.as_static()
            ));
            Ok(system(o.command_for(&self).ok_or(err_msg)?, s)?)
        }
    }
}
