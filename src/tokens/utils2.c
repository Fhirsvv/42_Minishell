/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:16:38 by ecortes-          #+#    #+#             */
/*   Updated: 2025/01/31 20:20:15 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_add_after(t_myshell *tshell, char **arr, t_token *new, int *i)
{
	while (arr[*i])
	{
		ft_tokenadd_after(&tshell->tokens,
			ft_token_new(ft_strjoin("$", arr[*i]), WORD), new);
		new = new->next;
		*i = *i + 1;
	}
}

t_token_handler	init_token_handler(char *str, t_myshell *ms)
{
	t_token_handler	h;

	h.i = 0;
	h.str = str;
	h.quote = 0;
	h.ms = ms;
	return (h);
}
