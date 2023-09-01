/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:45 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/01 06:55:27 by jenavarr         ###   ########.fr       */
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
	int	i;
	t_table	*table;

	table = (t_table *)_table;
	while (!table->data.some1died)
	{
		i = -1;
		usleep(500); //Añadir factor por el que multiplicar ya que sino cuando hay muchos filósofos mueren porque no les da tiempo a iniciarse
		while (++i < table->data.philo_amount)
		{
			if (table->data.philos_full == table->data.philo_amount && table->data.hunger != -1)
			{
				table->data.some1died = 1;
				return (NULL);
			}
			if (time_since(table->philos[i].last_meal) > table->data.death_time \
			&& table->philos[i].state != ST_EATING)
			{
				table->philos[i].state = ST_DEAD;
				table->data.some1died = 1;
				print_state(&table->philos[i]);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table table;

	if (!check_input(argc, argv))
		f_exit(WRONG_INPUT, GROC);
	init_allocs(&table, argv);
	init_joins(&table);
	//If all the threads have ended, then a philosopher died or something went wrong
	//In any of those cases, we unlock all the mutexes, destroy them and free them along with all the other mallocs just before we exit
	return (0);
}
