/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:22:01 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/13 17:57:28 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

void	ft_get_size_map(t_game *so_long, int fd, char *argv[])
{
	int	bol;

	bol = 0;
	while (1)
	{
		so_long->map = get_next_line(fd);
		if (!so_long->map)
			break ;
		if (bol == 0)
		{
			so_long->map_first_line = ft_strlen(so_long->map) - 1;
			bol++;
		}
		so_long->map_width = ft_strlen(so_long->map) - 1;
		if (so_long->map_width != so_long->map_first_line)
			ft_putstr_error("Error\nInvalid size of the map\n");
		free(so_long->map);
		so_long->map_height++;
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	ft_fitoar(so_long, fd);
}

void	ft_fitoar(t_game *so_long, int fd)
{
	so_long->map = get_next_line(fd);
	so_long->matrix = (char **)malloc(sizeof(char *) * so_long->map_height + 1);
	if (!so_long->matrix)
		exit (EXIT_FAILURE);
	while (so_long->map)
	{
		so_long->m1 = 0;
		so_long->matrix[so_long->m2] = \
				(char *)malloc(sizeof(char) * so_long->map_width + 1);
		if (!so_long->matrix[so_long->m2])
			exit (EXIT_FAILURE);
		while (so_long->map[so_long->m1])
		{
			so_long->matrix[so_long->m2][so_long->m1] = \
					so_long->map[so_long->m1];
			so_long->m1++;
		}
		so_long->matrix[so_long->m2][so_long->m1 - 1] = '\0';
		free(so_long->map);
		so_long->map = get_next_line(fd);
		so_long->m2++;
	}
	so_long->matrix[so_long->m2] = NULL;
	close(fd);
}

void	ft_count_chars(t_game *so_long)
{
	int	a;
	int	b;

	a = 0;
	so_long->chars->nc = 0;
	while (so_long->matrix[a])
	{
		b = 0;
		while (so_long->matrix[a][b])
		{
			if (so_long->matrix[a][b] == 'P')
				so_long->chars->np++;
			else if (so_long->matrix[a][b] == 'E')
				so_long->chars->ne++;
			else if (so_long->matrix[a][b] == 'C')
				so_long->chars->nc++;
			b++;
		}
		a++;
	}
}

void	ft_copy_map(t_game *so_long)
{
	int	i;

	i = 0;
	so_long->almatrix = (char **)ft_calloc(sizeof(char *) * \
			so_long->map_height, 1);
	if (!so_long->almatrix)
		exit (EXIT_FAILURE);
	while (so_long->matrix[i])
	{
		so_long->almatrix[i] = ft_strdup(so_long->matrix[i]);
		i++;
	}
	so_long->almatrix[i] = NULL;
}

void	ft_find_player(t_game *so_long)
{
	int	a;
	int	b;

	a = 0;
	while (so_long->matrix[a])
	{
		b = 0;
		while (so_long->matrix[a][b])
		{
			if (so_long->matrix[a][b] == 'P')
			{
				so_long->chars->pl[0] = a;
				so_long->chars->pl[1] = b;
			}
			b++;
		}
		a++;
	}
}
