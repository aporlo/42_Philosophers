/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:24:00 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/07 16:24:01 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phillosophers.h"
void*    routine(void* arg)
{
    t_philo *philo;

    philo = (t_philo*) arg;

    if (philo->id % 2 == 0)
        usleep(50);
    if (philo->data->n_philo == 1 )
        my_usleep(philo->data->t_die, philo);
    while(philo->data->die == 0)
    {
        if (philo->data->n_mustEat > 0 && philo->data->n_philo == philo->data->count_eat)
            break;
        if (philo->data != NULL && philo->data->die == 0)
        {
            pthread_mutex_lock(&philo->data->fork[philo->id % philo->data->n_philo]);
            pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
            print_ph(philo, "has take a fork");
            print_ph(philo, "has take a fork");
            eating(philo);
            pthread_mutex_unlock(&philo->data->fork[philo->id % philo->data->n_philo]);
            pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
            phi_sleep(philo);
            thinking(philo);
        }
        
    }
    return arg;
}

void   eating(t_philo *philo)
{
    if (philo->data != NULL && philo->data->die == 0)
    {
        print_ph(philo, "is eating");
        my_usleep(philo->data->t_eat, philo);
        pthread_mutex_lock(&philo->data->print);
        philo->n_eat++;
        // printf("id %d n eat is %d\n", philo->id, philo->n_eat);
    
        if (philo->n_eat == philo->data->n_mustEat)
        {
            philo->data->count_eat++;
            // printf("id %d count eat is %d\n", philo->id, philo->data->count_eat);
        }
        pthread_mutex_unlock(&philo->data->print);
    }
}

void   phi_sleep(t_philo *philo)
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

void   thinking(t_philo *philo)
{
    if (philo->data != NULL && philo->data->die == 0)
    {
        philo->t_eating = philo->t_current;
        print_ph(philo, "is thinking");
        pthread_mutex_unlock(&philo->data->print);
    }
}

void    create_thread(t_philo   *philo, t_data *data)
{
    int i;
    t_philo *new_join;

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
void    create(t_philo *philo)
{
    if (pthread_create(&philo->t1, NULL, &routine, (void*)philo) != 0)
        printf("Failed to create thread");
}

void    join(t_philo *philo)
{
    if (pthread_join(philo->t1, (void*)philo) != 0)
        printf("Failed to join thread");
}

void check_die(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print);
    if (philo->data->die == 0 && philo->t_life >= philo->data->t_die)
    {
        current_time(philo, philo->data);
        philo->data->die = philo->id;
        printf("%zu ms %d ", philo->t_life, philo->id);
        printf("%s\n", "died");
    }
    pthread_mutex_unlock(&philo->data->print);
}

int philo_die(t_philo *philo)
{
    int i;

    i = 0;
    while(i < philo->data->n_philo)
    {
        if (philo->status == S_DIED)
            return (1);
        philo = philo->next;
        i++;
    }
    return (0);
}
