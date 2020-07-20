/*
* Copyright (c) 2018-2020 Emil Engler et al.
* Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
* file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
*/

#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <stdlib.h>
#include <string.h>

typedef struct
{
    const char* search;
    const char* install;
    const char* uninstall;
    const char* autoremove;
    const char* update;
    const char* upgrade;
    const char* upgrade_pkg;
    const char* clean;
} packagemanager_t;

/* Returns the required packagemanager_t. search is NULL on error */
packagemanager_t pm_init(const char* pm);

#endif
