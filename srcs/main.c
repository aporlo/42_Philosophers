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
int	mails = 0;
pthread_mutex_t	mutex;

void*	routine(){
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	// if (!validate(argc, argv))
	// 	return (0);
	(void)argc;
	(void)argv;

	pthread_t	th[4];
	int i;
	pthread_mutex_init(&mutex, NULL);
	for (i = 0; i < 4; i++)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
			return 1;
		}
		printf("Thread %d has started\n", i);
		if (pthread_join(th[i], NULL) != 0)
			return 2;
		printf("Thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("Number of mails: %d\n", mails);
	return (0);
}
