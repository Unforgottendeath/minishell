#include "minishell.h"

void free_node(t_node **lst)
{
    t_node *current = *lst;
    t_node *next_node;
    while (current)
    {
        next_node = current->next;
        if (current->buffer)
        {
            free(current->buffer);
            current->buffer = NULL;
        }
        free_command(&current->command);
        free_redirect(&current->input);
        free_redirect(&current->output);
        free(current);
        current = next_node;
    }
    *lst = NULL;
}

t_node *ft_new_node(void )
{
    t_node *new = malloc(sizeof(t_node));
    if (!new)
        return NULL;
    new->command = NULL;
    new->buffer = malloc(2048);
    new->exit_nb = 0;
    ft_bzero(new->buffer,2048);
    new->input = NULL;
    new->output = NULL;
    new->next = NULL;
    return new;
}

void ft_add_node(t_node **lst, t_node *new)
{
    if (!*lst)
    {
        *lst = new;
        return;
    }
    t_node *current = *lst;
    while (current->next)
        current = current->next;
    current->next = new;
}