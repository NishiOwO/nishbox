#define GF_EXPOSE_FONT

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_font.h>

/* Engine */
#include <gf_log.h>
#include <gf_texture.h>

/* Standard */
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

gf_font_glyph_t* gf_font_get(gf_font_t* font, int code) {
	int i;
	if(code < 0x20) return NULL;
	for(i = 0; i < font->count; i++) {
		if(font->glyph[i] != NULL && font->glyph[i]->code == code) {
			return font->glyph[i];
		}
	}
	return NULL;
}

#ifdef _MSC_VER
#define gf_stat _stat
#else
#define gf_stat stat
#endif

GF_DECLARE_TYPE(font_store, { int glyph_index; });

/**
 * This is a private method to parse BDF line
 */
void gf_font_parse_line(const char* path, gf_font_store_t* store, gf_font_t* font, char* line) {
	int   i;
	char* args[32];
	int   argc = 0;
	int   incr = 0;
	int   dq   = 0;
	for(i = 0;; i++) {
		if((dq == 0 && line[i] == ' ') || line[i] == 0) {
			char oldc = line[i];
			line[i]	  = 0;

			args[argc] = line + incr;
			if(args[argc][0] == '"') args[argc]++;
			if(args[argc][strlen(args[argc]) - 1] == '"') args[argc][strlen(args[argc]) - 1] = 0;

			argc++;

			incr = i + 1;

			if(oldc == 0) break;
		} else if(line[i] == '"') {
			dq = 1 - dq;
		}
	}
	if(argc > 0 && strcmp(args[0], "STARTCHAR") == 0) {
		font->glyph[store->glyph_index] = malloc(sizeof(**font->glyph));
		memset(font->glyph[store->glyph_index], 0, sizeof(**font->glyph));
	} else if(argc > 0 && strcmp(args[0], "ENDCHAR") == 0) {
		store->glyph_index++;
	} else if(argc == 2) {
		if(strcmp(args[0], "COPYRIGHT") == 0) {
			gf_log_function(NULL, "%s: %s", path, args[1]);
		} else if(strcmp(args[0], "NOTICE") == 0) {
			gf_log_function(NULL, "%s: %s", path, args[1]);
		} else if(strcmp(args[0], "FOUNDRY") == 0) {
			gf_log_function(NULL, "%s: Made by %s", path, args[1]);
		} else if(strcmp(args[0], "CHARS") == 0) {
			int j;
			gf_log_function(NULL, "%s: %s characters", path, args[1]);
			font->count = atoi(args[1]);
			font->glyph = malloc(font->count * sizeof(*font->glyph));
			for(j = 0; j < font->count; j++) font->glyph[j] = NULL;
			store->glyph_index = 0;
		} else if(strcmp(args[0], "ENCODING") == 0) {
			font->glyph[store->glyph_index]->code = atoi(args[1]);
		}
	} else if(argc == 3) {
		if(strcmp(args[0], "DWIDTH") == 0) {
			font->glyph[store->glyph_index]->dwidth[0] = atoi(args[1]);
			font->glyph[store->glyph_index]->dwidth[1] = atoi(args[2]);
		}
	} else if(argc == 5) {
		if(strcmp(args[0], "FONTBOUNDINGBOX") == 0) {
			font->bbox.width  = atoi(args[1]);
			font->bbox.height = atoi(args[2]);
			font->bbox.x	  = atoi(args[3]);
			font->bbox.y	  = atoi(args[4]);
		} else if(strcmp(args[0], "BBX") == 0) {
			font->glyph[store->glyph_index]->bbox.width  = atoi(args[1]);
			font->glyph[store->glyph_index]->bbox.height = atoi(args[2]);
			font->glyph[store->glyph_index]->bbox.x	     = atoi(args[3]);
			font->glyph[store->glyph_index]->bbox.y	     = atoi(args[4]);
		}
	}
}

gf_font_t* gf_font_create(const char* path) {
	gf_font_t*	font = malloc(sizeof(*font));
	struct gf_stat	s;
	char*		buf;
	FILE*		f;
	int		i    = 0;
	int		incr = 0;
	gf_font_store_t store;
	memset(font, 0, sizeof(*font));
	if(gf_stat(path, &s) != 0) {
		free(font);
		return NULL;
	}
	gf_log_function(NULL, "%s: %lu bytes", path, (unsigned long)s.st_size);
	buf	       = malloc(s.st_size + 0);
	buf[s.st_size] = 0;
	f	       = fopen(path, "r");
	fread(buf, s.st_size, 1, f);
	fclose(f);

	for(i = 0;; i++) {
		if(buf[i] == 0 || buf[i] == '\n') {
			char  oldc = buf[i];
			char* line = buf + incr;
			buf[i]	   = 0;
			incr	   = i + 1;

			gf_font_parse_line(path, &store, font, line);

			if(oldc == 0) break;
		}
	}

	free(buf);
	return font;
}
