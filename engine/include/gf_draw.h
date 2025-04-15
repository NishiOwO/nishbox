/**
 * @file gf_draw.h
 * @~english
 * @brief Drawing interface
 */

#ifndef __GF_DRAW_H__
#define __GF_DRAW_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/draw.h>

/* Engine */
#include <gf_type/core.h>

/* Standard */

/**
 * @~english
 * @brief Create drawing interface
 * @param engine Engine instance
 * @param title Window title
 */
GF_EXPORT gf_draw_t* gf_draw_create(gf_engine_t* engine, const char* title);

/**
 * @~english
 * @brief Destroy drawing interface
 * @param draw Drawing interface
 */
GF_EXPORT void gf_draw_destroy(gf_draw_t* draw);

/**
 * @~english
 * @brief Draw frame (common part)
 * @param draw Drawing interface
 * @warning Do not call this - call gf_draw_step instead
 */
GF_EXPORT void gf_draw_frame(gf_draw_t* draw);

/**
 * @~english
 * @brief Do drawing single step
 * @param draw Drawing interface
 */
GF_EXPORT int gf_draw_step(gf_draw_t* draw);

/**
 * @~english
 * @brief Initialize drawing stuffs
 * @warning Do not call this - gf_engine_begin calls this
 */
GF_EXPORT void gf_draw_begin(void);

/**
 * @~english
 * @brief Cleanup drawing stuffs
 * @warning Do not call this - gf_engine_end calls this
 */
GF_EXPORT void gf_draw_end(void);

/**
 * @~english
 * @brief Set user-drawing callback
 * @warning Do not call this - gf_engine_set_draw calls this
 */
GF_EXPORT void gf_draw_set_draw(gf_draw_t* engine, void (*func)(gf_draw_t*));

/**
 * @~english
 * @brief Do stuffs required on resizing window
 * @note Internal function, you don't need to call this
 */
GF_EXPORT void gf_draw_reshape(gf_draw_t* draw);

#endif
