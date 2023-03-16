/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:12:15 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/16 14:26:45 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	int	ft_find_diff_chars(t_game *so_long)
{
	int	a;
	int	b;

	a = 0;
	while (so_long->matrix[a])
	{
		b = 0;
		while (so_long->matrix[a][b])
		{
			if (so_long->matrix[a][b] != 'P' && so_long->matrix[a][b] != 'C' \
					&& so_long->matrix[a][b] != 'E' \
					&& so_long->matrix[a][b] != '1' \
					&& so_long->matrix[a][b] != '0')
				return (0);
			b++;
		}
		a++;
	}
	return (1);
}

static	int	ft_check_size_map(t_game *so_long)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (so_long->matrix[a])
	{
		if (ft_strlen(so_long->matrix[b]) == so_long->map_width)
			b++;
		else
			return (0);
		a++;
	}
	return (1);
}

static	int	ft_check_char(t_game *so_long)
{
	t_char	*chars;

	ft_count_chars(so_long);
	chars = so_long->chars;
	if (chars->np > 1)
		return (0);
	else if (chars->ne > 1)
		return (0);
	return (1);
}

void	ft_check_errors(t_game *so_long, char *filename)
{
	ft_find_player(so_long);
	if (ft_check_extension(filename) == -0)
		ft_putstr_error("Error\nThe file has to be .ber\n");
	if (ft_check_size_map(so_long) == 0)
		ft_putstr_error("Error\nInvalid map size\n");
	if (ft_check_char(so_long) == 0)
		ft_putstr_error("Error\nInvalid numbers of chars\n");
	if (ft_find_diff_chars(so_long) == 0)
		ft_putstr_error("Error\nInvalid chars presents in the map\n");
	if (ft_no_limits(so_long) == 0)
		ft_putstr_error("Error\nThe outside map limits are \
				not the corrects ones\n");
	if (ft_check_path(so_long) == 0)
		ft_putstr_error("Error\nThere is no exit available\n");
}
