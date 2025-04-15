/**
 * @file gf_type/mesh.h
 * @~english
 * @brief Type definitions related to mesh
 */

#ifndef __GF_TYPE_MESH_H__
#define __GF_TYPE_MESH_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_MESH
/* External library */

/* Engine */
#include <gf_type/math.h>

/* Standard */

/**
 * @struct gf_triangle_t
 * @~english
 * @brief Triangle
 *
 * @var gf_triangle_t::points
 * @brief Triangle points
 *
 * @var gf_triangle_t::color
 * @brief Triangle color
 */
GF_DECLARE_TYPE(triangle, {
	gf_vector_t points[3];
	gf_vector_t color;
});

/**
 * @struct gf_mesh_t
 * @~english
 * @brief Mesh
 *
 * @var gf_mesh_t::triangles
 * @brief Triangles
 *
 * @var gf_mesh_t::triangle_count
 * @brief Triangle count
 */
GF_DECLARE_TYPE(mesh, {
	gf_triangle_t* triangles;
	int	       triangle_count;
});
#else
typedef void gf_mesh_t;
typedef void gf_triangle_t;
#endif

#endif
