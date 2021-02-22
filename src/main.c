#include "../include/cub3d.h"

int	close_win(void *param)
{
	t_config	*c;

	c = (t_config *)param;
	free_all(c);
	exit(0);
}

int	main_loop(t_config *config)
{
	move_camera(config);
	fill_floor_ceiling(config);
	raycast(config);
	mlx_put_image_to_window(config->mlx, config->win.win, config->img.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_config	config;

	config.mlx = mlx_init();
	init_config(&config);
	g_camera_count = 0;
	if (!parse_file(&config, argv[1]))
		error_etc("ERROR\nFalid to load file");
	if (!check_and_find(&config))
		error_etc("ERROR\nInvalidMap");
	init_window(&config);
	parse_texture(&config);
	mlx_hook(config.win.win, X_EVENT_KEY_PRESS, 0, key_press, &config);
    mlx_hook(config.win.win, X_EVENT_KEY_RELEASE,0, key_release, &config);
	mlx_hook(config.win.win, X_EVENT_KEY_EXIT, 0, close_win, &config);
	mlx_loop_hook(config.mlx, main_loop, &config);
	mlx_loop(config.mlx);
	return (0);
}