#define GLFW_INCLUDE_NONE

// IMGUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/quaternion.hpp>

// STD Lib
#include <iostream>
#include <cstdlib>

// GlECS
#include <Entity.h>
#include <Component.h>
#include <Camera.h>

#include <components/Transform.h>
#include <components/MeshRenderer.h>

#include <assets/Shader.h>
#include <assets/Material.h>
#include <assets/Mesh.h>
#include <assets/ObjMesh.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

GLFWwindow *InitGUI();

int main()
{
    using namespace nbop::glecs;

    const std::vector<float> cubePositions({
        -0.5f, -0.5f,  0.5f,
        0.5,  -0.5f,  0.5f,
        0.5,   0.5f,  0.5f,
        -0.5,   0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5,  -0.5f, -0.5f,
        0.5,   0.5f, -0.5f,
        -0.5,   0.5f, -0.5f
    });

    const std::vector<float> cubeColors({
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f
    });

    const std::vector<unsigned int> cubeIndices({
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        5, 4, 7,
        7, 6, 5,
        4, 0, 3, 
        3, 7, 4,
        2, 6, 7,
        7, 3, 2,
        4, 5, 1,
        1, 0, 4
    });

    // Initialize GLFW / OpenGL / ImGUI / etc
    GLFWwindow *window = InitGUI();

    // Compiling 3 shaders : vertex, fragment, and geometry
    std::shared_ptr<Shader> vertexShader   = std::make_shared<Shader>("resources/default_vertex.glsl",   std::vector<Shader::Uniform>(), GL_VERTEX_SHADER  );
    std::shared_ptr<Shader> fragmentShader = std::make_shared<Shader>("resources/default_fragment.glsl", std::vector<Shader::Uniform>(), GL_FRAGMENT_SHADER);
    std::shared_ptr<Shader> geometryShader = std::make_shared<Shader>("resources/default_geometry.glsl", std::vector<Shader::Uniform>(), GL_GEOMETRY_SHADER);
    
    // Creating a material
    std::vector<std::weak_ptr<Shader>> shaders = { vertexShader, fragmentShader, geometryShader };
    std::shared_ptr<Material> material = std::make_shared<Material>(shaders);

    // Creating a mesh
    std::shared_ptr<ObjMesh> mesh = std::make_shared<ObjMesh>("resources/teapot.obj");
    
    // Adding game object to the scene
    std::shared_ptr<Entity> cubeObject = std::make_shared<Entity>("cube");
    std::weak_ptr<Transform> cubeTransform = cubeObject->addComponent<Transform>();
    std::weak_ptr<MeshRenderer> cubeMeshRenderer = cubeObject->addComponent<MeshRenderer>();

    // Setting up the mesh renderer
    {
        std::shared_ptr<MeshRenderer> meshRenderer = cubeMeshRenderer.lock();
        meshRenderer->setup(material, mesh);
    }

    float cameraRadius = 5.0f;
    float cameraTheta = 0.0f;
    float cameraHeight = 0.0f;
    
    // Starting the game loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            // IMGUI WINDOW HERE
            ImGui::Begin("Test");
            ImGui::SliderFloat("Radius", &cameraRadius, 0.0f, 10.0f);
            ImGui::SliderFloat("Theta", &cameraTheta, 0.0f, 3.14f * 2.0f);
            ImGui::SliderFloat("Height", &cameraHeight, -10.0f, 10.0f);
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        // Clear
        glm::vec3 clearColor = Camera::getClearColor();
        glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Camera Setup
        Camera::setViewMatrix(glm::lookAt(
            glm::vec3(cameraRadius * cos(cameraTheta), cameraHeight, cameraRadius * sin(cameraTheta)),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
        ));
        Camera::setProjectionMatrix(glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 1.0f, 100.0f));
        // Frame Update
        cubeMeshRenderer.lock()->onNewFrame();
        // Show
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    std::cout << "Program finished with no crash \\o/" << std::endl;
    return 0;
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow *InitGUI()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        exit(1);

    // Decide GL+GLSL versions
    // GL 3.0 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        exit(1);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Using GLAD loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_MULTISAMPLE);

    return window;
}