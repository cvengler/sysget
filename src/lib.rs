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

#![deny(warnings)]
#[macro_use]
extern crate failure;
extern crate strum;
#[macro_use]
extern crate strum_macros;
extern crate shlex;

pub mod operations;
pub mod package_managers;
mod utils;
pub use operations::*;
pub use package_managers::*;
