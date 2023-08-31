/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:04:58 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/31 05:48:51 by jenavarr         ###   ########.fr       */
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

//Main philo loop
void	*philo_thread(void *_philo)
{
	t_philo *philo;

	philo = (t_philo *)_philo;
	pthread_mutex_lock(&philo->data->start_mtx);
	pthread_mutex_unlock(&philo->data->start_mtx);
	philo->last_meal = philo->data->start_time;
	//print_state(philo);
	if (philo->data->death_time == 0)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(500);
	while (!philo->data->some1died)
	{

	}
	return (NULL);
}

int	philo_eat(t_philo *philo)
{
	if (philo->data->some1died)
		return (0);
	pthread_mutex_lock(philo->leftfork);
	print_fork_grabbed(philo);
	if (!philo->rightfork)
		return (0);
	pthread_mutex_lock(philo->rightfork);
	print_fork_grabbed(philo);
	philo->state = ST_EATING;
	print_state(philo);
	//Funcion de wait aqui. En esa función hay que hacer otra comprobación para ver si hay algún filósofo muerto,
	//y en tal caso devolver 0 y unlockear los mutexes, ya que ningún otro filósofo volverá a entrar aquí debido a
	//la primera comprobación
	philo->last_meal = current_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->rightfork);
	return ;
}
