#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

#define count 8000
#define max_vars 100

struct local_var {
    char names[max_vars][500];
    char values[max_vars][500];
};

int main(int argc, char **argv)
{
    char buf[count];
    struct local_var vars;
    int var_count = 0;

    while (1) {
        printf("M-BOT ;) HEHEHEHE $ ");
        fgets(buf, count, stdin);

        buf[strcspn(buf, "\n")] = 0;

        if (strlen(buf) == 0)
            continue;

        if (strchr(buf, '=') != 0 && var_count < max_vars) {
            int i;
            int space_before = 0;
            for (i = 0; buf[i] != '='; i++) {
                if (buf[i] == ' ') {
                    space_before = 1;
                }
                vars.names[var_count][i] = buf[i];
            }
            vars.names[var_count][i] = 0;
            int j;
            i++;
            int space = 0;
            for (j = 0; buf[i] != '\0'; i++, j++) {
                if (buf[i] == ' ') {
                    space = 1;
                }
                vars.values[var_count][j] = buf[i];
            }
            if (space || space_before) {
                printf("Invalid command\n");
                var_count++;
            } else {
                printf("name: %s, value: %s\n", vars.names[var_count],
                       vars.values[var_count]);
                var_count++;
            }
        } else if (buf[0] == '$') {
            for (int m = 0; m < var_count; m++) {
                if (strcmp(vars.names[m], buf + 1) == 0) {
                    printf("%s\n", vars.values[m]);
                    continue;
                }
            }
        } else if (strncmp(buf, "export ", 7) == 0) {
            char env_str[1000];
            for (int m = 0; m < var_count; m++) {
                if (strcmp(vars.names[m], buf + 7) == 0) {
                    sprintf(env_str, "%s=%s", vars.names[m],
                            vars.values[m]);
                    putenv(env_str);
                    printf("Exported: %s\n", buf + 7);
                    break;
                }
            }
        } else if (strncmp(buf, "printenv", 8) == 0) {
            extern char **environ;
            if (strlen(buf) == 8) {
                for (int i = 0; environ[i] != NULL; i++) {
                    printf("%s\n", environ[i]);
                }
            } 
        } else if (strncmp(buf, "echo ", 5) == 0) {
            printf("%s\n", buf + 5);
        } else if (strcmp(buf, "pwd") == 0) {
            if (getcwd(buf, sizeof(buf)) != NULL) {
                printf("%s\n", buf);
            } else {
                printf("pwd: error getting directory\n");
            }
        } else if (strncmp(buf, "cd ", 3) == 0) {
            if (chdir(buf + 3) != 0) {
                printf("cd: cannot change directory\n");
            }
        } else if (strcmp(buf, "exit") == 0) {
            printf("Good Bye :)\n");
            return 0;
        } else if (strncmp(buf, "ls", 2) == 0) {
            char cmd[count];
            strcpy(cmd, buf);

            for (int m = 0; m < var_count; m++) {
                char search[600];
                sprintf(search, "$%s", vars.names[m]);
                char *pos = strstr(cmd, search);

                if (pos != NULL) {
                    char temp[count];
                    int offset = pos - cmd;
                    strncpy(temp, cmd, offset);
                    temp[offset] = 0;
                    strcat(temp, vars.values[m]);
                    strcat(temp, pos + strlen(search));
                    strcpy(cmd, temp);
                }
            }

            if (strchr(cmd, '$') != NULL) {
                printf("not there\n");
            } else {
                char path[500] = ".";
                if (strlen(cmd) > 2) {
                    if (cmd[2] == ' ') {
                        strcpy(path, cmd + 3);
                    }
                }

                DIR *dir = opendir(path);
                if (dir == NULL) {
                    printf("ls: cannot access '%s': No such file or directory\n", path);
                } else {
                    struct dirent *entry;
                    while ((entry = readdir(dir)) != NULL) {
                        if (entry->d_name[0] != '.') {
                            printf("%s\n", entry->d_name);
                        }
                    }
                    closedir(dir);
                }
            }
        } else if (strchr(buf, '<') || strchr(buf, '>') || strstr(buf, "2>")) {
            char cmd_copy[count];
            strcpy(cmd_copy, buf);

            char *input_file = NULL;
            char *output_file = NULL;
            char *error_file = NULL;

            if ((strstr(cmd_copy, "2>")) != NULL) {
                char *ptr = strstr(cmd_copy, "2>");
                *ptr = '\0';
                error_file = ptr + 2;
                while (*error_file == ' ') error_file++;
            }

            if ((strchr(cmd_copy, '>')) != NULL) {
                char *ptr = strchr(cmd_copy, '>');
                *ptr = '\0';
                output_file = ptr + 1;
                while (*output_file == ' ') output_file++;
            }
            pid_t pid = fork();
            if (pid == 0) {
                if (input_file) {
                    int fd_in = open(input_file, O_RDONLY);
                    dup2(fd_in, STDIN_FILENO);
                    close(fd_in);
                }
                if (output_file) {
                    int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd_out, STDOUT_FILENO);
                    close(fd_out);
                }
                if (error_file) {
                    int fd_err = open(error_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    dup2(fd_err, STDERR_FILENO);
                    close(fd_err);
                }

                char *args[100];
                int argc = 0;
                char *token = strtok(cmd_copy, " ");
                while (token != NULL) {
                    args[argc++] = token;
                    token = strtok(NULL, " ");
                }
                args[argc] = NULL;

                execvp(args[0], args);
                exit(-1);
            } else {
                wait(NULL);
            }
        } else {
            printf("Invalid command\n");
        }
    }

    return 0;
}
