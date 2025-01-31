/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecortes- <ecortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:08:06 by ecortes-          #+#    #+#             */
/*   Updated: 2025/01/31 20:20:05 by ecortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_space(t_token_handler *h)
{
	if (h->str[h->i] == ' ' && h->quote == '\0' && h->start_q)
	{
		add_token_free(h->start_q, &h->str[h->i], h->str, h->ms);
		h->start_q = NULL;
	}
}

static void	handle_quotes(t_token_handler *h)
{
	if (h->str[h->i] == '\'' || h->str[h->i] == '"')
	{
		if (h->quote == h->str[h->i])
		{
			add_token_free(h->start_q, &h->str[h->i], h->str, h->ms);
			update_last_token_symbol(h->ms, token_type(&h->quote));
			h->start_q = NULL;
			h->quote = '\0';
		}
		else if (h->quote == '\0')
		{
			h->quote = h->str[h->i];
			if (h->start_q)
				add_token_free(h->start_q, &h->str[h->i], h->str, h->ms);
			h->start_q = &h->str[h->i + 1];
		}
	}
}

static void	handle_pipe(t_token_handler *h)
{
	if (h->str[h->i] == '|')
	{
		if (h->quote == '\0')
		{
			if (h->start_q)
			{
				add_token_free(h->start_q, &h->str[h->i], h->str, h->ms);
				h->start_q = NULL;
			}
			add_token_free(&h->str[h->i], &h->str[h->i + 1], h->str, h->ms);
		}
		else if (!h->start_q)
			h->start_q = &h->str[h->i];
	}
}

static void	handle_redirection(t_token_handler *h)
{
	if ((h->str[h->i] == '<' || h->str[h->i] == '>') && h->quote == '\0')
	{
		if ((h->str[h->i] == '<' && h->str[h->i + 1] == '<')
			|| (h->str[h->i] == '>' && h->str[h->i + 1] == '>'))
		{
			if (h->start_q)
			{
				add_token_free(h->start_q, &h->str[h->i], h->str, h->ms);
				h->start_q = NULL;
			}
			add_token_free(&h->str[h->i], &h->str[h->i + 2], h->str, h->ms);
			h->i += 1;
		}
		else
		{
			if (h->start_q)
			{
				add_token_free(h->start_q, &h->str[h->i], h->str, h->ms);
				h->start_q = NULL;
			}
			add_token_free(&h->str[h->i], &h->str[h->i + 1], h->str, h->ms);
		}
	}
}

void	tokens(char *str, t_myshell *ms)
{
	t_token_handler	h;

	h = init_token_handler(str, ms);
	while (str[h.i])
	{
		handle_space(&h);
		handle_quotes(&h);
		handle_pipe(&h);
		handle_redirection(&h);
		if (str[h.i] != ' ' && str[h.i] != '\'' && str[h.i] != '"'
			&& str[h.i] != '|' && str[h.i] != '<' && str[h.i] != '>'
			&& !h.start_q)
			h.start_q = &str[h.i];
		h.i++;
	}
	if (h.start_q)
		add_token_free(h.start_q, &str[h.i], str, ms);
	split_various_dolar(ms);
}
