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

packagemanager_t get_custom()
{
    packagemanager_t ret = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
    const char* fpath = getenv("SYSGET_CUSTOM_PATH") ? getenv("SYSGET_CUSTOM_PATH") : "/etc/sysget/custom";
    char* content = NULL;
    long fsize = 0L;
    FILE* fp = fopen(fpath, "r");
    /* If we cannot open the file, the user does not want that feature */
    if(!fp)
        return ret;
    /* Otherwise lets read the file */
    /* Get file size */
    fseek(fp, 0L, SEEK_END);
    fsize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    /* Check for overflow, not 100% sure */
    if(fsize < 0)
    {
        fprintf(stderr, "error: Potential overflow, cannot use custom package manager\n");
        return ret;
    }
    /* If file is empty, skip */
    if(!fsize)
    {
        fprintf(stderr, "error: Empty file, cannot use custom package manager\n");
        return ret;
    }
    /* Read the actual file */
    content = malloc(sizeof(char) * (fsize + 1));
    fread(content, 1, fsize, fp);
    content[fsize] = '\0';
    /* Close the file */
    fclose(fp);
    fp = NULL;
    /* Parse the file */
    {
        size_t i;
        /* The start of the line */
        size_t line_start = 0;
        /* The line number */
        size_t line_count = 1;
        /* The current item in ret, we can increment */
        char** cur = &ret.search;
        for(i = 0; i < strlen(content); ++i)
        {
            /* Everything else is irrelevant */
            if(line_count > 8)
                break;
            if(content[i] == '\n' || content[i] == '\0')
            {
                /* Length of line */
                size_t line_len = i - line_start;
                *cur = malloc(sizeof(char) * (line_len + 1));
                if(!*cur)
                {
                    fprintf(stderr, "error: Cannot allocate enough memory\n");
                    free(content);
                    pm_free(&ret);
                    return ret;
                }
                /* Fill cur */
                {
                    size_t j;
                    for(j = 0; j < line_len; ++j)
                        (*cur)[j] = content[j + line_start];
                    (*cur)[j] = '\0';
                }
                line_start = i + 1;
                ++line_count;
                ++cur;
            }
        }
    }
    free(content);
    return ret;
}
