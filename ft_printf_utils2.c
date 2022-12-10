/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:12:43 by mgaldino          #+#    #+#             */
/*   Updated: 2022/06/22 16:11:16 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_aux_with_prec(char *aux, t_specs *specs)
{
	char			*temp;
	char			*temp2;
	int				neg;
	unsigned int	i;

	if (ft_char_in_string(specs->identifier, NUMBER_IDENTIFIERS))
	{
		neg = (aux[0] == '-');
		if (specs->precision <= ft_strlen(aux + neg))
			return (aux);
		temp = (char *) malloc(specs->precision + neg);
		if (temp == NULL)
			return (aux);
		if (neg)
			temp[0] = '-';
		i = -1;
		while (++i < (specs->precision - ft_strlen(aux + neg)))
			temp[neg + i] = '0';
		temp[neg + i] = '\0';
		temp2 = ft_strjoin(temp, aux + neg);
		free(temp);
		free(aux);
		return (temp2);
	}
	return (aux);
}

void	ft_putstr_printf(char *str, int *bytes_written, int precision)
{
	int	i;

	if (!str)
	{
		*bytes_written += write(1, "(null)", 6);
		return ;
	}
	i = -1;
	if (precision > 0)
	{
		while ((str[++i] != '\0') && (*bytes_written < precision))
			ft_putchar_printf(str[i], bytes_written);
	}
	else if (precision < 0)
		return ;
	else
	{
		while (str[++i] != '\0')
			ft_putchar_printf(str[i], bytes_written);
	}		
}

void	ft_putchar_printf(char c, int *bytes_written)
{
	int	aux;

	aux = write(1, &c, 1);
	if (aux >= 0)
		*bytes_written += aux;
}
