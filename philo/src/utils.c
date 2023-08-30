/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:18:26 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/30 18:23:48 by jenavarr         ###   ########.fr       */
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

//Returns the current time in milliseconds since 01/01/1970 00:00
long long	current_time(void)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

//Returns how many milliseconds have passed since start time
long long	timestamp(t_philo *philo)
{
	return (current_time() - philo->data->start_time);
}
