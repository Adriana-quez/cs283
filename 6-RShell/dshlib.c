#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "dshlib.h"

int execute_pipeline(command_list_t *clist) {
    int num_commands = clist->num;
    int pipes[num_commands - 1][2];
    pid_t pids[num_commands];

    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipes[i]) == -1) {
            return ERR_MEMORY;
        }
    }

    for (int i = 0; i < num_commands; i++) {
        pids[i] = fork();
        
        if (pids[i] == -1) {
            return ERR_MEMORY;
        }

        if (pids[i] == 0) {
            if (i > 0) {
                dup2(pipes[i-1][0], STDIN_FILENO);
            }

            if (i < num_commands - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < (num_commands - 1); ++j) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            if (execvp(clist->commands[i].argv[0], clist->commands[i].argv) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
    }

    for (int i = 0; i < (num_commands - 1); ++i) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < num_commands; ++i) {
        waitpid(pids[i], NULL, 0);
    }

    return OK;
}

int build_cmd_buff(char *cmd_line, cmd_buff_t *cmd_buff) {
    char *innerSpace = NULL;
    cmd_buff->_cmd_buffer = malloc(strlen(cmd_line) + 1);

    if (cmd_buff->_cmd_buffer == NULL) {
        return ERR_MEMORY;
    }

    strcpy(cmd_buff->_cmd_buffer, cmd_line);
    
    char *token = strtok_r(cmd_line, " ", &innerSpace);
    int argc = 0;

    while (token != NULL && argc < CMD_ARGV_MAX) {
        cmd_buff->argv[argc++] = token;
        token = strtok_r(NULL, " \t", &innerSpace);
    }

    cmd_buff->argv[argc++] = NULL;
    cmd_buff->argc = (argc - 1);
    return OK;
}

int build_cmd_list(char *cmd_line, command_list_t *clist) {
    clist->num = 0;
    char *outerPipe = NULL;

    char *token = strtok_r(cmd_line, PIPE_STRING, &outerPipe);

    while (token != NULL && clist->num < CMD_MAX) {
        cmd_buff_t *cmd_buff = &clist->commands[clist->num];
        
        if (build_cmd_buff(token, cmd_buff) != OK) {
            return ERR_MEMORY;
        }

        clist->num++;
        token = strtok_r(NULL, PIPE_STRING, &outerPipe);
    }
    return OK;
}

/**** 
 **** FOR REMOTE SHELL USE YOUR SOLUTION FROM SHELL PART 3 HERE
 **** THE MAIN FUNCTION CALLS THIS ONE AS ITS ENTRY POINT TO
 **** EXECUTE THE SHELL LOCALLY
 ****
 */

/*
 * Implement your exec_local_cmd_loop function by building a loop that prompts the 
 * user for input.  Use the SH_PROMPT constant from dshlib.h and then
 * use fgets to accept user input.
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
 *      ERR_MEMORY              dynamic memory management failure
 * 
 *   errors returned
 *      OK                     No error
 *      ERR_MEMORY             Dynamic memory management failure
 *      WARN_NO_CMDS           No commands parsed
 *      ERR_TOO_MANY_COMMANDS  too many pipes used
 *   
 *   console messages
 *      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
 *      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
 *      CMD_ERR_EXECUTE        print on execution failure of external command
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 1+)
 *      malloc(), free(), strlen(), fgets(), strcspn(), printf()
 * 
 *  Standard Library Functions You Might Want To Consider Using (assignment 2+)
 *      fork(), execvp(), exit(), chdir()
 */
int exec_local_cmd_loop() {
    char *cmd_buff = malloc(SH_CMD_MAX);
    int rc = 0;
    command_list_t clist;
    if (cmd_buff == NULL) {
        return ERR_MEMORY;
    }

    while (1) {
        printf("%s", SH_PROMPT);
        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL) {
            printf("\n");
            break;
        }

        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';

        if (cmd_buff[0] == '\0') {
            continue;
        }

        rc = build_cmd_list(cmd_buff, &clist);

        if (rc == 0) {
            for (int i = 0; i < clist.num; i++)
            {
                if (strcmp(clist.commands[i].argv[0], "exit") == 0) {
                    free(cmd_buff);
                    return OK;
                } else if (strcmp(clist.commands[i].argv[0], "dragon") == 0) {
                    FILE *fptr = NULL;
                        
                    if ((fptr = fopen("dragon.txt", "r")) == NULL) {
                        printf("error opening file\n");
                        return -1;
                    }
                        
                    char readStr[128];
                    
                    while (fgets(readStr, sizeof(readStr), fptr) != NULL) {
                        printf("%s", readStr);
                    }
                    printf("\n");
                    
                    fclose(fptr);
                } else if (strcmp(clist.commands[i].argv[0], "cd") == 0) {
                    if (clist.commands[i].argc >= 2) {
                        if (chdir(clist.commands[i].argv[1]) != 0) {
                            return WARN_NO_CMDS;
                        }
                    }
                } else {
                    execute_pipeline(&clist);
                    break;
                }
            }
        }
    }
   
    free(cmd_buff);
    return OK;
}