/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:55:37 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/13 17:36:08 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"

static	void	ft_print_chars(t_game *so_long)
{
	t_char	*chars;

	chars = so_long->chars;
	ft_printf("np: %d\n", chars->np);
	ft_printf("np: %d\n", chars->ne);
	ft_printf("np: %d\n", chars->nc);
	ft_printf("pl[1]: %d\n", so_long->chars->pl[0]);
	ft_printf("pl[2]: %d\n", so_long->chars->pl[1]);
}

void	ft_print_stack(t_game *t)
{
	int	i;
	int	b;

	b = 0;
	i = 0;
	while (t->matrix[i])
	{
		ft_printf("array t->marrix[%d]: \t%s\n", i, t->matrix[i]);
		i++;
	}
	ft_printf("Prueba de array: %c\n", t->matrix[2][9]);
	i = 0;
	while (t->matrix[i])
	{
		b = 0;
		while (t->matrix[i][b])
		{
			ft_printf("%c", t->matrix[i][b]);
			b++;
		}
		ft_printf("\n");
		i++;
	}
	ft_print_chars(t);
}
