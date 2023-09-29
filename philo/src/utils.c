/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:18:26 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/29 19:41:50 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

//Prints a message with a color and returns 0
int	f_error(char *err_message, char *color)
{
	printf("%s%s", color, err_message);
	return (0);
}

//Returns the current time in milliseconds since 01/01/1970 00:00
long long	current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

//Returns how many milliseconds have passed since time
//This is useful to determine the timestamp or
//if some philosopher died of starvation :3
long long	time_since(long long time)
{
	return (current_time() - time);
}

//This function waits time milliseconds and in the meantime checks if
//someone died, including himself
void	wait_x(int time)
{
	long long	start_time;
	long long	time_since_x;

	start_time = current_time();
	time_since_x = current_time() - start_time;
	while (time_since_x < time)
	{
		time_since_x = current_time() - start_time;
		usleep(250);
	}
}

//This function makes sure there are no leaks by destroying the mutexes
//one by one and liberating them along with the philos
int	liberate(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->data.philo_amount && table->forks != NULL)
	{
		if (&table->forks[i] != NULL && pthread_mutex_destroy(&table->forks[i]))
		{
			if (table->forks != NULL)
				free(table->forks);
			if (table->philos != NULL)
				free(table->philos);
			return (f_error(MTX_ERROR2, ROJO));
		}
	}
	if (table->forks != NULL)
		free(table->forks);
	if (table->philos != NULL)
		free(table->philos);
	if (pthread_mutex_destroy(&table->data.start_mtx) || \
	pthread_mutex_destroy(&table->data.print_mtx) || \
	pthread_mutex_destroy(&table->data.death_mtx) || \
	pthread_mutex_destroy(&table->data.eat_mtx) || \
	pthread_mutex_destroy(&table->data.lastmeal_mtx))
		return (f_error(MTX_ERROR2, ROJO));
	return (0);
}
