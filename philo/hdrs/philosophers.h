/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:13:02 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/22 22:38:05 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* --------------------------------- HEADERS -------------------------------- */
# include "../lib/ft_printf/inc/ft_printf.h"
# include "colors.h"
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* --------------------------------- FUNCS -------------------------------- */
//STRUCTS

typedef struct philosopher
{
	int	number;
	int	state;
	pthread_t	thread;
}	t_philosopher;

//STATES

# define DEAD 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3 

#endif
