/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusung <yusung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:07:22 by yusung            #+#    #+#             */
/*   Updated: 2023/11/15 21:30:20 by yusung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
}

void	error(int num)
{
	if (num == ARG_ERR)
		write(2, "Wrong argument\n", 16);
	else if (num == PIPE_ERR)
		perror("Pipe error ");
	else if (num == FORK_ERR)
		perror("Fork error ");
	else if (num == OPEN_ERR)
		perror("File open error ");
	else if (num == DUP_ERR)
		perror("Dup error ");
	else if (num == EXECVE_ERR)
		perror("Execve error ");
	else if (num == CMD_ERR)
		write(2, "Command not found\n", 19);
	else if (num == WAIT_ERR)
		perror("Wait error");
	exit(1);
}

char	*find_path(char **path_list, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (path_list && path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	if (access(cmd, X_OK) == 0)
		return (cmd);
	error(CMD_ERR);
	return (NULL);
}

char	**parse_envp(char **envp)
{
	int		i;
	char	*tmp;
	char	**path_list;

	path_list = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			tmp = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			path_list = ft_split(tmp, ':');
			free(tmp);
			break ;
		}
		i++;
	}
	return (path_list);
}

int	main(int argc, char **argv, char **envp)
{
	int		cur[2];
	int		prev[2];
	pid_t	pid;
	int		i;
	int		child_cnt;

	child_cnt = argc - 3;
	i = 0;
	while (i < child_cnt)
	{
		if (i > 1)  // cur를 prev에 저장시키는 코드
		{
			close(prev[0]);
			close(prev[1]);
		}
		prev[0] = cur[0];
		prev[1] = cur[1];
		if (pipe(cur) < 0)
			error(PIPE_ERR);
		pid = fork();
		if (pid < 0)
			error(FORK_ERR);
		if (pid == 0)
		{
			if (i == 0)
				first_process(cur, argv[1], argv[i+2], envp);
			else if (i == child_cnt - 1)
				last_process(prev, argv[argc-1], argv[i+2], envp);
			else
				mid_process(prev, cur, argv[i+2], envp);
		}
		i++;
	}
	close(cur[0]);
	close(cur[1]);
	close(prev[0]);
	close(prev[1]);
	i = 0;
	while (i < child_cnt)
	{
		if (wait(NULL) < 0)
			error(WAIT_ERR);
		i++;
	}
	return (0);
}
