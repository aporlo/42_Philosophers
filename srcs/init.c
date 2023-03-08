/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:52 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/07 16:23:54 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phillosophers.h"

int	ft_atoi(const char *s)
{
	unsigned int	n;
	int				i;
	int				sign;

	i = 0;
	n = 0;
	sign = 1;
	while ((s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		|| s[i] == '\f' || s[i] == '\v' || s[i] == '\r')
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + (s[i] - '0');
		i++;
	}
	return ((int)(sign * n));
}

void	init_data(char **argv, t_data *data)
{
	int	i;

	i = 0;
	data->n_philo = ft_atoi(argv[1]);
	data->die = 0;
    data->count_eat = 0;
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->t_think = 0;
	if (argv[5])
		data->n_mustEat = ft_atoi(argv[5]);
	else
		data->n_mustEat = 0;
	data->t_start = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			write(2, "Failed to mutex init", 20);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0)
		write(2, "Failed to mutex init", 20);
}

t_philo	*create_philo(t_data *data, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->id = id;
	philo->n_eat = 0;
	philo->status = 0;
	philo->t_current = 0;
	philo->t_life = 0;
	philo->data = data;
	philo->next = NULL;
	return (philo);
}

void	add_philo(t_philo **philo, t_data *data)
{
	int		i;
	t_philo	*new_philo;

	i = 0;
	while (i < data->n_philo)
	{
		new_philo = create_philo(data, i + 1);
		philoadd_back(philo, new_philo);
		i++;
	}
}

void	philoadd_back(t_philo  **philo, t_philo *new)
{
	t_philo *last;

	if (*philo == NULL)
	{
		*philo = new;
    }
    else
    {
        last = *philo;
        while (last->next)
        {
            last = last->next;
        }
        last->next = new;
    }
}
