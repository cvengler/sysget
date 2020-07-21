/*
* Copyright (c) 2018-2020 Emil Engler et al.
* Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
* file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>

#include "packagemanager.h"

/* Get the package manager name */
char* get_pm();
/* Get a custom config */
packagemanager_t get_custom();

#endif
