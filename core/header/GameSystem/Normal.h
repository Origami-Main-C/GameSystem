#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Normal {
namespace Function {
// Normal framebuffer_size_callback function for glfw
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
} // namespace Function
} // namespace Normal