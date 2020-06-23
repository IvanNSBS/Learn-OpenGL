#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "./Shaders/ShaderProgram.h"
#include "ImGuiWindows/PR_Viewport.h"
#include "ImGuiWindows/PR_WindowManager.h"

#include "Scene/Camera.h"
#include "Scene/PHObject.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

    const char* vertexPath = "D:\\Visual Studio Projects\\OGL-PixelRenderer\\OGL-PixelRenderer\\Resources\\ShaderFiles\\dfVert.glsl";
    const char* fragPath = "D:\\Visual Studio Projects\\OGL-PixelRenderer\\OGL-PixelRenderer\\Resources\\ShaderFiles\\dfFrag.glsl";
    //const char* fragPath = "E:\\Visual Studio Projects\\OGL - PixelRenderer\\Pixel Renderer VS\\Assets\\Resources\\ShaderFiles\\defaultFrag.glsl";
    ShaderProgram shader(vertexPath, fragPath);

    PR_WindowManager prWindowManager(window, "#version 430");



    //Begin FBO
    GLuint FBO, fboTex, RBO;
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    int sizeSqr = 128;

    glGenTextures(1, &fboTex);
    glBindTexture(GL_TEXTURE_2D, fboTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizeSqr, sizeSqr, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTex, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, sizeSqr, sizeSqr);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // END FBO

    //PR_Viewport prViewport("Viewport");
    PR_Viewport prViewport("Viewport", &fboTex);
    prWindowManager.AddWindow(&prViewport);

    glViewport(0, 0, sizeSqr, sizeSqr);

    glm::vec3 pos(0,0,4);
    glm::vec3 at(0, 0, -1);
    glm::vec3 up(0,1,0);
    Camera cam(pos, at, up, 30, 0.1, 100, &prViewport);

    const char* objVertPath = "D:\\Visual Studio Projects\\OGL-PixelRenderer\\OGL-PixelRenderer\\Resources\\ShaderFiles\\phObjectVert.glsl";
    const char* objFragPath = "D:\\Visual Studio Projects\\OGL-PixelRenderer\\OGL-PixelRenderer\\Resources\\ShaderFiles\\phObjectFrag.glsl";
    const char* objMeshPath = "D:\\Visual Studio Projects\\OGL-PixelRenderer\\OGL-PixelRenderer\\Resources\\3DObjects\\monkey_smooth.obj";


    Transform trf({ 0,0,0 }, { 0,0,0 }, {1, 1, 1});
    PHObject obj(objMeshPath, trf, objVertPath, objFragPath);
    obj.Start();
    glEnable(GL_DEPTH_TEST);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render FBO
        // ----
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glEnable(GL_DEPTH_TEST);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDisable(GL_DEPTH_TEST);
        //draw bg first
        shader.Bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        
        glEnable(GL_DEPTH_TEST);
        obj.Draw(cam);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // render normally
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        prWindowManager.Update();
        cam.begin_imgui();
        obj.start_imgui();

        prWindowManager.Render();

        //glViewport(0, 0, prViewport.ViewportSize().x, prViewport.ViewportSize().y);

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
    //glViewport(0, 0, width, height);
    //SCR_WIDTH = width;
    //SCR_HEIGHT = height;
}