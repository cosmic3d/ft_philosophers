/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/07 04:49:18 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

//Main philo loop
void	*philo_thread(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	pthread_mutex_lock(&philo->data->start_mtx);
	pthread_mutex_unlock(&philo->data->start_mtx);
	if (philo->data->death_time == 0)
		if (check_death_or_full(philo))
			return (NULL);
	if (philo->id % 2 == 0)
		wait_x(philo->data->eat_time + 2, philo);
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
	{
		wait_x(philo->data->death_time, philo);
		return (drop_forks(philo, 1, 0));
	}
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
	if (time_since(philo->last_meal) >= philo->data->death_time && \
	philo->state != ST_EATING && !philo->data->some1died)
		return (check_death(philo));
	if (!philo->philo_full && philo->times_eaten >= philo->data->hunger)
	{
		philo->philo_full = 1;
		pthread_mutex_lock(&philo->data->eat_mtx);
		philo->data->philos_full++;
		pthread_mutex_unlock(&philo->data->eat_mtx);
	}
	if (philo->data->philos_full == philo->data->philo_amount \
	&& philo->data->hunger != -1)
	{
		pthread_mutex_lock(&philo->data->eat_mtx);
		philo->data->some1died = 1;
		pthread_mutex_unlock(&philo->data->eat_mtx);
		return (1);
	}
	return (0);
}

//Norminette forces me to create an auxiliar function >:(
int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mtx);
	if (philo->data->some1died)
	{
		pthread_mutex_unlock(&philo->data->death_mtx);
		return (1);
	}
	philo->state = ST_DEAD;
	philo->data->some1died = 1;
	pthread_mutex_unlock(&philo->data->death_mtx);
	//usleep(1000);
	print_death(philo, time_since(philo->data->start_time));
	return (1);
}
