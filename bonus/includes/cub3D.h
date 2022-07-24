#ifndef CUBE3D_H
# define CUBE3D_H

/* Arrow Key */
# define K_A_LEFT 123
# define K_A_RIGHT 124 
# define K_A_DOWN 125
# define K_A_UP 126 
# define B_A_LEFT 4
# define B_A_RIGHT 5 
# define B_A_DOWN 6
# define B_A_UP 7 
# define K_ENTER 36

/* Movement Key */
# define K_Q 0
# define K_S 1
# define K_D 2
# define K_Z 13
# define B_Q 0
# define B_S 1
# define B_D 2
# define B_Z 3

/* Other */
# define K_M 41
# define K_C 8

/* changement d'objet
# define K_1 18
# define K_2 19
# define K_3 20
# define K_4 21
*/

# define K_ESC 53
# define K_SPACE 49

/* Hard coding the resolution */
# define RES_WIDTH 960
# define RES_HEIGHT 720

/* Bit Set/Unset/Get Macro */
# define bit_is_set(byte,pos) ((byte) & (1 << pos))
# define bit_set(byte, pos)	((byte) |= (1 << pos))
# define bit_unset(byte, pos) ((byte) ^= (1 << pos))

typedef struct s_vect		t_vect;
typedef struct s_map		t_map;
typedef struct s_cube		t_cube;
typedef struct s_walls		t_walls;
typedef struct s_obj		t_obj;
typedef struct s_mlx_img	t_mlx_img;
typedef struct s_texture	t_texture;
typedef struct s_menu		t_menu;

t_cube	g_cube;

typedef enum e_btn_content
{
	menu,
	play,
	select_level,
	config,
	quit,
	retry,
	back,
	none
}	t_btn_content;

struct s_vect
{
	float	x;
	float	y;
};

struct s_mlx_img
{
	void	*img_ptr;
	void	*buffer;
	int		bpp;
	int		sl;
	int		endian;
	int		img_width;
	int		img_height;
};

struct s_walls
{
	short		id;
	t_mlx_img	txtr;
	t_walls		*next;
};

struct s_obj
{
	short		id;
	t_vect		pos;
	float		rayon;
	float		v_pos;
	int			transparency;
	t_mlx_img	txtr;
	t_obj		*next;
};


struct s_map
{
	short int	**map;
	t_vect		p_pos;
	t_vect		p_dir;
	t_vect		s_dir;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			cell_color;
	t_walls		*w_txtr;
	t_obj		*obj;
};

struct	s_menu
{
	t_mlx_img		menu_bg;
	t_mlx_img		menu_btn_on;
	t_mlx_img		menu_btn_off;
	t_btn_content	menu_curr;
	short int		select;
	short int		max_select;
};

struct s_cube
{
	t_map		curr_map;
	int			map_width;
	int			map_height;
	t_menu		menu;
	void		*mlx;
	void		*win;
	t_mlx_img	img_raycast;
	t_mlx_img	mini_map;
	int			key_state;
};

/*
	Parsing function
	- open file refered by pathfile
	- fill info from file into t_map structure contained in g_cube
	Return values :
		- 0 : if something went wrong (unknown pathfile, access permission, not vaid info..)
		- 1 : if parsing was sucessfull
*/
int		try_parse_file(char *pathfile);

/*
	Move functions
	- Change the position of the player
	Rotate functions
	- Change the direction of the player
	Rotate function with float parameter
	- Change the direction of the player with 'angle' value (usefull for mouse rotation)
	Collision Solver
	- Put the player in the right position if his hitbox overflow on a wall
*/
void	rotate_left();
void	rotate_right();
void	rotate(float angle);
void	move_left();
void	move_right();
void	move_backward();
void	move_forward();
void	collision_solver(float *add_to_x, float *add_to_y);

/*
	Loop hooks seters
		LoopMenu - setting all keyhook and loophook to display a beautiful menu
		LoopInGame - setting all keyhook, mousehook and loophook to run the game
*/
void	loopMenu();
void	loopInGame();

/*
	raycasting functions

*/
void	raycast();


/*
	Exit funciton, called when 'Esc' key is pressed OR when QUIT is selected in menu
	- Destroy all images (textures etc)
	- Destroy map data stored in an int[][]
	- Display leaks state
	- Display quit the programm with Success value
*/
void	cube_exit();

/*
	Error displayer
	- Display on error output in the folowing form :
		Cub3D: <some custom message>: <perror message>
*/
void	handle_errors(char *message);

#endif