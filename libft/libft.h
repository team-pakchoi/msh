/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:04:28 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/30 03:24:51 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

int				ft_atoi(const char *str);
void			ft_bzero(void *b, size_t len);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
void			*ft_memset(void *b, int c, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(char *src);
char			*ft_strndup(char *src, size_t n);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
int				ft_strlen(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);

char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			**ft_split_free(char **tab);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				get_next_line(int fd, char **line);
int				ft_strarr_len(char *str[]);
size_t			ft_strarr_lcpy(char *dest[], char *src[], size_t size);
char			**ft_strarr_join(char *a1[], char *a2[]);
char			**ft_strarr_shift(char ***strarr);
void			ft_free_arr(char **arr);

#endif
