/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/30 21:03:46 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../hdrs/philosophers.h"

//Joins all the threads
void	init_joins(t_table *table)
{
	int	i;
	int	len;

	i = -1;
	len = table->data.philo_amount;
	while (++i < len)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			f_exit(JOIN_ERROR, ROJO); //Esto en el futuro será reemplazado por una función que libere toda la memória y haga pthread_mutex_destroy antes de hacer exit
	}
}

void	*philo_thread(void *_philo)
{
	t_philo *philo;

	philo = (t_philo *)_philo;
	pthread_mutex_lock(&philo->data->start_mtx);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->data->start_mtx);
	print_state(philo);
	return (NULL);
}
