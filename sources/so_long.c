/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:26:23 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/20 10:32:32 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	int	ft_actions(int keycode, t_game *so_long)
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
	return (1);
}

static	void	ft_put_string_to_screen(t_game *so_long)
{
	char	*screen;

	screen = 0;
	ft_put_img(so_long, so_long->imgs->wall[0], 0 * PXS, 0 * PXS);
	ft_put_img(so_long, so_long->imgs->wall[0], 1 * PXS, 0 * PXS);
	ft_put_img(so_long, so_long->imgs->wall[0], 2 * PXS, 0 * PXS);
	screen = ft_itoa(so_long->chars->mp);
	mlx_string_put(so_long->mlx, so_long->win, 8, 20, 0x1C0808, "Movements:");
	mlx_string_put(so_long->mlx, so_long->win, 110, 20, 0x1C0808, screen);
	free(screen);
}

static	int	ft_print_game(t_game *so_long)
{
	if (so_long->check == 1)
	{
		ft_count_chars(so_long);
		ft_print_background(so_long);
		ft_print_player(so_long);
		ft_print_exit(so_long);
		so_long->check = 0;
		ft_put_string_to_screen(so_long);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_game	*so_long;
	int		fd;

	if (argc != 2)
		ft_putstr_error("Error\nUsage: ./so_long [*.ber]\n");
	fd = open(argv[1], O_RDONLY);
	so_long = ft_init_game();
	ft_get_size_map(so_long, fd, argv);
	ft_check_errors(so_long, argv[1]);
	so_long->win = mlx_new_window(so_long->mlx, so_long->map_width * PXS, \
			so_long->map_height * PXS, "Rocket man");
	so_long->img = mlx_new_image(so_long->mlx, so_long->map_width * PXS, \
			so_long->map_height * PXS);
	ft_print_walls(so_long);
	ft_print_collectable(so_long);
	mlx_hook(so_long->win, 17, 1L << 0, (void *)exit, 0);
	mlx_hook(so_long->win, 2, 0, ft_actions, so_long);
	mlx_loop_hook(so_long->mlx, ft_print_game, so_long);
	mlx_loop(so_long->mlx);
	ft_free(so_long);
	return (0);
}
