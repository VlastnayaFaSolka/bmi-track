#include <GLFW/glfw3.h>
#include <windows.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        // glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// g++ main.cpp -I"C:C:\work\cpp\glfw-3.4.bin.WIN64\include\GLFW" -L"C:\work\cpp\incl\glfw-3.4.bin.WIN64\lib-mingw-w64" -lglfw3 -lopengl32 -lgdi32 -o main.exe
