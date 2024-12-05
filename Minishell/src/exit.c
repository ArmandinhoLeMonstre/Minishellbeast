/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:17:44 by armitite          #+#    #+#             */
/*   Updated: 2024/12/05 19:12:44 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exit(char *arg, long n)
{

	if (arg)
	{
		ft_printf_fd(1, "exit\n");
		ft_printf_fd(2, "minishell: exit: %s: numeric argument required\n",
			arg);
		exit(g_exitcode = 255);
	}
	else
	{
		ft_printf_fd(1, "exit\n");
		exit(g_exitcode = n % 256);
	}
}

static long	ft_atol(const char *str, int *overflow)
{
	int		i;
	int		sign;
	long	num;
	long	buf;

	i = 0;
	sign = 1;
	num = 0;
	buf = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9' && !*overflow)
	{
		num = (num * 10) + (str[i++] - 48) * sign;
		if ((buf > num && sign > 0) || (buf < num && sign < 0))
			*overflow = 1;
		buf = num;
	}
	if ((str[i] && (str[i] < 9 || str[i] > 13 || (str[i] != 32))))
		*overflow = 1;
	return (num);
}

void	exit_built(char **cmd_built)
{
	char	*arg;
	long	n;
	int		overflow;

	if (!cmd_built[1])
	{
		ft_printf_fd(1, "exit\n");
		exit(g_exitcode);
	}
	arg = ft_strdup(cmd_built[1]);
	overflow = 0;
	n = ft_atol(arg, &overflow);
	if (overflow)
		ft_exit(arg, n);
	if (cmd_built[2])
	{
		ft_printf_fd(2, "minishell: exit: too many arguments\n");
		g_exitcode = 1;
	}
	else
		ft_exit(NULL, n);
	free(arg);
}
