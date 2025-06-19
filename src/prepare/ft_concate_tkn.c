/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concate_tkn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:36:38 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/19 12:27:01 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	type_string(int type)
// {
// 	return (type == STRING || type == SINGLE_Q || type == DOUBLE_Q
// 		|| type == VAR || type == DOUBLE_DLR || type == EXIT_STATUS);
// }

// void	concate_string(t_token_node **debut, t_token_node **new)
// {
// 	char			*reslut_concat;
// 	t_token_node	*new_tkn;
// 	bool			flag_chek;

// 	reslut_concat = NULL;
// 	flag_chek = false;
// 	while (*debut && type_string((*debut)->type))
// 	{
// 		if ((*debut)->flag)
// 			flag_chek = true;
// 		reslut_concat = ft_strjoin(reslut_concat, (*debut)->value);
// 		*debut = (*debut)->next;
// 	}
// 	new_tkn = new_token(STRING, reslut_concat, -2);
// 	if (flag_chek)
// 		new_tkn->flag = true;
// 	add_lst_back_token(new, new_tkn);
// }

// t_token_node	*ft_concate_tkn(t_token_node *debut)
// {
// 	t_token_node	*new_list;
// 	t_token_node	*new;
// 	new_list = NULL;
	
// 	while (debut)
// 	{
// 		if (type_string(debut->type))
// 			concate_string(&debut, &new_list);
// 		else
// 		{
// 			new = new_token(debut->type, debut->value,debut->fd_hrd);
// 			if (debut->flag == true)
// 					new->flag = true;
// 			add_lst_back_token(&new_list, new);
// 			debut = debut->next;
// 		}
// 	}
// 	return (new_list);
// }

int	type_string(int type)
{
	return (type == STRING || type == SINGLE_Q || type == DOUBLE_Q
		|| type == VAR || type == DOUBLE_DLR || type == EXIT_STATUS);
}

//Nouvelle 
void	concate_string(t_token_node **debut, t_token_node **new)
{
	char			*reslut_concat;
	t_token_node	*new_tkn;
	bool			flag_chek;

	reslut_concat = NULL;
	flag_chek = false;

	while (*debut && type_string((*debut)->type))
	{
		// 💥 Arrêt si on rencontre une nouvelle variable (VAR) sans '=' et flag 0
		if ((*debut)->type == VAR && (*debut)->flag == 0 && !ft_fofo((*debut)->value, '='))
			break;

		if ((*debut)->flag)
			flag_chek = true;

		reslut_concat = ft_strjoin(reslut_concat, (*debut)->value);
		*debut = (*debut)->next;
	}

	new_tkn = new_token(STRING, reslut_concat, -2);
	if (flag_chek)
		new_tkn->flag = true;

	add_lst_back_token(new, new_tkn);
}

// Nouvelle version ft_concate_tkn 
t_token_node	*ft_concate_tkn(t_token_node *debut)
{
	t_token_node	*new_list = NULL;
	t_token_node	*new;

	while (debut)
	{
		if (type_string(debut->type))
			concate_string(&debut, &new_list);
		else
		{
			new = new_token(debut->type, debut->value, debut->fd_hrd);
			if (debut->flag == true)
				new->flag = true;
			add_lst_back_token(&new_list, new);
			debut = debut->next;
		}
	}
	return (new_list);
}


//export a=$var b=$var_1 c=$var_2 d=$var_3 e=$var_4 f=$var_5