// Copyright (c) 2018-2019 Emil Engler et al.
// Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
// file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "packagemanager.hpp"
#include "utils.hpp"
#include "translation.hpp"

// Use secure_getenv when compiling for linux-gnu, linux-musl doesn't support secure_getenv
#ifdef __GLIBC__
	#define getenv secure_getenv
#endif

extern nlohmann::json lang;
#endif
