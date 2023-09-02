/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/02 04:54:21 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../hdrs/philosophers.h"

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
			f_exit(JOIN_ERROR, ROJO); //Esto en el futuro será reemplazado por una función que libere toda la memória y haga pthread_mutex_destroy antes de hacer exit
	}
	if (pthread_join(table->watcher, NULL))
		f_exit(JOIN_ERROR, ROJO);
}

//Main philo loop
void	*philo_thread(void *_philo)
{
	t_philo *philo;

	philo = (t_philo *)_philo;
	pthread_mutex_lock(&philo->data->start_mtx);
	pthread_mutex_unlock(&philo->data->start_mtx);
	philo->last_meal = philo->data->start_time;
	if (philo->data->death_time == 0)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(50 * philo->data->philo_amount);
	while (!philo->data->some1died)
	{
		if (!philo_eat(philo))
			return (NULL);
		print_state(philo);
		wait(philo->data->sleep_time, &philo->data->some1died);
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
	if (!philo->rightfork)
		return (drop_forks(philo, 1, 0));
	pthread_mutex_lock(philo->rightfork);
	if (philo->data->some1died)
		return (drop_forks(philo, 1, 1));
	print_fork_grabbed(philo);
	philo->state = ST_EATING;
	print_state(philo);
	wait(philo->data->eat_time, &philo->data->some1died);
	philo->last_meal = current_time();
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->hunger)
		philo->data->philos_full++;
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
