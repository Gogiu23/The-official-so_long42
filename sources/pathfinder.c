/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:53:45 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/16 12:44:28 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	int	ft_check_exit_path(t_game *so_long, int r, int c)
{
	if (so_long->almatrix[r + 1][c] != 'V' && so_long->almatrix[r - 1][c] \
			!= 'V' && so_long->almatrix[r][c + 1] != 'V' && \
			so_long->almatrix[r][c - 1] != 'V')
		return (0);
	return (1);
}

static	int	ft_where_is_the_exit(t_game *so_long)
{
	int	r;
	int	c;

	r = 0;
	while (so_long->almatrix[r])
	{
		c = 0;
		while (so_long->almatrix[r][c])
		{
			if (so_long->almatrix[r][c] == 'C')
				return (0);
			if (so_long->almatrix[r][c] == 'E')
			{
				if (ft_check_exit_path(so_long, r, c) == 0)
					return (0);
			}
			c++;
		}
		r++;
	}
	return (1);
}

static	int	ft_a_valid_wayout(t_game *so_long, int r, int c)
{
	if (r < 0 || c < 0 || so_long->almatrix[r][c] == '1' \
			|| so_long->almatrix[r][c] == 'V')
		return (0);
	if (so_long->almatrix[r][c] == 'E')
		return (0);
	so_long->almatrix[r][c] = 'V';
	ft_a_valid_wayout(so_long, r + 1, c);
	ft_a_valid_wayout(so_long, r - 1, c);
	ft_a_valid_wayout(so_long, r, c + 1);
	ft_a_valid_wayout(so_long, r, c - 1);
	if (ft_where_is_the_exit(so_long) == 0)
		return (0);
	return (1);
}

static	int	ft_where_is_p(t_game *so_long)
{
	int	f;
	int	c;

	f = 0;
	while (so_long->almatrix[f])
	{
		c = 0;
		while (so_long->almatrix[f][c])
		{
			if (so_long->almatrix[f][c] == 'P')
			{
				if (ft_a_valid_wayout(so_long, f, c) == 0)
					return (0);
			}
			c++;
		}
		f++;
	}
	return (1);
}

int	ft_check_path(t_game *so_long)
{
	ft_copy_map(so_long);
	if (ft_where_is_p(so_long) == 0)
		return (0);
	return (1);
}
