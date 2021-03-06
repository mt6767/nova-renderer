//
// Created by jannis on 01.09.18.
//

#ifndef NOVA_RENDERER_X_11_WINDOW_HPP
#define NOVA_RENDERER_X_11_WINDOW_HPP

#ifdef NOVA_LINUX

#include "../window.hpp"
#include <X11/Xlib.h>
#include <stdint.h>

namespace nova {
    class x11_window : public iwindow {
    private:
        Window window;
        Display *display;
        bool should_window_close = false;
        Atom wm_protocols;
        Atom wm_delete_window;

    public:
        explicit x11_window(uint32_t width, uint32_t height);
        virtual ~x11_window();

        Window &get_x11_window();
        Display *get_display();

        void on_frame_end() override;
        bool should_close() const override;

        glm::uvec2 get_window_size() const override;
    };
}  // namespace nova

#endif

// X11 macros that are bad
#ifdef Always
#undef Always
#endif

#ifdef None
#undef None
#endif

#ifdef Bool
#undef Bool
#endif

#endif  // NOVA_RENDERER_X_11_WINDOW_HPP
