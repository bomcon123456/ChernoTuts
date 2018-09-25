#include "Texture.h"

#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path) :
	m_RendererID(0),m_FilePath(path), m_LocalBuffer(nullptr),
	m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	// stbi_load will write in the Width/Height/BPP variable
	// 4 is number of color channel we want to write (in this case : R/G/B/A)
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	GLCall(glGenTextures(1, &m_RendererID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

	/* MUST DEFINE AT LEAST THESE 4 PARAMS OR WILL GET A BLACK IMAGE*/
	// GL_TEXTURE_MIN_FILTER: if textures needs to be rendered smaller. (minifying)
	// GL_TEXTURE_MAG_FILTER: if textures needs to be rendered larger. (magnifying)
	// GL_LINEAR: linearly resample anything
	// GL_TEXTURE_WRAP_S: wrap horizontally
	// GL_TEXTURE_WRAP_T: wrap vertically
	// GL_CLAMP: not extend the area
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// Give OPENGL the data above in m_LocalBuffer
	// internalformat: how openGL will store the data
	// format: what format that we provided to openGL (in the LocalBuffer)
	// rga"8" -> 8bits per channel
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

}
