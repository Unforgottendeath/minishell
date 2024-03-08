#include "minishell.h"

void ft_del_command(t_command **lst)
{
    t_command *current = *lst;
    int i = 0;
    free(current->str);
    while (current->options[i])
        free(current->options[i++]);
    free(current->options);
    free_redirect(&current->input);
    free_redirect(&current->output);
    free(current);
    *lst = NULL;
}

void free_command(t_command **lst)
{
    t_command *current = *lst;
    t_command *next_node;
    while (current)
    {
        next_node = current->next;
        ft_del_command(&current);
        current = next_node;
    }
    *lst = NULL;
}

t_command *ft_new_command(char *buffer)
{
    t_command *new = malloc(sizeof(t_command));
    if (!new)
        return NULL;
    new->input = NULL;
    new->output = NULL;
    new->fd_in = 0;
    new->fd_out = 1;
    new->exit_status = 0;
    new->options = malloc(sizeof(char *));
    *(new->options) = NULL;
    new->str = ft_strdup(buffer);
    new->next = NULL;
    return new;
}

void ft_add_command(t_command **lst, t_command *new)
{
    if (!*lst)
    {
        *lst = new;
        return;
    }
    t_command *current = *lst;
    while(current->next)
        current = current->next;
    current->next = new;
}
