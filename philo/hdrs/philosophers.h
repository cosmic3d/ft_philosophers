/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:13:02 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/25 04:09:47 by jenavarr         ###   ########.fr       */
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

/* --------------------------------- STRUCTS -------------------------------- */

typedef struct data
{
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	hunger;
}	t_data;

typedef struct philo
{
	int	id;
	int	state;
	int	times_eaten;
	pthread_t	thread;
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*rightfork;
}	t_philo;


typedef struct table
{
	t_philo	*philos;
	pthread_mutex_t	*forks;
}	t_table;

/* --------------------------------- STATES --------------------------------- */

# define DEAD 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3

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
#endif
