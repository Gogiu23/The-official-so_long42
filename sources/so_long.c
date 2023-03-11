/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:26:23 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/11 22:05:17 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	void ft_first_print(t_game *so_long)
{
	ft_print_walls(so_long);
	ft_print_collectable(so_long);
//	ft_print_exit(so_long);
}

static	int ft_actions(int keycode, t_game *so_long)
{
	so_long->check = 1;
	if (keycode == 53)
		ft_destroy_game(so_long);
	else if (keycode == 2)
		ft_move_right(so_long);
	else if (keycode == 0)
		ft_move_left(so_long);
	else if (keycode == 1)
		ft_move_down(so_long);
	else if (keycode == 13)
		ft_move_up(so_long);
//	ft_printf("so_long->chars->pl[1] = %d\n", so_long->chars->pl[1]);
	return (1);
}

static	int ft_print_game(t_game *so_long)
{
	if (so_long->check == 1)
	{
//		mlx_clear_window(so_long->mlx, so_long->win);
		ft_count_chars(so_long);
		ft_print_background(so_long);
		ft_first_print(so_long);
		ft_print_player(so_long);
		ft_print_exit(so_long);
		so_long->check = 0;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_game	*so_long;
	int		fd;

	if (argc == 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	so_long = ft_init_game();
	ft_get_size_map(so_long, fd, argv);
	ft_check_errors(so_long);
	so_long->win = mlx_new_window(so_long->mlx, so_long->map_width * PXS, \
			so_long->map_height * PXS, "Rocket man");
	so_long->img = mlx_new_image(so_long->mlx, so_long->map_width * PXS, \
			so_long->map_height * PXS);
//	ft_print_background(so_long);
	mlx_hook(so_long->win, 17, 1L << 0, (void *)exit, 0);
	mlx_hook(so_long->win, 2, 0, ft_actions, so_long);
	mlx_loop_hook(so_long->mlx, ft_print_game, so_long);
	mlx_loop(so_long->mlx);
	ft_free(so_long);
	return (0);
}
