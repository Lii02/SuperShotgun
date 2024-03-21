#include "FontGraphics.h"
#include "Wrapper.h"
#include "VAO.h"

static uint32_t font_vao, font_vbo;

void FontGraphics::Initialize()
{
	font_vao = Renderer_GenerateVAO();
	glGenBuffers(1, &font_vbo);
	Renderer_BindVAO(font_vao);
	glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Renderer_BindVAO(0);
}

void FontGraphics::Shutdown()
{
	glDeleteVertexArrays(1, &font_vao);
	glDeleteBuffers(1, &font_vbo);
}

float FontGraphics::CalculateWidth(FontData data, liString text, int kerning)
{
	float offset = 0;
	float output = 0;
	for (size_t i = 0; i < text.Length(); i++)
	{
		character_data_t& ch = (*data)[text[i]];
		float xpos = offset + ch.bearing.x;
		float w = ch.size.x;
		offset += (ch.advance >> kerning);
		output += xpos + w + offset;
	}
	return output;
}

void FontGraphics::DrawString(FontData data, liString text, int kerning)
{
	Renderer_BindVAO(font_vao);
	float offset = 0;
	for (size_t i = 0; i < text.Length(); i++)
	{
		character_data_t& ch = (*data)[text[i]];

		float xpos = offset + ch.bearing.x;
		float ypos = 0 - (ch.size.y - ch.bearing.y);

		float w = ch.size.x;
		float h = ch.size.y;
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		ch.texture->Bind();
		glBindBuffer(GL_ARRAY_BUFFER, font_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		offset += (ch.advance >> kerning);
		ch.texture->Unbind();
	}
	Renderer_BindVAO(0);
}