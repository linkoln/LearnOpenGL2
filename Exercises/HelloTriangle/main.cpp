#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(type, 512, nullptr, infoLog);
        cout << "ERROR::CompileShader" << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT") << "\n" << infoLog << endl;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int result;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        cout << "ERROR::CreateShader\n" << infoLog << endl;
    }

    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "HelloTriangle", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }
//    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices1[] = {0.0f, 0.0f, 0.0f,
                         -0.5f, 0.0f, 0.0f,
                         0.0f, 0.5f, 0.0f
                        };
    float vertices2[] = {0.0f, 0.0f, 0.0f,
                         0.0f, -0.5f, 0.0f,
                         0.5f, 0.0f, 0.0f
                        };

    const std::string vertexShader = "#version 330 core\n"
                                     "layout(location = 0) in vec3 pos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
                                     "}\n\0";
    const std::string fragmentShader = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices1), vertices1, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void*)0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices2), vertices2, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), (void*)0);

    unsigned int program = CreateShader(vertexShader, fragmentShader);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(2, VBO);
    glDeleteVertexArrays(2, VAO);
    glDeleteProgram(program);

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
