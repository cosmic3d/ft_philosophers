/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenavarr <jenavarr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:44:22 by jenavarr          #+#    #+#             */
/*   Updated: 2023/08/28 21:51:55 by jenavarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/philosophers.h"

//Converts a string into a number
int	ft_atoi(const char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (*str == ' ' || *str == '\n' || *str == '\v' || *str == '\t'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		n = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + (*str - '0');
		str++;
	}
	return (i * n);
}

//Checks that the string only contains the allowed characters
int	forbidden_chars(char *str, char *allowed)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strrchr(allowed, str[i]))
			return (1);
	return (0);
}

//Searches for a character in a string and returns a pointer to it
char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

//Check the limits of the number provided
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		i;

	i = 0;
	while (s1[i])
		i++;
	if (i < 10)
		return (0);
	if (i > 10)
		return (1);
	while (*s1 != '\0' && n > 0 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

//Checks the input provided by the user with the help
//of all the previous functions
int	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	while (argv[++i])
	{
		if (!argv[i] || !argv[i][0])
			return (0);
		if (forbidden_chars(argv[i], "0123456789") || \
		ft_strncmp(argv[i], "2147483647", 10) > 0)
			return (0);
	}
	return (1);
}
