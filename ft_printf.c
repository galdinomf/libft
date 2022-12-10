/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:13:06 by mgaldino          #+#    #+#             */
/*   Updated: 2022/06/22 16:11:22 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "libft.h"

int		ft_process_param(const char *format, int *start, va_list *list);
void	ft_print_char(char c, int *bytes_written, t_specs *specs);
void	ft_print_str(char *aux, int *bytes_written, t_specs *specs);
char	*ft_get_str(char identifier, va_list *list);

int	ft_printf(const char *format, ...)
{
	int		i;
	int		bytes_written;
	va_list	list;

	if (!format)
		return (0);
	va_start(list, format);
	bytes_written = 0;
	i = -1;
	while (format[++i])
	{	
		if (format[i] != '%')
		{
			write(1, &format[i], 1);
			bytes_written++;
		}
		else
		{
			bytes_written += ft_process_param(format, &i, &list);
		}
	}
	va_end(list);
	return (bytes_written);
}

int	ft_process_param(const char *format, int *start, va_list *list)
{
	int		bytes_written;
	char	*param;
	t_specs	*specs;
	char	*aux;

	bytes_written = 0;
	param = ft_get_param(format, start);
	specs = ft_get_specs(param);
	if (specs->identifier == 'c')
		ft_print_char(va_arg(*list, int), &bytes_written, specs);
	else if (specs->identifier == '%')
		ft_print_char('%', &bytes_written, specs);
	else
	{
		aux = ft_get_str(specs->identifier, list);
		if (specs->precision > 0)
			aux = ft_aux_with_prec(aux, specs);
		ft_print_str(aux, &bytes_written, specs);
		free(aux);
	}
	free(param);
	free(specs);
	return (bytes_written);
}

void	ft_print_char(char c, int *bytes_written, t_specs *specs)
{
	int	i;

	i = 0;
	if (specs->l_justif <= 0)
		while (++i < specs->min_width)
			ft_putchar_printf(' ', bytes_written);
	ft_putchar_printf(c, bytes_written);
	i = 0;
	if (specs->l_justif > 0)
		while (++i < specs->min_width)
			ft_putchar_printf(' ', bytes_written);
}

void	ft_print_str(char *aux, int *bytes_written, t_specs *specs)
{
	int		len_aux;
	int		i;
	char	c;
	int		neg;

	len_aux = ft_strlen(aux);
	neg = ((aux) && (aux[0] == '-') && (specs->identifier != 's'));
	c = 32 - ((specs->l_justif) * 16);
	i = -1;
	if ((neg) && (specs->l_justif < 0))
		ft_putchar_printf('-', bytes_written);
	while ((specs->l_justif <= 0) && (++i < (specs->min_width - len_aux)))
		ft_putchar_printf(c, bytes_written);
	if ((neg) && (specs->l_justif >= 0))
		ft_putchar_printf('-', bytes_written);
	ft_process_prefix(aux, bytes_written, specs);
	if (specs->identifier != 's')
		specs->precision = 0;
	ft_putstr_printf(aux + neg, bytes_written, specs->precision);
	i = -1;
	while ((specs->l_justif > 0) && (++i < (specs->min_width - len_aux)))
		ft_putchar_printf(' ', bytes_written);
}

char	*ft_get_str(char identifier, va_list *list)
{
	char	*aux;
	char	*temp;

	if (identifier == 's')
		aux = ft_strdup(va_arg(*list, char *));
	if ((identifier == 'i') || (identifier == 'd'))
		aux = ft_itoa(va_arg(*list, int));
	if ((identifier == 'u') || (identifier == 'x') || (identifier == 'X'))
		aux = ft_uitoa(va_arg(*list, unsigned int), identifier);
	if (identifier == 'p')
	{
		aux = ft_uitoa(va_arg(*list, unsigned long long int), identifier);
		temp = aux;
		if (aux[0] == '0')
			aux = ft_strdup("(nil)");
		else
			aux = ft_strjoin("0x", aux);
		free(temp);
	}
	return (aux);
}
