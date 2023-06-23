/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shtanemu <shtanemu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:04:29 by kakiba            #+#    #+#             */
/*   Updated: 2023/06/23 14:30:11 by shtanemu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdbool.h>
# include "get_next_line_bonus.h"

# define FALSE 0
# define TRUE 1

typedef struct s_list {
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_clist {
	void			*content;
	struct s_clist	*next;
}			t_clist;

typedef struct s_dlist {
	struct s_dlist	*prev;
	void			*content;
	struct s_dlist	*next;
}				t_dlist;

typedef enum e_dtree_type {
	DT_ROOT,
	DT_NODE,
	DT_LEAF,
}			t_dtree_type;

typedef struct s_dtree {
	struct s_dtree	*root;
	struct s_dtree	*left;
	struct s_dtree	*right;
	void			*content;
	t_dtree_type	type;
}			t_dtree;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isdigit_str(char *str, size_t sign_allowable);
int			ft_isdouble(char *str);
int			ft_isspace(int c);
char		*get_addrr_before_space(char *line);

size_t		ft_strlen(const char *str);
size_t		ft_strlen_s(const char *str);
void		*ft_memset(void *buf, int ch, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strchr_s(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp_s(const char *s1, const char *s2);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, \
					const char *needle, size_t len);
int			ft_atoi(const char *str);
double		ft_atof(char *str);
void		*ft_calloc(size_t count, size_t size);
void		*ft_galloc(size_t size, t_dlist **alloc_list);

char		*ft_strdup(const char *s1);
char		*ft_strdup_s(const char *s1);
char		*ft_strndup_s(const char *str, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, \
						void *(*f)(void *), void (*del)(void *));

t_dlist		*ft_dlstnew(void *content);
t_dlist		*ft_dlsthead(t_dlist *lst);
t_dlist		*ft_dlstlast(t_dlist *lst);
void		ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void		ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void		ft_dlstclear(t_dlist **lst, void (*del)(void*));
void		ft_dlstdelone(t_dlist *lst, void (*del)(void *));
t_dlist		*ft_dlstsearch(t_dlist *node, void *target);
bool		ft_dlstdelete(t_dlist **lst, void *target, void (*del)(void *));

long int	ft_strtol(const char *nptr, char **endptr, int base);

int			ft_printf(char *format, ...);
void		output_format(char *format, va_list *ap, int *sum);
int			filter(char *format, va_list *ap, int *sum);
void		print_char(va_list *ap, int *sum);
void		print_str(va_list *ap, int *sum);
void		print_pointer(va_list *ap, int *sum);
void		print_str(va_list *ap, int *sum);
int			out_put_llnbr(long long n, int fd);
int			ft_putllnbr_fd(int long long n, int fd);
char		c_to_hex(int n, char c);
int			ft_puthex_fd(unsigned long long n, int fd, char c);
int			ft_hex_output(unsigned long long n, int fd, char c);

bool		ft_tree_add(t_dtree **root, t_dtree *new, char *label);
t_dtree		*ft_treenew(void *content);
int			print_node(t_dtree *node, size_t level, int c);

// gc
t_dlist		**get_gc_list(void);
void		*gc_malloc(size_t size);
bool		gc_free(void *ptr);
void		gc_clear(void);
bool		gc_add(void *ptr);

void		free_double_ptr(char **ptr);
size_t		get_size_double_ptr(char **ptr);

size_t		count_char_matrix_rows(char **matrix);
void		free_char_matrix(char **matrix);

#endif
