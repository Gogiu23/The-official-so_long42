/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:30:03 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/08 22:05:34 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

void	ft_move_right(t_game *so_long)
{
	t_char	*player;

	player = so_long->chars;
//	ft_printf("matrix despues de jugador: %c\n", so_long->matrix[player->pl[0]][player->pl[1]]);
	if (so_long->matrix[player->pl[0]][player->pl[1] + 1] != '1' &&\
			so_long->matrix[player->pl[0]][player->pl[1] + 1] != 'E')
	{
		player->pl[1]++;
		so_long->chars->dp = 1;
		so_long->matrix[player->pl[0]][player->pl[1] - 1] = '0';
		return ;
	}
	if (so_long->matrix[player->pl[0]][player->pl[1] + 1] == 'E' && so_long->chars->nc == 0)
	{
		mlx_destroy_window(so_long->mlx, so_long->win);
		exit (EXIT_SUCCESS);
	}
	ft_printf("posicion player: %c\n", so_long->matrix[player->pl[0]][player->pl[1]]);
	ft_printf("numbver of collectable: %d\n", so_long->chars->nc);
//	ft_printf("matrix despues de jugador: %c\n", so_long->matrix[player->pl[0]][player->pl[1] - 1]);
//	exit (0);
}

void	ft_move_left(t_game *so_long)
{
	t_char	*player;

	player = so_long->chars;
	if (so_long->matrix[player->pl[0]][player->pl[1] - 1] != '1')
	{
		player->pl[1]--;
		so_long->chars->dp = 2;
		so_long->matrix[player->pl[0]][player->pl[1] + 1] = '0';
	}
}

void	ft_move_down(t_game *so_long)
{
	t_char	*player;

	player = so_long->chars;
	if (so_long->matrix[player->pl[0] + 1][player->pl[1]] != '1')
	{
		player->pl[0]++;
		so_long->matrix[player->pl[0] - 1][player->pl[1]] = '0';
	}
}

void	ft_move_up(t_game *so_long)
{
	t_char	*player;

	player = so_long->chars;
//	ft_printf("matrix up jugador: %c\n", so_long->matrix[player->pl[0] + 1][player->pl[1]]);
	if (so_long->matrix[player->pl[0] - 1][player->pl[1]] != '1')
	{
		player->pl[0]--;
		so_long->matrix[player->pl[0] + 1][player->pl[1]] = '0';
	}
}
