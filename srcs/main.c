/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phillosophers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:44:29 by lsomrat           #+#    #+#             */
/*   Updated: 2023/02/25 19:44:31 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "phillosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (!validate(argc, argv))
		return (0);
	init_data(argv, &data);
	if (!check_limit(data))
		return (0);
	if (data.n_philo == 1)
		philo = create_philo(&data, data.n_philo);
	else
		add_philo(&philo, &data);
	create_thread(philo, &data);
	free_philo(&philo);
	free(data.fork);
	return (0);
}
