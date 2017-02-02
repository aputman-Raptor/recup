#ifndef RT_H
# define RT_H

# define W 800
# define H 600

# include <math.h>
# include "libft/libft.h"
# include "mlx.h"
# include <stdio.h>
# include <time.h>

typedef struct		s_v
{
	double			x;
	double			y;
	double			z;
}					t_v;

typedef struct		s_ray
{
	t_v				color;
	t_v				a;
	t_v				b;
	t_v				dir;
	t_v				current;
	int				id;
	double			t;
}					t_ray;

typedef struct		s_cam
{
	t_v				pos;
	t_v				dir;
}					t_cam;

typedef struct		s_light
{
	t_v				pos;
	t_v				color;
	t_v				dir;
	double			a;
}					t_light;

typedef struct		s_object
{
	t_v				color;
	t_v				a;			/* pos */
	t_v				b;			/* dir */
	t_v				c;			/* normal */
	double			r;
	double			min;
	double			max;
	char			type;		/* object type */
}					t_object;

typedef struct		s_video
{
	char			*img;
	int				id;
	struct s_video	*next;
}					t_video;

typedef struct		s_file
{
	char			**file;
	int				size;		/* size of file in line */
	int				nbobj;		/* number of object */
	int				nbcam;		/* number of camera (avoid porblems) */
	int				nblight;	/* number of light */
	int				nbsphere;	/* number of sphere */
	int				nbcylinder;	/* number of cylinder */
	int				nbplane;	/* number of plane */
	int				nbcone;		/* number of cone */
	int				nbtriangle;	/* number of triangle */
	int				nbtorus;	/* number of torus */
	int				nbct;		/* number of torus */
	int				nbelli;		/* number of torus */
}					t_file;

typedef struct		s_option
{
	t_v				color;
	char			*cmd;
	char			oselect;	/* object selected id (-1 default) */
	char			lselect;	/* light selected id (0 default) */
	char			recordmode;	/* recording mode active or not */
	char			console;	/* console active or not */
	char			render;		/* render mode precision (cpu/gpu) */
	char			sepia;		/* sepia activated or not */
	char			fxaa;
	char			trt;
	double			speed;
}					t_option;

typedef struct		s_winfo
{
	t_file			file;
	t_video			*video;
	t_video			*tmp;
	t_option		opt;
	t_cam			cam;
	t_light			*light;
	t_object		*obj;
	t_ray			ray;
	time_t			start;
	time_t			end;
	void			*mlx;		/* mlx initialization */
	void			*win;		/* windows info */
	void			*img;		/* image info */
	char			*data;		/* map of image */
	char			*filename;	/* opened file name */
	int				bpp;		/* bits per pixel */
	int				line;		/* number of bits per line */
	int				endian;		/* endian of pixel map */
}					t_winfo;

/* winfo.c: 2*/
void				init_winfo(t_winfo *w, char *filename);
void				init_winfo_file(t_winfo *w, t_file *file);

/* press.c: 1*/
int					key_press(int key, void *param);
int					mouse_button(int key, int x, int y, void *param);

/* error.c: 1*/
void				print_error(int n);

/* parse.c: 2*/
void				parse_file(char *filename, t_file *file);
/*	STATIC:
 *	int				check_filename(char *filename);
 */

/* check.c: 3*/
void				check_file(t_file *file);
/*	STATIC
 *	int				check_content(t_file *file, char **tab);
 *	int				get_type_id(t_file *file, char **tab, int x, int y);
 */

/* memory.c: 2*/
void				free_memory(void **mem, int nb);
int					check_split(char **split, int nb);

/* help.c: 1*/
void				get_split(t_v *v, char **file, int x, int y);
char				*del_space(char *str, int i);

/* get_camera: 3*/
int					get_camera(t_winfo *w);
/*	STATIC:
 *	int				get_camera_arg(t_cam *cam, char **file, int x, int y);
 *	void			get_arg(t_cam *cam, char **file, int x, int y);
 */

/* get_light.c: 3*/
void				get_light(t_winfo *w);
/*	STATIC:
 *	int				get_light_arg(t_light *light, char **file, int x, int y);
 *	void			get_arg(t_light *light, char **file, int x, int y);
 */

/* get_object.c: 4*/
void				get_object(t_winfo *w);
/*	STATIC
 *	void			get_object_if(t_winfo *w, int x, int y, int *index);
 *	int				get_object_arg(t_object *obj, char **file, int x, int y);
 *	void			get_arg(t_object *obj, char **file, int x, int y);
 */

/* ensure.c: 2*/
void				ensure_object(t_object *obj);
void				ensure_light(t_light *light);

/* vector.c: 3*/
t_v					set_v(double x, double y, double z);
double				norm_v(t_v v);
t_v					normalize(t_v v);
t_v					get_v(t_v a, t_v b);

/* draw.c: 1*/
void				put_pixel(t_winfo *w, int x, int y, t_v color);
void				put_pixel_sepia(t_winfo *w, int x, int y, t_v color);
void				draw_console(t_winfo *w, t_v color);

/* render_cpu.c: 2*/
void				render_cpu(t_winfo *w);
void				set_vrep(t_v d, t_v v[3]);
/*	STATIC:
 *	void			render_loop(t_winfo *w, int x, int y);
 */

/* ray.c: 1*/
t_v					reflection(t_ray ray, t_winfo *w, int *nb, int depth);

/* intersection.c: 2*/
void				intersection(t_ray *ray, t_object *obj, int nbobj);

/* calculate.c:  4*/
double				check_sphere(t_ray *ray, t_object obj);
double				check_cylinder(t_ray *ray, t_object obj);
double				check_plane(t_ray *ray, t_object *obj);
double				check_cone(t_ray *ray, t_object obj);
double				check_triangle(t_ray *ray, t_object *obj);


/* math.c: 1*/
double				get_t_a(double delta, double a, double b);
double				get_t_b(t_object *obj, t_ray *ray, double delta, double *ab);
t_v					limit_v(t_v v, double min, double max);

//double			get_t_b(double delta, double a, double b);
double				dpower(double n, double t);

/* vector_s.c*/
double				dot(t_v v1, t_v v2);
t_v					cross(t_v v1, t_v v2);
t_v					add_v(t_v a, t_v b);
t_v					mult_v(t_v a, double b);
t_v					invert_v(t_v v);

/* light.c: 3*/
void				check_light(t_light *l, t_ray *ray, t_object *obj, int nbl);
void				get_normal(t_ray *ray, t_object *obj);
t_v					get_normal_other(t_ray *ray, t_object *obj, t_light l);
/*	STATIC:
 *	void			light(t_light *l, t_ray *ray, t_object *obj);
 *	void			get_normal(t_ray *ray, t_object *obj);
 */

/* shadow.c: 1*/
double				shadow(t_light *l, t_ray ray, t_object *obj, int *nb);

/* press_nc.c: 3*/
void				press_noconsole(t_winfo *w, int key);
/*	STATIC:
 *void				press_a(t_winfo *w, int key);
 *void				press_b(t_winfo *w, int key);
 */

/* press_c.c: 1*/
void				press_console(t_winfo *w, int key);

/* ft_fxaa.c: 4*/
void				ft_fxaa(void *img, int w, int h, int i);

/* ft_rgbcmp.c: 1*/
double				ft_rgbcmp(int ca, int cb);

/* ft_putpixel_img.c: 1*/
void				ft_putpixel_img(void *img, int x, int y, int c);

/* ft_getpixel.c: 1*/
int					ft_getpixel(void *img, int x, int y);

/* file.c: 2*/
void 				save_file(char *name, t_winfo *winfo);

/* execute.c: 1*/
void				exec(t_winfo *winfo, char *cmd);

char				*get_keycode(int key);

/* degree_2.c: 1*/
int					degree_2(double *pol, double *res);

/* cubic.c: 4*/
int					cubic(double *pol, double *res);

/* quartic.c: 3*/
int					quartic(double *pol, double *res);

/* new_double.c: 1*/
double				*new_double(int nbr);

/* torus.c: 4*/
double				check_torus(t_ray *ray, t_object obj);
t_v 				normal_torus(t_ray *ray, t_object *obj);
double				ft_condition(double *res, int max);

/* video.c: 3*/
t_video				*add_video(t_video *video, char *data);
char				*copy_img_to_data(char *img, char *data);
void				show_video(t_winfo *w);
char				*copy_img(char *data);

/* ellipsoid.c: 4*/
double				check_ellipsoid(t_ray *ray, t_object obj);
t_v 				normal_ellipsoid(t_ray *ray, t_object *obj);

/* ct.c: 4*/
double				check_ct(t_ray *ray, t_object obj);
t_v 				normal_ct(t_ray *ray, t_object *obj);

#endif
