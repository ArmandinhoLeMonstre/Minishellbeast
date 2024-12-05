/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:18:08 by armitite          #+#    #+#             */
/*   Updated: 2024/12/03 11:25:08 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_char(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	return (i);
}

static int	envchr(char *name, t_env *env)
{
	t_env	*tmp;

	if (!env)
		return (0);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, INT_MAX))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	set_value(char *name, char *value, t_env **env, int p)
{
	t_env	*top;

	top = *env;
	while (top && p)
	{
		if (!ft_strncmp(top->name, name, INT_MAX))
		{
			free(top->value);
			top->value = value;
			top->equal = p;
			return ;
		}
		top = top->next;
	}
	free(value);
}

static void	set_var(char *str, t_env **env)
{
	int		len;
	char	*name;
	char	*value;
	int		p;

	len = find_char(str, '=');
	name = ft_substr(str, 0, len);
	value = ft_substr(str, len + 1, INT_MAX);
	if (ft_strchr(str, '='))
		p = 1;
	else
		p = 0;
	if (envchr(name, *env))
		return (set_value(name, value, env, p), free(name));
	else
		append_list(env, str);
	free(name);
	free(value);
}

void	export(char **cmd_built, t_env **env)
{
	int	i;

	if (!cmd_built[1])
	{
		sort_env(*env);
		return ;
	}
	i = 1;
	while (cmd_built[i])
	{
		if (!check_identifier(cmd_built[i]))
		{
			ft_printf_fd(2, "bash: export: %s: not a valid identifier\n",
				cmd_built[i]);
			g_exitcode = 1;
		}
		else
			set_var(cmd_built[i], env);
		i++;
	}
}
