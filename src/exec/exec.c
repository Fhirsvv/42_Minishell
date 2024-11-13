/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:26:18 by ecortes-          #+#    #+#             */
/*   Updated: 2024/11/13 19:02:47 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


static void exec_one(t_comand *cmd)
{
	int fd[2];
	int pid;

	if (pipe(fd) < 0)
		perror("error en pipe\n");
	pid = fork();
	if (pid == 0)
	{
		ft_exec();
	}
}

//https://www.youtube.com/watch?v=6xbLgZpOBi8
//https://www.youtube.com/watch?v=NkfIUo_Qq4c
static void	exec_pipe(t_comand *cmd)
{
	//fd[0] = read end -- fd[1] = write end
	int fd[2];
	int pid;

	if (pipe(fd) < 0)
		perror("error pipe\n");
	pid = fork();
	if(cmd->fds->fd_in >= 0)
		dup2(cmd->fds->fd_in, STDIN_FILENO);
	if (pid < 0)
		perror("errore algo 1\n");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		//exec
	}
	if (cmd->next->next) //o aqui solo añadir el dup2(stdin_fileno, cmd->next->next->fds.fd_in)
		dup2(fd[0], cmd->next->next->fds->fd_in);

	waitpid(pid, NULL, 0);
	close(fd[0]);
	close(fd[1]);
}

void	exec(t_myshell *tshell)
{
	t_comand	*cmd;
	int		*flds;
	int i;
	
	i = 0;
	//inicio aqui u nproceso para que aunque solo haya
	//un comando no cierre el comando actual
	flds = ft_calloc(tshell->pipes_count + 1, sizeof(int));
	cmd = tshell->comands;
	while (cmd)
	{
		if (tshell->pipes_count == 0)
			ft_exec_one(cmd);
		else
			exec_pipe(cmd);
		cmd = cmd->next;
	}
	
	free(flds);
}

/*
int	comand_exec(t_myshell *tshell, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	else if (ft_strcmp(cmd->args[0], "ls") == 0)
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
	else if (ft_strcmp(cmd->args[0], "env") == 0)
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	
}
*/