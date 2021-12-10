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
    char **cmd;

    if (!(cmd = (char**)malloc(sizeof(char) * (len + 1))))
        return (NULL);
    i = 0;
    while (i < len)
    {
        cmd[i] = ptr_cmd[i];
        i++;
    }
    cmd[i] = NULL;
    return (cmd);
}

void print_tab(char **s)
{
    int i;

    i = 0;
    while (s[i])
    {
        printf("tab[%i]: %s\n", i, s[i]);
        i++;
    }
}

int execute_command(t_gen *micro, char **args, int len)
{
    pid_t pid;
    int exit_stat;
    char **cmd;

   cmd = NULL;
    pid = fork();
    if (pid < 0)
        return (0);
    else if (pid == 0)
    {
        cmd = create_cmd(args, len);
        execve(cmd[0], cmd, micro->env);
        ft_putstr_fd("error: cannot execute ", 2);
        ft_putstr_fd(cmd[0], 2);
        ft_putstr_fd("\n", 2);
        //free();
    }
    else
        waitpid(pid, &exit_stat, 0);
    return (1);
}

int execute_command_pipe(t_gen *micro, char **args, int len)
{
    pid_t pid;
    int exit_stat;

    
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
        cmd = create_cmd(args, len);
        execve(cmd[0], cmd, micro->env);
        ft_putstr_fd("error: cannot execute ", 2);
        ft_putstr_fd(cmd[0], 2);
        ft_putstr_fd("\n", 2);
        //free();
    }
    else
        micro->pid++;
        close(fd[WRITE]);
        dup2(fds[READ], STD_IN);
        close(fds[READ]);
    }
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
            execute_command(micro, head, i);
            head = &head[i + 1];
            i = 0;
        }
        else if (ft_strncmp(head[i], "|", 1))
        {
            execute_command_pipe(micro, head, i);
            head = &head[i + 1];
            i = 0;
        }
        else
            i++;
    }
    execute_command(micro, head, i);
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
