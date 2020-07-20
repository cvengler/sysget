/*
* Copyright (c) 2018-2020 Emil Engler et al.
* Distributed under the GNU GENERAL PUBLIC LICENSE Version 3, see the accompanying
* file LICENSE.txt or <https://www.gnu.org/licenses/gpl-3.0.html>.
*/

#include "config.h"

char* get_pm()
{
    /* A 9 len str is enough */
    char* ret = malloc(sizeof(char) * 10);
    const char* fpath = getenv("SYSGET_CONFIG_PATH") ? getenv("SYSGET_CONFIG_PATH") : "/etc/sysget/sysget";
    char c;
    int len = 0;
    FILE* fp = fopen(fpath, "r");
    if(!ret)
    {
        fprintf(stderr, "error: Cannot allocate enough memory\n");
        return NULL;
    }
    if(!fp)
    {
        fprintf(stderr, "error: Cannot open %s\n", fpath);
        free(ret);
        return NULL;
    }
    /* Read file char by char */
    while((c = fgetc(fp)) != EOF)
    {
        ++len;
        if(len > 9)
        {
            fclose(fp);
            fprintf(stderr, "error: Invalid package manager in %s\n", fpath);
            free(ret);
            return NULL;
        }
        if(c == '\n')
            break;
        ret[len-1] = c;
    }
    ret[len] = '\0';
    fclose(fp);
    return ret;
}
