#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow *window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // build and compile our shader program
  Shader ourShader(std::string("resources/shaders/shader.vs"),std::string("resources/shaders/shader.fs"));
  // set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
  float vertices[] = {
    // Vertices         // Colors
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
     0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
  };

  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2,   // first triangle
  };

  unsigned int VBO; // Vertex Buffer Object, array buffer to store data on GPU
  // Vertex Array Object stores the attribute configuration `glVertexAttribPointer`
  // and the buffer object associated with the attributes
  unsigned int VAO; 
  unsigned int EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // NOTE: Bind the VAO first, then bind vertex buffers and configure attributes
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind buffer, to use it for subsequent calls
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy data to the array buffer

  /* An EBO is a buffer, just like a vertex buffer object,
   * that stores indices that OpenGL uses to decide what vertices to draw.
   */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Link vertex attributes: Tell GPU how to interpret the GL_ARRAY_BUFFER data
  // and send it to the vertex shader
  /*
   * arg1: location of the vertex attribute | layout (location = 0) in the vertex shader code
   * arg2: size of vertex attribute, the vertex attribute is a vec3, so size is 3
   * arg3: Type of data
   * arg4: Boolean specify data should be normalized or not
   * arg5: Strides, tells space between consecutive vertex attributes.
   */
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind buffer
  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the
  // vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0); 

  // WARNING: do NOT unbind the EBO while a VAO is active as the bound element
  // buffer object IS stored in the VAO; keep the EBO bound.
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO,
  // but this rarely happens.
  // Modifying other VAOs requires a call to glBindVertexArray anyways so we generally
  // don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray(0);


  // uncomment this call to draw in wireframe polygons.
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {
    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();

    glBindVertexArray(VAO);
    /*glDrawArrays(GL_TRIANGLES, 0, 3);*/
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    /*glBindVertexArray(sVAO);*/
    /*glDrawArrays(GL_TRIANGLES, 0, 3);*/
    /*glBindVertexArray(0);*/

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glUseProgram(ourShader.ID);

  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS )
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
