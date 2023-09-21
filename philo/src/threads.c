/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/21 20:13:08 by jenavarr         ###   ########.fr       */
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
		wait_x((philo->data->eat_time + 1), philo);
	while (!some1died(philo))
	{
		if (!philo_eat(philo) || some1died(philo))
			return (NULL);
		if (check_death_or_full(philo) || !print_state(philo))
			return (NULL);
		wait_x(philo->data->sleep_time, philo);
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
	if (!philo->rightfork || some1died(philo))
	{
		wait_x(philo->data->death_time, philo);
		return (drop_forks(philo, 1, 0));
	}
	pthread_mutex_lock(philo->rightfork);
	if (!print_fork_grabbed(philo))
		return (drop_forks(philo, 1, 1));
	if (check_death_or_full(philo) || some1died(philo))
		return (drop_forks(philo, 1, 1));
	philo->last_meal = current_time();
	philo->state = ST_EATING;
	philo->times_eaten++;
	if (!print_state(philo))
		return (drop_forks(philo, 1, 0));
	wait_x(philo->data->eat_time, philo);
	if (some1died(philo))
		return (drop_forks(philo, 1, 1));
	philo->state = ST_SLEEPING;
	return (drop_forks(philo, 1, 1) + 1);
}

//This way we check if a philosopher died or if they are all full
int	check_death_or_full(t_philo *philo)
{
	if (time_since(philo->last_meal) >= philo->data->death_time && \
	!some1died(philo))
		return (check_death(philo));
	pthread_mutex_lock(&philo->data->eat_mtx);
	if (!philo->philo_full && philo->times_eaten >= philo->data->hunger)
	{
		philo->philo_full = 1;
		philo->data->philos_full++;
	}
	if (philo->data->philos_full == philo->data->philo_amount \
	&& philo->data->hunger != -1)
	{
		starvation(philo);
		pthread_mutex_unlock(&philo->data->eat_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_mtx);
	return (0);
}

//Norminette forces me to create an auxiliar function >:(
int	check_death(t_philo *philo)
{
	if (some1died(philo))
		return (1);
	philo->state = ST_DEAD;
	starvation(philo);
	print_death(philo, time_since(philo->data->start_time));
	return (1);
}
