/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 10:52:45 by tbouma            #+#    #+#             */
/*   Updated: 2022/07/12 10:53:06 by tbouma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	recursion(long long n, int fd)
{
	char	d;
	int		count;

	count = 0;
	while (n > 0)
	{
		d = (n % 10) + '0';
		n /= 10;
		count += recursion(n, fd);
		count += write(fd, &d, sizeof(char));
		n = 0;
	}
	return (count);
}

int	ft_putnbr_fd(long long n, int fd)
{
	int	count;

	count = 0;
	if (n == 0)
		return (write(fd, "0", 1));
	else if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	else if (n > 0)
		return (recursion(n, fd));
	else if (n < 0)
	{
		count = write(fd, "-", 1);
		n *= -1;
		count += recursion(n, fd);
	}
	return (count);
}

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	return (write(fd, s, i));
}

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
