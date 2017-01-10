/*!
 * \brief
 *
 * \author ddubois 
 * \date 27-Sep-16.
 */

#ifndef RENDERER_GEOMETRY_CACHE_H
#define RENDERER_GEOMETRY_CACHE_H

#include <vector>
#include <mutex>
#include <functional>
#include <unordered_map>
#include "render_object.h"
#include "../../data_loading/geometry_cache/builders/mesh_builder.h"
#include "shaders/geometry_filter.h"

namespace nova {
    /*!
         * \brief Provides access to the meshes that Nova will want to deal with
         *
         * The primary way it does this is by allowing the user to specify
         */
    class mesh_accessor {
    public:
        /*!
         * \brief Initializes this mesh_accessor, telling it to get new meshes from the given mesh_builder
         *
         * \param builder_ref The mesh_builder to get new meshes from
         */
        mesh_accessor(mesh_builder &builder_ref);

        /*!
         * \brief Checks the mesh_builder for new mesh definitions. If we have any, creates an OpenGL mesh for them
         */
        void update();

        std::vector<render_object *> get_meshes_for_filter(geometry_filter& filter);
    private:
        std::vector<render_object> renderable_objects;
        std::unordered_map<std::string, std::vector<render_object>> renderables_grouped_by_shader;

        mesh_builder &builder;

        void update_gui_mesh();
    };
};

#endif //RENDERER_GEOMETRY_CACHE_H