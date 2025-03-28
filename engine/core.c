#define NB_EXPOSE_CORE

/* External library */
#include <ode/ode.h>
#ifdef _WIN32
#include <winsock.h>
#endif

/* Interface */
#include "nb_core.h"

/* NishBox */
#include "nb_draw.h"
#include "nb_log.h"
#include "nb_version.h"

/* Standard */
#include <stdlib.h>
#include <string.h>

void nb_engine_begin(void) {
	nb_version_t ver;
#ifdef _WIN32
	WSADATA wsa;
#endif
	nb_get_version(&ver);
	nb_function_log("NishBox engine %s", ver.full);
	nb_function_log("OpenGL backend: %s", ver.opengl);
#ifdef _WIN32
	WSAStartup(MAKEWORD(1, 1), &wsa);
	nb_function_log("Winsock ready", "");
#endif
	dInitODE();
}

void nb_engine_end(void) { dCloseODE(); }

nb_engine_t* nb_engine_create(int nogui) {
	nb_engine_t* engine = malloc(sizeof(*engine));
	memset(engine, 0, sizeof(*engine));
	if(nogui) {
		nb_function_log("No GUI mode", "");
		engine->draw = NULL;
	} else {
		nb_function_log("GUI mode", "");
		engine->draw = nb_draw_create();
		if(engine->draw == NULL) {
			nb_function_log("Failed to create drawing interface", "");
			free(engine);
			return NULL;
		}
	}
	engine->world = dWorldCreate();
	dWorldSetGravity(engine->world, 0, 0, -9.81);
	return engine;
}

void nb_engine_loop(nb_engine_t* engine) {
	while(1) {
		if(engine->draw != NULL) {
			if(nb_draw_step(engine->draw) != 0) break;
		}
	}
}

void nb_engine_destroy(nb_engine_t* engine) {
	dWorldDestroy(engine->world);
	if(engine->draw != NULL) nb_draw_destroy(engine->draw);
	free(engine);
	nb_function_log("Destroyed engine", "");
}
