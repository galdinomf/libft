/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:12:34 by mgaldino          #+#    #+#             */
/*   Updated: 2022/06/22 16:11:08 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_char_in_string(char c, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_param(const char *format, int *start)
{
	int		j;
	char	*param;

	j = 1;
	while (!ft_char_in_string(format[*start + j], MY_IDENTIFIERS))
		j++;
	param = ft_substr(format, *start + 1, j);
	*start += j;
	return (param);
}

void	ft_initialize_specs(t_specs *specs)
{	
	specs->l_justif = 0;
	specs->min_width = 0;
	specs->precision = 0;
	specs->identifier = 0;
	specs->prefix = 0;
}

t_specs	*ft_get_specs(char *param)
{
	t_specs	*specs;
	int		j;

	specs = (t_specs *) malloc(sizeof(t_specs));
	ft_initialize_specs(specs);
	j = -1;
	while (ft_char_in_string(param[++j], FLAGS) && (param[j] != '.'))
	{
		if ((param[j] == '0') && (specs->l_justif == 0))
			specs->l_justif = -1;
		if (param[j] == '-')
			specs->l_justif = 1;
		if (ft_char_in_string(param[j], PREFIXS))
			specs->prefix = param[j];
	}
	while (ft_isdigit(param[j]))
		specs->min_width = specs->min_width * 10 + param[j++] - '0';
	if (param[j] == '.')
		j++;
	while (ft_isdigit(param[j]))
		specs->precision = specs->precision * 10 + param[j++] - '0';
	specs->identifier = param[j];
	if ((j != 0) && (param[j] == 's') && (param[j - 1] == '.'))
		specs->precision = -1;
	return (specs);
}

void	ft_process_prefix(char *aux, int *bytes_written, t_specs *specs)
{
	int	*bw_addrss;

	bw_addrss = bytes_written;
	if ((specs->prefix == '#'))
	{
		if ((specs->identifier == 'x') && (aux[0] != '0'))
			ft_putstr_printf("0x", bw_addrss, specs->precision);
		if ((specs->identifier == 'X') && (aux[0] != '0'))
			ft_putstr_printf("0X", bw_addrss, specs->precision);
	}
	if (specs->prefix == ' ')
	{
		if ((specs->identifier != 's') && (aux) && (aux[0] != '-'))
			ft_putstr_printf(" ", bytes_written, specs->precision);
	}
	if ((specs->prefix == '+') && (aux) && (aux[0] != '-'))
		ft_putstr_printf("+", bytes_written, specs->precision);
}
