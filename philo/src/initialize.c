/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:23:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/29 00:08:58 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

void	init_allocs(t_table *table, char **argv)
{
	table->data.philo_amount = ft_atoi(argv[1]);
	if (!table->data.philo_amount)
		f_exit(NO_PHILOS, ROJO);
	table->data.death_time = ft_atoi(argv[2]);
	table->data.eat_time = ft_atoi(argv[3]);
	table->data.sleep_time = ft_atoi(argv[4]);
	table->data.hunger = -1;
	if (argv[5])
		table->data.hunger = ft_atoi(argv[5]);
	if (!table->data.hunger)
		f_exit(PHILOS_FULL, VERDE);
	if (!init_mutexes(table))
		f_exit(MTX_ERROR, ROJO);
	if (!init_philos(table))
		f_exit(PHL_ERROR, ROJO);
	debug_philos(table);
	printf_color("✅ Mutexes and Philosophers correctly initialized! ✅\n", VERDE);
}

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
	if (pthread_mutex_init(&table->start_mtx, NULL) || \
	pthread_mutex_init(&table->print_mtx, NULL))
		return (0);
	return (1);
}
