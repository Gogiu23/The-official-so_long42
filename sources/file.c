/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:18:49 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/16 14:26:58 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

int	ft_check_extension(char *file)
{
	size_t	len;

	len = 0;
	len = ft_strlen(file);
	if (!ft_strnstr(&file[len - 4], ".ber", 4))
		return (0);
	return (1);
}
