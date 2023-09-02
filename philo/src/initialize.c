/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:23:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/02 05:05:39 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

//Main function that initializes mutexes, philos and threads
void	init_allocs(t_table *table, char **argv)
{
	table->data.philo_amount = ft_atoi(argv[1]);
	if (!table->data.philo_amount)
		f_exit(NO_PHILOS, ROJO);
	table->data.death_time = ft_atoi(argv[2]);
	table->data.eat_time = ft_atoi(argv[3]);
	table->data.sleep_time = ft_atoi(argv[4]);
	table->data.hunger = -1;
	table->data.some1died = 0;
	table->data.philos_full = 0;
	if (argv[5])
		table->data.hunger = ft_atoi(argv[5]);
	if (!table->data.hunger)
		f_exit(PHILOS_FULL, VERDE);
	if (!init_mutexes(table))
		f_exit(MTX_ERROR, ROJO);
	if (!init_philos(table))
		f_exit(PHL_ERROR, ROJO);
	if (!init_threads(table))
		f_exit(THR_ERROR, ROJO);
}

//Initializes the philos and assigns the forks to each one of them
int	init_philos(t_table *table)
{
	int	i;
	int	len;

	i = -1;
	len = table->data.philo_amount;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * len);
	if (!table->philos)
		return (0);
	while (++i < len)
	{
		table->philos[i].id = i + 1;
		table->philos[i].data = &table->data;
		table->philos[i].state = ST_THINKING;
		table->philos[i].times_eaten = 0;
		table->philos[i].leftfork = &table->forks[i];
		if (len > 1)
		{
			if (i != len - 1)
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
			return (0);
	}
	if (pthread_mutex_init(&table->data.start_mtx, NULL) || \
	pthread_mutex_init(&table->data.print_mtx, NULL))
		return (0);
	return (1);
}

//Initializes the threads and stablishes the start time right after they all started and can begin the loop
int	init_threads(t_table *table)
{
	int	i;
	int	len;

	i = -1;
	len = table->data.philo_amount;
	pthread_mutex_lock(&table->data.start_mtx);
	while (++i < len)
	{
		if (pthread_create(&table->philos[i].thread, \
		NULL, philo_thread, (void *)&table->philos[i]))
			return (0);
	}
	table->data.start_time = current_time();
	if (pthread_create(&table->watcher, \
		NULL, sisyphus_watcher, (void *)table))
			return (0);
	pthread_mutex_unlock(&table->data.start_mtx);
	return (1);
}
