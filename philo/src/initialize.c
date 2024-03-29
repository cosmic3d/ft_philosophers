/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:23:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/29 21:01:30 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

//Main function that initializes mutexes, philos and threads
int	init_allocs(t_table *table, char **argv)
{
	table->philos = NULL;
	table->forks = NULL;
	table->data.philo_amount = ft_atoi(argv[1]);
	if (!table->data.philo_amount)
		return (f_error(NO_PHILOS, ROJO));
	table->data.death_time = ft_atoi(argv[2]);
	table->data.eat_time = ft_atoi(argv[3]);
	table->data.sleep_time = ft_atoi(argv[4]);
	table->data.hunger = -1;
	table->data.some1died = 0;
	table->data.philos_full = 0;
	if (argv[5])
		table->data.hunger = ft_atoi(argv[5]);
	if (!table->data.hunger)
		return (f_error(PHILOS_FULL, VERDE));
	if (!table->data.eat_time || !table->data.sleep_time)
		return (f_error(WRONG_INPUT, GROC));
	if (!init_mutexes(table))
		return (f_error(MTX_ERROR, ROJO));
	if (!init_philos(table))
		return (f_error(PHL_ERROR, ROJO));
	if (!init_threads(table))
		return (f_error(THR_ERROR, ROJO));
	return (1);
}

//Initializes the philos and assigns the forks to each one of them
int	init_philos(t_table *table)
{
	int	i;

	i = -1;
	table->philos = malloc(sizeof(t_philo) * table->data.philo_amount);
	if (!table->philos)
		return (liberate(table));
	while (++i < table->data.philo_amount)
	{
		table->philos[i].id = i + 1;
		table->philos[i].data = &table->data;
		table->philos[i].state = ST_THINKING;
		table->philos[i].times_eaten = 0;
		table->philos[i].philo_full = 0;
		table->philos[i].leftfork = &table->forks[i];
		table->philos[i].rightfork = NULL;
		if (table->data.philo_amount > 1)
		{
			if (i != table->data.philo_amount - 1)
				table->philos[i].rightfork = &table->forks[i + 1];
			else
				table->philos[i].rightfork = &table->forks[0];
		}
	}
	return (1);
}

//Initializes the mutexes
int	init_mutexes(t_table *table)
{
	int	i;
	int	len;

	i = -1;
	len = table->data.philo_amount;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * len);
	if (!table->forks)
		return (0);
	while (++i < len)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (error_destroy(table, i, 0));
	}
	if (pthread_mutex_init(&table->data.start_mtx, NULL))
		return (error_destroy(table, i, 0));
	if (pthread_mutex_init(&table->data.print_mtx, NULL))
		return (error_destroy(table, i, 1));
	if (pthread_mutex_init(&table->data.death_mtx, NULL))
		return (error_destroy(table, i, 2));
	if (pthread_mutex_init(&table->data.eat_mtx, NULL))
		return (error_destroy(table, i, 3));
	if (pthread_mutex_init(&table->data.lastmeal_mtx, NULL))
		return (error_destroy(table, i, 4));
	return (1);
}

//Initializes the threads and stablishes the start time right after
//they all started and can begin the loop
int	init_threads(t_table *table)
{
	int	i;
	int	len;
	int	error;

	i = -1;
	error = 0;
	len = table->data.philo_amount;
	pthread_mutex_lock(&table->data.start_mtx);
	while (++i < len && !error)
		error = pthread_create(&table->philos[i].thread, \
		NULL, philo_thread, (void *)&table->philos[i]);
	if (error || pthread_create(&table->watcher, \
	NULL, sisyphus_watcher, (void *)table))
	{
		starvation(&table->philos[0]);
		pthread_mutex_unlock(&table->data.start_mtx);
		return (liberate(table));
	}
	table->data.start_time = current_time();
	i = -1;
	while (++i < len)
		table->philos[i].last_meal = table->data.start_time;
	pthread_mutex_unlock(&table->data.start_mtx);
	return (1);
}
