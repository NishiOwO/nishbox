#define GF_EXPOSE_DRAW
#define GF_EXPOSE_TEXTURE

#include <gf_pre.h>

/* External library */
#include <gf_opengl.h>

/* Interface */
#include <gf_graphic.h>

/* Engine */
#include <gf_draw.h>
#include <gf_texture.h>
#include <gf_draw_driver.h>
#include <gf_math.h>

/* Standard */
#include <stdarg.h>
#include <stdio.h>

void gf_graphic_begin_2d(gf_draw_t* draw) {
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, draw->width, draw->height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void gf_graphic_end_2d(gf_draw_t* draw) {
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void gf_graphic_clear(gf_draw_t* draw) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }

void gf_graphic_draw_texture_polygon(gf_draw_t* draw, gf_texture_t* texture, gf_graphic_color_t color, int dim, int npair, ...) {
	double	tw = (double)texture->width / texture->internal_width;
	double	th = (double)texture->height / texture->internal_height;
	int	i;
	va_list va;
	va_start(va, npair);

	if(dim == 2) gf_graphic_begin_2d(draw);
	gf_draw_driver_begin_texture_2d(draw, texture);

	gf_draw_driver_set_color(draw, color);
	glBegin(GL_TRIANGLE_FAN);

	for(i = 0; i < npair; i++) {
		float tx = va_arg(va, double) * tw;
		float ty = va_arg(va, double) * th;
		float x	 = va_arg(va, double);
		float y	 = va_arg(va, double);
		glTexCoord2f(tx, ty);
		if(dim == GF_GRAPHIC_2D) {
			glVertex2f(x, y);
		} else if(dim == GF_GRAPHIC_3D) {
			float z = va_arg(va, double);
			glVertex3f(x, y, z);
		}
	}

	glEnd();

	gf_draw_driver_end_texture_2d(draw);
	if(dim == 2) gf_graphic_end_2d(draw);

	va_end(va);
}

void gf_graphic_fill_polygon(gf_draw_t* draw, gf_graphic_color_t color, int dim, int npair, ...) {
	int	i;
	va_list va;
	va_start(va, npair);

	if(dim == 2) gf_graphic_begin_2d(draw);

	gf_draw_driver_set_color(draw, color);
	glBegin(GL_TRIANGLE_FAN);

	for(i = 0; i < npair; i++) {
		float x = va_arg(va, double);
		float y = va_arg(va, double);
		if(dim == GF_GRAPHIC_2D) {
			glVertex2f(x, y);
		} else if(dim == GF_GRAPHIC_3D) {
			float z = va_arg(va, double);
			glVertex3f(x, y, z);
		}
	}

	glEnd();
	if(dim == 2) gf_graphic_end_2d(draw);

	va_end(va);
}

void gf_graphic_perspective(gf_draw_t* draw, double fovy, double znear, double zfar) {
	double	 aspect = (double)draw->width / (double)draw->height;
	double	 f	= gf_math_cot(fovy / 180 * GF_MATH_PI / 2);
	GLdouble matrix[16];
	int	 i;

	for(i = 0; i < 16; i++) matrix[i] = 0;
	matrix[4 * 0 + 0] = f / aspect;
	matrix[4 * 1 + 1] = f;
	matrix[4 * 2 + 2] = (zfar + znear) / (znear - zfar);
	matrix[4 * 3 + 2] = ((double)2 * zfar * znear) / (znear - zfar);
	matrix[4 * 2 + 3] = -1;

	glLoadIdentity();
	glLoadMatrixd(matrix);
}

GF_EXPORT void gf_graphic_set_camera(gf_draw_t* draw) {
	GLdouble	 matrix[16];
	gf_math_vector_t f;
	gf_math_vector_t up;
	gf_math_vector_t s;
	gf_math_vector_t u;
	int		 i;

	f[0] = draw->lookat[0] - draw->camera[0];
	f[1] = draw->lookat[1] - draw->camera[1];
	f[2] = draw->lookat[2] - draw->camera[2];
	gf_math_normalize(f);

	up[0] = 0;
	up[1] = 1;
	up[2] = 0;
	gf_math_normalize(up);

	gf_math_multiply(s, f, up);
	gf_math_normalize(s);

	gf_math_multiply(u, s, f);

	for(i = 0; i < 16; i++) matrix[i] = 0;
	matrix[4 * 0 + 0] = s[0];
	matrix[4 * 1 + 0] = s[1];
	matrix[4 * 2 + 0] = s[2];
	matrix[4 * 0 + 1] = u[0];
	matrix[4 * 1 + 1] = u[1];
	matrix[4 * 2 + 1] = u[2];
	matrix[4 * 0 + 2] = -f[0];
	matrix[4 * 1 + 2] = -f[1];
	matrix[4 * 2 + 2] = -f[2];
	matrix[4 * 3 + 3] = 1;

	glLoadIdentity();
	glLoadMatrixd(matrix);
	glTranslated(-draw->camera[0], -draw->camera[1], -draw->camera[2]);
}
