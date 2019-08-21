#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "packagemanager.hpp"
#include "utils.hpp"
#include "translation.hpp"

// Use secure_getenv when compiling for Linux
#ifdef __linux__
	#define getenv secure_getenv
#endif

extern json lang;
#endif