/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:45 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/30 21:02:43 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

int	main(int argc, char **argv)
{
	t_table table;

	if (!check_input(argc, argv))
		f_exit(WRONG_INPUT, GROC);
	init_allocs(&table, argv);
	init_joins(&table);
	//If all the threads have ended, or a philosopher died or something went wrong
	//In any of those cases, we unlock all the mutexes, destroy them and free them along with all the other mallocs just before we exit
	return (0);
}
