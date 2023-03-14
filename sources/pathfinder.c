/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:53:45 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/14 17:42:21 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	int	ft_where_is_the_exit(t_game *so_long)
{
	int	a;
	int	b;

	a = 0;
	while (so_long->almatrix[a])
	{
		b = 0;
		while (so_long->almatrix[a][b])
		{
			if (so_long->almatrix[a][b] == 'C')
				return (0);
			b++;
		}
		a++;
	}
	return (1);
}

static	int	ft_a_valid_wayout(t_game *so_long)
{
	int	a;
	int	b;

	a = 0;
	while (so_long->almatrix[a])
	{
		b = 0;
		while (so_long->almatrix[a][b])
		{
			if (so_long->almatrix[a][b] == '0')
				so_long->almatrix[a][b] = 'V';
			if (so_long->almatrix[a][b] == 'C')
				so_long->almatrix[a][b] = 'V';
			b++;
		}
		a++;
	}
	if (ft_where_is_the_exit(so_long) == 0)
		return (0);
	return (1);
}

static	int	ft_where_is_P(t_game *so_long)
{
	int	x;
	int	y;

	y = 0;
	while (so_long->almatrix[y])
	{
		x = 0;
		while (so_long->almatrix[y][x])
		{
			if (so_long->almatrix[y][x] == 'P')
			{
				if (ft_a_valid_wayout(so_long) == 0)
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	ft_check_path(t_game *so_long)
{
	ft_copy_map(so_long);
	if (ft_where_is_P(so_long) == 0)
		return (0);
	return (1);
}
