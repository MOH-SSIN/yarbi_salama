/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:38:46 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/19 20:20:20 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	oui_space(char *str)
{
	while (*str)
	{
		if (!is_espace(*str)) // ou isspace(*str) si tu utilises <ctype.h>
			return (0);
		str++;	
	}
	return (1);
}

int	ft_isalpha(int alpha)
{
	if ((alpha >= 'a' && alpha <= 'z') || (alpha >= 'A' && alpha <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
