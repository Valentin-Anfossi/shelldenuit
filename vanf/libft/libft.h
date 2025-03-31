/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:54:36 by vanfossi          #+#    #+#             */
/*   Updated: 2024/12/07 19:27:09 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>

# define SIZE_MAX  	2147483647
# define INT_MAX  	2147483647
# define INT_MIN	-2147483648

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

// Bonus

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// ft_printf

int		ft_printf(const char *form, ...);
char	*ft_itohex(unsigned long nb);
int		ft_print_hexlow(va_list ptr);
int		ft_print_hexup(va_list ptr);
int		ft_print_char(va_list ptr);
int		ft_print_void(va_list ptr);
int		ft_print_dec(va_list ptr);
int		ft_print_str(va_list ptr);
int		ft_print_int(va_list ptr);
int		ft_print_usign(va_list ptr);
int		ft_print_perc(void);
int		ft_putunbr(unsigned int n);
int		ft_get_uintlen(unsigned int nb);
int		ft_get_intlen(int nb);

// ft_fprintf

int		ft_fprintf(int fd, const char *form, ...);
int		ft_fprintf_parsing(char *form, va_list ptr, int fd);
int		ft_fprint_char(va_list ptr, int fd);
int		ft_fprint_str(va_list ptr, int fd);
int		ft_fprint_void(va_list ptr, int fd);
int		ft_fprint_dec(va_list ptr, int fd);
int		ft_fprint_int(va_list ptr, int fd);
int		ft_fprint_usign(va_list ptr, int fd);
int		ft_fprint_hexlow(va_list ptr, int fd);
int		ft_fprint_hexup(va_list ptr, int fd);
int		ft_fprint_perc(int fd);
int		ft_fget_intlen(int nb);
int		ft_fget_uintlen(unsigned int nb);
char	*ft_fitohex(unsigned long nb);
int		ft_fputunbr(unsigned int n, int fd);
int		ft_fprintf_types(char *form, va_list ptr, int i, int fd);

// get_next_line

char	*get_next_line(int fd);
char	*get_line_from_buffer(int fd, char *rest, char *buffer);
char	*get_rest(char *line);

#endif