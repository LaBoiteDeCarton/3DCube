#ifndef CUBE3D_H
# define CUBE3D_H
/* Arrow Key */
# define K_A_LEFT 123
# define K_A_RIGHT 124 
# define B_A_LEFT 4
# define B_A_RIGHT 5 

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

/* Bit Set/Unset/Get Macro */
# define bit_is_set(byte,pos) ((byte) & (1 << pos))
# define bit_set(byte, pos)	((byte) |= (1 << pos))
# define bit_unset(byte, pos) ((byte) &= (1 << pos))

typedef struct s_vect	t_vect;
typedef struct s_map	t_map;
typedef struct s_cube	t_cube;

t_cube	g_cube;

struct s_vect
{
	float	x;
	float	y;
};

struct s_map
{
	t_vect	p_pos;
	t_vect	p_dir;
	t_vect	s_dir;
	int		**map;
};

struct s_cube
{
	void	(*display)(void); //here we scitch what we display depending of if we are in the menu or in game
	int		resX;
	int		resY;
	t_map	curr_map;
	void	*mlx;
	void	*win;
	void	*img;
	int		key_state;
};

#endif