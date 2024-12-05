/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:41:38 by armitite          #+#    #+#             */
/*   Updated: 2024/12/05 19:07:48 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_env(t_env **env)
{
	t_env	*node;
	int		len;
	char	**envp;
	char	*tmp;

	len = ft_len_list(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	node = *env;
	len = 0;
	while (node)
	{
		if (node->value != NULL)
		{
			tmp = ft_strjoin(node->name, "=");
			envp[len] = ft_strjoin(tmp, node->value);
			free(tmp);
			if (!envp[len++])
				return (NULL);
		}
		node = node->next;
	}
	envp[len] = 0;
	return (envp);
}
