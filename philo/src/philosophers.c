/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 20:30:45 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/30 06:02:01 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

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
	//write(1, "Estoy\n", 7);
	pthread_mutex_lock(&philo->data->start_mtx);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&philo->data->start_mtx);
	usleep(200000);
	print_state(philo);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table table;

	if (!check_input(argc, argv))
		f_exit(WRONG_INPUT, GROC);
	init_allocs(&table, argv);
	init_joins(&table);
	return (0);
}
