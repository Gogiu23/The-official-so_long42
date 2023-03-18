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

### ▶︎ Check errors
First of all we have to check the errors and manage the parsing code coming form the console. 
```c
if (argc != 2)
	ft_putstr_error("Error\nUsage: ./so_long [*.ber]\n");
```
