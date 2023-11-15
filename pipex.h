/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:15:46 by yusung            #+#    #+#             */
/*   Updated: 2023/11/15 17:08:33 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "lib/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

# define ARG_ERR 0
# define PIPE_ERR 1
# define FORK_ERR 2
# define OPEN_ERR 3
# define DUP_ERR 4
# define EXECVE_ERR 5
# define CMD_ERR 6
# define WAIT_ERR 7

# define PIPE_READ 0
# define PIPE_WRITE 1

void	free_list(char **list);
void	error(int num);
char	*find_path(char **path_list, char *cmd);
char	**parse_envp(char **envp);

int	first_process(int *pipe_fd, char *infile, char *cmd, char **envp);
int	mid_process(int *prev, int *cur, char *cmd, char **envp);
int	last_process(int *pipe_fd, char *out_file, char *cmd, char **envp);

#endif