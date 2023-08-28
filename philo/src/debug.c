/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 23:57:49 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/29 00:09:51 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

void	debug_philos(t_table *table)
{
	int	i;

	i = -1;
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
	}
}
