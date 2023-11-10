/*
Copyright (c) 2004-2021, Lode Vandevenne

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "include/raycast.h"


/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
g++ *.cpp -lSDL
*/

//place the example code below here:

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 728
#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int	worldMap[MAP_WIDTH][MAP_HEIGHT]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_speed
{
	double move;
	double rotat;
}

typedef struct s_info
{
	t_pos	sd;
	t_pos	pos;
	t_pos	dir;
	t_pos	plane;
	t_pos	ray_dir;
	t_pos	delta_dist;
	t_posi	map;
	t_posi	step;
	double	time;
	double	oldTime;
	int		draw_end;
	int		draw_start;
	t_speed	speed;
}	t_info;

t_info	ft_init_info()
{
	t_info	info;

	ft_bzero(&info, sizeof(info));
	info.pos.x = 22;
	info.pos.y = 12;  //x and y start position
	info.dir.x = -1;
	info.dir.y = 0; //initial direction vector
	info.plane.x = 0;
	info.plane.y = 0.66; //the 2d raycaster version of camera plane
	info.time = 0; //time of current frame
	info.oldTime = 0; //time of previous frame
	return (info);
}

void	ft_step_direction(t_info *info)
{
	if (info->ray_dir.x < 0)
	{
		info->step.x = -1;
		info->sd.x = (info->pos.x - map.x) * delta_dist.x;
	}
	else
	{
		info->step.x = 1;
		info->sd.x = (map.x + 1.0 - info->pos.x) * delta_dist.x;
	}
	if (info->ray_dir.y < 0)
	{
		info->step.y = -1;
		info->sd.y = (info->pos.y - map.y) * delta_dist.y;
	}
	else
	{
		info->step.y = 1;
		info->sd.y = (map.y + 1.0 - info->pos.y) * delta_dist.y;
	}
}

void	ft_dda(t_info *info)
{
	//perform DDA
	while (hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (sd.x < sd.y)
		{
			sd.x += delta_dist.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			sd.y += delta_dist.y;
			map.y += step.y;
			side = 1;
		}
		//Check if ray has hit a wall
		if (worldMap[map.x][map.y] > 0)
			hit = 1;
	}
}

void	ft_set_colors()
{
	//choose wall color
	ColorRGB color;

	switch(worldMap[map.x][map.y])
	{
		case 1:  color = RGB_Red;//red
		case 2:  color = RGB_Green;//green
		case 3:  color = RGB_Blue;//blue
		case 4:  color = RGB_White; //white
		default: color = RGB_Yellow; //yellow
	}
}

void	ft_draw_limits(t_info *info)
{
	//calculate lowest and highest pixel to fill in current stripe
	info->draw_start = -(info->lineHeight) / 2 + SCREEN_HEIGHT / 2;
	info->draw_end = info->lineHeight / 2 + SCREEN_HEIGHT / 2;
	if (info->draw_start < 0)
		info->draw_start = 0;
	if (info->draw_end >= SCREEN_HEIGHT)
		info->draw_end = SCREEN_HEIGHT - 1;
}

int main(int ac, char **av)
{
	t_info	info;

	info = ft_init_info();

	/*screen(SCREEN_WIDTH, SCREEN_HEIGHT, 0, "Raycaster");*/
	while (!done())
	{
		int	x;

		x = 0;
		while (x < SCREEN_WIDTH)
		{
			int		hit;
			int		side; //was a NS or a EW wall hit?
			double	cameraX;
			double	perpWallDist;

			cameraX	= 2 * x / (double)w - 1; //x-coordinate in camera space
			ray_dir.x = dir.x + plane.x * cameraX;
			ray_dir.y = dir.y + plane.y * cameraX;
			map.x = int(info->pos.x);
			map.y = int(info->pos.y);


			delta_dist.x = fabs(1 / ray_dir.x);
			delta_dist.y = fabs(1 / ray_dir.y);


			hit = 0; //was there a wall hit?
			ft_step_direction();
			ft_dda();
			
			//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
			//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
			//This can be computed as (map.x - info->pos.x + (1 - step.x) / 2) / ray_dir.x for side == 0, or same formula with Y
			//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
			//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
			//steps, but we subtract deltaDist once because one step more into the wall was taken above.
			if (side == 0)
				perpWallDist = (info->sd.x - delta_dist.x);
			else
				perpWallDist = (info->sd.y - delta_dist.y);

			//Calculate height of line to draw on screen
			int lineHeight = (int)(h / perpWallDist);
			ft_draw_limits();
			
			ft_set_colors();

			//give x and y sides different brightness
			if (side == 1)
				color = color / 2;

			//draw the pixels of the stripe as a vertical line
			verLine(x, draw_start, draw_end, color);
		}
		//timing for input and FPS counter
		oldTime = time;
		time = getTicks();
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / frameTime);
		/*redraw();*/
		/*cls();*/

		//speed modifiers
		ft_set_speed();

		readKeys();
		//move forward if no wall in front of you
		ft_hero_move();
		ft_camera_move();
	}
}

void	ft_set_speed(t_info *info)
{
	info->speed.move = frameTime * 5.0; //the constant value is in squares/second
	info->speed.rota = frameTime * 3.0; //the constant value is in radians/second
}

void	ft_hero_move()
{
	int moved_x;
	int	moved_y;

	if (keyDown(SDLK_UP))
	{
		moved_x = info->pos.x + dir.x * moveSpeed;
		moved_y = info->pos.y + dir.y * moveSpeed;
		if (worldMap[(int)moved_x][(int)info->pos.y] == false)
			info->pos.x += dir.x * moveSpeed;
		if (worldMap[(int)info->pos.x][(int)moved_y] == false)
			info->pos.y += dir.y * moveSpeed;
	}
	if (keyDown(SDLK_DOWN))
	{
		moved_x = info->pos.x - dir.x * moveSpeed;
		moved_y = info->pos.y - dir.y * moveSpeed;
		if (worldMap[(int)moved_x][(int)info->pos.y] == false)
			info->pos.x -= dir.x * moveSpeed;
		if (worldMap[(int)info->pos.x][(int)moved_y] == false)
			info->pos.y -= dir.y * moveSpeed;
	}
}

void	ft_camera_move()
{
	double oldPlaneX;
	double oldDirX;

	if (keyDown(SDLK_RIGHT))
	{
		oldDirX = dir.x;
		dir.x = dir.x * cos(-rotSpeed) - dir.y * sin(-rotSpeed);
		dir.y = oldDirX * sin(-rotSpeed) + dir.y * cos(-rotSpeed);
		oldPlaneX = plane.x;
		plane.x = plane.x * cos(-rotSpeed) - plane.y * sin(-rotSpeed);
		plane.y = oldPlaneX * sin(-rotSpeed) + plane.y * cos(-rotSpeed);
	}
	if (keyDown(SDLK_LEFT))
	{
		oldDirX = dir.x;
		dir.x = dir.x * cos(rotSpeed) - dir.y * sin(rotSpeed);
		dir.y = oldDirX * sin(rotSpeed) + dir.y * cos(rotSpeed);
		oldPlaneX = plane.x;
		plane.x = plane.x * cos(rotSpeed) - plane.y * sin(rotSpeed);
		plane.y = oldPlaneX * sin(rotSpeed) + plane.y * cos(rotSpeed);
	}
}
