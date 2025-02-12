#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dshlib.h"

/*
 *  build_cmd_list
 *    cmd_line:     the command line from the user
 *    clist *:      pointer to clist structure to be populated
 *
 *  This function builds the command_list_t structure passed by the caller
 *  It does this by first splitting the cmd_line into commands by spltting
 *  the string based on any pipe characters '|'.  It then traverses each
 *  command.  For each command (a substring of cmd_line), it then parses
 *  that command by taking the first token as the executable name, and
 *  then the remaining tokens as the arguments.
 *
 *  NOTE your implementation should be able to handle properly removing
 *  leading and trailing spaces!
 *
 *  errors returned:
 *
 *    OK:                      No Error
 *    ERR_TOO_MANY_COMMANDS:   There is a limit of CMD_MAX (see dshlib.h)
 *                             commands.
 *    ERR_CMD_OR_ARGS_TOO_BIG: One of the commands provided by the user
 *                             was larger than allowed, either the
 *                             executable name, or the arg string.
 *
 *  Standard Library Functions You Might Want To Consider Using
 *      memset(), strcmp(), strcpy(), strtok(), strlen(), strchr()
 */
int build_cmd_list(char *cmd_line, command_list_t *clist)
{
    if (strlen(cmd_line) == 0) {
        printf(CMD_WARN_NO_CMD);
        return WARN_NO_CMDS;
    }

    char *splitCMD;
    char *outerPipe = NULL;
    char *innerSpace = NULL;

    clist->num = 0;
    
    splitCMD = strtok_r(cmd_line, PIPE_STRING, &outerPipe);

    while (splitCMD != NULL) {
        int exe = 0;
        int argv = 0;

        char *innerSplit = strtok_r(splitCMD, " ", &innerSpace);
        while (innerSplit != NULL) {
            int length = strlen(innerSplit);
            
            if (exe == 0) {
                if (length > EXE_MAX) {
                    return ERR_CMD_OR_ARGS_TOO_BIG;
                }

                strcpy(clist->commands[clist->num].exe, innerSplit);
                ++exe;
            } else {
                if (argv > ARG_MAX) {
                    return ERR_CMD_OR_ARGS_TOO_BIG;
                }

               strcpy(clist->commands[clist->num].args+argv, innerSplit);

                argv += length;
            }

            innerSplit = strtok_r(NULL, " ", &innerSpace);
        }

        clist->num += 1;

        if (clist->num > CMD_MAX) {
            printf(CMD_ERR_PIPE_LIMIT, 8);
            return ERR_TOO_MANY_COMMANDS;
        }

        splitCMD = strtok_r(NULL, PIPE_STRING, &outerPipe);
    }

    printf(CMD_OK_HEADER, clist->num);
    int count = clist->num;

    for (int i=0; i<count; ++i) {
        printf("<%d> %s ", i+1, clist->commands[i].exe);

        if (strlen(clist->commands[i].args) > 2) {
            printf("[%s]\n", clist->commands[i].args);
        } else {
            printf("\n");
        }
    }

    memset (clist->commands, 0, sizeof(clist->commands));
    return OK;
}