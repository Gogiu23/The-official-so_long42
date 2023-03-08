#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>

# define PXS 50

/*
 * pl = player position [1] = X; [2] = Y;
 * np = number player;
 * dp = direccion player [0] = right; [1] = left;
 * nc = number collectables;
 * ne = number exit;
 */
typedef struct	s_char {
	int	pl[2];
	int	np;
	int	nc;
	int	ne;
	int	dp;
}	t_char;

typedef	struct	s_img {
	void	*player[2];
	void	*wall[1];
	void	*ground[1];
	void	*collectable[1];
	void	*exit[2];
}	t_img;

typedef	struct s_game {
	void	*mlx;
	void	*img;
	void	*win;
	char	*map;
	int		map_first_line;
	int		map_height;// altura of the map //
	int		map_width;// anchura del mapa //
	char	**matrix;
	char	**almatrix;
	t_img	*imgs;
	t_char	*chars;
}	t_game;

//Init structures
t_game	*ft_init_game(void);
t_game	*ft_init_struct(void);
void	ft_init_variables_struct(t_game *so_long);

//Map handler
void	ft_get_size_map(t_game *so_long, int fd, char *argv[]);
void	ft_fitoar(t_game *so_long, int fd);
void	ft_copy_map(t_game *so_long);

//Check errors
void	ft_check_errors(t_game *so_long);
int 	ft_no_limits(t_game *so_long);

//Counting chars
void	ft_count_chars(t_game *so_long);

//Print stack
void	ft_print_stack(t_game *t);

//Free and cleaning all leaks
void	ft_free(t_game *so_long);

//Find Player
void	ft_find_player(t_game *so_long);

//Create mallocs for images
void	ft_load_images(t_game *so_long);

//Printers
void	ft_put_img(t_game *so_long, void *img, int a, int b);
void	ft_print_walls(t_game *so_long);
void	ft_print_background(t_game *so_long);
void	ft_print_collectable(t_game *so_long);
void	ft_print_player(t_game *so_long);
void	ft_print_exit(t_game *so_long);

//End game
void	ft_destroy_game(t_game *so_long);

//Movements
void	ft_move_right(t_game *so_long);
void	ft_move_left(t_game *so_long);
void	ft_move_down(t_game *so_long);
void	ft_move_up(t_game *so_long);

# endif
