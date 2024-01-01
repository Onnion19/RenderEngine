#include "OpenGl/VertexAttributeObject.h"




Renderer::GL::VertexAtributeObject::VertexAtributeObject()
{
	glGenVertexArrays(1, &id);
}

Renderer::GL::VertexAtributeObject::~VertexAtributeObject()
{
	glDeleteVertexArrays(1, &id);
}

void Renderer::GL::VertexAtributeObject::Bind()
{
	glBindVertexArray(id);
}

void Renderer::GL::VertexAtributeObject::Unbind()
{
	glBindVertexArray(0);
}


void Renderer::GL::VertexAtributeObject::Enable(uint8 attributeID)
{
	Bind();
	glEnableVertexAttribArray(attributeID);
}

void Renderer::GL::VertexAtributeObject::Disable(uint8 attributeID)
{
	Bind();
	glDisableVertexAttribArray(attributeID);
}

