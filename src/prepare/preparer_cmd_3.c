/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparer_cmd_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:27:06 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/20 20:21:25 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*join_flag_tokens(t_token_node **cur)
{
	char	*joined;

	joined = NULL;
	while (*cur && (*cur)->flag == 1)
	{
		if ((*cur)->value && (*cur)->value[0] != '\0')
			joined = ft_strjoin(joined, (*cur)->value);
		*cur = (*cur)->next;
	}
	return (joined);
}

static void	copy_flag_tokens(t_token_node **cur, t_token_node **new_list)
{
	t_token_node	*tmp;

	while (*cur && (*cur)->flag == 1)
	{
		if ((*cur)->value && (*cur)->value[0] != '\0')
		{
			tmp = new_token((*cur)->type, (*cur)->value, (*cur)->fd_hrd);
			tmp->flag = 1;
			add_lst_back_token(new_list, tmp);
		}
		*cur = (*cur)->next;
	}
}

static void	handle_flag_tokens(t_token_node **cur, t_token_node **new_list)
{
	t_token_node	*tmp;
	char			*joined;

	if (start_zone_has_equal(*cur))
	{
		joined = join_flag_tokens(cur);
		tmp = new_token(5, joined, -2);
		tmp->flag = 1;
		add_lst_back_token(new_list, tmp);
	}
	else
		copy_flag_tokens(cur, new_list);
}

t_token_node	*regrouper_tokens_marques(t_token_node *head)
{
	t_token_node	*new_list;
	t_token_node	*cur;
	t_token_node	*tmp;

	new_list = NULL;
	cur = head;
	while (cur)
	{
		if (cur->flag == 1 && (!cur->value || cur->value[0] == '\0'))
			cur = cur->next;
		else if (cur->flag == 1)
			handle_flag_tokens(&cur, &new_list);
		else
		{
			tmp = new_token(cur->type, cur->value, cur->fd_hrd);
			tmp->flag = 0;
			add_lst_back_token(&new_list, tmp);
			cur = cur->next;
		}
	}
	return (new_list);
}
