/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:17:14 by armitite          #+#    #+#             */
/*   Updated: 2024/12/03 11:23:45 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_findnode(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, INT_MAX) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	cd_error(t_env **env, t_built *var)
{
	var->dir = opendir(var->path);
	var->env_oldpwd = ft_findnode(*env, "OLDPWD");
	var->env_pwd = ft_findnode(*env, "PWD");
	var->env_home = ft_findnode(*env, "HOME");
	if (var->path && !var->dir && !diff_dir(var->path))
	{
		ft_printf_fd(2, "bash: cd: %s: %s\n", var->path, strerror(errno));
		g_exitcode = 1;
		return (0);
	}
	if (var->dir)
		closedir(var->dir);
	return (1);
}

void	cd(char **cmd_built, t_env **env)
{
	t_built	var;

	var.path = cmd_built[1];
	if (var.path && ft_strncmp(var.path, "--", INT_MAX) == 0)
		var.path = cmd_built[2];
	else if (var.path && cmd_built[2])
	{
		ft_printf_fd(2, "bash: cd: too many arguments\n");
		g_exitcode = 1;
		return ;
	}
	if (!cd_error(env, &var))
		return ;
	if (!var.path || ft_strncmp(var.path, "~", INT_MAX) == 0
		|| ft_strncmp(var.path, "#", INT_MAX) == 0)
	{
		cd_home(&var);
	}
	else if (ft_strncmp(var.path, "-", INT_MAX) == 0)
		cd_oldpwd(&var);
	else
		cd_dir(&var);
}
