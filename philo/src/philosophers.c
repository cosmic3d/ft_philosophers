/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:45 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/21 20:27:40 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

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
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_input(argc, argv))
		return (f_error(WRONG_INPUT, GROC));
	init_allocs(&table, argv);
	if (!init_joins(&table))
		f_error(JOIN_ERROR, ROJO);
	liberate(&table);
}
