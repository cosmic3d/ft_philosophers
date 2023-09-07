/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:40:33 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/07 21:22:24 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../hdrs/philosophers.h"

//In case some philosopher dies and we are still inside a function,
// we will unlock the forks mutexes so later on I can destroy them correctly
int	drop_forks(t_philo *philo, int left, int right)
{
	if (left)
		pthread_mutex_unlock(philo->leftfork);
	if (right)
		pthread_mutex_unlock(philo->rightfork);
	return (0);
}

//This function makes sure there are no data races
//when reading in that memory address
int	some1died(t_philo *philo)
{
	int	_some1died;

	pthread_mutex_lock(&philo->data->death_mtx);
	_some1died = philo->data->some1died;
	pthread_mutex_unlock(&philo->data->death_mtx);
	return (_some1died);
}

//This function makes sure there are no data races
//when writing in that memory address
void	starvation(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mtx);
	philo->data->some1died = 1;
	pthread_mutex_unlock(&philo->data->death_mtx);
	return ;
}
