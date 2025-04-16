/**
 * @file gf_type/draw_driver.h
 * @~english
 * @brief Type definitions related to drawing driver
 */

#ifndef __GF_TYPE_DRAW_DRIVER_H__
#define __GF_TYPE_DRAW_DRIVER_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_DRAW_DRIVER
/* External library */
#if defined(DRV_OPENGL)
#include <gf_opengl.h>
#endif

/* Engine */

/* Standard */

#if defined(DRV_OPENGL)
GF_DECLARE_TYPE(draw_driver, { int unused; });
GF_DECLARE_TYPE(draw_driver_texture, {
	GLuint id;
	int    width;
	int    height;
});
#else
/**
 * @struct gf_draw_driver_t
 * @~english
 * @brief Drawing driver
 * @note Definition depends on the drawing driver, read the header file for definition
 */
GF_DECLARE_TYPE(draw_driver, {});

/**
 * @struct gf_draw_driver_texture_t
 * @~english
 * @brief Driver-dependent texture
 * @note Definition depends on the drawing driver, read the header file for definition
 */
GF_DECLARE_TYPE(draw_driver_texture, {});
#endif
#else
typedef void gf_draw_driver_t;
typedef void gf_draw_driver_texture_t;
#endif

#endif
