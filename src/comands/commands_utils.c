/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:44:22 by ecortes-          #+#    #+#             */
/*   Updated: 2025/01/31 20:27:48 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	args_size(t_token *token)
{
	t_token	*aux;
	int		count;

	count = 0;
	aux = token;
	while (aux->symbol == WORD || aux->symbol == D_QUOTE ||
			aux->symbol == S_QUOTE)
	{
		count++;
		aux = aux->next;
	}
	return (count);
}
