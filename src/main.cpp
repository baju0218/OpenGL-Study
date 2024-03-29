#include "context.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <spdlog/spdlog.h>

void OnFramebufferSizeChange(GLFWwindow *window, int width, int height) {
  SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
  auto context = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
  context->Reshape(width, height);
}

void OnMouseButton(GLFWwindow *window, int button, int action, int modifier) {
  auto context = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  context->MouseButton(button, action, x, y);
}

void OnCursorPos(GLFWwindow *window, double x, double y) {
  auto context = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
  context->MouseMove(x, y);
}

void OnKeyEvent(GLFWwindow *window, int key, int scancode, int action,
                int mods) {
  SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}", key, scancode,
              action == GLFW_PRESS     ? "Pressed"
              : action == GLFW_RELEASE ? "Released"
              : action == GLFW_REPEAT  ? "Repeat"
                                       : "Unknown",
              mods & GLFW_MOD_CONTROL ? "C" : "-",
              mods & GLFW_MOD_SHIFT ? "S" : "-",
              mods & GLFW_MOD_ALT ? "A" : "-");
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int main(int argc, const char **argv) {
  SPDLOG_INFO("Initialize glfw");
  if (!glfwInit()) {
    const char *description = nullptr;
    glfwGetError(&description);
    SPDLOG_ERROR("failed to initialize glfw: {}", description);
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  SPDLOG_INFO("Create glfw window");
  auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
                                 nullptr, nullptr);
  if (!window) {
    SPDLOG_ERROR("failed to create glfw window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    SPDLOG_ERROR("failed to initialize glad");
    glfwTerminate();
    return -1;
  }

  const auto glVersion =
      reinterpret_cast<const char *>(glGetString(GL_VERSION));
  SPDLOG_INFO("OpenGL context version: {}", glVersion);

  auto context = Context::Create();
  if (!context) {
    SPDLOG_ERROR("failed to create context");
    glfwTerminate();
    return -1;
  }

  glfwSetWindowUserPointer(window, context.get());
  glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
  glfwSetKeyCallback(window, OnKeyEvent);
  glfwSetMouseButtonCallback(window, OnMouseButton);
  glfwSetCursorPosCallback(window, OnCursorPos);

  OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);

  auto imguiContext = ImGui::CreateContext();
  ImGui::SetCurrentContext(imguiContext);
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  SPDLOG_INFO("Start main loop");
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    context->ProcessInput(window);
    context->Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext(imguiContext);

  context.reset();
  glfwTerminate();

  return 0;
}