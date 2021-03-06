/*!
 * \author ddubois
 * \date 28-Apr-18.
 */

#ifndef NOVA_RENDERER_FRAMEBUFFER_MANAGER_H
#define NOVA_RENDERER_FRAMEBUFFER_MANAGER_H

#include <cstdint>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <vector>
#include "../../util/utils.hpp"

namespace nova {
    class vulkan_render_engine;

    NOVA_EXCEPTION(swapchain_creation_failed);
    NOVA_EXCEPTION(present_failed);

    /*!
     * \brief Deals with the swapchain, yo
     *
     * Methods to get he next swapchain image and whatnot are found here
     *
     * You can even get the framebuffer constructed from the current swapchain. Wow!
     */
    class swapchain_manager {
    public:
        swapchain_manager(uint32_t num_swapchain_images, vulkan_render_engine& render_engine, const glm::ivec2 window_dimensions);

        void present_current_image(const std::vector<VkSemaphore>& wait_semaphores) const;

        void acquire_next_swapchain_image(VkSemaphore image_acquire_semaphore);

        void set_current_layout(VkImageLayout new_layout);

        VkFramebuffer get_current_framebuffer();
        VkFence get_current_frame_fence();

        VkImage get_current_image();
        VkImageLayout get_current_layout();
        VkExtent2D get_swapchain_extent() const;
        VkFormat get_swapchain_format() const;


        // I've had a lot of bugs with RAII so here's an explicit cleanup method
        void deinit();

        uint32_t get_current_index() const;

    private:
        vulkan_render_engine& render_engine;
        
        VkSwapchainKHR swapchain;
        VkExtent2D swapchain_extent;
        VkPresentModeKHR present_mode;
        VkFormat swapchain_format;
        
        std::vector<VkFramebuffer> framebuffers;
        std::vector<VkImageView> swapchain_image_views;
        std::vector<VkImage> swapchain_images;
        std::vector<VkImageLayout> swapchain_image_layouts;
        std::vector<VkFence> fences;

        uint32_t cur_swapchain_index = 0;

        static VkSurfaceFormatKHR choose_surface_format(const std::vector<VkSurfaceFormatKHR> &formats);

        static VkPresentModeKHR choose_present_mode(const std::vector<VkPresentModeKHR> &modes);

        static VkExtent2D choose_surface_extent(const VkSurfaceCapabilitiesKHR &caps, const glm::ivec2 &window_dimensions);

        void transition_swapchain_images_into_correct_layout(const std::vector<VkImage> &images) const;
    };
}

#endif //NOVA_RENDERER_FRAMEBUFFER_MANAGER_H