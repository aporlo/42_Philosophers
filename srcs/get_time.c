/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:32 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/07 16:23:35 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../phillosophers.h"
#include <sys/time.h>

long long get_time()
{
	struct timeval te;
	long long ms;

	gettimeofday(&te, NULL); // get current time
	ms = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
	return ms;
}

void  current_time(t_philo *philo, t_data *data)
{
	size_t  ml_time;

	ml_time = get_time();
	philo->t_current = ml_time - (data->t_start);
	philo->t_life = (philo->t_current) - (philo->t_eating);
}

void   my_usleep(size_t time, t_philo *philo)
{
    size_t  start;
    size_t  end;
    size_t  life;

    life = philo->t_life;
    start = get_time();
    end = start + time;
    usleep(1000);
    while (start < end)
    {
        start = get_time();
        philo->t_life = life + (time - (end - start));
    }
    check_die(philo);
}
