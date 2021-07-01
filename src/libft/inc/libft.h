/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:32:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/06/26 07:22:43 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef IS_LINUX
#  define IS_LINUX 0
# endif

# ifndef NULL_SIZE
#  define NULL_SIZE 6
# endif

# define UTF8_1 0x7F
# define UTF8_2 0x7FF
# define UTF8_3 0xFFFF
# define UTF8_4 0x1FFFFF

typedef enum e_type_mods
{
	no_type = 0b00000000,
	character = 0b00000001,
	string = 0b00000010,
	digit = 0b00000100,
	integer = 0b00001000,
	unsig = 0b00010000,
	hex = 0b00100000,
	upper_hex = 0b01000000,
	percent = 0b00000011,
	pointer = 0b00000111
}				t_type_mods;

typedef enum e_flags
{
	none = 0b00000000,
	zero = 0b00000001,
	minus = 0b00000010,
	space = 0b00000100,
	sharp = 0b00001000
}				t_flags;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
**	general prototypes
*/
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *a, int c, size_t n);
int					ft_isspace(char c);
int					ft_isalnum(int c);
int					ft_atoi(const char *np);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int n);
int					ft_isprint(int c);
int					ft_memcmp(const void *arr1, const void *arr2, size_t n);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_putchar_fd(int c, int fd);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_itoa(int n);
char				*ft_itoa_base(unsigned long long value,
						int base, int up_low);
char				*ft_strchr(const void *s, int c);
int					ft_memdel(char **ptr);
char				*ft_strdup(const char *str);
char				*ft_strrchr(const char *str, int ch);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, const char *src, size_t n);
char				*ft_strnew(size_t size);
size_t				ft_strlen(const char *s);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strnstr(const char *big, const char *lit, size_t len);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
char				**ft_split(char const *s, char c);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/*
**	prototype for get_next_line
*/
int					get_next_line(int fd, char **line);
#endif
