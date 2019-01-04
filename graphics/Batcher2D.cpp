#include "BatchRender.h"
#include <iostream>

void Batcher2D::load(BatchRender2D& b) {
	unsigned int indices[INDICES_LENGTH];
	// Fill ibo data
	unsigned int offset = 0;
	for (unsigned int i = 0; i < INDICES_LENGTH; i += 6) {
		indices[i] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset;

		offset += 4;
	}
	glGenVertexArrays(1, &b.m_vao);
	glBindVertexArray(b.m_vao);

	glGenBuffers(1, &b.m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, b.m_vbo);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_DATA_SIZE, 0, b.m_drawType);

	// TODO: Automate
	// Coord vertex pointer
	glVertexAttribPointer(
		0,
		COORD_VERTEX,
		GL_FLOAT,
		GL_FALSE,
		COORD_VERTEX * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	// Texture vertex pointer
	//glVertexAttribPointer(
	//	1,
	//	2,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	5 * sizeof(float),
	//	(const void*)COORD_VERTEX * sizeof(float)
	//);
	//glEnableVertexAttribArray(1);

	glGenBuffers(1, &b.m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, b.m_drawType);
}

void Batcher2D::set(BatchRender2D b) {
	glBindVertexArray(b.m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, b.m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.m_ibo);
}

void Batcher2D::fill(BatchRender2D& b, Renderable2D r) {
	float vertices[] = {
		r.m_posX, r.m_posY, 0.0f,
		(r.m_posX + r.m_width), r.m_posY, 0.0f,
		(r.m_posX + r.m_width), (r.m_posY + r.m_height), 0.0f,
		r.m_posX, (r.m_posY + r.m_height), 0.0f
	};

	glBufferSubData(GL_ARRAY_BUFFER,
		sizeof(vertices) * b.m_objectCount,
		sizeof(vertices), vertices);

	b.m_objectCount++;
}

void Batcher2D::draw(BatchRender2D b) {
	// bind shader
	glDrawElements(GL_TRIANGLES, b.m_objectCount * 6, GL_UNSIGNED_INT, 0);
}

void Batcher2D::clear(BatchRender2D& b) {
	glBindBuffer(GL_ARRAY_BUFFER, b.m_vbo);
	glBufferData(GL_ARRAY_BUFFER, VERTEX_DATA_SIZE, 0, b.m_drawType);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	b.m_objectCount = 0;
}