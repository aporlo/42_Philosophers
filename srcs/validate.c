/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:36:08 by lsomrat           #+#    #+#             */
/*   Updated: 2023/02/26 17:36:09 by lsomrat          ###   ########.fr       */
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
			i++;
		}
		return (1);
	}
	return (0);
}
