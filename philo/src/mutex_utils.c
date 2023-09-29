/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:40:33 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/29 21:03:31 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

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

//This way we check the value of last meal without having any data races
long long	check_last_meal(t_philo *philo)
{
	long long	_lastmeal;

	pthread_mutex_lock(&philo->data->lastmeal_mtx);
	_lastmeal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->lastmeal_mtx);
	return (_lastmeal);
}

//This function destroys the mutexes according to how many of them were created
// (There is no point in destroying something that wasn't created)
int	error_destroy(t_table *table, int i, int j)
{
	if (!i)
		return (0);
	while (i-- > -1)
	{
		if (&table->forks[i] != NULL && pthread_mutex_destroy(&table->forks[i]))
			return (f_error(MTX_ERROR2, ROJO));
	}
	if (!j)
		return (0);
	if (j >= 1 && pthread_mutex_destroy(&table->data.start_mtx))
		return (f_error(MTX_ERROR2, ROJO));
	if (j >= 2 && pthread_mutex_destroy(&table->data.print_mtx))
		return (f_error(MTX_ERROR2, ROJO));
	if (j >= 3 && pthread_mutex_destroy(&table->data.death_mtx))
		return (f_error(MTX_ERROR2, ROJO));
	if (j == 4 && pthread_mutex_destroy(&table->data.eat_mtx))
		return (f_error(MTX_ERROR2, ROJO));
	return (0);
}
