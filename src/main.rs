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

#[macro_use]
extern crate common_failures;
#[macro_use]
extern crate failure;
extern crate sysget;

use sysget::*;

use failure::Fallible;

quick_main!(run);

fn run() -> Fallible<()> {
    let mut it = std::env::args();
    it.next(); // argv[0] is the executable name
    let operation: Operation = it
        .next()
        .ok_or(failure::err_msg("Error, you need an operation"))?
        .parse()?;
    let operands_ = it.collect::<Vec<_>>();
    let operands = operands_.iter().map(|s| s.as_str()).collect::<Vec<_>>();
    if operation.needs_operands() {
        ensure!(
            operands.len() > 0,
            "Error, you need to specify a parameter for {}",
            operation
        );
    }
    PackageManager::from_file_or_interact("/usr/local/share/sysget/config.txt")?
        .operate(operation, operands)
}
