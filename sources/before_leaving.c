/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_leaving.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:35:40 by gdominic          #+#    #+#             */
/*   Updated: 2023/02/09 14:41:29 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

void	ft_free(t_game *so_long)
{
	int	nbr;

	nbr = 0;
	if (so_long->matrix)
	{
		exit (0);
		while (so_long->matrix[nbr])
		{
			free(so_long->matrix[nbr]);
			nbr++;
		}
		free(so_long->matrix);
		if (so_long->imgs)
			free(so_long->imgs);
		if (so_long->chars)
			free(so_long->chars);
	}
}

