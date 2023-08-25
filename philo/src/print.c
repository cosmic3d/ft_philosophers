/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 03:31:08 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/25 04:44:55 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

int	printf_color(char *err_message, char* color)
{
	if (!color)
		color = RESET;
	if (*err_message)
	{
		if (printf("%s%s%s", color, err_message, RESET) < 0)
		{
			write(1, "An error occurred while printing with printf\n", 46);
			exit(1);
		}
	}
	return (0);
}
