#define GF_EXPOSE_DRAW
#define GF_EXPOSE_TEXTURE

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_graphic.h>

/* Engine */
#include <gf_draw.h>

/* Standard */
#include <string.h>

void gf_graphic_fill_rect(gf_draw_t* draw, float x, float y, float w, float h, gf_color_t color) { gf_graphic_fill_polygon(draw, color, 4, x, y, x, y + h, x + w, y + h, x + w, y); }

void gf_graphic_text(gf_draw_t* draw, float x, float y, float size, const char* text, gf_color_t color) {
	int i;
	for(i = 0; text[i] != 0; i++) {
		gf_graphic_draw_texture_2d(draw, x + i * (size * GF_GRAPHIC_FONT_ASPECT_X / GF_GRAPHIC_FONT_ASPECT_Y), y, size * GF_GRAPHIC_FONT_ASPECT_X / GF_GRAPHIC_FONT_ASPECT_Y, size, draw->font[text[i]], color);
	}
}

float gf_graphic_text_width(gf_draw_t* draw, float size, const char* text) { return (float)strlen(text) * (size * GF_GRAPHIC_FONT_ASPECT_X / GF_GRAPHIC_FONT_ASPECT_Y); }
