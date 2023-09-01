/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 02:18:26 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/01 03:06:45 by jenavarr         ###   ########.fr       */
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

//Returns how many milliseconds have passed since time
//This is useful to determine the timestamp or if some philosopher died of starvation :3
long long	time_since(long long time)
{
	return (current_time() - time);
}

//This function waits time milliseconds
void	wait(int time, int *some1died)
{
	long long	start_time;

	start_time = current_time();
	while (!*some1died && time_since(start_time) < time)
		usleep(500);
}
