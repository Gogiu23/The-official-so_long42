/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:12:47 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/08 21:36:25 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

void	ft_print_walls(t_game *so_long)
{
	t_img	*sprite;
	int		a;
	int		b;

	sprite = so_long->imgs;
	a = 0;
	while (so_long->matrix[a])
	{
		b = 0;
		while (so_long->matrix[a][b])
		{
			if (so_long->matrix[a][b] == '1')
				ft_put_img(so_long, sprite->wall[0], b * PXS, a * PXS);
			b++;
		}
		a++;
	}
}

void	ft_print_background(t_game *so_long)
{
	t_img	*sprite;
	int		a;
	int		b;

	sprite = so_long->imgs;
	a = 0;
	while (so_long->matrix[a])
	{
		b = 0;
		while (so_long->matrix[a][b])
		{
			if (so_long->matrix[a][b] == '0')
				ft_put_img(so_long, sprite->ground[0], b * PXS, a * PXS);
			b++;
		}
		a++;
	}
}

void	ft_print_collectable(t_game *so_long)
{
	t_img	*sprite;
	int		a;
	int		b;

	sprite = so_long->imgs;
	a = 0;
	while (so_long->matrix[a])
	{
		b = 0;
		while (so_long->matrix[a][b])
		{
			if (so_long->matrix[a][b] == 'C')
				ft_put_img(so_long, sprite->collectable[0], b * PXS, a * PXS);
			b++;
		}
		a++;
	}
}

void	ft_print_player(t_game *so_long)
{
	t_img	*sprite;

	sprite = so_long->imgs;
	if (so_long->chars->dp == 1)
		ft_put_img(so_long, sprite->player[0], so_long->chars->pl[1] * PXS, \
				so_long->chars->pl[0] * PXS);
	else
		ft_put_img(so_long, sprite->player[1], so_long->chars->pl[1] * PXS, \
				so_long->chars->pl[0] * PXS);
}

void	ft_print_exit(t_game *so_long)
{
	t_img	*sprite;
	int		a;
	int		b;

	sprite = so_long->imgs;
	a = 0;
	while (so_long->matrix[a])
	{
		b = 0;
		while (so_long->matrix[a][b])
		{
			if (so_long->matrix[a][b] == 'E')
			{
				if (so_long->chars->nc == 0)
					ft_put_img(so_long, sprite->exit[1], b * PXS, a * PXS);
				else
					ft_put_img(so_long, sprite->exit[0], b * PXS, a * PXS);
			}
			b++;
		}
		a++;
	}
}
