#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <iostream>

int main(void) {

  std::cout << "Just the usaul stuff nothing new, I will just try to speedrun "
               "the getting started in a clean way to refresh my memory"
               "We will try to full finish OpenGL before moving To vulkan"
            << std::endl;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  glfwTerminate();

  return 0;
}
