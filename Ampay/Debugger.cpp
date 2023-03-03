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

	glGenVertexArrays(1, &m_vao);//Esta función genera un identificador para un nuevo objeto de matriz de vértices
	glBindVertexArray(m_vao);//Esta función enlaza el objeto de matriz de vértices actual con el identificador especificado

	glGenBuffers(1, &m_vbo);//Esta función genera un identificador para un nuevo búfer de vértices
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);//Esta función enlaza el objeto de búfer de vértices actual con el identificador especificado
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STREAM_DRAW);//Esta función reserva y asigna memoria para el búfer de vértices actual
	glEnableVertexAttribArray(0);//Esta función habilita un atributo de vértice especificado por su índice. En este caso, habilita el atributo de vértice 0.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);//Esta función define cómo se deben interpretar los datos del búfer de vértices para un atributo de vértice específico

	glBindBuffer(GL_ARRAY_BUFFER, 0);//Esta función desenlaza el objeto de búfer de vértices actual.
	glBindVertexArray(0);//Esta función desenlaza el objeto de matriz de vértices actual.
}

void Debugger::DrawRay(glm::vec3& rayPos, glm::vec3& rayDir, Camera& cam)
{
	m_shader.ActivateProgram();

	float vertices[] = 
	{
		rayPos.x, rayPos.y, rayPos.z,
		rayPos.x, rayPos.y + 0.1f, rayPos.z,
		(rayDir.x * 50.0f) + rayPos.x, (rayDir.y * 50.0f) + rayPos.y, (rayDir.z * 50.0f) + rayPos.z
	};

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);//Esta función actualiza una parte del búfer de vértices actual con nuevos datos de vértices. La función toma como entrada el tipo de búfer, un desplazamiento en bytes desde el inicio del búfer, el tamaño de los datos a actualizar y un puntero a los nuevos datos.

	m_shader.SetMat4("view", cam.GetViewMatrix());//Esta función establece el valor de una variable de matriz uniforme en el programa de sombreado actualmente activo
	m_shader.SetMat4("projection", cam.GetProjectionMatrix());//Esta función establece el valor de una variable de matriz uniforme en el programa de sombreado actualmente activo
	m_shader.SetMat4("model", model);//Esta función establece el valor de una variable de matriz uniforme en el programa de sombreado actualmente activo

	glBindVertexArray(m_vao);//Esta función enlaza el objeto de matriz de vértices actual con el identificador especificado
	glDrawArrays(GL_TRIANGLES, 0, 3);//Esta función dibuja primitivas geométricas utilizando los datos del búfer de vértices actual
	glBindVertexArray(0);//Esta función desenlaza el objeto de matriz de vértices actual.

	m_shader.DeactivateProgram();//Esta función desactiva el programa de sombreado actualmente activo, lo que permite que otros programas de sombreado se activen en su lugar.
}