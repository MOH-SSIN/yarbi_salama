

#include "../../include/minishell.h"

int	ft_fofo(char *str, char c)
{
	if (!str)
		return(0);
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}


t_token_node *ft_test(t_token_node *debut)
{
	t_token_node *temp;
	t_token_node *next;

	temp = debut;
	while (temp)
	{
		if (ft_fofo(temp->value, '=') == 1 && temp->flag == 1)
		{
			next = temp->next;
			if (next && next->type == SPC)
			{
				next->type = STRING;
				next = next->next;
				while (next && next->type == SPC)
				{
					next->type = STRING;
					next = next->next;
				}
			}
			temp = next;
			continue;
		}
		temp = temp->next;
	}
	return (debut);
}

/*
ona probelem ici
export a="ls -l -a"
export b=$a c=$a
*/