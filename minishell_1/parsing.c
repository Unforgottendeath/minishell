#include "minishell.h"

void parsing_quote(char **temp, char **str)
{
    char *x;
    char *y;
    
    x = *temp;
    y = *str;
    if (*y == '"')
    {
        *x++ = *y++;
        while (*y != '"' && *y)
            *x++ = *y++;
        if (*y == '"')
            *x++ = *y++;
        *temp = x;
        *str = y;
    }
    else if (*y == '\'')
    {
        *x++ = *y++;
        while (*y != '\'' && *y)
            *x++ = *y++;
        if (*y == '\'')
            *x++ = *y++;
        *temp = x;
        *str = y;
    }
}

void parsing_input(t_node *content, char **str)
{
    char *x;
    char *buffer;
    char *temp;
    
    buffer = malloc(2048);
    x = *str;
    temp = buffer;
    int flag = 0;
    x++;
    if (*x == '<')
    {
        flag++;
        x++;
    }
    while (*x == ' ')
        x++;
    while (*x != '|' && *x != '<' && *x != '>' && *x != ' ' && *x)
    {
        if (*x == '"' || *x == '\'')
            parsing_quote(&temp, &x);
        else
            *temp++ = *x++;
    }
    *str = x;
    *temp = 0;
    ft_add_redirect(&content->input, ft_new_redirect(buffer, flag));
    free(buffer);
    buffer = NULL;
}

void parsing_output(t_node *content, char **str)
{
    char *x;
    char *buffer;
    char *temp;
    
    buffer = malloc(2048);
    x = *str;
    temp = buffer;
    int flag = 0;
    x++;
    if (*x == '>')
    {
        flag++;
        x++;
    }
    while (*x == ' ')
        x++;
    while (*x != '|' && *x != '<' && *x != '>' && *x != ' ' && *x)
    {
        if (*x == '"' || *x == '\'')
            parsing_quote(&temp, &x);
        else
            *temp++ = *x++;
    }
    *str = x;
    *temp = 0;
    ft_add_redirect(&content->output, ft_new_redirect(buffer, flag));
    free(buffer);
    buffer = NULL;
}

void parsing_standard(t_node *content, char **str, char **buffer)
{
    char *x;
    char *temp;
    
    x = *str;
    temp = *buffer;
    while (*temp)
        temp++;
    while (*x != '|' && *x != '<' && *x != '>' && *x)
    {
        if (*x == '"' || *x == '\'')
            parsing_quote(&temp, &x);
        else
            *temp++ = *x++;
    }
    if (*x == '|' || !*x)
    {
        ft_add_command(&content->command, ft_new_command(*buffer));
        copy_input(content);
        copy_output(content);
        free(*buffer);
        *buffer = malloc(2048);
        ft_bzero(*buffer, 2048);
        if (*x == '|')
            x++;
    }
    *str = x; 
}

void parsing(t_node *content, char *str, char **buffer)
{
    if (!str || !*str)
    {
        if (**buffer)
        {
            ft_add_command(&content->command, ft_new_command(*buffer));
            copy_input(content);
            copy_output(content);
            free(*buffer);
            *buffer = NULL;
        }
        return ;
    }
    if (*str == '<')
        parsing_input(content, &str);
    else if (*str == '>')
        parsing_output(content, &str);
    else
        parsing_standard(content, &str, buffer);
    parsing(content, str, buffer);
}