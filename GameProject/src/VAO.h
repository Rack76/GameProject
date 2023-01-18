#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "glew.h"
#include "VBO.h"

class VAO
{
	public:
		GLuint ID;
		VAO()
		{
			glGenVertexArrays(1, &ID);
		}

		void LinkVBO(VBO& VBO, GLuint layout)
		{
			//VBO.Bind();
			glVertexAttribLPointer(layout, 3, GL_DOUBLE, 0, (void*)0);
			glEnableVertexAttribArray(layout);
			VBO.Unbind();
		}

		void Bind()
		{
			glBindVertexArray(ID);
		}

		void Unbind()
		{
			glBindVertexArray(0);
		}

		void Delete()
		{
			glDeleteVertexArrays(1, &ID);
		}
};

#endif // !VAO_CLASS_H

