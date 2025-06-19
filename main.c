/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 01:23:06 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/19 14:54:03 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int			g_status = 0;

// int	oui_space(char *str)
// {
// 	while(*str)
// 	{
// 		if (!is_espace(*str))
// 			return(0);
// 		str++;	
// 	}
// 	return (1);
// }


// t_token_node *ft_mohcine(t_token_node *debut)
// {
//     t_token_node	*temp;
// 	t_token_node	*curt = NULL;
// 	t_token_node	*chek;

// 	temp = debut;
//     while (temp)
//     {
//         if (temp->flag == 1 && ft_fofo(temp->value, '=') == 1)
// 		{
// 			curt = temp;
// 			break ;
// 		}
// 		temp = temp->next;
//     }
// 	if (curt == NULL)
// 		return debut;
// 	while (curt)
// 	{
// 		if (oui_space(curt->value))
// 		{
// 			chek = curt->next;
// 			if (chek && chek->flag == 1 && ft_fofo(chek->value, '=') == 1)
// 				curt->type = SPC;
// 		}
// 		curt = curt->next;
// 	}
//     return debut;
// }

// t_token_node	*ikram(t_token_node *debut)
// {
// 	t_token_node *temp;
// 	t_token_node *next;

// 	temp = debut;
// 	while (temp)
// 	{
// 		if (ft_fofo(temp->value, '=') && temp->flag == 1)
// 		{
// 			next = temp->next;
// 			while (next && !(ft_fofo(next->value, '=') && next->flag == 1))
// 			{
// 				if (next->type == SPC)
// 					next->type = STRING;
// 				next = next->next;
// 			}
// 			temp = next;
// 			continue;
// 		}
// 		temp = temp->next;
// 	}
// 	return (ft_mohcine(debut));
// 	return (debut);
// }




// nouvelle version 
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
t_token_node *ft_mohcine(t_token_node *debut)
{
	t_token_node	*temp;
	t_token_node	*curt = NULL;
	t_token_node	*chek;

	temp = debut;
	while (temp)
	{
		if (temp->flag == 1 && ft_fofo(temp->value, '='))
		{
			curt = temp;
			break ;
		}
		temp = temp->next;
	}
	if (curt == NULL)
		return debut;
	while (curt)
	{
		if (oui_space(curt->value))
		{
			chek = curt->next;
			if (chek && chek->flag == 1 && ft_fofo(chek->value, '='))
				curt->type = SPC; // Ne pas toucher : entre deux affectations
		}
		curt = curt->next;
	}
	return debut;
}

t_token_node	*ikram(t_token_node *debut)
{
	t_token_node *temp;
	t_token_node *next;

	temp = debut;
	while (temp)
	{
		if (ft_fofo(temp->value, '=') && temp->flag == 1)
		{
			next = temp->next;
			while (next && !(ft_fofo(next->value, '=') && next->flag == 1))
			{
				next->type = 5;   // transforme tout en type VAR_ASSIGN ou équivalent
				next->flag = 1;   // indique que ça fait partie de la valeur d’affectation
				next = next->next;
			}
			temp = next;
			continue;
		}
		temp = temp->next;
	}
	return ft_mohcine(debut);
}

t_token_node *ikram_2(t_token_node *debut)
{
	t_token_node *temp;

	temp = debut;
	while (temp)
	{
		if (temp->type == SPC && temp->flag == 1)
			temp->type = STRING;
		temp = temp->next;
	}
	return (debut);
}
//fihicer pour test ok

t_token_node *hiba_diba(t_token_node *debut)
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

#include <stdbool.h>

bool	start_zone_has_equal(t_token_node *start)
{
	return (start && start->flag == 1 && ft_strchr(start->value, '='));
}

t_token_node *ikram_batbota(t_token_node *head)
{
	t_token_node *new_list = NULL;
	t_token_node *cur = head;
	t_token_node *tmp;
	char *joined;

	while (cur)
	{
		if (cur->flag == 1 && start_zone_has_equal(cur))
		{
			// On commence la concaténation
			joined = NULL;
			while (cur && cur->flag == 1)
			{
				joined = ft_strjoin(joined, cur->value);
				cur = cur->next;
			}
			tmp = new_token(5, joined, -2); // type 5 = STRING ou VAR_ASSIGN
			tmp->flag = 1;
			add_lst_back_token(&new_list, tmp);
		}
		else if (cur->flag == 1)
		{
			// Zone flag==1 mais ne commence pas par `=`, on copie sans concat
			while (cur && cur->flag == 1)
			{
				tmp = new_token(cur->type, cur->value, cur->fd_hrd);
				tmp->flag = 1;
				add_lst_back_token(&new_list, tmp);
				cur = cur->next;
			}
		}
		else
		{
			// Zone flag == 0, on copie normalement
			tmp = new_token(cur->type, cur->value, cur->fd_hrd);
			tmp->flag = cur->flag;
			add_lst_back_token(&new_list, tmp);
			cur = cur->next;
		}
	}
	return new_list;
}


//

t_cmd	*ft_prepare_cmd(t_token_node *debut_token, t_env_var *debut_env,
		t_minishell *data)
{
	t_token_node	*debut;
	t_cmd			*cmd_final;

	debut = expand_var(debut_token, debut_env, data);
	// exit(1);
	print_token(debut);
	printf("****\n");
	debut = hiba_diba(debut);
	debut = ikram_batbota(debut);
	print_token(debut);
	// exit(1);
	// debut = ft_concate_tkn(debut);
	// debut = ikram_2(debut);
	// debut = ikram(debut);
	debut = ft_concate_tkn(debut);
	// debut = ikram_2(debut);
	debut = remove_red(debut);
	debut = remove_invalid_tokens(debut);

	cmd_final = token_list_to_cmd_list(debut);
	return (cmd_final);
}
// t_cmd	*ft_prepare_cmd(t_token_node *debut_token, t_env_var *debut_env,
// 		t_minishell *data)
// {
// 	t_token_node	*debut;
// 	t_cmd			*cmd_final;

// 	debut = expand_var(debut_token, debut_env, data);
// 	// exit(1);
// 	print_token(debut);
// 	printf("****\n");
// 	// exit(1);
// 	debut = ft_concate_tkn(debut);
// 	// debut = ikram_2(debut);
// 	debut = ikram(debut);
// 	print_token(debut);
// 	debut = ft_concate_tkn(debut);
// 	// debut = ikram_2(debut);
// 	debut = remove_red(debut);
// 	debut = remove_invalid_tokens(debut);

// 	cmd_final = token_list_to_cmd_list(debut);
// 	return (cmd_final);
// }

void	handle_input(t_env_var *debut_env, t_minishell *data)
{
	char			*command;
	t_token_node	*debut_token;
	t_cmd			*cmd_final;

	(1) && (command = NULL, cmd_final = NULL);
	while (1 && isatty(STDIN_FILENO))
	{
		debut_env = data->envp;
		debut_token = NULL;
		gestion_input(&command, &debut_token, debut_env, data);
		if (invalide_fd_hrdc(debut_token) == 1)
			clean_cmd_line(command);
		else if (verify_cmd(debut_token, command, true) == -1)
			clean_exit(command, data);
		else
		{
			cmd_final = ft_prepare_cmd(debut_token, debut_env, data);
			data->cmd_list = set_cmd_false_true(&cmd_final);
			execute_cmds(data);
			print_cmd(cmd_final);
			clean_cmd_line(command);
		}
		if (command)
			free(command);
		g_status = 0;
	}
}

t_env_var	*find_env(t_env_var *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->cle, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	handle_shlvl(t_env_var **env)
{
	t_env_var	*node;
	int			lvl;

	node = find_env(*env, "SHLVL");
	if (node && node->value)
	{
		lvl = ft_atol(node->value);
		if (lvl < 0)
			node->value = ft_itoa(0);
		else if (lvl == 999)
		{
			node->value = ft_strdup("");
			lvl = 0;
		}
		else if (lvl >= 1000)
			node->value = ft_itoa(1);
		else
		{
			lvl++;
			node->value = ft_itoa(lvl);
		}
	}
	else
		add_new_env("SHLVL", "1", true);
}

int	main(int argc, char **argv, char **env)
{
	t_env_var	*debut_env;
	t_minishell	data;
	char		*pwd_env;

	(void)argc;
	(void)argv;
	debut_env = NULL;
	init_env(&debut_env, env, &data);
	data.envp = debut_env;
	data.exit_status = 0;
	handle_shlvl(&data.envp);
	pwd_env = get_env_value_char(data.envp, "PWD");
	if (pwd_env)
		ft_strlcpy(data.logical_pwd, pwd_env, PATH_MAX);
	else if (getcwd(data.logical_pwd, PATH_MAX))
		;
	else
		ft_strlcpy(data.logical_pwd, "", PATH_MAX);
	handle_input(debut_env, &data);
	free_env(debut_env);
	return (0);
}

/*
Minishell$ export a="b c= d="
➜ Minishell$ export $a
➜ Minishell$ export p=$a
➜ Minishell$ export



export a=$var b=$var_1 c=$var_2  d=$var_3  e=$var_4 f=$var_5 



*/