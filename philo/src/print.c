/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 03:31:08 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/29 06:10:49 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

// Prints a message with a color
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

// Prints the current state of the philosopher and locks the code with a mutex to prevent message mixing
void	print_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	//Code
	pthread_mutex_unlock(&philo->data->print_mtx);
}
