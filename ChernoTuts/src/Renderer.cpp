#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

/*		GLCheckError
* Return the error ID, we need to convert to error to Hexadecimal, then go to glew.h and find that hex
* How to use:
* use "GLClearError()" before the function we need to check
* use "GLCheckError()" after the function we need to check
*/
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): "
			<< function << "\n in : " << file << " at line: " << line << std::endl;
		return false;
	}
	return true;
}