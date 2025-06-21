/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparer_cmd_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:27:06 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/21 20:12:15 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_flag_tokens(t_token_node **cur, t_token_node **new_list)
{
	t_token_node	*tmp;

	// NOUVELLE LOGIQUE: Traiter chaque token individuellement
	// au lieu de les grouper tous ensemble
	if ((*cur)->value && (*cur)->value[0] != '\0')
	{
		tmp = new_token((*cur)->type, (*cur)->value, (*cur)->fd_hrd);
		tmp->flag = 1;
		add_lst_back_token(new_list, tmp);
	}
	*cur = (*cur)->next;
}

static void	process_empty_flag_token(t_token_node *cur, t_token_node **new_list)
{
	t_token_node	*tmp;

	if (cur->type == 9)
	{
		tmp = new_token(cur->type, cur->value, cur->fd_hrd);
		tmp->flag = cur->flag;
		add_lst_back_token(new_list, tmp);
	}
}

static void	process_regular_token(t_token_node *cur, t_token_node **new_list)
{
	t_token_node	*tmp;

	tmp = new_token(cur->type, cur->value, cur->fd_hrd);
	tmp->flag = 0;
	add_lst_back_token(new_list, tmp);
}

t_token_node	*regrouper_tokens_marques(t_token_node *head)
{
	t_token_node	*new_list;
	t_token_node	*cur;

	new_list = NULL;
	cur = head;
	while (cur)
	{
		if (cur->flag == 1 && (!cur->value || cur->value[0] == '\0'))
		{
			process_empty_flag_token(cur, &new_list);
			cur = cur->next;
		}
		else if (cur->flag == 1)
			handle_flag_tokens(&cur, &new_list);
		else
		{
			process_regular_token(cur, &new_list);
			cur = cur->next;
		}
	}
	return (new_list);
}
