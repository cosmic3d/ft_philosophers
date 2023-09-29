/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 03:31:08 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/29 19:50:21 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

// Prints the current state of the philosopher and locks
//the code with a mutex to prevent message mixing
int	print_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	if (some1died(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mtx);
		return (0);
	}
	printf("%lld %i", time_since(philo->data->start_time), philo->id);
	if (philo->state == ST_EATING)
		printf(PHL_EAT);
	else if (philo->state == ST_SLEEPING)
		printf(PHL_SLEEP);
	else if (philo->state == ST_THINKING)
		printf(PHL_THINK);
	pthread_mutex_unlock(&philo->data->print_mtx);
	return (1);
}

//Prints that X philosophers has grabbed a fork
int	print_fork_grabbed(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	if (some1died(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mtx);
		return (0);
	}
	printf("%lld %i %s", time_since(philo->data->start_time), philo->id, \
	PHL_FORK);
	pthread_mutex_unlock(&philo->data->print_mtx);
	return (1);
}

//Prints the death of a philosopher
int	print_death(t_philo *philo, long long timestamp)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	printf("%lld %i %s", timestamp, philo->id, PHL_DEAD);
	pthread_mutex_unlock(&philo->data->print_mtx);
	return (1);
}
