#include "minishell.h"
int escape_quote(int i, char *str, int *size)
{
    if (str[i] == '"')
    {
        i++;
        while ( str[i] && str[i] != '"')
            i++;
        if (str[i] == '"')
            i++;
        if (!str[i] || str[i] == ' ')
            *size+=1;
    }
    else if (str[i] == '\'')
    {
        i++;
        while (str[i] && str[i] != '\'')
            i++;
        if (str[i] == '\'')
            i++;
        if (!str[i] || str[i] == ' ')
            *size+=1;
    }
    return i;
}
int count_options(char *str)
{
    int size = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] && (str[i +1] == ' ' || !str[i + 1]))
            size++;
        else if (str[i] == '\'' || str[i] == '"')
            i = escape_quote (i, str, &size);
        if (str[i])
            i++;
    }
    return size;
}
int ft_strcmp(char *s1, char *s2)
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
char *check_var(char *str, t_hold *env)
{
    t_hold *current = env;
    while (current)
    {
        if (ft_strcmp(current->str, str) && (*(current->str + ft_strlen(str)) == '='))
            return (ft_strdup(current->str + ft_strlen(str) + 1));
        current = current->next;
    }
    return NULL;
}
int copy_quote(char **s1, char *s2, int i, t_hold *env)
{
    char *temp = *s1;
    char env_var[2048];
    char *k;
    int l;
    ft_bzero(env_var, 2048);
    if (*temp == '"')
    {
        temp++;
        while (*temp && *temp != '"')
        {
            if (*temp == '$')
            {
                if (*(temp) && (*temp) != ' ')
                {
                    l = 0;
                    temp++;
                    while (*temp && *temp != ' ' && *temp != '"' && *temp != '\'')
                    {
                        env_var[l]=*temp;
                        l++;
                        temp++;
                    }
                    k = check_var(env_var, env);
                    if (k)
                    {
                        l = 0;
                        while (k[l])
                        {
                            s2[i] = k[l];
                            i++;
                            l++;
                        }
                        free(k);
                    }
                }
            }
            if (*temp && *temp != '"')
            {
                s2[i] = *temp;
                i++;;
                temp++;
            }
        }
        if (*temp == '"')
            temp++;
    }
    else if(*temp == '\'')
    {
        temp++;
        while (*temp && *temp != '\'')
        {
            s2[i] = *temp;
            i++;;
            temp++;
        }
        if (*temp == '\'')
            temp++;
    }
    *s1 = temp;
    return i;
}
char *copy_content(char **s1, t_hold *env)
{
    char *temp = *s1;
    char env_var[2048];
    char *k;
    int l;
    char buffer[2048];
    ft_bzero(env_var,2048);
    ft_bzero(buffer, 2048);
    int i = 0;
    while (*temp == ' ')
        temp++;
    while (*temp && *temp != ' ')
    {
        if (*temp == '"' || *temp =='\'')
            i = copy_quote(&temp, buffer, i, env);
        else if (*temp == '$')
        {
            if (*(temp + 1) && *(temp + 1) != ' ')
            {
                l = 0;
                temp++;
                while (*temp && *temp != ' ' && *temp != '"' && *temp != '\'')
                {
                    env_var[l]=*temp;
                    l++;
                    temp++;
                }
                k = check_var(env_var, env);
                if (k)
                {
                    l = 0;
                    while (k[l])
                    {
                        buffer[i] = k[l];
                        i++;
                        l++;
                    }
                    free(k);
                }
            }
        }
        if (*temp && *temp != ' ')
        {
            buffer[i] = *temp;
            temp++;
            i++;
        }
    }
    *s1 = temp;
    char *s2 = ft_strdup(buffer);
    return s2;
}
void split_helper(t_command *content, t_hold *env)
{
    int size ;
    char *temp = content->str;
    size = count_options(content->str);
    free(content->options);
    content->options = malloc((size + 1) * sizeof(char *));
    int i = 0;
    while(i < size)
    {   
        content->options[i] = copy_content(&temp, env);
        i++;
    }
    content->options[i] = NULL;
}

void split_command(t_command *content, t_hold *env)
{
    t_command *current = content;
    while(current)
    {
        split_helper(current, env);
        current = current->next;
    }
}

void clear_two(t_redirect **data)
{
    t_redirect *current;

    current = *data;
    while (current) 
    {
        current->str = ft_strtrim(current->str, " ");
        current = current->next;
    }
}

void clear_help(t_command **data)
{
    t_command *current;
    
    current = *data;
    while (current) 
    {
        clear_two(&current->input);
        clear_two(&current->output);
        current->str = ft_strtrim(current->str, " ");
        current = current->next;
    }
}

void split_parsing(t_node *content, t_hold *env)
{
    clear_help(&content->command);
    split_command(content->command, env);
}