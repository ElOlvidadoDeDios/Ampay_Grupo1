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

	glGenVertexArrays(1, &m_vao);//Esta funci�n genera un identificador para un nuevo objeto de matriz de v�rtices
	glBindVertexArray(m_vao);//Esta funci�n enlaza el objeto de matriz de v�rtices actual con el identificador especificado

	glGenBuffers(1, &m_vbo);//Esta funci�n genera un identificador para un nuevo b�fer de v�rtices
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);//Esta funci�n enlaza el objeto de b�fer de v�rtices actual con el identificador especificado
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STREAM_DRAW);//Esta funci�n reserva y asigna memoria para el b�fer de v�rtices actual
	glEnableVertexAttribArray(0);//Esta funci�n habilita un atributo de v�rtice especificado por su �ndice. En este caso, habilita el atributo de v�rtice 0.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);//Esta funci�n define c�mo se deben interpretar los datos del b�fer de v�rtices para un atributo de v�rtice espec�fico

	glBindBuffer(GL_ARRAY_BUFFER, 0);//Esta funci�n desenlaza el objeto de b�fer de v�rtices actual.
	glBindVertexArray(0);//Esta funci�n desenlaza el objeto de matriz de v�rtices actual.
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

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);//Esta funci�n actualiza una parte del b�fer de v�rtices actual con nuevos datos de v�rtices. La funci�n toma como entrada el tipo de b�fer, un desplazamiento en bytes desde el inicio del b�fer, el tama�o de los datos a actualizar y un puntero a los nuevos datos.

	m_shader.SetMat4("view", cam.GetViewMatrix());//Esta funci�n establece el valor de una variable de matriz uniforme en el programa de sombreado actualmente activo
	m_shader.SetMat4("projection", cam.GetProjectionMatrix());//Esta funci�n establece el valor de una variable de matriz uniforme en el programa de sombreado actualmente activo
	m_shader.SetMat4("model", model);//Esta funci�n establece el valor de una variable de matriz uniforme en el programa de sombreado actualmente activo

	glBindVertexArray(m_vao);//Esta funci�n enlaza el objeto de matriz de v�rtices actual con el identificador especificado
	glDrawArrays(GL_TRIANGLES, 0, 3);//Esta funci�n dibuja primitivas geom�tricas utilizando los datos del b�fer de v�rtices actual
	glBindVertexArray(0);//Esta funci�n desenlaza el objeto de matriz de v�rtices actual.

	m_shader.DeactivateProgram();//Esta funci�n desactiva el programa de sombreado actualmente activo, lo que permite que otros programas de sombreado se activen en su lugar.
}