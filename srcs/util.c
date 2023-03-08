#include "phillosophers.h"

void    print_ph(t_philo *philo, char *status)
{
    pthread_mutex_lock(&philo->data->print);
    if (philo->data->n_mustEat > 0 && philo->data->n_philo == philo->data->count_eat)
    {
        pthread_mutex_unlock(&philo->data->print);
        return ;
    }
    if (philo->data->die == 0)
    {
        current_time(philo, philo->data);
        printf("%zu ms %d %s\n",philo->t_current, philo->id , status);
    }
    pthread_mutex_unlock(&philo->data->print);
}