#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

typedef struct s_hold
{
    char *str;
    struct s_hold *next;
}t_hold;

typedef struct s_redirect
{
    char *str;
    int flag;
    struct s_redirect *next;
}t_redirect;

typedef struct s_command
{
    char *str;
    char **options;
    t_redirect *input;
    int fd_in;
    int fd_out;
    int exit_status;
    t_redirect *output;
    struct s_command *next;
}t_command;

typedef struct s_node
{
    int exit_nb;
    t_command *command;
    t_redirect *input;
    t_redirect *output;
    char *buffer;
    struct s_node *next;
}t_node;

// G    L   O   B   A   L       U    T   I   L   S

char *ft_strdup(char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char *s1, char *s2);
void ft_bzero(char *str, int size);
void execution(t_node *content, t_hold *env);
char	**ft_split(char *s, char c);
char    *ft_strjoined(char *s1, char *s2);

//  P   A   R   S   I   N   G

void parsing(t_node *content, char *str, char **buffer);
void copy_input(t_node *content);
void copy_output(t_node *content);
void split_parsing(t_node *content, t_hold *env);


//  R   E   D   I   R   E   C   T       U   T   I   L   S

t_redirect *ft_new_redirect(char *buffer, int k);
void ft_add_redirect(t_redirect **lst, t_redirect *new);
void free_redirect(t_redirect **lst);

//  N   O   D   E       U   T   I   L   S

t_node *ft_new_node(void );
void ft_add_node(t_node **lst, t_node *new);
void free_node(t_node **lst);

//  E   N   V       U   T   I   L   S

t_hold *ft_new_env(char *buffer);
void ft_add_env(t_hold **lst, t_hold *new);
void free_env(t_hold **lst);

//  C   O   M   M   A   N   D       U   T   I   L   S

void ft_add_command(t_command **lst, t_command *new);
t_command *ft_new_command(char *s);
void free_command(t_command **lst);
void ft_del_command(t_command **lst);

#endif