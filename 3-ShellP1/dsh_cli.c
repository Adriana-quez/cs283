#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dshlib.h"

void printDragon(FILE *fptr) {
    char readStr[128];

    while (fgets(readStr, sizeof(readStr), fptr) != NULL) {
        printf("%s", readStr);
    }

    printf("\n");
}

int openDragon(char *file) {
    FILE *fptr = NULL;

    if ((fptr = fopen(file, "r")) == NULL) {
        printf("error opening file\n");
        return -1;
    }

    printDragon(fptr);

    fclose(fptr);
    return OK;
}

/*
 * Implement your main function by building a loop that prompts the
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.  Since we want fgets to also handle
 * end of file so we can run this headless for testing we need to check
 * the return code of fgets.  I have provided an example below of how
 * to do this assuming you are storing user input inside of the cmd_buff
 * variable.
 *
 *      while(1){
 *        printf("%s", SH_PROMPT);
 *        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
 *           printf("\n");
 *           break;
 *        }
 *        //remove the trailing \n from cmd_buff
 *        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
 *
 *        //IMPLEMENT THE REST OF THE REQUIREMENTS
 *      }
 *
 *   Also, use the constants in the dshlib.h in this code.
 *      SH_CMD_MAX              maximum buffer size for user input
 *      EXIT_CMD                constant that terminates the dsh program
 *      SH_PROMPT               the shell prompt
 *      OK                      the command was parsed properly
 *      WARN_NO_CMDS            the user command was empty
 *      ERR_TOO_MANY_COMMANDS   too many pipes used
 *
 *   Expected output:
 *
 *      CMD_OK_HEADER      if the command parses properly. You will
 *                         follow this by the command details
 *
 *      CMD_WARN_NO_CMD    if the user entered a blank command
 *      CMD_ERR_PIPE_LIMIT if the user entered too many commands using
 *                         the pipe feature, e.g., cmd1 | cmd2 | ... |
 *
 *  See the provided test cases for output expectations.
 */
int main()
{
    char *cmd_buff = malloc(SH_CMD_MAX * sizeof(char));
    command_list_t clist;

    while (1) {
        printf("%s", SH_PROMPT);
        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL) {
            printf("\n");
            break;
        }

        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';

        if (strcmp(cmd_buff, "exit") == 0) {
            exit(0);
        } else if (strcmp(cmd_buff, "dragon") == 0) {
            openDragon("dragon.txt");
        } else {
            build_cmd_list(cmd_buff, &clist);
        }
    }

    return 0;
}