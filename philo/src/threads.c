/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/28 22:58:15 by jenavarr         ###   ########.fr       */
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
	if (some1died(philo))
		return (NULL);
	if (philo->data->death_time == 0)
		return (NULL);
	if (philo->id % 2 == 0)
		wait_x((philo->data->eat_time));
	while (!some1died(philo))
	{
		if (!philo_eat(philo))
			return (NULL);
		if (!print_state(philo))
			return (NULL);
		wait_x(philo->data->sleep_time);
		philo->state = ST_THINKING;
		if (!print_state(philo))
			return (NULL);
	}
	return (NULL);
}

//In this function I manage all the logic behind the philosophers eating
int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->leftfork);
	if (!print_fork_grabbed(philo))
		return (drop_forks(philo, 1, 0));
	if (!philo->rightfork)
	{
		wait_x(philo->data->death_time);
		return (drop_forks(philo, 1, 0));
	}
	pthread_mutex_lock(philo->rightfork);
	if (!print_fork_grabbed(philo))
		return (drop_forks(philo, 1, 1));
	if (some1died(philo))
		return (drop_forks(philo, 1, 1));
	pthread_mutex_lock(&philo->data->lastmeal_mtx);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->data->lastmeal_mtx);
	philo->state = ST_EATING;
	if (!print_state(philo))
		return (drop_forks(philo, 1, 1));
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->hunger)
		philo->philo_full = 1;
	wait_x(philo->data->eat_time);
	// if (some1died(philo))
	// 	return (drop_forks(philo, 1, 1));
	philo->state = ST_SLEEPING;
	return (drop_forks(philo, 1, 1) + 1);
}

//This way we check if a philosopher died or if they are all full
int	check_death_or_full(t_philo *philo)
{
	int	debug;

	debug = time_since(check_last_meal(philo));
	if (debug >= philo->data->death_time && \
	!some1died(philo))
		return (check_death(philo));
	if (philo->philo_full)
	{
		philo->philo_full = 0;
		philo->data->philos_full++;
	}
	if (philo->data->hunger != -1 && philo->data->philos_full == \
	philo->data->philo_amount)
	{
		starvation(philo);
		return (1);
	}
	return (0);
}

//Norminette forces me to create an auxiliar function >:(
int	check_death(t_philo *philo)
{
	if (some1died(philo))
		return (1);
	starvation(philo);
	print_death(philo, time_since(philo->data->start_time));
	return (1);
}
