/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:42:01 by mgaldino          #+#    #+#             */
/*   Updated: 2022/06/22 15:44:54 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	int				bytes_read;
	char			*buf;
	static char		*acc[OPEN_MAX];
	int				i;
	char			*result;

	if ((fd < 0) || (fd > OPEN_MAX) || (BUFFER_SIZE <= 0))
		return (NULL);
	buf = (char *) malloc(BUFFER_SIZE + 1);
	bytes_read = ft_initialize_and_get_line(fd, buf, &acc[fd]);
	if ((bytes_read < 0) || (!acc[fd][0]))
	{
		free (acc[fd]);
		acc[fd] = NULL;
		return (NULL);
	}
	else
	{
		i = -1;
		while ((acc[fd][++i] != '\n') && (acc[fd][i]))
			;
		result = ft_substr(acc[fd], 0, i + 1);
		acc[fd] = ft_extract_remainder_bytes_from_line(acc[fd]);
		return (result);
	}
}
