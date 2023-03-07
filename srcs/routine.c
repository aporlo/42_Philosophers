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
    while(philo->data->die == 0)
    {
        if (philo->id % 2 == 0)
            usleep(50);
        if (philo->data != NULL && philo->data->die == 0)
        {
            pthread_mutex_lock(&philo->data->fork[philo->id % philo->data->n_philo]);
            pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
            pthread_mutex_lock(&philo->data->print);
            current_time(philo, philo->data);
            printf("%zu ms %d ",philo->t_current, philo->id);
            printf("%s\n", "has taken a fork");
            printf("%zu ms %d ",philo->t_current, philo->id);
            printf("%s\n", "has taken a fork");
            pthread_mutex_unlock(&philo->data->print);
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
        pthread_mutex_lock(&philo->data->print);
        current_time(philo, philo->data);
        philo->t_eating = philo->t_current;
        printf("%zu ms %d ",philo->t_current, philo->id);
        printf("%s\n", "is eating");
        pthread_mutex_unlock(&philo->data->print);
        my_usleep(philo->data->t_eat, philo);
    }
}

void   phi_sleep(t_philo *philo)
{
    if (philo->data != NULL && philo->data->die == 0)
    {
        pthread_mutex_lock(&philo->data->print);
        current_time(philo, philo->data);
        philo->t_life = 0;
        philo->t_eating = philo->t_current;
        printf("%zu ms %d ",philo->t_current, philo->id);
        printf("%s\n", "is sleeping");
        pthread_mutex_unlock(&philo->data->print);
        my_usleep(philo->data->t_sleep, philo);
        philo->t_life += philo->data->t_sleep;
    }
}

void   thinking(t_philo *philo)
{
    if (philo->data != NULL && philo->data->die == 0)
    {
        pthread_mutex_lock(&philo->data->print);
        current_time(philo, philo->data);
        philo->t_eating = philo->t_current;
        printf("%zu ms %d ",philo->t_current, philo->id);
        printf("%s\n", "is thinking");
        pthread_mutex_unlock(&philo->data->print);
    }
}

void    create_thread(t_philo   *philo, t_data *data)
{
    int i;
    t_philo *new_join;
    // t_philo *detach_philo;
    
    i = 0;
    new_join = philo;
    data->t_start = get_time();
    // create(philo);
    // join(philo);
    // detach(philo);
    while(i < data->n_philo)
    {
        create(philo);
        philo = philo->next;
        i++;
    }
    i = 0;
    while(i < data->n_philo)
    {
        join(new_join);
        new_join = new_join->next;
        i++;
    }
    usleep(500);
}
void    create(t_philo *philo)
{
    // int i;
    
    // i = 0;
    // while(i < philo->data->n_philo)
    // {
        if (pthread_create(&philo->t1, NULL, &routine, (void*)philo) != 0)
            printf("Failed to create thread");
        // philo = philo->next;
        // i++;
    // }
}

void    join(t_philo *philo)
{
    if (pthread_join(philo->t1, (void*)philo) != 0)
        printf("Failed to join thread");
}

void    detach(t_philo *philo)
{
    int i;
    
    i = 0;
    while(i < philo->data->n_philo)
    {
        if (pthread_detach(philo->t1) != 0)
            printf("Failed to detach\n");
        philo = philo->next;
        i++;
    }
}

int check_die(t_philo *philo)
{
    if (philo->t_life >= philo->data->t_die)
    {
        pthread_mutex_lock(&philo->data->print);
        philo->data->die = philo->id;
        printf("%zu ms %d ", philo->t_life, philo->id);
        printf("%s\n", "died");
        // usleep(500);
        pthread_mutex_unlock(&philo->data->print);
        pthread_mutex_destroy(&philo->data->print);
        return (philo->id);
    }
    return (0);
}
