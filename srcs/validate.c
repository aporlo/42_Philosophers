/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:36:08 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/07 16:24:18 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phillosophers.h"

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	validate(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc >= 5 && argc <= 6)
	{
		while (i < argc)
		{
			j = 0;
			while (argv[i][j])
			{
				if (!is_digit(argv[i][j]))
					return (0);
				j++;
			}
			if (ft_atoi(argv[i]) <= 0)
			{
				printf("must positive\n");
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	check_limit(t_data data)
{
	if (data.t_eat < 60 || data.t_sleep < 60 || data.t_die < 60)
	{
		printf("eat time and sleep time must not under 60ms");
		return (0);
	}
	if (data.n_philo > 200)
	{
		printf("philo no more than 200 philosophers\n");
		return (0);
	}
	return (1);
}
