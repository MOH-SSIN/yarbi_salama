/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:00:41 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/21 19:59:20 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_mot(char **mots)
{
	int	i;

	i = 0;
	if (!mots || !mots[0])
	{
		printf("vide\n");
		return ;
	}
	while (mots[i])
	{
		printf("mot[%i]:%s\n", i, mots[i]);
		i++;
	}
}

void	print_token(t_token_node *cur)
{
	if (!cur)
		printf("liste de token est vide \n");
	while (cur)
	{
		printf("value:%s,type:%d,flag:%d\n", cur->value, cur->type, cur->flag);
		if (cur->next)
			printf(",");
		cur = cur->next;
	}
}

void	print_token_3(t_token_node *cur)
{
	while (cur)
	{
		printf("value:%s,type:%d,flag:%d,fd_hrd:%d", cur->value, cur->type,
			cur->flag, cur->fd_hrd);
		if (cur->next)
			printf(",");
		cur = cur->next;
	}
}

void	print_cmd(t_cmd *cur)
{
	int	i;
	int	j;

	j = 0;
	while (cur)
	{
		i = 0;
		printf("               commande %d : [%s]\n", j++, cur->argv[i]);
		printf("outfile: %d\n", cur->outfile);
		printf("infile: %d\n", cur->infile);
		printf("isfirst: %d\n", cur->isfirst);
		printf("islast: %d\n", cur->islast);
		while (cur->argv[i])
		{
			printf("argv[%i] = %s\n", i, cur->argv[i]);
			i++;
		}
		if (cur->red)
		{
			printf("cette commande contient redirection :\n");
			print_token_3(cur->red);
		}
		cur = cur->next;
	}
}

void	print_env(t_env_var *env)
{
	while (env)
	{
		printf("%s=%s\n", env->cle, env->value);
		env = env->next;
	}
}
