# So_long 42
#### A 2D game using "MiniLibX", a graphical interface library (Copyright ol@ - 2002-2019 - Olivier Crouzet).
###### The game consists in collecting collectibles and finding the exit to win.


<h1 align="center">

![gif](https://github.com/Gogiu23/The-official-so_long42/blob/master/images_markdown/so_long.gif)

</h1>

[TOC]
### ▶︎ The init...
On this point i made a function mother that recopile all the variable and start all of them to zero.
Here all my structs are allocated with `ft_calloc` from my **Libft**.
```c
int	main(int argc, char *argv[])
{
  t_game  *so_long;
  
  so_long = ft_init_game();
}
```
I define the struct on the main
```c
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
```
Here i allocated the memory for the three struct i used for the game.

**The struct i used**
```c
typedef struct s_char {

}	t_char;

typedef struct s_img {

}	t_img;

typedef struct s_game {

}	t_game;
```

### ▶︎ The map

We use again the `get_next_line` from the **Libft** (we also discovered that `ft_strjoin` was givinig me several leaks) in order
to read the map we'll pass from the command line.
I choose to make doble array i order to storage the map as a chars.
First we need to know the width and the height of the map. Nothing better that a function call `ft_get_size_map(t_game *so_long, int fd, char *argv[])`
```c
void	ft_get_size_map(t_game *so_long, int fd, char *argv[])
{
	int	bol;

	bol = 0;
	while (1)
	{
		so_long->map = get_next_line(fd);
		if (!so_long->map)
			break ;
		if (bol == 0)
		{
			so_long->map_first_line = ft_strlen(so_long->map) - 1;
			bol++;
		}
		so_long->map_width = ft_strlen(so_long->map) - 1;
		if (so_long->map_width != so_long->map_first_line)
			ft_putstr_error("Error\nInvalid size of the map\n");
		free(so_long->map);
		so_long->map_height++;
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	ft_fitoar(so_long, fd);
}
```
With all this info i should be able to recopile i'm finally ready to allocate the memory for the doble array of chars:
```c
void	ft_fitoar(t_game *so_long, int fd)
{
	so_long->map = get_next_line(fd);
	so_long->matrix = (char **)malloc(sizeof(char *) * so_long->map_height + 1);
	if (!so_long->matrix)
		exit (EXIT_FAILURE);
	while (so_long->map)
	{
		so_long->m1 = 0;
		so_long->matrix[so_long->m2] = \
				(char *)malloc(sizeof(char) * so_long->map_width + 1);
		if (!so_long->matrix[so_long->m2])
			exit (EXIT_FAILURE);
		while (so_long->map[so_long->m1])
		{
			so_long->matrix[so_long->m2][so_long->m1] = \
					so_long->map[so_long->m1];
			so_long->m1++;
		}
		so_long->matrix[so_long->m2][so_long->m1 - 1] = '\0';
		free(so_long->map);
		so_long->map = get_next_line(fd);
		so_long->m2++;
	}
	so_long->matrix[so_long->m2] = NULL;
	close(fd);
}
```
The name `ft_fitoar(t_game *so_long, int fd)` came to me inspired from `ft_atoi`. It means nothing else that *files to array*.
Now is the time to check the possibles errors made in the map.

### ▶︎ Check errors
First of all we have to check the errors and manage the parsing code coming form the console. 
```c
if (argc != 2)
	ft_putstr_error("Error\nUsage: ./so_long [*.ber]\n");
```
Then we checked if the map was corrupted:
```c
	if (fd < 0)
		ft_putstr_error("Error\nNo file available\n");
```
After that we move to a function that resume all the possible errors, including the `pathfinder` 👹
```c
void	ft_check_errors(t_game *so_long, char *filename)
{
	ft_find_player(so_long);
	if (ft_check_extension(filename) == -0)
		ft_putstr_error("Error\nThe file has to be .ber\n");
	if (ft_check_size_map(so_long) == 0)
		ft_putstr_error("Error\nInvalid map size\n");
	if (ft_check_char(so_long) == 0)
		ft_putstr_error("Error\nInvalid numbers of chars\n");
	if (ft_find_diff_chars(so_long) == 0)
		ft_putstr_error("Error\nInvalid chars presents in the map\n");
	if (ft_no_limits(so_long) == 0)
		ft_putstr_error("Error\nThe outside map limits are \
				not the corrects ones\n");
	if (ft_check_path(so_long) == 0)
		ft_putstr_error("Error\nThere is no exit available\n");
}
```
❖ The first function check the extension of the file passed trought the arguments `ft_check_extension`:
```c
int	ft_check_extension(char *file)
{
	size_t	len;

	len = 0;
	len = ft_strlen(file);
	if (!ft_strnstr(&file[len - 4], ".ber", 4))
		return (0);
	return (1);
}
```
❖ The `ft_check_size_map` i check if the size of the map is the correct one:
```c
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
```
❖ The `ft_check_char` control if there is at least:
1. one player:
2. one exit:
3. any collectable;
```c
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
```
❖ The `ft_find_diff_chars` check if there is differents chars in the map that shouldn't be there:
```c
static	int	ft_find_diff_chars(t_game *so_long)
{
	int	a;
	int	b;

	a = 0;
	while (so_long->matrix[a])
	{
		b = 0;
		while (so_long->matrix[a][b])
		{
			if (so_long->matrix[a][b] != 'P' && so_long->matrix[a][b] != 'C' \
					&& so_long->matrix[a][b] != 'E' \
					&& so_long->matrix[a][b] != '1' \
					&& so_long->matrix[a][b] != '0')
				return (0);
			b++;
		}
		a++;
	}
	return (1);
}
```
❖ The `ft_no_limits` check if there is no limits in the map (the map must be surrounded by '1');
this function is divided into 3 more, as check:
1. `ft_upper_limits`
2. `ft_sides_limits`
3. `ft_below_limits`
```c
static	int	ft_upper_limit(t_game *so_long)
{
	int	b;

	b = 0;
	while (so_long->matrix[0][b])
	{
		if (so_long->matrix[0][b] != '1')
			return (0);
		b++;
	}
	return (1);
}

static	int	ft_sides_limits(t_game *so_long)
{
	int	a;

	a = 0;
	while (so_long->matrix[a])
	{
		if (so_long->matrix[a][0] != '1')
			return (0);
		a++;
	}
	a = 0;
	while (so_long->matrix[a][so_long->map_width])
	{
		if (so_long->matrix[a][so_long->map_width] != '1')
			return (0);
		a++;
	}
	return (1);
}

static	int	ft_below_limits(t_game *so_long)
{
	int	b;

	b = 0;
	while (so_long->matrix[b])
	{
		if (so_long->matrix[so_long->map_height - 1][b] != '1')
			return (0);
		b++;
	}
	return (1);
}
```
And the beatiful one, the `ft_check_path` that is a function that is divided into 4 more that everyone control a point:
1. First function:
```c
int	ft_check_path(t_game *so_long)
{
	ft_copy_map(so_long);
	if (ft_where_is_p(so_long) == 0)
		return (0);
	return (1);
}
```
I just copy the map in a secondary doble array of chars, the second dimension is done with the function `ft_strdup`
from my ***Libft***
```c
void	ft_copy_map(t_game *so_long)
{
	int	i;

	i = 0;
	so_long->almatrix = (char **)ft_calloc(sizeof(char *) * \
			so_long->map_height, 1);
	if (!so_long->almatrix)
		exit (EXIT_FAILURE);
	while (so_long->matrix[i])
	{
		so_long->almatrix[i] = ft_strdup(so_long->matrix[i]);
		i++;
	}
	so_long->almatrix[i] = NULL;
}
```
2. Then, i have to find the Player (P) before to start the pathfinder:
```c
static	int	ft_where_is_p(t_game *so_long)
{
	int	f;
	int	c;

	f = 0;
	while (so_long->almatrix[f])
	{
		c = 0;
		while (so_long->almatrix[f][c])
		{
			if (so_long->almatrix[f][c] == 'P')
			{
				if (ft_a_valid_wayout(so_long, f, c) == 0)
					return (0);
			}
			c++;
		}
		f++;
	}
	return (1);
}
```
3. Once founded the 'P' we use a recursive fucntion, that fill all the '0' chars with 'V' (a.k.a. visited). We skip the exit and the walls:
```c
static	int	ft_a_valid_wayout(t_game *so_long, int r, int c)
{
	if (r < 0 || c < 0 || so_long->almatrix[r][c] == '1' \
			|| so_long->almatrix[r][c] == 'V')
		return (0);
	if (so_long->almatrix[r][c] == 'E')
		return (0);
	so_long->almatrix[r][c] = 'V';
	ft_a_valid_wayout(so_long, r + 1, c);
	ft_a_valid_wayout(so_long, r - 1, c);
	ft_a_valid_wayout(so_long, r, c + 1);
	ft_a_valid_wayout(so_long, r, c - 1);
	if (ft_where_is_the_exit(so_long) == 0)
		return (0);
	return (1);
}
```
4. Almost close to the end, we must check if there is an exit if some collectable left on the map, the path is no valid and we should return 0:
```c
static	int	ft_where_is_the_exit(t_game *so_long)
{
	int	r;
	int	c;

	r = 0;
	while (so_long->almatrix[r])
	{
		c = 0;
		while (so_long->almatrix[r][c])
		{
			if (so_long->almatrix[r][c] == 'C')
				return (0);
			if (so_long->almatrix[r][c] == 'E')
			{
				if (ft_check_exit_path(so_long, r, c) == 0)
					return (0);
			}
			c++;
		}
		r++;
	}
	return (1);
}
```
5. Finally, if we found an exit, we just have to check if alongside there is a 'V', that means we passed there as a Player and the path is valid. The return value is '1':
```c
static	int	ft_check_exit_path(t_game *so_long, int r, int c)
{
	if (so_long->almatrix[r + 1][c] != 'V' && so_long->almatrix[r - 1][c] \
			!= 'V' && so_long->almatrix[r][c + 1] != 'V' && \
			so_long->almatrix[r][c - 1] != 'V')
		return (0);
	return (1);
}
```
