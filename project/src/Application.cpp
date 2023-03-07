#include <GameSystem.h>


void processInput(Window &windows) {
    if (glfwGetKey(windows.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        windows.SetWindowShouldClose();
    }
}

int main() {
    //Init window
    Window gamesystem(800, 600, const_cast<char*>("GameSystem"), const_cast<char*>("../project/icon/icon.png"));
    Shader shader("../project/shader/rectangleShader/vertexShader.glsl", "../project/shader/rectangleShader/fragmentShader.glsl");
    Texture texture("../project/texture/icon.png");
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };
    VBO vbo;
    vbo.Data(sizeof(vertices), vertices);
    EBO ebo;
    ebo.Data(sizeof(indices), indices);
    VAO vao;
    vao.Bind();
    vbo.Bind();
    ebo.Bind();
    vao.Layout(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vao.Layout(1, 3, GL_FLOAT, 8 * sizeof(float), 3*sizeof(float));
    vao.Layout(2, 2, GL_FLOAT, 8 * sizeof(float), 6*sizeof(float));
    glm::mat4 trans(1.0f);
    //colors
    ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    ImVec4 rectangle_color = ImVec4(0.2f, 0.3f, 0.5f, 1.0f);
    shader.use();
    shader.setInt("texture1",0);
    float deltaTime;
    float lastFrame=0.0f;
    float angle_change=0.0f;
    ImGui::FileBrowser fileDialog;
    // (optional) set browser properties
    fileDialog.SetTitle("file browser");
    std::filesystem::path pwd("../");
    fileDialog.SetPwd(pwd);
    bool openFileDialog=false;
    int time=0;
    while (!gamesystem.ShouldClose()) {
        if(time=1)
            openFileDialog= false;
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(gamesystem);
        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        texture.Bind();
        trans = glm::rotate(trans, (angle_change / 180.0f) * 3.14f, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.use();
        shader.setVec4("ourColor", glm::vec4(rectangle_color.x, rectangle_color.y, rectangle_color.z, rectangle_color.w));
        shader.setMat4("transform",trans);
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.Unbind();
        //Gui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        ImGui::PopStyleVar(2);
        ImGuiIO& io = ImGui::GetIO();
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Add"))
            {
                if (ImGui::MenuItem("Model", NULL, false, true))
                {
                    openFileDialog= true;
                    time=1;

                }
                if (ImGui::MenuItem("Light", NULL, false, true))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Shader"))
            {
                if (ImGui::MenuItem("New", NULL, false, true))
                {
                    openFileDialog= true;
                    time=1;
                }
                if (ImGui::MenuItem("Set Default", NULL, false, true))
                {

                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();
        ImGui::Begin("Viewport", nullptr);
        ImGui::End();
        ImGui::Begin("Object Editor");
        ImGui::End();
        if(openFileDialog)
        {
            fileDialog.Open();
        }
        fileDialog.Display();
        if(fileDialog.HasSelected())
        {
            std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
            fileDialog.ClearSelected();
            fileDialog.Close();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(gamesystem.window);
        glfwPollEvents();
    }
}