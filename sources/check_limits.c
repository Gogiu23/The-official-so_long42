/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_limits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 13:42:01 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/13 18:02:27 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	int	ft_upper_limit(t_game *so_long)
{
	int	b;

	b = 0;
	while (so_long->matrix[0][b])
	{
		if (so_long->matrix[0][b] != '1')
			return (0);
		b++;
	}
	return (1);
}

static	int	ft_sides_limits(t_game *so_long)
{
	int	a;

	a = 0;
	while (so_long->matrix[a])
	{
		if (so_long->matrix[a][0] != '1')
			return (0);
		a++;
	}
	a = 0;
	while (so_long->matrix[a][so_long->map_width])
	{
		if (so_long->matrix[a][so_long->map_width] != '1')
			return (0);
		a++;
	}
	return (1);
}

static	int	ft_below_limits(t_game *so_long)
{
	int	b;

	b = 0;
	while (so_long->matrix[b])
	{
		if (so_long->matrix[so_long->map_height - 1][b] != '1')
			return (0);
		b++;
	}
	return (1);
}

int	ft_no_limits(t_game *so_long)
{
	if (ft_upper_limit(so_long) == 0)
		return (0);
	if (ft_sides_limits(so_long) == 0)
		return (0);
	if (ft_below_limits(so_long) == 0)
		return (0);
	return (1);
}
