/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:29:11 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/09 14:29:13 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phillosophers.h"

void	dinning(t_philo *philo)
{
	int	i;
	int	j;

	i = philo->id % philo->data->n_philo;
	j = philo->id - 1;
	pthread_mutex_lock(&philo->data->fork[i]);
	pthread_mutex_lock(&philo->data->fork[j]);
	print_ph(philo, "has take a fork");
	print_ph(philo, "has take a fork");
	eating(philo);
	pthread_mutex_unlock(&philo->data->fork[i]);
	pthread_mutex_unlock(&philo->data->fork[j]);
	phi_sleep(philo);
	thinking(philo);
}

void	eating(t_philo *philo)
{
	int		n_musteat;

	if (philo->data != NULL && philo->data->die == 0)
	{
		n_musteat = philo->data->n_musteat;
		if (philo->n_eat != n_musteat || n_musteat == 0)
			print_ph(philo, "is eating");
		my_usleep(philo->data->t_eat, philo);
		pthread_mutex_lock(&philo->data->print);
		philo->n_eat++;
		if (philo->n_eat == philo->data->n_musteat)
			philo->data->count_eat++;
		pthread_mutex_unlock(&philo->data->print);
	}
}

void	phi_sleep(t_philo *philo)
{
	if (philo->data != NULL && philo->data->die == 0)
	{
		philo->t_life = 0;
		philo->t_eating = philo->t_current;
		print_ph(philo, "is sleeping");
		my_usleep(philo->data->t_sleep, philo);
		philo->t_life += philo->data->t_sleep;
	}
}

void	thinking(t_philo *philo)
{
	if (philo->data != NULL && philo->data->die == 0)
	{
		philo->t_eating = philo->t_current;
		print_ph(philo, "is thinking");
		pthread_mutex_unlock(&philo->data->print);
	}
}
