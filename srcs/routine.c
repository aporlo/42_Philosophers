/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:24:00 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/09 21:49:47 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phillosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	int		n_philo;
	int		count;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		usleep(50);
	if (philo->data->n_philo == 1)
		my_usleep(philo->data->t_die, philo);
	while (philo->data->die == 0)
	{
		printf("data is%d\n", philo->data->die);
		n_philo = philo->data->n_philo;
		count = philo->data->count_eat;
		if (philo->data->n_musteat > 0 && n_philo == count)
			break ;
		if (philo->data != NULL && philo->data->die == 0)
			dinning(philo);
		printf("hello1\n");
	}
	printf("hello2\n");
	return (arg);
}

void	create_thread(t_philo *philo, t_data *data)
{
	int		i;
	t_philo	*new_join;

	i = 0;
	new_join = philo;
	data->t_start = get_time();
	while (i < data->n_philo && philo)
	{
		create(philo);
		philo = philo->next;
		i++;
	}
	i = 0;
	while (i < data->n_philo && new_join)
	{
		join(new_join);
		new_join = new_join->next;
		i++;
	}
	usleep(500);
}

void	create(t_philo *philo)
{
	if (pthread_create(&philo->t1, NULL, &routine, (void *)philo) != 0)
		printf("Failed to create thread");
}

void	join(t_philo *philo)
{
	if (pthread_join(philo->t1, (void *)philo) != 0)
		printf("Failed to join thread");
}

void	check_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->die == 0 && philo->t_life >= philo->data->t_die)
	{
		philo->data->die = philo->id;
		printf("%zu ms %d ", philo->t_life, philo->id);
		printf("%s\n", "died");
	}
	pthread_mutex_unlock(&philo->data->print);
}
