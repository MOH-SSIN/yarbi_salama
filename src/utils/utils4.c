/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idahhan <idahhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:01:47 by idahhan           #+#    #+#             */
/*   Updated: 2025/06/09 16:30:56 by idahhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_signal_output(int signal_type)
{
	if (signal_type == SIGINT)
		write(1, "\n", 1);
	else if (signal_type == SIGQUIT)
		;
}

static void	set_final_status(int last_status, int any_signal, int signal_type,
		t_minishell *data)
{
	if (any_signal)
	{
		handle_signal_output(signal_type);
		if (signal_type != SIGINT && signal_type != SIGQUIT)
		{
			data->exit_status = 0;
			return ;
		}
	}
	if (WIFEXITED(last_status))
		data->exit_status = WEXITSTATUS(last_status);
	else if (WIFSIGNALED(last_status))
		data->exit_status = 128 + WTERMSIG(last_status);
}

void	wait_for_children(pid_t last_pid, t_minishell *data)
{
	int		status;
	pid_t	pid;
	int		last_status;
	int		any_signal;
	int		signal_type;

	last_status = 0;
	any_signal = 0;
	signal_type = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
			last_status = status;
		if (WIFSIGNALED(status) && !any_signal)
		{
			any_signal = 1;
			signal_type = WTERMSIG(status);
		}
		pid = wait(&status);
	}
	set_final_status(last_status, any_signal, signal_type, data);
}
