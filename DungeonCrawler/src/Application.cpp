#define STB_IMAGE_IMPLEMENTATION

#include "Application.h"


Application::Application(unsigned int WIDTH, unsigned int HEIGHT)
    : WINDOW_SIZE_X(WIDTH), WINDOW_SIZE_Y(HEIGHT)
{

}

Application::~Application()
{
    Logger::log("Application instance destroyed");
}

int Application::Start()
{
    initialiseGLFW();

    // Making a GLFW window
    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "OpenGL", NULL, NULL);
    if (window == NULL)
    {
        Logger::logError("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    ImGuiUserInterface userInterface(window);

    userInterface.initialiseImGui(window);

    // GLAD manages function pointers for OpenGL, so we cannot run without it
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::logError("Failed to initialize GLAD");
        return -1;
    }

    // Creating shaders
    Shader solidColorShader("src/shaders/solidColorVertexShader.shader",
        "src/shaders/solidColorFragmentShader.shader");
    Shader marchingCubesShader("src/shaders/marchingCubesVertexShader.shader",
        "src/shaders/marchingCubesFragmentShader.shader",
        "src/shaders/marchingCubesGeometryShader.shader");
    Shader marchingCubesPointRenderShader("src/shaders/marchingCubesVertexShader.shader",
        "src/shaders/marchingCubesPointFragmentShader.shader",
        "src/shaders/marchingCubesPointGeometryShader.shader");

    Shader textRenderShader("src/shaders/textVertex.shader", "src/shaders/textFragment.shader");

    // Enabling depth testing for rasterized view: 
    // makes sure objects get drawn on top of each other in the correct order
    glEnable(GL_DEPTH_TEST);

    // Change the viewport size if the window is resized
    glfwSetFramebufferSizeCallback(window, &Callbacks::framebuffer_size_callback);

    Callbacks& callbacks = Callbacks::getInstance();

    GameManager gameManager;

    // Generating a VAO for the axes so that they can be rendered easily
    generateAxesVAO();

    unsigned int frame = 0;

    SimpleText simpleText("src/fonts/arial.ttf");
    SimpleGUI simpleGUI(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    SimpleGUIComponent::Rectangle* item = 
        new SimpleGUIComponent::Rectangle(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    SimpleGUIComponent::Item* titleItem =
        new SimpleGUIComponent::Image("src/images/title_image.png", 
            WINDOW_SIZE_X, WINDOW_SIZE_Y, 
            120.0f, // Image height
            glm::vec2(0.5f, 0.95f));

    titleItem->setHorizontalAnchorPoint(HorizontalAnchorPoint::Middle);
    titleItem->setVerticalAnchorPoint(VerticalAnchorPoint::Top);

    simpleGUI.addItemToRenderQueue(item);
    simpleGUI.addItemToRenderQueue(titleItem);

    while (!glfwWindowShouldClose(window))
    {
        Profiler::addCheckpoint("Start of frame");

        // Getting viewport size
        glfwGetWindowSize(window, (int*)&WINDOW_SIZE_X, (int*)&WINDOW_SIZE_Y);

        // Setting viewport size
        glViewport(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Input
        processInput(window);

        // Check whether the UI is enabled
        if (!userInterface.isEnabled())
        {
            // Calling the mouse callback
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            gameManager.processInput(window, xpos, ypos, deltaTime);
        }

        userInterface.handleInput(window, gameManager.getCamera());

        // Rendering
        glClearColor(gameManager.getFogColor().r, gameManager.getFogColor().g, gameManager.getFogColor().b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // ??
        glDisable(GL_DEPTH_TEST);

        glEnable(GL_DEPTH_TEST);

        /* REGULAR RENDERING */
        solidColorShader.use();

        // Drawing axes
        drawAxes(axesVAO, solidColorShader, gameManager.getCamera());
        Profiler::addCheckpoint("Axes draw");

        gameManager.update(deltaTime);

        Profiler::addCheckpoint("Game update");

        gameManager.render(marchingCubesShader, marchingCubesPointRenderShader, WINDOW_SIZE_X, WINDOW_SIZE_Y);

        Profiler::addCheckpoint("Game render");

        simpleText.renderText(textRenderShader, "What's up?!", WINDOW_SIZE_X, WINDOW_SIZE_Y, 50, 50, glm::vec2(1.0f), glm::vec3(1.0f));

        simpleGUI.render(WINDOW_SIZE_X, WINDOW_SIZE_Y);

        Profiler::addCheckpoint("Gui render");

        userInterface.drawUserInterface(window, gameManager.getMarchingCubesGridsHandler());

        Profiler::addCheckpoint("ImGui render");


        Profiler::addCheckpoint("End of frame");

        // Rendering and resetting profiler
        Profiler::createProfilerWindow();
        Profiler::emptyCheckpointList();

        frame++;

        // Output
        glfwSwapBuffers(window);
        // Check for input
        glfwPollEvents();
    }

    Logger::stop();

    glfwTerminate();

	return 0;
}

void Application::initialiseGLFW()
{
    // Initialising GLFW
    glfwInit();

    // Setting OpenGL version 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // OpenGL profile: core
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Application::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Application::generateAxesVAO()
{
    // Creating our vertex array object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Putting the vertices into the array buffer
    float vertices[] = {
        // Position
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1
    };

    unsigned int VBO;
    // Making a buffer with the ID in VBO
    glGenBuffers(1, &VBO);
    // Binding our new buffer to the GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Binding our custom data into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Binding the element buffer object
    unsigned int EBO;
    // Generating a buffer for the EBO
    glGenBuffers(1, &EBO);
    // Binding the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Inserting data into the buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // Telling OpenGL how to interpret the data
    // Position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    axesVAO = VAO;
}

void Application::drawAxes(unsigned int VAO, Shader& shader, Camera& camera)
{
    glLineWidth(0.01f);
    float s = 1.0f;

    shader.use();

    // Model matrix
    glm::mat4 model{ glm::mat4(1.0f) };
    shader.setMat4("model", model);

    // View matrix
    glm::mat4 view{ camera.getViewMatrix() };
    shader.setMat4("view", view);

    // Projection matrix
    glm::mat4 projection{ camera.getProjectionMatrix(WINDOW_SIZE_X, WINDOW_SIZE_Y) };
    shader.setMat4("projection", projection);

    // Binding the VAO
    glBindVertexArray(VAO);

    // Drawing the x-axis (red)
    shader.setVector3("inputColor", 194 / 255.0f, 31 / 255.0f, 19 / 255.0f);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT /* index type */, 0);

    // Drawing the y-axis (up) (green)
    model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setMat4("model", model);
    shader.setVector3("inputColor", 29 / 255.0f, 194 / 255.0f, 57 / 255.0f);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT /* index type */, 0);

    // Drawing the z-axis (blue)
    model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    shader.setMat4("model", model);
    shader.setVector3("inputColor", 19 / 255.0f, 37 / 255.0f, 194 / 255.0f);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT /* index type */, 0);
    glBindVertexArray(0);
}
