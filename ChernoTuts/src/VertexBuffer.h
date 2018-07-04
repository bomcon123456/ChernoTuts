#pragma once

class VertexBuffer
{
private:
	// Make an ID for VertexBuffer just like other stuff that OpenGL use ID.
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
