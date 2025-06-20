/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:02:18 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/06/19 20:14:46 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_pid_var(t_token_node **new_debut, t_token_node *debut)
{
	add_lst_back_token(new_debut, new_token(debut->type, ft_itoa(getpid()),
			debut->fd_hrd));
}

void	ft_expand_var(t_token_node *debut, t_env_var *env, t_minishell *data)
{
	char	*str_var;
	char	*str_exp;

	str_var = debut->value;
	if (ft_strlen(str_var) == 1)
		debut->value = ft_strdup("$");
	else
	{
		str_exp = expand_segment(str_var, env, data);
		debut->value = str_exp;
	}
}

//->ajouter 
void	add_mots_to_new_list(t_token_node **new_debut, char **mots)
{
	t_token_node	*tmp;
	t_token_node	*new;
	int				i;
	int				is_hrd;

	is_hrd = search_hrd(*new_debut);
	i = 0;
	tmp = NULL;
	while (mots && mots[i])
	{
		if (!is_espace(mots[i][0]))
			new = new_token(VAR, mots[i], -2);
		else if  (is_espace(mots[i][0]) && is_hrd == 1)//ici
			new = new_token(STRING, mots[i], -2);
		else if  (is_espace(mots[i][0]))//ici
			new = new_token(SPC, mots[i], -2);
		new->flag = 4;
		add_lst_back_token(new_debut, new);
		if (!tmp)
			tmp = new;
		// if (mots[i + 1])
		// {
		// 	if (is_hrd == 1)
		// 		add_lst_back_token(new_debut, new_token(STRING, " ", -2));
		// 	// else
		// 	// 	add_lst_back_token(new_debut, new_token(SPC, "  ", -2));
		// }
		i++;
	}
	if (tmp && i > 1)
		tmp->flag = true;
	// print_token(*new_debut);
}
//

// void	add_mots_to_new_list(t_token_node **new_debut, char **mots)
// {
// 	t_token_node	*tmp;
// 	t_token_node	*new;
// 	int				i;
// 	int				is_hrd;

// 	is_hrd = search_hrd(*new_debut);
// 	i = 0;
// 	tmp = NULL;
// 	while (mots && mots[i])
// 	{
// 		new = new_token(VAR, mots[i], -2);
// 		new->flag = 4;
// 		add_lst_back_token(new_debut, new);
// 		if (!tmp)
// 			tmp = new;
// 		if (mots[i + 1])
// 		{
// 			if (is_hrd == 1)
// 				add_lst_back_token(new_debut, new_token(STRING, " ", -2));
// 			else
// 				add_lst_back_token(new_debut, new_token(SPC, " ", -2));
// 		}
// 		i++;
// 	}
// 	if (tmp && i > 1)
// 		tmp->flag = true;
// }

//--> ajuter 
char **split_words_and_spaces(const char *str)
{
    int len = ft_strlen(str);
    char **result = ft_malloc((len + 2) * sizeof(char *)); // +2 pour mot final + NULL
    int i = 0, j = 0;

	if (!str)
		return (NULL);
    while (str[i])
	{
        if (str[i] == ' ')
		{
            // Allouer une chaîne juste pour un espace
            result[j] = ft_malloc(2); // 1 caractère + '\0'
            result[j][0] = ' ';
            result[j][1] = '\0';
            j++;
            i++;
        }
		else
		{
            // C'est un mot, collecter jusqu'à prochain espace
            int start = i;
            while (str[i] && str[i] != ' ')
                i++;

            int word_len = i - start;
            result[j] = ft_malloc(word_len + 1);
            strncpy(result[j], str + start, word_len);
            result[j][word_len] = '\0';
            j++;
        }
    }
    result[j] = NULL; // Fin du tableau
    return result;
}

//


void	expand_typ_var(t_token_node **new_debut, t_token_node *debut,
		t_env_var *env, t_minishell *data)
{
	char			**mots;
	t_token_node	*new;
	int 			x=0;
	// printf("******************\n");
	ft_expand_var(debut, env, data);
	// print_token();
	// printf("******************\n");
	mots = split_words_and_spaces(debut->value);
	// exit(1);
	if (x == 1)
		mots = ft_decoupe_en_mots(debut->value);
	if (!mots || !mots[0])
	{
		new = new_token(VAR, NULL, debut->fd_hrd);
		new->flag = true;
		add_lst_back_token(new_debut, new);
	}
	add_mots_to_new_list(new_debut, mots);
}

t_token_node	*expand_var(t_token_node *debut, t_env_var *env,
		t_minishell *data)
{
	t_token_node	*new_debut;

	new_debut = NULL;
	while (debut)
	{
		if (debut->type == EXIT_STATUS)
		{
			debut->value = ft_itoa(data->exit_status);
			add_lst_back_token(&new_debut, new_token(STRING, debut->value,
					debut->fd_hrd));
		}
		else if (debut->type == VAR)
			expand_typ_var(&new_debut, debut, env, data);
		else if (debut->type == DOUBLE_Q && debut->value[0])
			add_lst_back_token(&new_debut, new_token(debut->type,
					expand_vars_and_heredoc(debut->value, env, data),
					debut->fd_hrd));
		else if (debut->type == DOUBLE_DLR)
			expand_pid_var(&new_debut, debut);
		else
			add_lst_back_token(&new_debut, new_token(debut->type, debut->value,
					debut->fd_hrd));
		debut = debut->next;
	}
	// printf("----expn------>\n");
	// print_token(new_debut);
	// printf("<--------------\n");
	return (new_debut);
}
