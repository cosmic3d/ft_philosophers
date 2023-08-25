/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:18:26 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/25 04:44:57 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

//Prints a message with a color and exits
int	f_exit(char *err_message, char* color)
{
	printf_color(err_message, color);
	exit(1);
	return (0);
}
