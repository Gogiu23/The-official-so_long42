/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 20:42:42 by gdominic          #+#    #+#             */
/*   Updated: 2023/02/23 17:28:03 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

t_game	*ft_init_game(void)
{
	t_game	*so_long;

	so_long = ft_init_struct();
	ft_init_variables_struct(so_long);
	return (so_long);
}

t_game	*ft_init_struct(void)
{
	t_game	*so_long;

	so_long = ft_calloc((sizeof(t_game) * 1), 1);
	if (!so_long)
		exit (EXIT_FAILURE);
	so_long->imgs = ft_calloc((sizeof(t_img) * 1), 1);
	if (!so_long->imgs)
		exit (EXIT_FAILURE);
	so_long->chars = ft_calloc((sizeof(t_char) * 1), 1);
	if (!so_long->chars)
		exit (EXIT_FAILURE);
	return (so_long);
}

void	ft_init_variables_struct(t_game *so_long)
{
	so_long->map_height = 0;
	so_long->map_width = 0;
	so_long->chars->pl[0] = 0;
	so_long->chars->pl[1] = 0;
}
