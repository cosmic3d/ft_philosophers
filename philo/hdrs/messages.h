/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:34:55 by jenavarr          #+#    #+#             */
/*   Updated: 2023/09/28 20:22:31 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

# define NO_PHILOS "🤔❗At least 1 philosopher needed to start the simulation❗🤔\n"
# define WRONG_INPUT "❗❌ Incorrect input ❌❗\n"
# define PHILOS_FULL "🥂 All philosophers have eaten enough 🥂\n"
# define PRINTF_ERROR "❗❌ An error occurred while printing with printf ❌❗\n"
# define MTX_ERROR "❗❌ An error occurred when initializing the mutexes ❌❗\n"
# define MTX_ERROR2 "❗❌ An error occurred when destroying the mutexes ❌❗\n"
# define THR_ERROR "❗❌ An error occurred when initializing the threads ❌❗\n"
# define JOIN_ERROR "❗❌ An error occurred when joining the threads ❌❗\n"
# define PHL_ERROR "❗❌ An error occurred when initializing the philos ❌❗\n"
# define PHL_EAT " is eating\n"
# define PHL_SLEEP " is sleeping\n"
# define PHL_THINK " is thinking\n"
# define PHL_DEAD " died\n"
# define PHL_FORK " has taken a fork\n"
// # define PHL_EAT "🍝 is eating 🍝\n"
// # define PHL_SLEEP "💤 is sleeping 💤\n"
// # define PHL_THINK "🧠 is thinking 🧠\n"
// # define PHL_DEAD "☠️  died ☠️\033[0m\n"
// # define PHL_FORK "🍴 has taken a fork 🍴\n"
#endif
