#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>

typedef	struct	s_img {
}	t_img;

typedef	struct s_game {
	void	*mlx;
	void	*img;
	void	*win;
	char	*map;
	char	**map_2;
	int		map_height;// altura of the map //
	int		map_width;// anchura del mapa //
	char	**matrix;
	t_img	*imgs;
}	t_game;

# endif

