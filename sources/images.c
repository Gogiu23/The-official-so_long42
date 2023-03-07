/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdominic <gdominic@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:48:45 by gdominic          #+#    #+#             */
/*   Updated: 2023/03/07 19:14:43 by gdominic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../libft/includes/libft.h"
#include "../mlx/mlx.h"


static	char *ft_strjoin2(char *ptr, char *buffer)
{
	char	*str;
	size_t	j;
	size_t	i;

	if (!ptr)
	{
		ptr = (char *)malloc(sizeof(char) * 1);
		if (!ptr)
			return (NULL);
		ptr[0] = '\0';
	}
	i = -1;
	j = 0;
	str = malloc(sizeof(char) * (ft2_strlen(ptr) + ft2_strlen(buffer) + 1));
	if (!str)
		return (NULL);
	if (ptr)
		while (ptr[++i] != '\0')
			str[i] = ptr[i];
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[ft2_strlen(ptr) + ft2_strlen(buffer)] = '\0';
	return (str);
}

static	char *ft_path_to_sprite(char *img_name, int n)
{
	char	*nmbr;
	char	*str1;
	char	*str2;

	nmbr = ft_itoa(n);
	str1 = ft_strjoin2("images/", img_name);
	str2 = ft_strjoin2(str1, "/");
	ft_printf("str1: %s\n", str1);
	ft_printf("str2: %s\n", str2);
	ft_printf("img_name: %s\n", img_name);
	free(str1);
	str1 = ft_strjoin2(str2, img_name);
	free(str2);
	str2 = ft_strjoin2(str1, nmbr);
	free(str1);
	str1 = ft_strjoin2(str2, ".png");
	free(str2);
	free(nmbr);
//	exit (0);
	return (str1);
}

static	void ft_final_sprite_loading(int a, char *path, int ty_sprite, \
		t_game *so_long)
{
	int	size;

	size = PXS;
	if (ty_sprite == 1)
		so_long->imgs->player[a - 1] = mlx_png_file_to_image(so_long->mlx, \
				path, &size, &size);
	else if (ty_sprite == 2)
		so_long->imgs->wall[a - 1] = mlx_png_file_to_image(so_long->mlx, \
				path, &size, &size);
	else if (ty_sprite == 3)
		so_long->imgs->ground[a - 1] = mlx_png_file_to_image(so_long->mlx, \
				path, &size, &size);
	else if (ty_sprite == 4)
		so_long->imgs->collectable[a - 1] = mlx_png_file_to_image(so_long->mlx, \
				path, &size, &size);
	else if (ty_sprite == 5)
		so_long->imgs->exit[a - 1] = mlx_png_file_to_image(so_long->mlx, \
				path, &size, &size);
//	free(path);
//	exit(0);
}

static	void ft_load_spites(char *img_name, int mem_sprite, int ty_sprite, \
		t_game *so_long)
{
	int		i;
	char	*path;
	int		fd;

	i = 0;
	while (i++ < mem_sprite)
	{
		path = ft_path_to_sprite(img_name, i - 1);
//		exit (0);
		fd = open(path, O_RDONLY);
		if (fd < 0)
			ft_putstr_error("Image format not valid\n");
		close(fd);
		ft_final_sprite_loading(i, path, ty_sprite, so_long);
		free(path);
	}
}

void	ft_load_images(t_game *so_long)
{
//	exit (0);
	ft_load_spites("player", 2, 1, so_long);
	ft_load_spites("wall", 1, 2, so_long);
	ft_load_spites("ground", 1, 3, so_long);
	ft_load_spites("collectable", 1, 4, so_long);
	ft_load_spites("exit", 2, 5, so_long);
}
