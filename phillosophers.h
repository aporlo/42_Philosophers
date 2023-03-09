/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phillosophers.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:23:08 by lsomrat           #+#    #+#             */
/*   Updated: 2023/03/09 15:17:07 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILLOSOPHERS_H
# define PHILLOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	int				count_eat;
	int				die;
	int				n_musteat;
	int				n_philo;
	size_t			t_eat;
	size_t			t_die;
	size_t			t_sleep;
	size_t			t_think;
	size_t			t_start;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	pthread_t		t1;
	int				id;
	int				status;
	int				n_eat;
	size_t			t_current;
	size_t			t_life;
	size_t			t_eating;
	t_data			*data;
	struct s_philo	*next;
}	t_philo;

int			is_digit(int c);
int			ft_atoi(const char *s);
int			validate(int argc, char **argv);
void		init_data(char **argv, t_data *data);
t_philo		*create_philo(t_data *data, int id);
void		add_philo(t_philo **philo, t_data *data);
void		philoadd_back(t_philo **philo, t_philo *new);
void		*routine(void *arg);
void		create_thread(t_philo *philo, t_data *data);
void		create(t_philo *philo);
void		join(t_philo *philo);
void		dinning(t_philo *philo);
void		eating(t_philo *philo);
void		phi_sleep(t_philo *philo);
void		thinking(t_philo *philo);
long long	get_time(void);
void		current_time(t_philo *philo, t_data *data);
void		my_usleep(size_t time, t_philo *philo);
void		check_die(t_philo *philo);
int			check_limit(t_data data);
void		print_ph(t_philo *philo, char *status);
void		free_fork(t_philo *philo);
void		free_philo(t_philo **philo);

#endif
