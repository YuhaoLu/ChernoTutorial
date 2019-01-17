#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Dependencies
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Vendor 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

// Self Wrote headers
#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include "Shader.h"

#include "Texture.h"

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW Init Error!" << std::endl;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	{ 
		/*
		float positions[] = {
		   -50.0f, -50.0f, 0.0f, 0.0f, // 0
		    50.0f, -50.0f, 1.0f, 0.0f, // 1
		    50.0f,  50.0f, 1.0f, 1.0f, // 2
		   -50.0f,  50.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		*/

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		/*
		// 1. Vertex Array
		VertexArray va;

		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		va.AddBuffer(vb, layout);

		// 2. Index Buffers
		IndexBuffer ib(indices, 6);

		// Model View Projection Matrices
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		// 3. Shader
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		// Uniforms
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f); 
		

		// Texture
		Texture texture("res/textures/ChernoLogo.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();
		*/

		Renderer renderer;
		
		// ImGui
		ImGui::CreateContext();

		ImGui::StyleColorsDark();

		const char* glsl_version = "#version 150";
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		/*
		float r = 0.0f;
		float increment = 0.05f;
		glm::vec3 translationA(200, 200, 0);
		glm::vec3 translationB(400, 200, 0);
		*/

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture2D>("Texture 2D");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			renderer.Clear();

			// ImGui: Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			
			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-")) {
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}

			/*
			{
				// shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = proj * view * model;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp); // Model View Projection Matrix
				
				renderer.Draw(va, ib, shader);
			}

			// Draw the 2nd Object
			{
				// shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 mvp = proj * view * model;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", mvp); // Model View Projection Matrix

				renderer.Draw(va, ib, shader);
			}
			

			if (r > 1.0f) {
				increment = -0.05f;
			}
			else if (r < 0.0f)
			{
				increment = 0.05f;
			}
			r += increment;
           

			// ImGui: Show a simple window that we create ourselves. 
			{
				static float f = 0.0f;

				ImGui::Begin("Hello, world!");  // Create a window called "Hello, world!" and append into it.

				ImGui::SliderFloat3("translation A", &translationA.x, 0.0f, 960.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::SliderFloat3("translation B", &translationB.x, 0.0f, 960.0f);  // Edit 1 float using a slider from 0.0f to 1.0f

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			} 
			*/

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		delete currentTest;
		if (currentTest != testMenu) {
			delete testMenu;
		}

	}

	// ImGui: Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}