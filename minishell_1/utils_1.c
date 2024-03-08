#include "minishell.h"

char *ft_strdup(char *s)
{
    int i;
    char *ptr;

    if (!s)
        return NULL;
    i = 0;
    while (s[i])
        i++;
    ptr = malloc(i + 1);
    if (!ptr)
        return (NULL);
    i = 0;
    while (s[i])
    {
        ptr[i] = s[i];
        i++;
    }
    ptr[i] = 0;
    return ptr;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*temp;
	unsigned char	*temp_2;
	size_t			i;

	if (src == NULL && dest == NULL)
		return (0);
	temp = (unsigned char *)dest;
	temp_2 = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		temp[i] = temp_2[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	check(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*pointer;
	size_t	j;
	char *temp;

	temp = (char *)s1;
	if (!*temp || !temp)
	{
		if (!*temp)
			free(temp);
		return NULL;
	}
	while (check(*s1, (char *)set))
		s1++;
	j = ft_strlen(s1);
	while (check(s1[j - 1], (char *)set) && j > 0)
		j--;
	pointer = (char *)malloc(j + 1);
	if (pointer == 0)
		return (0);
	pointer = (char *)ft_memcpy(pointer, s1, j);
	pointer[j] = 0;
	free(temp);
	return (pointer);
}