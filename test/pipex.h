/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 17:01:30 by cpak              #+#    #+#             */
/*   Updated: 2022/03/31 15:36:30 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>


char	**split_command(char *cmd);
char	*find_command_path(char *envp[], char *command);
void	set_pipe_write_to_stdout(int *fds);
void	set_pipe_read_to_stdin(int *fds);
void	redirect_file_to_read(char *path, int fd);
void	redirect_file_to_write(char *path, int fd);

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strnstr(const char *haystack, const char *needle, unsigned int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

#endif
