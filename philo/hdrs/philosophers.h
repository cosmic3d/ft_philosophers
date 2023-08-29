/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:13:02 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/29 06:05:55 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* --------------------------------- HEADERS -------------------------------- */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "colors.h"
# include "messages.h"

/* --------------------------------- STRUCTS -------------------------------- */

typedef struct data
{
	int 			philo_amount;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				hunger;
	pthread_mutex_t	start_mtx;
	pthread_mutex_t	print_mtx;
	long long		start_time;
}	t_data;

typedef struct philo
{
	int				id;
	int				state;
	int				times_eaten;
	pthread_t		thread;
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*rightfork;
	long long		last_time_eaten;
	t_data			*data;
}	t_philo;


typedef struct table
{
	t_philo	*philos;
	pthread_mutex_t	*forks;
	t_data data;
}	t_table;

/* --------------------------------- STATES --------------------------------- */

# define ST_DEAD 0
# define ST_EATING 1
# define ST_SLEEPING 2
# define ST_THINKING 3

/* --------------------------------- FUNCS -------------------------------- */

//Parse
int		ft_atoi(const char *str);
int		forbidden_chars(char *str, char *allowed);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_input(int argc, char **argv);
//Utils
int		f_exit(char *err_message, char* color);
//Print
int		printf_color(char *err_message, char* color);
//Initialize
void	init_allocs(t_table *table, char **argv);
int		init_mutexes(t_table *table);
int		init_philos(t_table *table);
//Debug
void	debug_philos(t_table *table);
#endif
