#include "minishell.h"

void free_env(t_hold **lst)
{
    t_hold *current = *lst;
    t_hold *next_node;
    while (current)
    {
        next_node = current->next;
        free(current->str);
        free(current);
        current = next_node;
    }
    *lst = NULL;
}

t_hold *ft_new_env(char *buffer)
{
    t_hold *new = malloc(sizeof(t_hold));
    if (!new)
        return NULL;
    new->str = ft_strdup(buffer);
    new->next = NULL;
    return new;
}

void ft_add_env(t_hold **lst, t_hold *new)
{
    if (!*lst)
    {
        *lst = new;
        return;
    }
    t_hold *current = *lst;
    while (current->next)
        current= current->next;
    current->next = new;
}