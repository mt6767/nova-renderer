/*!
 * \author ddubois 
 * \date 30-Aug-18.
 */

#include "general_test_setup.hpp"
#undef TEST

#include <iostream>

#ifdef __linux__
#include <signal.h>
void sigsegv_handler(int signal);
void sigabrt_handler(int signal);
#include "../../src/util/linux_utils.hpp"
#endif

namespace nova {
    int main() {
        TEST_SETUP_LOGGER();

        char buff[FILENAME_MAX];
        getcwd(buff, FILENAME_MAX);
        NOVA_LOG(DEBUG) << "Running in " << buff << std::flush;
        NOVA_LOG(DEBUG) << "Predefined resources at: " << CMAKE_DEFINED_RESOURCES_PREFIX;

        settings_options settings;
        settings.api = graphics_api::vulkan;
        settings.vulkan.application_name = "Nova Renderer test";
        settings.vulkan.application_version = { 0, 8, 0 };
        settings.debug.enabled = true;
        settings.debug.renderdoc.enabled = false;
        settings.window.width = 640;
        settings.window.height = 480;
        const auto renderer = nova_renderer::initialize(settings);

        renderer->load_shaderpack(CMAKE_DEFINED_RESOURCES_PREFIX "shaderpacks/DefaultShaderpack");

        render_engine* engine = renderer->get_engine();
        std::shared_ptr<iwindow> window = engine->get_window();

        mesh_data cube = {};
        cube.vertex_data = {
            full_vertex{{-1, -1, -1}, {}, {}, {}, {}, {}, {}},
            full_vertex{{-1, -1, 1}, {}, {}, {}, {}, {}, {}},
            full_vertex{{-1, 1, -1}, {}, {}, {}, {}, {}, {}},
            full_vertex{{-1, 1, 1}, {}, {}, {}, {}, {}, {}},
            full_vertex{{1, -1, -1}, {}, {}, {}, {}, {}, {}},
            full_vertex{{1, -1, 1}, {}, {}, {}, {}, {}, {}},
            full_vertex{{1, 1, -1}, {}, {}, {}, {}, {}, {}},
            full_vertex{{1, 1, 1}, {}, {}, {}, {}, {}, {}},
        };
        cube.indices = {
            0, 1, 3,
            6, 0, 2,
            5, 0, 4,
            6, 4, 0,
            0, 3, 2,
            5, 1, 0,
            3, 1, 5,
            7, 4, 6,
            4, 7, 5,
            7, 6, 2,
            7, 2, 3,
            7, 3, 5
        };
        engine->add_mesh(cube);

        while(!window->should_close()) {
            renderer->execute_frame();
            window->on_frame_end();
        }

        nova_renderer::deinitialize();

        return 0;
    }
}


int main() {
#ifdef __linux__
    signal(SIGSEGV, sigsegv_handler);
    signal(SIGABRT, sigabrt_handler);
#endif
    return nova::main();
}

#ifdef __linux__
void sigsegv_handler(int sig) {
    signal(sig, SIG_IGN);

    std::cerr << "!!!SIGSEGV!!!" << std::endl;
    nova_backtrace();

    _exit(1);
}

void sigabrt_handler(int sig) {
    signal(sig, SIG_IGN);

    std::cerr << "!!!SIGABRT!!!" << std::endl;
    nova_backtrace();

    _exit(1);
}
#endif
