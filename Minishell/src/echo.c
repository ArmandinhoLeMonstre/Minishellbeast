/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:17:26 by armitite          #+#    #+#             */
/*   Updated: 2024/12/03 11:24:07 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_bool(char *cmd_built)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (cmd_built[i] != '-')
		return (n_flag);
	i++;
	while (cmd_built[i] && cmd_built[i] == 'n')
		i++;
	if (cmd_built[i] == '\0')
		n_flag = true;
	return (n_flag);
}

static void	echo_print(char **cmd_built, bool n_flag, int i)
{
	if (!cmd_built[i])
	{
		if (!n_flag)
			printf("\n");
		return ;
	}
	while (cmd_built[i])
	{
		printf("%s", cmd_built[i]);
		if (cmd_built[i + 1])
			printf(" ");
		else if (!cmd_built[i + 1] && !n_flag)
			printf("\n");
		i++;
	}
}

void	echo_built(char **cmd_built)
{
	int		i;
	bool	n_bool;

	n_bool = false;
	i = 1;
	while (cmd_built[i] && is_n_bool(cmd_built[i]))
	{
		n_bool = true;
		i++;
	}
	echo_print(cmd_built, n_bool, i);
}
