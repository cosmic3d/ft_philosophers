/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/06 07:20:11 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

//Joins all the threads
void	init_joins(t_table *table)
{
	int	i;
	int	len;

	i = -1;
	len = table->data.philo_amount;
	while (++i < len)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			f_exit(JOIN_ERROR, ROJO);
	}
}

//Main philo loop
void	*philo_thread(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	pthread_mutex_lock(&philo->data->start_mtx);
	pthread_mutex_unlock(&philo->data->start_mtx);
	if (philo->data->death_time == 0)
		return (NULL);
	if (philo->id % 2 == 0)
		wait_x(philo->data->eat_time - 1, philo);
	while (!philo->data->some1died)
	{
		if (!philo_eat(philo) || philo->data->some1died)
			return (NULL);
		if (check_death_or_full(philo))
			return (NULL);
		print_state(philo);
		wait_x(philo->data->sleep_time, philo);
		philo->state = ST_THINKING;
		print_state(philo);
	}
	return (NULL);
}

//In this function I manage all the logic behind the philosophers eating
int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->leftfork);
	print_fork_grabbed(philo);
	if (!philo->rightfork || philo->data->some1died)
		return (drop_forks(philo, 1, 0));
	pthread_mutex_lock(philo->rightfork);
	if (check_death_or_full(philo) || philo->data->some1died)
		return (drop_forks(philo, 1, 1));
	print_fork_grabbed(philo);
	philo->state = ST_EATING;
	philo->last_meal = current_time();
	print_state(philo);
	wait_x(philo->data->eat_time, philo);
	if (philo->data->some1died)
		return (drop_forks(philo, 1, 1));
	philo->last_meal = current_time();
	philo->times_eaten++;
	philo->state = ST_SLEEPING;
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->rightfork);
	return (1);
}

//In case some philosopher dies and we are still inside a function,
// we will unlock the forks mutexes so later on I can destroy them correctly
int	drop_forks(t_philo *philo, int left, int right)
{
	if (left)
		pthread_mutex_unlock(philo->leftfork);
	if (right)
		pthread_mutex_unlock(philo->rightfork);
	return (0);
}

//This way we check if a philosopher died or if they are all full
int	check_death_or_full(t_philo *philo)
{
	long long	timestamp;
	if (time_since(philo->last_meal) >= philo->data->death_time && \
	philo->state != ST_EATING && !philo->data->some1died)
	{
		pthread_mutex_lock(&philo->data->death_mtx);
		if (philo->data->some1died)
			return (1);
		philo->state = ST_DEAD;
		philo->data->some1died = 1;
		pthread_mutex_unlock(&philo->data->death_mtx);
		timestamp = time_since(philo->data->start_time);
		usleep(4000);
		print_death(philo, timestamp);
		return (1);
	}
	/* if (!philo->philo_full && philo->times_eaten >= philo->data->hunger)
	{
		philo->philo_full = 1;
		philo->data->philos_full++;
	}
	if (philo->data->philos_full == philo->data->philo_amount \
	&& philo->data->hunger != -1)
	{
		philo->data->some1died = 1;
		return (1);
	} */
	return (0);
}
