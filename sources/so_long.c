/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:26:23 by gdominic          #+#    #+#             */
/*   Updated: 2023/02/02 23:32:43 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

int	main(int argc, char *argv[])
{
	t_game	so_long;
	int		fd;

	if (argc == 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	ft_init_game(&so_long);
	ft_get_size_map(&so_long, fd, argv);
	ft_fitoar(&so_long, fd);
	ft_check_errors(&so_long);
	return (0);
}
