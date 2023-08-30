/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 03:31:08 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/30 03:29:41 by jenavarr         ###   ########.fr       */
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
			write(1, PRINTF_ERROR, 46);
			exit(1);
		}
	}
	return (0);
}

// Prints the current state of the philosopher and locks the code with a mutex to prevent message mixing
void	print_state(t_philo *philo)
{
	print_info(philo);
	if (philo->state == ST_DEAD)
		printf_color(PHL_DEAD, GROC);
	else if (philo->state == ST_EATING)
		printf_color(PHL_EAT, GROC);
	else if (philo->state == ST_SLEEPING)
		printf_color(PHL_SLEEP, GROC);
	else if (philo->state == ST_THINKING)
		printf_color(PHL_THINK, GROC);
	pthread_mutex_unlock(&philo->data->print_mtx);
}

//Prints that X philosophers has grabbed a fork
void	print_fork_grabbed(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mtx);
	print_info(philo);
	printf_color(PHL_FORK, GROC);
	pthread_mutex_unlock(&philo->data->print_mtx);
}

//Prints the current timestamp and philo. This is a complementary function,
//so it must not be called from outside print_state or print_fork_grabbed
void	print_info(t_philo *philo)
{
	if (printf(MAGENTA) < 0 || printf("\t%lld ms\t", timestamp(philo)) < 0 || \
	printf(VERDE) < 0 || printf("🤔[%i]\t", philo->id) < 0)
	{
		write(1, PRINTF_ERROR, 46);
		exit(1);
	}
}
