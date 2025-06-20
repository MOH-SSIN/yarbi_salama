/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparer_cmd_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:16:29 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/20 11:20:32 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_assign_form(const char *value)
{
	int i = 0;

	if (!value)
		return false;

	while (value[i])
	{
		if (value[i] == '=')
			return (i > 0 && value[i + 1] == '\0'); // = est à la fin
		i++;
	}
	return false;
}

bool	start_zone_has_equal(t_token_node *start)
{
	return (start && start->flag == 1 && is_assign_form(start->value));
}

