#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "TestTexture2D.h"

namespace test {

	TestTexture2D::TestTexture2D()
		: m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0)
	{
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

	    glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		
		// 1. Vertex Array
		m_VAO = std::make_unique<VertexArray>();
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		// 2. Index Buffers
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		// Model View Projection Matrices
		// m_Proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		// m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		// 3. Shader
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		// Uniforms
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


		// Texture
		m_Texture = std::make_unique<Texture>("res/textures/ChernoLogo.png");
		m_Shader->SetUniform1i("u_Texture", 0);

	}

	TestTexture2D::~TestTexture2D()
	{
	}
    
	void TestTexture2D::OnUpdate(float deltaTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;

		m_Texture->Bind();

		{
			// shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp); // Model View Projection Matrix

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}

		// Draw the 2nd Object
		{
			// shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp); // Model View Projection Matrix

			renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("translation A", &m_TranslationA.x, 0.0f, 960.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat3("translation B", &m_TranslationB.x, 0.0f, 960.0f);  // Edit 1 float using a slider from 0.0f to 1.0f

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
