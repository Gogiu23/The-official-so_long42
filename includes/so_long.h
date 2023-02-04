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

//Init structures
t_game	*ft_init_game(void);
t_game	*ft_init_struct(void);
void	ft_init_variables_struct(t_game *so_long);

//Map handler
void	ft_get_size_map(t_game *so_long, int fd, char *argv[]);
void	ft_fitoar(t_game *so_long, int fd);
# endif

