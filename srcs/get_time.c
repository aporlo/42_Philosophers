#include "../phillosophers.h"
#include <sys/time.h>

long long get_time() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}

void  current_time(t_philo *philo, t_data *data)
{
    size_t  ml_time;
    ml_time = get_time();
    philo->t_current = ml_time - data->t_start;
    // printf("current is %ld %d\n", philo->t_current, philo->id);
    philo->t_life = philo->t_current - philo->t_eating;
    // printf("life %zu ms %d\n", philo->t_life, philo->id);
    // check_die(philo);
}

void   my_usleep(size_t time, t_philo *philo)
{
    size_t  start;
    size_t  end;
    size_t  life;
    // size_t  i;

    life = philo->t_life;
    start = get_time();
    end = start + time;
    usleep(1000);
    while (start < end)
    {
        // usleep(2000);
        start = get_time();
        // if (philo->id == 1)
        //     printf("time is %ld\n", philo->t_life);
        // i = (time - (end - start));
        philo->t_life = life + (time - (end - start));
        // printf("time is %ld\n", end - start);
        check_die(philo, time);
    }
}