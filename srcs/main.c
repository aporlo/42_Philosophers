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
	t_data 	data;
	t_philo	*philo;
	int i;

	i = 0;
	philo = NULL;
	if (!validate(argc, argv))
		return (0);
	init_data(argv, &data);
	if (data.t_eat < 60 || data.t_sleep < 60 || data.t_die < 60)
	{
		printf("eat time and sleep time must 60ms");
		return (0);
	}
	if (data.n_philo == 1)
		philo = create_philo(&data, data.n_philo);
	else
		add_philo(&philo, &data);
	create_thread(philo, &data);
	while (i < philo->data->n_philo)
	{
		pthread_mutex_destroy(&philo->data->fork[i]);
		i++;
	}
	free(data.fork);
	pthread_mutex_destroy(&philo->data->print);
	// สร้างclear linklist philo
	return (0);
}
