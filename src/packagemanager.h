/*
* Copyright (c) 2018-2020 Emil Engler et al.
* Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
* file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <stdlib.h>
#include <string.h>

/* We cannot use a const because of the custom package manager */
typedef struct
{
    char* search;
    char* install;
    char* uninstall;
    char* autoremove;
    char* update;
    char* upgrade;
    char* upgrade_pkg;
    char* clean;
} packagemanager_t;

/* Returns the required packagemanager_t. search is NULL on error */
packagemanager_t pm_init(const char* pm);

#endif
