/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 12:00:09 by mkamei            #+#    #+#             */
/*   Updated: 2023/03/07 13:13:14 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	write_bmp_header(t_img img, int fd, int *real_width)
{
	unsigned long	info[6];
	unsigned char	header[BMP_HEADER_SIZE];

	*real_width = img.width * 3 + img.width % 4;
	info[FILE_SIZE] = img.height * *real_width + BMP_HEADER_SIZE;
	info[OFFSET_TO_DATA] = BMP_HEADER_SIZE;
	info[INFO_HEADER_SIZE] = BMP_INFO_HEADER_SIZE;
	info[PLANES] = 1;
	info[COLOR] = 24;
	info[DATA_SIZE] = img.height * *real_width;
	ft_bzero(header, BMP_HEADER_SIZE);
	header[0] = 'B';
	header[1] = 'M';
	ft_memcpy(header + 2, &info[FILE_SIZE], sizeof(unsigned long));
	ft_memcpy(header + 10, &info[OFFSET_TO_DATA], sizeof(unsigned long));
	ft_memcpy(header + 14, &info[INFO_HEADER_SIZE], sizeof(unsigned long));
	ft_memcpy(header + 18, &img.width, sizeof(long));
	ft_memcpy(header + 22, &img.height, sizeof(long));
	ft_memcpy(header + 26, &info[PLANES], sizeof(unsigned int));
	ft_memcpy(header + 28, &info[COLOR], sizeof(unsigned int));
	ft_memcpy(header + 34, &info[DATA_SIZE], sizeof(unsigned long));
	write(fd, header, BMP_HEADER_SIZE);
}

static int	write_bmp_data(t_img img, int fd, int real_width)
{
	int				x;
	int				y;
	unsigned char	*buf;
	unsigned int	color;

	if ((!(buf = (unsigned char *)calloc(real_width, sizeof(unsigned char)))))
		return (MALLOC_ERROR);
	y = img.height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < img.width)
		{
			color = *(unsigned int *)(img.addr + y * img.line_length +
												x * (img.bits_per_pixel / 8));
			buf[3 * x + 2] = color / (256 * 256);
			buf[3 * x + 1] = color / 256 - buf[3 * x + 2] * 256;
			buf[3 * x] = color - buf[3 * x + 2] * 65536 - buf[3 * x + 1] * 256;
			x++;
		}
		write(fd, buf, real_width);
		y--;
	}
	free(buf);
	return (SUCCESS);
}

void		save_bmp(t_data *d, t_img img)
{
	int fd;
	int real_width;
	int ret;

	fd = open("capture.bmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(2, "Error\n", 7);
		perror("capture.bmp");
		finish_program(d, FILE_OPEN_ERROR);
	}
	img.width = d->win.width;
	img.height = d->win.height;
	write_bmp_header(img, fd, &real_width);
	ret = write_bmp_data(img, fd, real_width);
	close(fd);
	if (ret == MALLOC_ERROR)
		finish_program(d, MALLOC_ERROR);
	else
		finish_program(d, SUCCESS);
}
