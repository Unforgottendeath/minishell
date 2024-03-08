#include "minishell.h"

void    ft_handle_sigint(int sig)
{
    if (sig != SIGINT)
        return;
    printf("\n");
    rl_replace_line("",0);
    rl_on_new_line();
    rl_redisplay();
}

void    ft_signals(void)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, ft_handle_sigint);
}

void initialize_env(t_hold **lst, char **env)
{
    int i = 0;
    while (env[i])
        ft_add_env(lst, ft_new_env(env[i++]));
}

static int escape_quote (char *s, int i)
{
    if (s[i] == '"')
    {
        i++;
        while (s[i] != '"' && s[i])
            i++;
        if (!s[i])
            return -1;
        else
            i++;
    }
    else if (s[i] == '\'')
    {
        i++;
        while (s[i] != '\'' && s[i])
            i++;
        if (!s[i])
            return -1;
        else
            i++;
    }
    return i;
}

int check_pipe(char *s, int i)
{
    if (s[i] == '|')
    {
        i++;
        while (s[i] == ' ')
            i++;
        if (!s[i])
            return -1;
    }
    return i;
}

int join_line(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
        {
            if (escape_quote(s, i) > 0)
                i = escape_quote(s, i);
            else
                return (0);
        }
        else if (s[i] == '|')
        {
            if (check_pipe(s, i) < 0)
                return 0;
            else
                i = check_pipe(s, i);
        }
        else if (s[i])
            i++;
    }
    return 1;
}

int is_cursed(char c)
{
    if (c == '|' || c == '&' || c == '-' || c == '>' || c == '<')
        return 1;
    return 0;
}
int find_export(char *str)
{
    int i = 0;
    char *s = "export";
    while (str[i])
    {
        int k = 0;
        while(str[i+k] && s[k] && str[i + k] == s[k])
            k++;
        if (!s[k] && str[i + k] == ' ')
            return i;
        i++;
    }
    return -1;
}
int check_2(char *str)
{
    int i = 0;
    while ( str[i])
    {
        if (find_export(str + i) >= 0)
        {
            i = find_export(str + i) + ft_strlen("export");
            while (str[i] && str[i] != '=')
                i++;
            if (str[i] == '=' && str[i - 1] == ' ')
                return 0;
        }
        if (str[i])
            i++;
    }
    return 1;
}

int check_line(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (i == 0 && str[i] == '|')
            return 0;
        if (str[i] == '>')
        {
            i++;
            if (str[i] && str[i] != '>' && is_cursed(str[i]))
                return 0;
            while (str[i] == ' ' || str[i] == '>')
            {
                if (str[i] == ' ' && (str[i + 1] == '<' || str[i + 1] == '>' || str[i + 1] == '|'))
                    return 0;
                if (str[i] == '>')
                    count++;
                i++;
            }
            if (count > 1)
                return 0;
        }
        else if (str[i] == '<')
        {
            i++;
            if (str[i] && str[i] != '<' && is_cursed(str[i]))
                return 0;
            while (str[i] == ' ' || str[i] == '<')
            {
                if (str[i] == ' ' && (str[i + 1] == '<' || str[i + 1] == '>' || str[i + 1] == '|'))
                    return 0;
                if (str[i] == '<')
                    count++;
                i++;
            }
            if (count > 1)
                return 0;
        }
        else if (str[i] == '|')
        {
            i++;
            count = 0;
            while (str[i] == ' ')
                i++;
            if (str[i] == '|')
                return 0;
        }
        if (str[i])
            i++;
    }
    if (!check_2(str))
        return 0;
    return 1;
}

int main(int ac, char **av, char **envr)
{
    (void)ac;
    (void)**av;
    t_node *node = NULL;
    ft_add_node(&node, ft_new_node());
    t_hold *env = NULL;
    ft_signals();
    initialize_env(&env, envr);
    char *s;

    while (1)
    {
        s = readline("Minishell > ");
        if  (!s)
        {
            free_node(&node);
            free_env(&env);
            exit(0);
        }
        add_history(s);
        if (!join_line(s))
        {
            free(s);
            write(2,"Syntax error !\n",15);
            continue;
        }
        s = ft_strtrim(s, " ");
        if (s && !check_line(s))
        {
            free(s);
            write(2,"Syntax error !\n",15);
            continue;
        }
        else if (!s)
            continue;
        parsing(node, s,&node->buffer);
        split_parsing(node, env);
        // t_command *current = node->command;
        // while (current)
        // {
        //     int i = 0;
        //     printf("Command:%s$\n", current->str);
        //     t_redirect *input = current->input;
        //     while(input)
        //     {
        //         printf("Input:%s$\n", input->str);
        //         input = input->next;
        //     }
        //     t_redirect *output = current->output;
        //     while(output)
        //     {
        //         printf("Output:%s$\n", output->str);
        //         output = output->next;
        //     }
        //     char **temp = current->options;
        //     while (temp[i])
        //     {
        //         printf("Option:%d:%s$\n", i, temp[i]);
        //         i++;
        //     }
        //     current = current->next;
        // }
        execution(node, env);
        free_node(&node);
        ft_add_node(&node, ft_new_node());
        free(s);
    }
}