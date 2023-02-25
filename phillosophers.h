#ifndef PHILLOSOPHERS_H
# define PHILLOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

typedef  struct s_phillo
{
    int n_phillo;
    int t_eat;
    int t_die;
    int t_sleep;
    int t_think;
    int t_mustEat;

}   t_phillo
#endif