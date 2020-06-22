#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./Shaders/ShaderProgram.h"
#include "ImGuiWindows/PR_Viewport.h"
#include "ImGuiWindows/PR_WindowManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pixel Renderer", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW Window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    //triangle draw text
    float vertices[] = { -1, -1, 0,  -1,  1, 0,   1,  1, 0,
                          1,  1, 0,   1, -1, 0,  -1, -1, 0 };
    float uvs[] = { 0, 0,   0, 1,   1, 1,
                    1, 1,   1, 0,   0, 0};

    GLuint VAO, VBO, UVS;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &UVS);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, UVS);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    const char* vertexPath = "E:\\Visual Studio Projects\\OGL-PixelRenderer\\OGL-PixelRenderer\\OGL-PixelRenderer\\src\\Shaders\\ShaderFiles\\dfVert.glsl";
    const char* fragPath = "E:\\Visual Studio Projects\\OGL-PixelRenderer\\OGL-PixelRenderer\\OGL-PixelRenderer\\src\\Shaders\\ShaderFiles\\dfFrag.glsl";
    //const char* fragPath = "E:\\Visual Studio Projects\\OGL - PixelRenderer\\Pixel Renderer VS\\Assets\\Resources\\ShaderFiles\\defaultFrag.glsl";
    ShaderProgram shader(vertexPath, fragPath);

    PR_WindowManager prWindowManager(window, "#version 130");
    PR_Viewport prViewport("Viewport");
    prWindowManager.AddWindow(&prViewport);

    //GLuint FBO;
    //glGenFramebuffers(FBO);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //ImGui_ImplOpenGL3_NewFrame();
        //ImGui_ImplGlfw_NewFrame();
        //ImGui::NewFrame();

        prWindowManager.Update();
        //prViewport.Update();

        shader.Bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        prWindowManager.Render();
        //ImGui::Render();
        //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}