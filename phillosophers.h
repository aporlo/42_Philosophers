#ifndef PHILLOSOPHERS_H
# define PHILLOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef  struct s_data
{
    int n_phillo;
    size_t  t_eat;
    size_t  t_die;
    size_t  t_sleep;
    size_t  t_think;
    size_t  t_mustEat;
    size_t  t_start;
}   t_data;

typedef struct  s_phillo
{
    pthread_t   t1;
    int         id;
    size_t      t_current;
    t_data      s_data;
}   t_phillo;

int     is_digit(int c);
int	    validate(int argc, char **argv);

#endif
