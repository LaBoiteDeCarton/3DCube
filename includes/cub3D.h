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
typedef struct s_img		t_img;
typedef struct s_texture	t_texture;

t_cube	g_cube;

// typedef enum e_

struct s_vect
{
	float	x;
	float	y;
};

struct s_img
{
	void		*ptr;
	int			img_width;
	int			img_height;
};

struct s_texture
{
	t_img	n_wall;
	t_img	s_wall;
	t_img	w_wall;
	t_img	e_wall;
	int		floor_color;
	int		cell_color;
};

/*
	Si bonus :
*/
// struct s_texture
// {
// 	t_list	*walls;
// 	int		floor_color;
// 	int		cell_color;
// };

struct s_map
{
	short int	**map;
	t_vect		p_pos;
	t_vect		p_dir;
	t_vect		s_dir;
	int			map_width;
	int			map_height;
	t_texture	textures;
};

struct s_cube
{
	t_map	curr_map;
	void	*mlx;
	void	*win;
	void	*img;
	int		key_state;
	t_img	menu_bg;
};

/*
	Move functions
*/
void	rotate_left();
void	rotate_right();
void	move_left();
void	move_right();
void	move_backward();
void	move_forward();

/*
	Loop hooks seters
*/
void	loopMenu();
void	loopInGame();

void	cube_exit();

void	handle_errors(char *message);

#endif