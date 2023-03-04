/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phillosophers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsomrat <lsomrat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:44:29 by lsomrat           #+#    #+#             */
/*   Updated: 2023/02/25 19:44:31 by lsomrat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "phillosophers.h"

// void* routine(void* arg) 
// {
// 	sleep(1);
// 	int index = *(int*)arg;
// 	// printf("%d ", primes[index]);
// 	int sum = 0;
// 	for (int j = 0; j < 5; j++)
// 	{
// 		sum += primes[index + j];
// 	}
// 	// free(arg);
// 	printf("Local sum: %d\n", sum);
// 	*(int*)arg = sum;
// 	return arg;
// }
// void* roll_dice() {
// 	int value = (rand() % 6) + 1;
// 	int	*result = malloc(sizeof(int));
// 	*result = value;
// 	// printf("%d\n", value);
// 	printf("Thread result: %p\n", result);
// 	return (void*) result;
// }

int	main(int argc, char **argv)
{
	t_data 	data;
	t_philo	*philo;
	int i;

	i = 0;
	philo = NULL;
	if (!validate(argc, argv))
		return (0);
	init_data(argv, &data);
	add_philo(&philo, &data);
	create_thread(philo, &data);
	// (void)argc;
	// (void)argv;
	// int*	res;
	// srand(time(NULL));
	// pthread_t	th[10];
	// int i;
	// for(i = 0; i < 2; i++)
	// {
	// 	int*	a = malloc(sizeof(int));
	// 	*a = i * 5;
	// 	if (pthread_create(&th[i], NULL, &routine, a) != 0)
	// 	{
	// 		perror("Failed to create thread");
	// 	}
	// }
	// int globalSum = 0;
	// for(i = 0; i < 10; i++)
	// {
	// 	int*	r = malloc(sizeof(int));
	// 	if (pthread_join(th[i], (void**) &r) != 0) 
	// 	{
	// 		perror("Failed to join thread");
	// 	}
	// 	globalSum += *r;
	// 	free(r);
	// }
	// printf("Global sum: %d\n", globalSum);
	// pthread_t th;
	// if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
	// {
	// 	return 1;
	// }
	// if (pthread_join(th, (void**) &res) != 0)
	// {
	// 	return 2;
	// }
	// printf("Main res: %p\n", res);
	// printf("Result: %d\n", *res);
	// free(res);
	// pthread_t	th[4];
	// int i;
	// pthread_mutex_init(&mutex, NULL);
	// for (i = 0; i < 4; i++)
	// {
	// 	if (pthread_create(th + i, NULL, &routine, NULL) != 0)
	// 	{
	// 		perror("Failed to create thread");
	// 		return 1;
	// 	}
	// 	printf("Thread %d has started\n", i);
	// 	if (pthread_join(th[i], NULL) != 0)
	// 		return 2;
	// 	printf("Thread %d has finished execution\n", i);
	// }
	// pthread_mutex_destroy(&mutex);
	// printf("Number of mails: %d\n", mails);
	return (0);
}
