#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*pointer;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	pointer = (char *)malloc(len1 + len2 + 1);
	if (pointer == NULL)
		return (NULL);
	if (s1)
    {
		ft_memcpy(pointer, s1, len1);
        free(s1);
    }
	if (s2)
    {
		ft_memcpy(pointer + len1, s2, len2);
        free(s2);
    }
	pointer[len1 + len2] = '\0';
	return (pointer);
}

void ft_bzero(char *str, int size)
{
    int i = 0;
    while (i < size)
        str[i++] = 0;
}

void copy_input(t_node *content)
{
	t_redirect *current = content->input;
	t_command *last_command = content->command;
	while (last_command->next)
		last_command = last_command->next;
	while (current)
	{
		ft_add_redirect(&(last_command->input), ft_new_redirect(current->str, current->flag));
		current = current->next;
	}
	free_redirect(&content->input);
}

void copy_output(t_node *content)
{
	t_redirect *current = content->output;
	t_command *last_command = content->command;
	while (last_command->next)
		last_command = last_command->next;
	while (current)
	{
		ft_add_redirect(&(last_command->output), ft_new_redirect(current->str, current->flag));
		current = current->next;
	}
	free_redirect(&content->output);
}
