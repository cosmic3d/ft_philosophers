/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:45 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/31 05:49:02 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

void	sisyphus_watcher(t_table *table)
{
	int	i;

	while (!table->data.some1died)
	{
		i = -1;
		while (++i < table->data.philo_amount)
		{
			//He añadido una variable para saber qué cantidad de filósofos han comido suficiente ya
			//He de añadir una compobación extra aquí para evitar un bucle infinito sin nada que se imprima
			if (time_since(table->philos[i].last_meal) > table->data.death_time\
			|| table->data.death_time == 0)
			{
				table->philos[i].state = ST_DEAD;
				table->data.some1died = 1;
				print_state(&table->philos[i]);
				return ;
			}
		}
		usleep(200);
	}
}

int	main(int argc, char **argv)
{
	t_table table;

	if (!check_input(argc, argv))
		f_exit(WRONG_INPUT, GROC);
	init_allocs(&table, argv);
	init_joins(&table);
	sisyphus_watcher(&table);
	//If all the threads have ended, then a philosopher died or something went wrong
	//In any of those cases, we unlock all the mutexes, destroy them and free them along with all the other mallocs just before we exit
	return (0);
}
