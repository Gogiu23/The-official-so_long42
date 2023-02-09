/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:12:15 by gdominic          #+#    #+#             */
/*   Updated: 2023/02/09 14:18:20 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	int	ft_check_size_map(t_game *so_long)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (so_long->matrix[a])
	{
		if (ft_strlen(so_long->matrix[b]) == so_long->map_width)
			b++;
		else
			return (0);
		a++;
	}
	return (1);
}

static	int	ft_check_char(t_game *so_long)
{
	t_char	*chars;

	ft_count_chars(so_long);
	chars = so_long->chars;
	if (chars->np > 1)
		return (0);
	else if (chars->ne > 1)
		return (0);
	return (1);	
}

void	ft_check_errors(t_game *so_long)
{
	if (ft_check_size_map(so_long) == 0)
		ft_putstr_error("Invalid map size\n");
	if (ft_check_char(so_long) == 0)
		ft_putstr_error("Error: Invalid numbers of chars\n");

}

