/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:45 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/04 06:53:34 by jenavarr         ###   ########.fr       */
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
	if (check_death_or_full(&table->philos[0]))
		return (NULL);
	usleep(50 * table->data.philo_amount);
	while (!table->data.some1died)
	{
		i = -1;
		usleep(100);
		while (++i < table->data.philo_amount)
		{
			if (check_death_or_full(&table->philos[i]))
				return (NULL);
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
	liberate(&table);
	return (0);
}
