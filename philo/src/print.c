/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 03:31:08 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/28 23:10:04 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

// Prints a message with a color
int	printf_color(char *error, char *color, pthread_mutex_t *mutex)
{
	if (*error)
	{
		if (printf("%s%s", color, error) < 0)
		{
			if (mutex)
				pthread_mutex_unlock(mutex);
			write(STDERR_FILENO, PRINTF_ERROR, 46);
			return (0);
		}
	}
	if (mutex)
		pthread_mutex_unlock(mutex);
	return (1);
}

// Prints the current state of the philosopher and locks
//the code with a mutex to prevent message mixing
int	print_state(t_philo *philo)
{
	//pthread_mutex_lock(&philo->data->print_mtx);
	if (some1died(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mtx);
		return (0);
	}
	//printf("%lld %s", time_since(philo->data->start_time), PHL_SLEEP);
	//pthread_mutex_unlock(&philo->data->print_mtx);
	//return (1);
	printf("%lld %i", time_since(philo->data->start_time), philo->id);
	// printf("\t%lld ms🗣 [%i]\t%s", \
	// time_since(philo->data->start_time),  philo->id, PHL_SLEEP);
	// if (philo->state == ST_EATING)
	// 	return (printf_color(PHL_EAT, VERDE, &philo->data->print_mtx));
	// else if (philo->state == ST_SLEEPING)
	// 	return (printf_color(PHL_SLEEP, AZUL, &philo->data->print_mtx));
	// else if (philo->state == ST_THINKING)
	// 	return (printf_color(PHL_THINK, CYAN, &philo->data->print_mtx));
	if (philo->state == ST_EATING)
		printf(PHL_EAT);
	else if (philo->state == ST_SLEEPING)
		printf(PHL_SLEEP);
	else if (philo->state == ST_THINKING)
		printf(PHL_THINK);
	//pthread_mutex_unlock(&philo->data->print_mtx);
	return (1);
}

//Prints that X philosophers has grabbed a fork
int	print_fork_grabbed(t_philo *philo)
{
	//pthread_mutex_lock(&philo->data->print_mtx);
	if (some1died(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mtx);
		return (0);
	}
	printf("%lld %i", time_since(philo->data->start_time), philo->id);
	// printf("\t%lld ms🗣 [%i]\t%s",  \
	// time_since(philo->data->start_time),  philo->id, PHL_FORK);
	// pthread_mutex_unlock(&philo->data->print_mtx);
	// return (1);
	// printf("%s\t%lld ms%s🗣 [%i]\t", MAGENTA, \
	// time_since(philo->data->start_time), VERDE, philo->id);
	// return (printf_color(PHL_FORK, MAGENTA, &philo->data->print_mtx));
	printf(PHL_FORK);
	//pthread_mutex_unlock(&philo->data->print_mtx);
	return (1);
}

//Prints the death of a philosopher
int	print_death(t_philo *philo, long long timestamp)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lld %i", timestamp, philo->id);
	return (printf_color(PHL_DEAD, ROJO, &philo->data->print_mtx));
}
