/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:16:48 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/09 16:04:07 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	restore_fd(t_cmd *cmd)
{
	dup2(cmd->infile, STDIN_FILENO);
	dup2(cmd->outfile, STDOUT_FILENO);
	close(cmd->infile);
	close(cmd->outfile);
}

void	update_env_value(t_env_var **env, char *key, char *value)
{
	t_env_var	*curr;

	curr = *env;
	while (curr)
	{
		if (strcmp(curr->cle, key) == 0)
		{
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
}

static void	update_last_arg(t_cmd *cmd, t_minishell *data)
{
	int		i;
	char	*last_arg;

	i = 0;
	last_arg = NULL;
	while (cmd->argv && cmd->argv[i])
		i++;
	if (i > 0)
		last_arg = cmd->argv[i - 1];
	if (last_arg)
		update_env_value(&data->envp, "_", last_arg);
}

static int	execute_single_cmd(t_cmd *cmd, t_minishell *data)
{
	if (set_redirection(cmd, data) == -1)
	{
		close(cmd->infile);
		close(cmd->outfile);
		return (0);
	}
	if (!cmd->argv || !cmd->argv[0])
	{
		restore_fd(cmd);
		return (0);
	}
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		close_fds_except_std();
		exec_exit(&cmd->argv[0], false, data);
		return (0);
	}
	if (is_builtin(cmd->argv[0]))
		exec_builtin(cmd, data);
	else
		exec_external(cmd, data);
	restore_fd(cmd);
	update_last_arg(cmd, data);
	return (1);
}

void	execute_cmds(t_minishell *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_list;
	if (!data || !cmd)
		return ;
	if (!cmd->next)
	{
		if (execute_single_cmd(cmd, data) == 0)
			return ;
	}
	else
	{
		execute_pipeline(cmd, data);
		update_env_value(&data->envp, "_", "");
	}
}
