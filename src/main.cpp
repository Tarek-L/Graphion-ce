#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <Core/core.hpp>

enum class WindowError { InitializationFailed, WindowCreationFailed };

class Window {
public:
  $<GLFWwindow*, Error<WindowError>> create();
};

$<GLFWwindow*, Error<WindowError>> Window::create() {
    GLFWwindow* window = glfwCreateWindow(10, 10, "dog", nullptr, nullptr);
    if (!window)
        return std::unexpected(Error<WindowError>{WindowError::WindowCreationFailed, "Failed to create GLFW window"});

    return window;
}



int main(void) {

  fmt::print("Just the usaul stuff nothing new, I will just try to speedrun "
             "the getting started in a clean way to refresh my memory"
             "We will try to full finish OpenGL before moving To vulkan\n");

  glfwInit();
  defer(glfwTerminate());

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  return 0;
}
