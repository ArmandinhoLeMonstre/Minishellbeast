/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:44:45 by armitite          #+#    #+#             */
/*   Updated: 2024/12/03 11:22:22 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isbuiltin(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "export") == 0 || ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "env") == 0)
		return (1);
	else
		return (0);
}

static int	ft_env(t_env *node)
{
	if (!node)
		return (1);
	while (node)
	{
		if (node->value)
			ft_printf_fd(1, "%s=%s\n", node->name, node->value);
		else if (!node->value && node->equal)
			ft_printf_fd(1, "%s=\n", node->name);
		node = node->next;
	}
	ft_printf_fd(1, "_=/usr/bin/env\n");
	return (0);
}

int	ft_builtins(char **cmd_built, t_env **env)
{
	t_env	*node;

	if (!cmd_built[0])
		return (1);
	g_exitcode = 0;
	node = *env;
	if (ft_strncmp(cmd_built[0], "cd", INT_MAX) == 0)
		return (cd(cmd_built, env), 0);
	else if (ft_strncmp(cmd_built[0], "pwd", INT_MAX) == 0)
		return (pwd(env), 0);
	else if (ft_strncmp(cmd_built[0], "unset", INT_MAX) == 0)
		return (unset(cmd_built, env), 0);
	else if (ft_strncmp(cmd_built[0], "export", INT_MAX) == 0)
		return (export(cmd_built, env), 0);
	else if (ft_strncmp(cmd_built[0], "env", INT_MAX) == 0)
	{
		if (!ft_env(node))
			return (0);
	}
	else if (ft_strncmp(cmd_built[0], "exit", INT_MAX) == 0)
		return (exit_built(cmd_built), 0);
	return (1);
}
