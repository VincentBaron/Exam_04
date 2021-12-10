# include "microshell.h"


int ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return(i);
}

void ft_putstr_fd(char *s, int fd)
{
    write(fd, s, ft_strlen(s));
}

int error(t_gen *mother, int type)
{
    (void)mother;

    if (type == 1)
        ft_putstr_fd("error: fatal\n", 2);
    return (1);
}


int ft_strncmp(char *s1, char *s2, int len)
{
    int i;

    i = 0;
    while (i < len && s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}

char **create_cmd(char **ptr_cmd, int len)
{
    int i;


}

int execute_command(t_gen *micro, char **args, int len)
{
    int pid;

    pid = fork();
    if (pid < 0)
        return (0);
    else if (pid == 0)
    {
        create_cmds();
        execve()
        error()
        free();
    }
    else
    {
        waitpid(&pid, &status, NULL);
        if (micro->fd_in >= 0)
            close(micro->fd_in);
    }
    return (1);
}

int execute_command_pipe(t_gen *micro, char **args, int len)
{
    (void)micro;
    (void)len;
    /*int pid

    if (fds[ENTRY] != -1)
        close(fds[WRITE]);
    if (fds[READ] != -1)
        close(fds[READ]);
    if (pipe(fds) == -1)
        error();
    pid = fork();
    if (pid == -1)
        error();
    else if (pid == 0)
    {
        close(fds[READ]);
        dup2(fds[WRITE], FD_OUT);
        close(fds[WRITE]);
        execve();
        error();
        free();
    }
    else
    {
        micro->pid++;
        close(fd[WRITE]);
        dup2(fds[READ], STD_IN);
        close(fds[READ]);
    }*/
    ft_putstr_fd(args[0], 1);
    ft_putstr_fd(" with pipe \n", 1);
    return (1);

}

int execution(t_gen *micro)
{
    int i;
    char **head;

    head = micro->args;
    i = 0;
    while (head[i])
    {
        if (ft_strncmp(head[i], ";", 1))
        {
            execute_command(micro, head, i - 1);
            head = &head[i + 1];
            i = 0;
        }
        else if (ft_strncmp(head[i], "|", 1))
        {
            execute_command_pipe(micro, head, i - 1);
            head = &head[i + 1];
            i = 0;
        }
        else
            i++;
    }
    execute_command(micro, head, i - 1);
    return(1);
}


int main (int ac, char **av, char **env)
{
    (void)ac;
    t_gen micro;

    micro.args = &av[1];
    micro.len = ac - 1;
    micro.env = env;
    if (!execution(&micro))
        error(&micro, 1);
    return (1);
}
