# So_long 42
#### A 2D game using "MiniLibX", a graphical interface library (Copyright ol@ - 2002-2019 - Olivier Crouzet).
###### The game consists in collecting collectibles and finding the exit to win.


<h1 align="center">

![gif](https://github.com/Gogiu23/The-official-so_long42/blob/master/images_markdown/so_long.gif)

</h1>

## TOC

1. [_The init_](#The-init)
2. [_The map_](#▶︎The-map)

## The init
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

## ▶︎The map

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
### ▶︎ LIBMLX
The libmlx, or libmlx.a, is a graphics library provided by the company Silicon Graphics (SGI). It is often used in conjunction with the X Window System on Unix-like operating systems to provide graphics capabilities to applications.

In particular, the libmlx library provides functions for creating and manipulating windows, handling input events such as mouse clicks and key presses, and rendering graphics using OpenGL or other graphics APIs. It is commonly used in the development of graphical applications such as games, scientific visualization tools, and graphical user interfaces.

The libmlx library is often used in combination with the Simple DirectMedia Layer (SDL) library to create cross-platform graphical applications. It is also used in the development of the popular computer game Minecraft.
The version we use is called minilibX, developed by 42-Paris, suitable for students.

> **WINDOW FUNCTIONS**

#### mlx_init

> Initialize the MLX library. Must be called before ANY other function. Return NULL if initialization failed.

```c
	void	*mlx_init();
```
- __generate the mlx instance__

#### mlx_new_window

> Creates new window instance. It will return a window instance pointer. 
```c
	void	*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
```
- __*mlx_ptr__ = the mlx instance pointer
- __size_x__ = the width of the window
- __size_y__ = the height of the window
- __*title__ = title of the window
- __return void*__ = the window instance pointer.

#### mlx_clear_window

> Clear the current window. This is not a recommend function to use. Instead it is recomment to use the function "mlx_put_image_to_window" with a recycled imaged that you have cleared
```c
	int	mlx_clear_window(void *mlx_ptr, void *mlx_ptr);
```
- __*mlx_ptr__ = the mlx instance pointer
- __*win_ptr__ = the window instance pointer
- __return int__ = no return value

#### mlx_destroy_window

> Destroy a window instance accordingly.
```c
	int	mlx_destroy_window(void *mlx_ptr, void *win_ptr);
```
- __*mlx_ptr__ = the mlx instance
- __*win_ptr__ = the window instance
- __no return value__

*********************************************************************************************

> **COLORS, PIXELS AND STRING TO THE SCREEN**

#### mlx_get_color_value
> Get the code for the color you want to show
```c
	uint	mlx_get_color_value(void *mlx_ptr, int color);
```
- __*mlx_ptr__ = the mlx instance
- __color__ = the int color (0xTTRRGGBB)
- __return value__ = the converted color

#### mlx_pixel_put
> Puts a pixel on the screen. it is suggested to use the function "mlx_put_image_to_window" instead.
```c
	int	mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
```
- __*mlx_ptr__ = the mlx instance
- __*win_ptr__ = the window instance pointer
- __int x__ = the coordinate x of the pixel to draw
- __int y__ = the coordinate y of the pixel to draw
- __int color__ = the color of the pixel to draw (0XTTRRGGBB)
- __return__ = no return value

#### mlx_string_put
> Puts a string on the location (x,y) in the given window
```c
	int	mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string);
```
- __*mlx_ptr__ = the mlx instance
- __int x__ = the x cordinate
- __int y__ = the y cordinate
- __int color__ = the font color
- __char *string__ = the text to write
- __return__ = no return value

*********************************************************************************************

> **IMAGES FUNCTIONS**

#### mlx_new_image
> Creates a new MLX comptatible image. The recommend way to buffer the image you are rendering. Will return a reference pointer to the image.
```c
	void	*mlx_new_image(void *mlx_ptr, int width, int height);
```
- __*mlx_ptr__ = the mlx instance
- __int width__ = the width of the image you want to put to the screen 
- __int height__ = the height of the image you want to put to the screen
- __return__ = the image instance reference

#### mlx_get_data_addr
> Gets the memory address of the given image. Memory of images is weird. It will set the line size in your 
> given pointer. To get or set the value of the pixel (5, 100) in an image size of (500, 500), we would need to locate the position as follows:
```c
	int pos = (y * size_line + x * (bits_per_pixel / 8));
```

> Here we multiply size_line by y as we need to skip y lines (and yes, line size is not equal to the amount of pixels in a line). We then add the remaining x units multiplied by bits_per_pixel / 8 to align with the final location.

>To modify each pixel with the correct color, we need to do some more fancy stuff. As we need to align the bits before writing, we need to do the following for the best result:
```c
	char	*mlx_data_addr = mlx_get_data_addr();
	*(unsigned int *)mlx_data_addr = color;
```

> The function prototype is as follows:
```c
	char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int size_line, int *endian);
```
- __*img_ptr__ = the image instance
- __*bits_per_pixel__ = a pointer to where the bpp is written
- __*size_line__ = a pointer to where the line is written
- __*endian__ = a pointer to where the endian is written
- __return__ = the memory address tof the image

#### mlx_put_image_to_window
> Puts an image to the given window instance at location (x,y). This is the recommended way to write large amounts of graphical data in one go. Do mind that when changing the memory of the locations, it will be displayed directly on the window.
```c
	int	mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
```
- __*mlx_ptr__ = the mlx instance
- __*win_ptr__ = the window instance
- __int x__ = the x location of where the image ought to be placed
- __int y__ = the y location of where the image ought to be placed
- __return__ = no return value

#### mlx_destroy_image
> Destroy an image instance accordingly.
```c
	int	mlx_destroy_image(void *mlx_ptr, void *img_ptr);
```
- __*mlx_ptr__ = the mlx instance
- __*img_ptr__ = the image instance
- __return__ = no return value

*********************************************************************************************

> **HOOKS**
> These functions will allow you to hook the MiniLibx functions. This is core funcionality and is required to use the library effectively.

#### mlx_mouse_hook
> Hook into mouse events. This will trigger every time you click somewhere in the given screen.
```c
	int	mlx_mouse_hook(void *win_ptr, int (*f)(), void *param);
```
- __*win_ptr__ = the windows instance
- __int (*f)()__ = the handler function, will be called as follows:
 	(*f)(int button, int x, int y, void *param);
- __void *param__ = the parameters to give on each event
- __return__ = no return value

#### mlx_key_hook
> Hook key into events. This will trigger every time a key is pressed in a focused window. Unfocused 
window will not register any events.
```c
	int	mlx_key_hook(void *win_ptr, int (*f)(), void *param);
```
- __*win_ptr__ = the window instance
- __int (*f)()__ = the handler function that will be called like that:
		(*f)(int key_code, void *param);
- __void *param__ = the parameter to give on each event
- __return__ = no return value

#### mlx_loop_hook
> Hook into the loop
```c
	int	mlx_loop_hook(void *mlx_ptr, int (*f)(), void *param)
```
- __*mlx_ptr__ = the mlx instance
- __int (*f)()__ = the handler function, will be called as follows
		(*f)(void *param);
- __void *param__ = the parameter to give on each event
- __return__ = no return value

#### mlx_loop
> Loop over the given MLX pointer. Each hook that was registeres prior to this will be called accordingly by
order of a registration.
```c
	int	mlx_loop(void *mlx_ptr);
```
- __*mlx_ptr__ = the mlx instance
- __return__ = no return value

*********************************************************************************************

> **IMAGE CONVERSIONS**
> These are functions that are useful for loading sprites or even saving images

#### mlx_xpm_to_image
> Converts xpm data to a new image instance
```c
	void	*mlx_xpm_to_image(void *mlx_ptr, char **xpm_data, int *width, int *height);
```
- __*mlx_ptr__ = the mlx instance
- __char **xpm_data__ = the xpm data in a 2 dimensional char array
- __int *width__ = a pointer to where the width ought to be written
- __int *height__ = a pointer to where the height ought to be written
- __return__ = the image instance, NULL in case of error

#### mlx_xpm_file_to_image
> Converts an xpm file to a new image instance.
```c
	void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height);
```
- __*mlx_ptr__ = the mlx instance
- __char *filename__ = the file to load;
- __int *width__ = a pointer to where the width ought to be written
- __int *height__ = a pointer to where the height ought to be written
- __return__ = the image instance, NULL in case of error

*********************************************************************************************

> **MOUSE FUNCTIONS**
> These functions will allow you to hide, show, move or get the mouse poisition.

#### mlx_mouse_hide
> Hide the mouse
```c
	int	mlx_mouse_hide();
```

#### mlx_mouse_show
> Shows the mouse
```c
	int	mlx_mouse_show();
```

#### mlx_mouse_move
> Move the cursor to the given location
```c
	int	mlx_mouse_move(void *win_ptr, int x, int y);
```
- __*win_ptr__ = the window instance
- __int x__ =  the x location to move to
- __int y__ = the y location to move to
- __return__ = has no return value

#### mlx_mouse_get_pos
> Get the current mouse position on the window
```c
	int	mlx_mouse_get_pos(void *win_ptr, int *x, int *y);
```
- __*win_ptr__ = the window instance
- __int *x__ = the pointer to write the x location to move to
- __int *y__ = the pointer to write the y location to move to
- __return__ = has no return value

*********************************************************************************************

> **KEY AUTO REPEAT and SYNX SCREEN etc**

#### mlx_do_key_autorepeatoff
> Disable key auto repeat.
```c
	int	mlx_do_key_autorepeatoff(void *mlx_ptr)
```

#### mlx_do_key_autorepeaton
> Enable key auto repeat
```c
	int	mlx_do_key_autorepeaton(void *mlx_ptr);
```

#### mlx_do_sync
```c
	int	mlx_do_sync(void *mlx_ptr);
```

#### mlx_get_screen_size
```c
	int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);
```
- __*mlx_ptr__ = the mlx instance
- __*sizex__ = the screen width
- __*sizey__ = the screen height
- __return__ = no return value
