/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:53:45 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/13 20:21:56 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	int	ft_move_verti(t_game *so_long, int x, int y)
{
	if (so_long->almatrix[x][y + 1] != '1')
	{
		so_long->almatrix[x][y] = 'V';
		return (0);
	}
	return (1);
}

static	int	ft_move_hori(t_game *so_long, int x, int y)
{
	if (so_long->almatrix[x + 1][y] != '1')
	{
		so_long->almatrix[x][y] = 'V';
		return (0);
	}
	return (1);
}

int	ft_check_path(t_game *so_long, int x, int y)
{
	ft_copy_map(so_long);
	if (ft_move_hori(so_long, x, y) == 0)
		ft_move_hori(so_long, x++, y);
	if (ft_move_verti(so_long, x, y) == 0)
		ft_move_verti(so_long, x, y++);
	if (ft_check_path(so_long, x, y) == 0)
		ft_check_path(so_long, x + 1, y);
	return (1);
}
