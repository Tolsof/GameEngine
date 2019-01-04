#pragma once
#include "GL\glew.h"
#include "../types/Renderable2D.h"

#define MAX_RENDER_OBJ 1000
#define COORD_VERTEX 3 // Float
#define TEXTURE_VERTEX 2 // Unsigned Int

#define VERTEX_DATA_SIZE (MAX_RENDER_OBJ * COORD_VERTEX * TEXTURE_VERTEX)
#define INDICES_LENGTH (MAX_RENDER_OBJ * 6)

// TODO: Clean this shit up a bit

struct BatchRender2D {
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

	unsigned int m_objectCount;

	GLenum m_drawType;

	float m_vertexData[VERTEX_DATA_SIZE];

	BatchRender2D(GLenum dType) {
		m_drawType = dType;
		m_objectCount = 0;
	}
};

struct Batcher2D {
	void load(BatchRender2D& b);
	void unload(BatchRender2D& b);

	void set(BatchRender2D b);
	void fill(BatchRender2D& b, Renderable2D r);
	void draw(BatchRender2D b);
	void clear(BatchRender2D& b);
};