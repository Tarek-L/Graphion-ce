#include <glad/glad.h>
//
#include <Core/core.hpp>
#include <GLFW/glfw3.h>
#include <memory>

enum class WindowError { InitializationFailed, WindowCreationFailed };

namespace Graphion::Window {
using WindowHandle =
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>;

$<void, Error<WindowError>> Init();
void Shutdown();
$<WindowHandle, Error<WindowError>> create(const char* title);
}; // namespace Graphion::Window

$<void, Error<WindowError>> Graphion::Window::Init() {
  if (!glfwInit())
    return std::unexpected(
        Error<WindowError>{WindowError::InitializationFailed,
                           "Failed to initialize Window sub system"});

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  return {};
}

void Graphion::Window::Shutdown() { glfwTerminate(); }

$<Graphion::Window::WindowHandle, Error<WindowError>>
Graphion::Window::create(const char* title) {
  GLFWwindow *window = glfwCreateWindow(10, 10, title, nullptr, nullptr);
  if (!window)
    return std::unexpected(Error<WindowError>{WindowError::WindowCreationFailed,
                                              "Failed to create a window"});

  return Graphion::Window::WindowHandle(window, glfwDestroyWindow);
}

int main(void) {

  fmt::print("Just the usaul stuff nothing new, I will just try to speedrun "
             "the getting started in a clean way to refresh my memory"
             "We will try to full finish OpenGL before moving To vulkan, i "
             "hope this codebase looks like C++\n");

  if (auto result = Graphion::Window::Init(); !result) {
    auto err = result.error();
    err.logError();
    return -1;
  }
  defer(Graphion::Window::Shutdown());

  return 0;
}
