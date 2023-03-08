/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phillosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:08 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/07 16:23:11 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILLOSOPHERS_H
# define PHILLOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define S_DIED 1

typedef  struct s_data
{
    int     n_philo;
    int     die;
    int     count_eat;
    size_t  t_eat;
    size_t  t_die;
    size_t  t_sleep;
    size_t  t_think;
    int     n_mustEat;
    size_t  t_start;
    pthread_mutex_t *fork;
    pthread_mutex_t print;
}   t_data;

typedef struct  s_philo
{
    pthread_t           t1;
    int                 id;
    int                 status;
    int                 n_eat;
    size_t              t_current;
    size_t              t_life;
    size_t              t_eating;
    t_data              *data;
    struct s_philo      *next;
}   t_philo;

int     is_digit(int c);
int     ft_atoi(const char *s);
int	    validate(int argc, char **argv);
void    init_data(char **argv, t_data *data);
t_philo    *create_philo(t_data *data, int id);
void    add_philo(t_philo **philo, t_data *data);
void    philoadd_back(t_philo  **philo, t_philo *new);
void*    routine(void* arg);
void    create_thread(t_philo   *philo, t_data *data);
void    create(t_philo *philo);
void    join(t_philo *philo);
void    eating(t_philo *philo);
void    phi_sleep(t_philo *philo);
void    thinking(t_philo *philo);
long long   get_time();
void    current_time(t_philo *philo, t_data *data);
void    my_usleep(size_t time, t_philo *philo);
void     check_die(t_philo *philo);
int     philo_die(t_philo *philo);
void    print_ph(t_philo *philo, char *status);

#endif
