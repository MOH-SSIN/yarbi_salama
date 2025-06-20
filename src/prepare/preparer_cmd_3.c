/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparer_cmd_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:07:06 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/20 11:20:11 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ignorer_jetons_vides(t_token_node **cur)
{
	while (*cur && (*cur)->flag == 1 && (!(*cur)->value || (*cur)->value[0] == '\0'))
		*cur = (*cur)->next;
}

static void	traiter_concatenation_affectation(t_token_node **cur, t_token_node **lst)
{
	char			*joined = NULL;
	t_token_node	*tmp;

	while (*cur && (*cur)->flag == 1)
	{
		if ((*cur)->value && (*cur)->value[0] != '\0')
			joined = ft_strjoin(joined, (*cur)->value);
		*cur = (*cur)->next;
	}
	tmp = new_token(5, joined, -2);
	tmp->flag = 1;
	add_lst_back_token(lst, tmp);
}

static void	copier_jetons_flag_un_par_un(t_token_node **cur, t_token_node **lst)
{
	t_token_node	*tmp;

	while (*cur && (*cur)->flag == 1)
	{
		if ((*cur)->value && (*cur)->value[0] != '\0')
		{
			tmp = new_token((*cur)->type, (*cur)->value, (*cur)->fd_hrd);
			tmp->flag = 1;
			add_lst_back_token(lst, tmp);
		}
		*cur = (*cur)->next;
	}
}

t_token_node	*generer_nouvelle_liste_tokens(t_token_node *head)
{
	t_token_node	*new_list = NULL;
	t_token_node	*cur = head;
	t_token_node	*tmp;

	while (cur)
	{
		if (cur->flag == 1 && (!cur->value || cur->value[0] == '\0'))
			ignorer_jetons_vides(&cur);
		else if (cur->flag == 1 && start_zone_has_equal(cur))
			traiter_concatenation_affectation(&cur, &new_list);
		else if (cur->flag == 1)
			copier_jetons_flag_un_par_un(&cur, &new_list);
		else
		{
			tmp = new_token(cur->type, cur->value, cur->fd_hrd);
			tmp->flag = 0;
			add_lst_back_token(&new_list, tmp);
			cur = cur->next;
		}
	}
	return new_list;
}


t_token_node *changer_flag(t_token_node *debut)
{
	t_token_node *temp;

	temp = debut;
	while (temp && temp->next)
	{
		if (ft_fofo(temp->value, '=') && temp->flag == 0)
		{
			if (temp->next->flag == 1)
				temp->flag = 1;
		}
		temp = temp->next;
	}
	return debut;
}
