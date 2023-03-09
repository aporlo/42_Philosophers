/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:34:15 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/09 14:34:17 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phillosophers.h"

void	print_ph(t_philo *philo, char *status)
{
	int		n_philo;
	int		count;

	pthread_mutex_lock(&philo->data->print);
	n_philo = philo->data->n_philo;
	count = philo->data->count_eat;
	if (philo->data->n_musteat > 0 && n_philo == count)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	if (philo->data->die == 0)
	{
		current_time(philo, philo->data);
		printf("%zu ms %d %s\n", philo->t_current, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print);
}

void	free_fork(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		pthread_mutex_destroy(&philo->data->fork[i]);
		pthread_mutex_destroy(&philo->data->print);
		i++;
	}
}

void	ft_lstdelone(t_philo *philo)
{
	pthread_mutex_destroy(&philo->data->print);
	free_fork(philo);
	free(philo);
}

void	free_philo(t_philo **philo)
{
	t_philo	*temp;
	t_philo	*n_philo;

	n_philo = *philo;
	while (n_philo != NULL && n_philo->next != *philo)
	{
		temp = n_philo->next;
		ft_lstdelone(n_philo);
		n_philo = temp;
	}
}
