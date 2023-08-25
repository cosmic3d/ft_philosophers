/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:45 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/25 04:44:52 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

int	main(int argc, char **argv)
{
	//t_table table;

	if (!check_input(argc, argv))
		f_exit("Incorrect input\n", GROC);
	printf_color("Parsing done correctly!\n", VERDE);
	return (0);
}
