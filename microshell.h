# ifndef MICRO_SHELL_H
# define MICRO_SHELL_H 
# include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>



# define WRITE 1
#define READ 0

typedef struct s_gen
{
    char **args;
    int len;
    int pids;
    char **env;
} t_gen;

void print_tab(char **s);

#endif






