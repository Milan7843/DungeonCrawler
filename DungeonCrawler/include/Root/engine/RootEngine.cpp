#include "RootEngine.h"

#include "Root/rendering/Camera.h"

namespace RootEngine
{

    // 'Private' members of the namespace
    namespace
    {
        unsigned int WINDOW_SIZE_X, WINDOW_SIZE_Y;

        std::vector<std::shared_ptr<Transform>> transforms;
        std::vector<std::shared_ptr<Script>> scripts;

        Shader* spriteRenderShader;

        Camera* activeCamera{ nullptr };
        GLFWwindow* window{ nullptr };

        bool physicsSimulationActive{ true };

        void initialiseGLFW()
        {
            // Initialising GLFW
            glfwInit();

            // Setting OpenGL version 4.6
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

            // OpenGL profile: core
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        void initialiseImGui(GLFWwindow* window)
        {
            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

            // Setup Dear ImGui style to be dark
            ImGui::StyleColorsDark();

            // Setup Platform/Renderer backends
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 130");
        }
    }

    int Start(unsigned int windowWidth, unsigned int windowHeight)
    {
        WINDOW_SIZE_X = windowWidth;
        WINDOW_SIZE_Y = windowHeight;

        initialiseGLFW();

        // Making a GLFW window
        window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, "OpenGL", NULL, NULL);
        if (window == NULL)
        {
            Logger::logError("Failed to create GLFW window");
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);

        // GLAD manages function pointers for OpenGL, so we cannot run without it
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            Logger::logError("Failed to initialize GLAD");
            return -1;
        }

        initialiseImGui(window);

        spriteRenderShader = new Shader(
            "include/Root/shaders/default_shader_source/spriteVertex.shader",
            "include/Root/shaders/default_shader_source/spriteFragment.shader");

        // Shader textRenderShader("src/shaders/textVertex.shader", "src/shaders/textFragment.shader");

        // Enabling depth testing for rasterized view: 
        // makes sure objects get drawn on top of each other in the correct order
        glEnable(GL_DEPTH_TEST);

        Renderer::initialise();

        InputEngine::initialise();

        unsigned int frame = 0;

        SimpleText simpleText("src/fonts/arial.ttf");
        SimpleGUI simpleGUI(WINDOW_SIZE_X, WINDOW_SIZE_Y);

        // Calling all component and script start() functions
        ComponentEngine::startScripts();

        //std::thread physicsSimulation(PhysicsEngine::simulate);

        while (!glfwWindowShouldClose(window))
        {
            Profiler::addCheckpoint("Start of frame");

            // Updating the variables in Time
            Time::update(glfwGetTime());

            // Getting viewport size
            glfwGetWindowSize(window, (int*)&WINDOW_SIZE_X, (int*)&WINDOW_SIZE_Y);

            // Updating the input engine
            InputEngine::update();

            // Setting viewport size
            glViewport(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

            // Calling all component and script update() functions
            ComponentEngine::updateScripts();

            PhysicsEngine::step(Time::getDeltaTime());

            ComponentEngine::updateRigidbodiesTransforms();

            // Input
            //processInput(window);

            // Rendering
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Calling all component render() functions
            ComponentEngine::renderComponents();

            InputEngine::newFrame();

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

        physicsSimulationActive = false;

        //physicsSimulation.join();

        terminateRoot();

        Logger::stop();

        glfwTerminate();

        return 0;
    }

    Shader* getSpriteRenderShader()
    {
        return spriteRenderShader;
    }


    void addScript(std::shared_ptr<Script> script)
    {
        scripts.push_back(script);
    }

    std::vector<std::shared_ptr<Script>>& getScripts()
    {
        return scripts;
    }

    void addTransform(std::shared_ptr<Transform> transform)
    {
        transforms.push_back(transform);
    }

    std::vector<std::shared_ptr<Transform>>& getTransforms()
    {
        return transforms;
    }

    void setActiveCamera(Camera* camera)
    {
        activeCamera = camera;
    }

    Camera* getActiveCamera()
    {
        return activeCamera;
    }

    GLFWwindow* getActiveWindow()
    {
        return window;
    }

    unsigned int getScreenWidth()
    {
        return WINDOW_SIZE_X;
    }

    unsigned int getScreenHeight()
    {
        return WINDOW_SIZE_Y;
    }

    void terminateRoot()
    {
        // Removing all links between transforms
        for (TransformPointer transform : transforms)
        {
            transform->setParent(NULL);
            transform->removeAllChildren();
        }
    }

    bool isPhysicsSimulationActive()
    {
        return physicsSimulationActive;
    }
};
