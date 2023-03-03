// Note to self: Review this file and optimize where possible in the future if needed
#include "Debugger.h"
#include <vector>

Debugger::Debugger() :
	model(1.0f)
{}

Debugger::~Debugger()
{}

void Debugger::Init(Camera& cam)
{
	m_shader.CreateProgram("res/Shaders/Debugger.vs", "res/Shaders/Debugger.fs");

	float vertices[9];

	// Configure buffers for debugger
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STREAM_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Debugger::DrawRay(glm::vec3& rayPos, glm::vec3& rayDir, Camera& cam)
{
	m_shader.ActivateProgram();



	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);

	m_shader.SetMat4("view", cam.GetViewMatrix());
	m_shader.SetMat4("projection", cam.GetProjectionMatrix());
	m_shader.SetMat4("model", model);

	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);

	m_shader.DeactivateProgram();
}