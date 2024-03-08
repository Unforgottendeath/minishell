#include "minishell.h"

void free_redirect(t_redirect **lst)
{
    t_redirect *current = *lst;
    t_redirect *next_node;
    while (current)
    {
        next_node = current->next;
        free(current->str);
        free(current);
        current = next_node;
    }
    *lst = NULL;
}

t_redirect *ft_new_redirect(char *buffer, int k)
{
    t_redirect *new = malloc(sizeof(t_redirect));
    if (!new)
        return NULL;
    new->str = ft_strdup(buffer);
    new->flag = k;
    new->next = NULL;
    return new;
}

void ft_add_redirect(t_redirect **lst, t_redirect *new)
{
    if (!*lst)
    {
        *lst = new;
        return;
    }
    t_redirect *current = *lst;
    while(current->next)
        current = current->next;
    current->next = new;
}