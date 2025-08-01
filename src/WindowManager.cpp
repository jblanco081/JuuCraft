#include "WindowManager.h"

namespace WindowManager {

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}
