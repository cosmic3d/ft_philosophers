/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:45 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/29 20:50:12 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

/* Sisyphus is doomed to carry a rock all the way up mount Olympus
for the rest of eternity. Thats absurd.
Philosophers can definitely ask themselves if infinitely eating,
sleeping and thinking is also absurd.
The only difference is that they can die :)*/
void	*sisyphus_watcher(void *_table)
{
	int		i;
	t_table	*table;

	table = (t_table *)_table;
	pthread_mutex_lock(&table->data.start_mtx);
	pthread_mutex_unlock(&table->data.start_mtx);
	if (check_death_or_full(&table->philos[0]))
		return (NULL);
	while (!some1died(&table->philos[0]))
	{
		i = -1;
		usleep(500);
		while (++i < table->data.philo_amount)
		{
			if (check_death_or_full(&table->philos[i]))
				return (NULL);
		}
	}
	return (NULL);
}

//Joins all the threads
int	init_joins(t_table *table)
{
	int	i;
	int	len;

	i = -1;
	len = table->data.philo_amount;
	while (++i < len)
	{
		if (pthread_join(table->philos[i].thread, NULL))
		{
			starvation(&table->philos[i]);
			return (0);
		}
	}
	pthread_join(table->watcher, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_input(argc, argv))
		return (f_error(WRONG_INPUT, GROC));
	if (!init_allocs(&table, argv))
		return (0);
	if (!init_joins(&table))
		f_error(JOIN_ERROR, ROJO);
	return (liberate(&table));
}
