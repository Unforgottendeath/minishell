#include "minishell.h"

// int ft_strncmp(char *s1, char *s2, int size)
// {
//     int i = 0;
//     while(s1[i] && s2[i] && i < size - 1 && s1[i] == s2[i])
//         i++;
//     if (s1[i] != s2[i])
//         return (0);
//     return (1);
// }
// int ft_strcmp(char *s1, char *s2)
// {
//     if (!s1 || !s2)
//         return(0);
//     int i = 0;
//     while (s1[i] && s2[i] && s1[i]==s2[i])
//         i++;
//     if (s1[i] != s2[i])
//         return 0;
//     return 1;
// }
// char **get_path(t_hold *content)
// {
//     t_redirect *temp = content->env;
//     while (temp)
//     {
//         if (ft_strncmp(temp->str, "PATH=",5))
//             return ft_split(temp->str + 5, ':');
//         temp = temp->next;
//     }
//     return NULL;
// }
// void free_stuff(char **str)
// {
//     int i = 0;
//     while (str[i])
//         free(str[i++]);
//     free(str);
// }

// char *get_local_path(t_command *command, t_parsed *content)
// {
//     char *joined;
//     char **global_path = get_path(content);
//     if (!global_path)
//         exit(1);
//     int i = 0;
//     while(global_path[i])
//     {
//         char *temp = ft_strjoin(global_path[i], "/");
//         joined = ft_strjoin(temp,command->parsed[0]);
//         free(temp);
//         if (!access(joined, R_OK))
//         {
//             free_stuff(global_path);
//             return joined;
//         }
//         else
//         {
//             free(joined);
//             i++;
//         }
//     }
//     free_stuff(global_path);
//     return NULL;
// }

// void execute_command(t_command *command, t_parsed *content)
// {
//     if (access(command->parsed[0], R_OK))
//     {
//         char *path = get_local_path(command, content);
//         if (!path)
//             exit(1);
//         command->command_path = path;
//     }
//     else
//         command->command_path = ft_strdup(command->parsed[0]);
//     int pid = fork();
//     if (pid == 0)
//     {
//         execve(command->command_path, command->parsed, content->envr);
//         perror("execve");
//         exit(1);
//     }
//     //waitpid(pid, NULL, 0);
// }

// // void handle_export(t_command *data, t_parsed *content)
// // {
// //     if ()
// // }

// // int built_int(t_command *data, t_parsed *content)
// // {
// //     if (strcmp(data->parsed[0],"export") && !strcmp (data->parsed[1], "="))
// //         handle_export (data, content);
// //     else if (strcmp (data->parsed[0], "echo") && strcmp(data->parsed[1], "-n"))
// //         handle_echo(data, content);
// // }

// void execution_on(int fd_in, int fd_out, t_parsed *content)
// {
//     int pipes[2];
//     int pid;
//     t_command *command = content->commands;
    
//     while(command)
//     {
//         pipe(pipes);
//         pid = fork();
//         if (pid == 0)
//         {
//             dup2(fd_in, 0);
// 			if (command->next != NULL)
// 				dup2(pipes[1], 1);
// 			else if (fd_out > 1)
// 				dup2(fd_out, 1);
// 			close(pipes[0]);
// 			close(pipes[1]);
// 			execute_command(command, content);
// 			close(fd_in);
// 			exit(0);
// 		}
// 		else if (pid > 0)
// 		{
// 			close(pipes[1]);
// 			fd_in = pipes[0];
// 		}
//         else
//         {
//             perror("fork");
//             exit(1);
//         }
// 		command = command->next;
//     }
//     if (fd_out > 1)
//         close(fd_out);
//     if (fd_in > 1)
//         close(fd_in);
// }

// void execution_part(int fd_in, int fd_out, t_parsed *content)
// {
//     t_command *temp = content->commands;
//     execution_on(fd_in, fd_out, content);
//     while (temp)
//     {
//         wait(NULL);
//         temp = temp->next;
//     }
// }

// int here_doc(t_redirect *data)
// {
//     int pipes[2];
//     pipe(pipes);
//     char *str;
//     str = readline("> ");
//     while (str && !ft_strcmp(str, data->str))
//     {
//         write(pipes[1], str, ft_strlen(str));
//         free(str);
//         str = readline("> ");
//     }
//     if (str)
//         free(str);
//     close(pipes[1]);
//     return pipes[0];
// }

// void execute_parsed(t_parsed *content)
// {
//     int fd_in;
//     fd_in = 0;
//     if (ft_last(content->input))
//     {
//         if (content->input->flag == 0)
//             fd_in = open(ft_last(content->input)->str, O_RDONLY);
//         else
//             fd_in = here_doc(ft_last(content->input));
//         if (fd_in < 0)
//             perror(ft_last(content->input)->str);
//     }
//     int fd_out;
//     fd_out = 1;
//     if (ft_last(content->output))
//     {
//         if (content->output->flag == 0)
//             fd_out = open(ft_last(content->output)->str, O_WRONLY | O_TRUNC | O_CREAT , 0664);
//         else
//             fd_out = open(ft_last(content->output)->str, O_WRONLY | O_APPEND | O_CREAT, 0664);
//         if (fd_out < 0)
//         {
//             perror(ft_last(content->output)->str);
//             exit(1);
//         }
//     }
//     execution_part(fd_in, fd_out, content);
// }
static int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return 0;
        i++;
    }
    return 1;
}

int is_built_in(char *s)
{
    char *built[]={"export", "cd","echo","env", "unset","exit", "pwd",NULL};
    int i = 0;
    while (built[i])
    {
        if (ft_strcmp(s, built[i]))
            return 1;
        i++;
    }
    return i;
}
char	*ft_get_unique_file(void)
{
	int		fd;
	char	s[11];
	int		i;

	fd = open("/dev/random",O_RDONLY,0777);
	if (fd == -1)
		return (NULL);
	read(fd, s, 10);
	s[11] = 0;
	char *arr = "0123456789abcdef";
	i = 0;
	int n;
	while (i < 10)
	{
		if (s[i] < 0)
			s[i] *= -1;
		s[i] = s[i] % 16;
		n = s[i];
		s[i] = arr[n];
		i++;
	}
	close(fd);
	return (ft_strdup(s));
}
void open_fd(t_node *content)
{
    t_command *current = content->command;
    while (current)
    {
        t_redirect *temp = current->input;
        while (temp && current->exit_status == 0)
        {
            if (temp->flag > 0)
            {
                char *s = ft_get_unique_file();
                int fd = open(s, O_WRONLY | O_CREAT | O_APPEND , 0644);
                free(s);
                char *t = readline("> ");
                while(ft_strcmp(t, temp->str))
                {
                    write(fd, t, ft_strlen(s));
                    write(fd, "\n", 1);
                    free(t);
                    t = readline("> ");
                }
                if (t)
                    free(t);
                close(fd);
                current->fd_in = open(s, O_RDONLY);
                free(temp->str);
                temp->str = s;
            }
            else
            {
                current->fd_in = open(temp->str, O_RDONLY);
                if (current->fd_in < 0)
                {
                    perror("temp->str");
                    current->exit_status = 1;
                }
            }
            temp = temp->next;
        }
        temp = current->output;
        while (temp && current->exit_status == 0)
        {
            if (temp->flag > 0)
            {
                current->fd_out = open(temp->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
                if (current->fd_out < 0)
                {
                    perror("temp->str");
                    current->exit_status = 1;
                }
            }
            else
            {
                current->fd_out = open(temp->str, O_WRONLY | O_CREAT, 0644);
                if (current->fd_out < 0)
                {
                    perror("temp->str");
                    current->exit_status = 1;
                }
            }
            temp = temp->next;
        }
        current = current->next;
    }
}

int ft_lstsize(t_command *command)
{
    t_command *current = command;
    int i =0;
    while(current)
    {
        i++;
        current = current->next;
    }
    return i;
}
char *has_equal(char *str)
{
    int i=0;
    int flag = 0;
    while (str[i])
    {
        if (str[i] == '=')
            flag = 1;
        i++;
    }
    if (flag == 0)
    {
        char *s = ft_strdup("=");
        char *t = ft_strjoin(str, s);
        free(s);
        return t;
    }
    return str;
}
void modify_env(char *str, t_hold **env)
{
    t_hold *current = *env;
    while (current)
    {
        if (ft_strcmp(str, current->str))
        {
            free(current->str);
            current->str = ft_strdup(str);
            return ;
        }
        current = current->next;
    }
    ft_add_env(env, ft_new_env(str));
}
int print_env(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            if (!str[i + 1])
                return 0;
        i++;
    }
    return 1;
}
void handle_export(t_command *content, t_hold *env, t_node *node)
{
    if (content->exit_status == 1)
        return;
    int i = 1;
    while (content->options[i])
    {
        content->options[i] = has_equal(content->options[i]);
        i++;
    }
    if (!content->options[1])
    {
        t_hold *current = env;
        while (current)
        {
            if (print_env(current->str))
            {
                write (content->fd_out,current->str,ft_strlen(current->str));
                write(content->fd_out, "\n",1);
            }
            else
            {
                int i = 0;
                while(current->str[i] != '=')
                {
                    write(content->fd_out, &current->str[i], 1);
                    i++;
                }
                write(content->fd_out, "\n", 1);
            }
            current = current->next;
        }
    }
    else if (ft_lstsize(node->command) == 1)
    {
        int i = 1;
        while (content->options[i])
        {
            modify_env(content->options[i], &env);
            i++;
        }
    }
}
void copy(char *s1, char *s2)
{
    int i = 0;
    while (s1[i])
    {
        s2[i] = s1[i];
        i++;
    }
}
void change_pwd(t_hold **env, char *s1, char *s2)
{
    t_hold *current = *env;
    char *old="OLDPWD=";
    char *new="PWD=";
    while (current)
    {
        if (ft_strcmp(new, current->str))
        {
            copy(current->str + ft_strlen(new), s1);
            free(current->str);
            getcwd(s2,2048);
            current->str = ft_strjoin(ft_strdup(new), ft_strdup(s2));
        }
        current = current->next;
    }
    current = *env;
    while (current)
    {
        if (ft_strcmp(old, current->str))
        {
            free(current->str);
            current->str = ft_strjoin(ft_strdup(old), ft_strdup(s1));
        }
        current = current->next;
    }
}
void handle_cd(t_command *content, t_hold *env, t_node *node)
{
    char s1[2048];
    char s2[2048];
    ft_bzero(s1, 2048);
    ft_bzero(s2,2048);
    if (content->exit_status == 1)
        return;
    if (ft_lstsize(node->command) == 1)
    {
        if (content->options[1])
        {
            chdir(content->options[1]);
            if (chdir(content->options[1]) < 0)
            {
                perror("chdir");
                content->exit_status = 1;
            }
            else
                change_pwd(&env, s1,s2);
        }
        else
            content->exit_status = 1;
    }
}
void handle_env(t_command *content, t_hold *env, t_node *node)
{
    t_hold *current = env;
    while (current)
    {
        if (print_env(current->str))
        {
            write(content->fd_out, content->str, ft_strlen(content->str));
            write(content->fd_out, "\n", 1);
        }
        current = current->next;
    }
}
void handle_echo(t_command *content, t_hold *env, t_node *node)
{
    if (ft_strcmp(content->options[1], "-n"))
        write(content->fd_out, content->options[2],ft_strlen(content->options[2]));
    else
        handle_default(content, env, node);
}
void handle_unset(t_command *content, t_hold *env, t_node *node)
{
    int i = 1;
    while(content->options[i])
    {
        content->options[i] = ft_strjoin(content->options[i], ft_strdup("="));
        t_hold *current = env;
        t_hold *previous = env;
        t_hold *next_node;
        while (current)
        {
            current->next = next_node;
            if (ft_strcmp(current->str, content->options[i]))
            {
                free(current->str);
                free(current);
                previous = next_node;
            }
            else
                previous = next_node;
            current = current->next;
        }
        i++;
    }
}
void handle_exit(t_command *content, t_hold *env, t_node *node)
{
    if (ft_lstsize(node->command) == 1)
    {
        
    }
}
//unset exit pwd
// handle exit status
// handle exit with too amny arguments
// handle exit
void execution(t_node *content, t_hold *env)
{
    open_fd(content);
    void (*build[8])(t_command *content, t_hold *env, t_node *node);
    build[0] = handle_export;
    build[1] = handle_cd;
    build[2] = handle_echo;
    build[3] = handle_env;
    build[4] = handle_unset;
    build[5] = handle_exit;
}