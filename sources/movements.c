/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:30:03 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/13 17:37:18 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

void	ft_move_right(t_game *so_long)
{
	t_char	*player;

	player = so_long->chars;
	if (so_long->chars->nc > 0)
	{
		if (so_long->matrix[player->pl[0]][player->pl[1] + 1] != '1' && \
				so_long->matrix[player->pl[0]][player->pl[1] + 1] != 'E')
		{
			player->pl[1]++;
			ft_printf("Movements player: %d\r", so_long->chars->mp++);
			so_long->chars->dp = 1;
			so_long->matrix[player->pl[0]][player->pl[1]] = '0';
			so_long->matrix[player->pl[0]][player->pl[1] - 1] = '0';
		}
	}
	else if (so_long->matrix[player->pl[0]][player->pl[1] + 1] != '1')
	{
		player->pl[1]++;
		ft_printf("Movements player: %d\r", so_long->chars->mp++);
		so_long->chars->dp = 1;
		if (so_long->matrix[player->pl[0]][player->pl[1]] == 'E')
			ft_destroy_game(so_long);
	}
}

void	ft_move_left(t_game *so_long)
{
	t_char	*player;

	player = so_long->chars;
	if (so_long->chars->nc > 0)
	{
		if (so_long->matrix[player->pl[0]][player->pl[1] - 1] != '1' && \
				so_long->matrix[player->pl[0]][player->pl[1] - 1] != 'E')
		{
			player->pl[1]--;
			ft_printf("Movements player: %d\r", so_long->chars->mp++);
			so_long->chars->dp = 2;
			so_long->matrix[player->pl[0]][player->pl[1]] = '0';
			so_long->matrix[player->pl[0]][player->pl[1] + 1] = '0';
		}
	}
	else if (so_long->matrix[player->pl[0]][player->pl[1] - 1] != '1')
	{
		player->pl[1]--;
		ft_printf("Movements player: %d\r", so_long->chars->mp++);
		so_long->chars->dp = 2;
		if (so_long->matrix[player->pl[0]][player->pl[1]] == 'E')
			ft_destroy_game(so_long);
	}
}

void	ft_move_down(t_game *so_long)
{
	t_char	*player;

	player = so_long->chars;
	if (so_long->chars->nc > 0)
	{
		if (so_long->matrix[player->pl[0] + 1][player->pl[1]] != '1' && \
				so_long->matrix[player->pl[0] + 1][player->pl[1]] != 'E')
		{
			player->pl[0]++;
			ft_printf("Movements player: %d\r", so_long->chars->mp++);
			so_long->matrix[player->pl[0]][player->pl[1]] = '0';
			so_long->matrix[player->pl[0] - 1][player->pl[1]] = '0';
		}
	}
	if (so_long->chars->nc == 0 && \
			so_long->matrix[player->pl[0] + 1][player->pl[1]] != '1')
	{
		player->pl[0]++;
		ft_printf("Movements player: %d\r", so_long->chars->mp++);
		if (so_long->matrix[player->pl[0]][player->pl[1]] == 'E')
		{
			mlx_destroy_window(so_long->mlx, so_long->win);
			exit (EXIT_SUCCESS);
		}
	}
}

void	ft_move_up(t_game *so_long)
{
	t_char	*player;

	player = so_long->chars;
	if (so_long->chars->nc > 0)
	{
		if (so_long->matrix[player->pl[0] - 1][player->pl[1]] != '1' && \
				so_long->matrix[player->pl[0] - 1][player->pl[1]] != 'E')
		{
			player->pl[0]--;
			ft_printf("Movements player: %d\r", so_long->chars->mp++);
			so_long->matrix[player->pl[0]][player->pl[1]] = '0';
			so_long->matrix[player->pl[0] + 1][player->pl[1]] = '0';
		}
	}
	else if (so_long->matrix[player->pl[0] - 1][player->pl[1]] != '1')
	{
		player->pl[0]--;
		ft_printf("Movements player: %d\r", so_long->chars->mp++);
		if (so_long->matrix[player->pl[0]][player->pl[1]] == 'E')
			ft_destroy_game(so_long);
	}
}
