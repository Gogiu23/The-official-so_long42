/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:22:01 by gdominic          #+#    #+#             */
/*   Updated: 2023/02/03 12:28:12 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

void	ft_get_size_map(t_game *so_long, int fd, char *argv[])
{
	while (1)
	{
		so_long->map = get_next_line(fd);
		if (!so_long->map)
			break;
		so_long->map_width = ft_strlen(so_long->map) - 1;
		free(so_long->map);
		so_long->map_height++;
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	ft_fitoar(so_long, fd);
}

void	ft_fitoar(t_game *so_long, int fd)
{
	int		i;
	int		nbr;

	i = 0;
	so_long->map = get_next_line(fd);
	so_long->matrix = (char **)malloc(sizeof(char *) * so_long->map_height + 1);
	if (!so_long->matrix)
		exit (EXIT_FAILURE);
	ft_printf("so_long->map_height: %d\n", so_long->map_height);
	ft_printf("so_long->map_width: %d\n", so_long->map_width);
	ft_printf("so_long->map: %d\n", ft_strlen(so_long->map));
	while (so_long->map)
	{
		nbr = 0;
		so_long->matrix[i] = (char *)malloc(sizeof(char) * so_long->map_width + 1);
		if (!so_long->matrix[i])
			exit (EXIT_FAILURE);
		while (so_long->map[nbr])
		{
			so_long->matrix[i][nbr] = so_long->map[nbr];
			nbr++;
		}
		so_long->matrix[i][nbr - 1] = '\0';
		free(so_long->map);
		so_long->map = get_next_line(fd);
		i++;
	}
	so_long->matrix[i] = NULL;
	close(fd);
}
