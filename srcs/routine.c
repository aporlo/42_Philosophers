#include "phillosophers.h"
void*    routine(void* arg)
{
    t_philo *philo;

    philo = (t_philo*) arg;
    while(philo->data->die == 0)
    {
        if (philo->id % 2 == 0)
            usleep(50);
        if (philo->data != NULL)
        {
            // check_die(philo);
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
    if (philo->data != NULL)
    {
        // check_die(philo);
        pthread_mutex_lock(&philo->data->print);
        current_time(philo, philo->data);
        philo->t_eating = philo->t_current;
        printf("%zu ms %d ",philo->t_current, philo->id);
        printf("%s\n", "is eating");
        pthread_mutex_unlock(&philo->data->print);
        my_usleep(philo->data->t_eat, philo);
        // printf("%zu ms %d ",philo->data->t_eat, philo->id);
    }
}

void   phi_sleep(t_philo *philo)
{
    if (philo->data != NULL)
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
        // check_die(philo);
    }
}

void   thinking(t_philo *philo)
{
    if (philo->data != NULL)
    {
        // check_die(philo);
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
    
    i = 0;
    new_join = philo;
    data->t_start = get_time();
    while(i < data->n_philo)
    {
        create(philo);
        // check_die(philo);
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
    if (pthread_detach(philo->t1) != 0)
    {
        write(2, "Failed to detach", 16);
    }
    // while(check_die(philo) == 0)
    //     ;
    usleep(500);
}
void create(t_philo *philo)
{
    if (pthread_create(&philo->t1, NULL, &routine, (void*)philo) != 0)
    {
        write(2, "Failed to create thread", 23);
    }
}

void    join(t_philo *philo)
{
    if (pthread_join(philo->t1, (void*)philo) != 0)
        write(2, "Failed to join thread", 21);
}

int check_die(t_philo *philo, size_t time)
{
    (void)time;
    // while (philo)
    // {
        // printf("%zu ms\n", philo->t_life);
        if (philo->t_life > philo->data->t_die)
        {
            philo->data->die = philo->id;
            // printf("life is %zu ms %d\n", philo->t_life, philo->id);
            // printf("life is %zu ms %d\n", philo->t_current, philo->id);
            // printf("life is %zu ms %d\n", time, philo->id);
            printf("%zu ms %d ", philo->t_life, philo->id);
            printf("%s\n", "died");
            exit(1);
            return (1);
        }
        // philo = philo->next; 
    // }
    return (0);
}