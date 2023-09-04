/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:57:49 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/04 17:12:56 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

void	debug_philos(t_table *table)
{
	int	i;
	long long	start;

	i = -1;
	start = current_time();
	while (++i < table->data.philo_amount)
	{
		printf_color("PHILO: ", VERDE);
		printf("%s%i\n", RESET, table->philos[i].id);
		printf_color("\tState: ", GROC);
		printf("%s%i\n", RESET, table->philos[i].state);
		printf_color("\tLeft fork: ", GROC);
		printf("%s%p\n", RESET, table->philos[i].leftfork);
		printf_color("\tRight fork: ", GROC);
		printf("%s%p\n", RESET, table->philos[i].rightfork);
		printf_color("\tLast meal: ", ROJO);
		printf("%s%lld\n", RESET, table->philos[i].last_meal - start);
	}
}
