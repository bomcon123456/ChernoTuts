#pragma once

//"size" => byte	(eg: 2*3*sizeof(float))
//"count" => element count (# of sth)

class IndexBuffer
{
private:
	// Make an ID for VertexBuffer just like other stuff that OpenGL use ID.
	unsigned int m_RendererID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};
