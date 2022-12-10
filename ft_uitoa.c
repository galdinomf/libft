/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 15:52:54 by mgaldino          #+#    #+#             */
/*   Updated: 2022/05/26 20:14:57 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static unsigned int	ft_strlen(char *str);
static char			*ft_alloc(unsigned long long int n, int base);
static int			ft_digits(unsigned long long int n, int base);
int					ft_get_base(char identif);

char	*ft_uitoa(unsigned long long int n, char identif)
{
	int				base;
	char			*result;
	int				i;
	unsigned int	len_result;

	base = ft_get_base(identif);
	if (!base)
		return (NULL);
	result = ft_alloc(n, base);
	if (result == NULL)
		return (NULL);
	len_result = ft_strlen(result);
	i = 0;
	while ((n != 0) || (i == 0))
	{
		if ((base == 10) || (n % base < 10))
			result[len_result - 1 - i] = (n % base) + '0';
		else if (identif == 'X')
			result[len_result - 1 - i] = (n % base) + 55;
		else
			result[len_result - 1 - i] = (n % base) + 87;
		n /= base;
		i++;
	}
	return (result);
}

int	ft_get_base(char identif)
{
	int	base;

	if ((identif == 'd') || (identif == 'i') || (identif == 'u'))
		base = 10;
	else if ((identif == 'x') || (identif == 'X'))
		base = 16;
	else if (identif == 'p')
		base = 16;
	else
		return (0);
	return (base);
}

static char	*ft_alloc(unsigned long long int n, int base)
{
	char	*result;
	int		n_digits;
	int		i;

	n_digits = ft_digits(n, base);
	result = (char *) malloc((n_digits + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < n_digits)
	{
		result[i] = '0';
		i++;
	}
	result[n_digits] = '\0';
	return (result);
}

static int	ft_digits(unsigned long long int n, int base)
{
	int		num_digits;

	num_digits = 0;
	while (n != 0)
	{
		n = n / base;
		num_digits++;
	}
	if (num_digits == 0)
		num_digits = 1;
	return (num_digits);
}

static unsigned int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
