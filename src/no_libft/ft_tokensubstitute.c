/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokensubstitute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:51:46 by ecortes-          #+#    #+#             */
/*   Updated: 2024/11/13 19:27:36 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_tokensubstitute(t_token **lst, t_token *new, t_token *wh)
{
	t_token	*node;

	if (new == NULL || lst == NULL || wh == NULL)
		return ;
	if (*lst == wh)
	{
		new->next = wh->next;
		*lst = new;
		free(wh->content);
		free(wh);
		return ;
	}
	node = *lst;
	while (node != NULL)
	{
		if (node->next == wh)
		{
			node->next = new;
			new->next = wh->next;
			free(wh->content);
			free(wh);
			return ;
		}
		node = node->next;
	}
}
