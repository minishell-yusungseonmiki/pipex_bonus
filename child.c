/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:08:29 by yusung            #+#    #+#             */
/*   Updated: 2023/11/16 14:03:03 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_process(int *pipe_fd, char *infile, char *cmd, char **envp)
{
	int		fd;
	char	**cmd_set;
	char	**path_list;
	char	*path;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		error(OPEN_ERR);
	close(pipe_fd[0]);
	if (dup2(fd, 0) < 0) //입력
		error(DUP_ERR);
	close(fd);
	if (dup2(pipe_fd[1], 1) < 0) //출력
		error(DUP_ERR);
	close(pipe_fd[1]);
	cmd_set = ft_split(cmd, ' ');
	path_list = parse_envp(envp);
	path = find_path(path_list, cmd_set[0]);
	free_list(path_list);
	if (execve(path, cmd_set, envp) < 0)
		error(EXECVE_ERR);
	return (0);
}
int	mid_process(int *prev, int *cur, char *cmd, char **envp)
{
	char	**cmd_set;
	char	**path_list;
	char	*path;

	close(prev[1]);
	close(cur[0]);
	if (dup2(prev[0], 0) < 0) //입력
		error(DUP_ERR);
	close(prev[0]);
	if (dup2(cur[1], 1) < 0) //출력
		error(DUP_ERR);
	close(cur[1]);
	cmd_set = ft_split(cmd, ' ');
	path_list = parse_envp(envp);
	path = find_path(path_list, cmd_set[0]);
	free_list(path_list);
	if (execve(path, cmd_set, envp) < 0)
		error(EXECVE_ERR);
	exit (0);
}

int	last_process(int *pipe_fd, char *out_file, char *cmd, char **envp)
{
	int		fd;
	char	**cmd_set;
	char	**path_list;
	char	*path;

	fd = open(out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		error(OPEN_ERR);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], 0) < 0) //입력
		error(DUP_ERR);
	if (dup2(fd, 1) < 0) //출력
		error(DUP_ERR);
	close(pipe_fd[0]);
	close(fd);
	cmd_set = ft_split(cmd, ' ');
	path_list = parse_envp(envp);
	path = find_path(path_list, cmd_set[0]);
	free_list(path_list);
	if (execve(path, cmd_set, envp) < 0)
		error(EXECVE_ERR);
	return (0);
}
