/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:20:51 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/07 19:15:23 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

void	ft_put_img(t_game *so_long, void *img, int a, int b)
{
	if (a < -PXS || b < -PXS)
		return ;
	mlx_put_image_to_window(so_long->mlx, so_long->win, img, a, b);
}
