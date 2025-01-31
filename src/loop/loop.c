/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 23:17:59 by ecortes-          #+#    #+#             */
/*   Updated: 2025/01/31 19:41:03 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void print_comands(t_myshell *tsh)
{
	t_comand *aux = tsh->comands;
	int i = 0;
	while (aux)
	{
		printf("_______________________________________________\n");
		while (aux->args[i])
		{
			printf("ARG %i: %s\n",i+1, aux->args[i]);
			i++;
		}
		i = 0;
		printf("APPEND FILE: %s\n", tsh->comands->fds->apend_file);
		printf("INPUT FILE: %s\n", tsh->comands->fds->input_file);
		printf("OUTPUT FILE: %s\n", tsh->comands->fds->output_file);
		printf("FD IN: %d\n", tsh->comands->fds->fd_in);
		printf("FD: OUT %d\n", tsh->comands->fds->fd_out);
		aux = aux->next;
	}
	printf("\n\n");
	return ;
}

void	free_minishell(t_myshell *tshell, char *str)
{
	ft_free(str);
	ft_free(tshell->prompt);
	free_tokens(&tshell->tokens);
	free_comands(&tshell->comands);
}

static void	reloop(char *str, char *prompt, t_myshell *tm)
{
	perror(str);
	free_minishell(tm, prompt);
	loop(tm);
}

void	loop(t_myshell *tshell)
{
	char	*pr;

	pr = NULL;
	while (true)
	{
		pr = readline("MINISHELL$ ");
		if (!pr)
			exit(1);
		tshell->prompt = ft_strtrim(pr, " \n\t\r\v\f");
		add_history(tshell->prompt);
		if (count_quotes(tshell->prompt) == FALSE)
			reloop(BAD_QUOTES, pr, tshell);
		tokens(tshell->prompt, tshell);
		expander(tshell);
		comands(tshell);
		setup_comands(tshell);
		print_comands(tshell);
		//print_args(tshell);
		//exec(tshell);
		free_minishell(tshell, pr);
	}
}
