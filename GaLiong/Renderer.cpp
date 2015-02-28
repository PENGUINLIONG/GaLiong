#include "Renderer.h"

_L_BEGIN
#define UPPER_LEFT 0.0f, textureCoord.Height
#define LOWER_LEFT 0.0f, 0.0f
#define UPPER_RIGHT textureCoord.Width, textureCoord.Height
#define LOWER_RIGHT textureCoord.Width, 0.0f

void Renderer::DrawRectangle(TextureIndex textureID, RectD rect, ReverseMethod reverseMethod, SizeD textureCoord)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBegin(GL_QUADS);
	switch (reverseMethod)
	{
		case ReverseMethod::None:
			glTexCoord2f(UPPER_LEFT);  glVertex2d(rect.Left, rect.Top);
			glTexCoord2f(LOWER_LEFT);  glVertex2d(rect.Left, rect.Bottom);
			glTexCoord2f(LOWER_RIGHT); glVertex2d(rect.Right, rect.Bottom);
			glTexCoord2f(UPPER_RIGHT); glVertex2d(rect.Right, rect.Top);
			break;
		case ReverseMethod::Vertical:
			glTexCoord2f(LOWER_LEFT);  glVertex2d(rect.Left, rect.Top);
			glTexCoord2f(UPPER_LEFT);  glVertex2d(rect.Left, rect.Bottom);
			glTexCoord2f(UPPER_RIGHT); glVertex2d(rect.Right, rect.Bottom);
			glTexCoord2f(LOWER_RIGHT); glVertex2d(rect.Right, rect.Top);
			break;
		case ReverseMethod::Horizontal:
			glTexCoord2f(UPPER_RIGHT); glVertex2d(rect.Left, rect.Top);
			glTexCoord2f(LOWER_RIGHT); glVertex2d(rect.Left, rect.Bottom);
			glTexCoord2f(LOWER_LEFT);  glVertex2d(rect.Right, rect.Bottom);
			glTexCoord2f(UPPER_LEFT);  glVertex2d(rect.Right, rect.Top);
			break;
		case ReverseMethod::BothDirection:
			glTexCoord2f(LOWER_RIGHT); glVertex2d(rect.Left, rect.Top);
			glTexCoord2f(UPPER_RIGHT); glVertex2d(rect.Left, rect.Bottom);
			glTexCoord2f(UPPER_LEFT);  glVertex2d(rect.Right, rect.Bottom);
			glTexCoord2f(LOWER_LEFT);  glVertex2d(rect.Right, rect.Top);
			break;
		default:
			break;
	}
	glEnd();
}

void Renderer::DrawBackGroundImage(TextureRef texture)
{
	TextureStrongRef ref = texture.lock();
	Size size = ref->GetSize();
	double &&ratio = (double)size.Width / (double)size.Height;
	DrawRectangle(ref->GetIndex(), { ratio * -50.0f, 50, ratio * 50.0f, -50.0f });
}

void Renderer::DrawWithoutTexture(RectD rect)
{
	glColor3ub(229, 229, 229);
	glBegin(GL_QUADS);
	{
		glVertex2d(rect.Left, rect.Top);
		glVertex2d(rect.Left, rect.Bottom);
		glVertex2d(rect.Right, rect.Bottom);
		glVertex2d(rect.Right, rect.Top);
	}
	glEnd();

	glColor3ub(153, 153, 153);
	glBegin(GL_LINE_STRIP);
	{
		glVertex2d(rect.Left, rect.Top);
		glVertex2d(rect.Left, rect.Bottom);
		glVertex2d(rect.Right, rect.Bottom);
		glVertex2d(rect.Right, rect.Top);
		glVertex2d(rect.Left, rect.Top);
	}
	glEnd();

	glBegin(GL_LINES);
	{
		glVertex2d(rect.Left, rect.Top);
		glVertex2d(rect.Right, rect.Bottom);
		glVertex2d(rect.Right, rect.Top);
		glVertex2d(rect.Left, rect.Bottom);
	}
	glEnd();
	glColor4ub(255, 255, 255, 255);
}

void Renderer::DrawTestImage()
{
	glDisable(GL_TEXTURE_2D);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glBegin(GL_QUADS);
	{
		glColor3ub(0, 188, 242);

		glVertex2f(-26.0f, 16.0f);
		glVertex2f(-26.0f, -16.0f);
		glVertex2f(26.0f, -26.0f);
		glVertex2f(26.0f, 26.0f);

		glColor3f(0.9f, 0.9f, 0.9f);

		glVertex2f(-4.0f, 26.0f);
		glVertex2f(-4.0f, -26.0f);
		glVertex2f(-2.0f, -26.0f);
		glVertex2f(-2.0f, 26.0f);

		glVertex2f(-26.0f, 1.0f);
		glVertex2f(-26.0f, -1.0f);
		glVertex2f(26.0f, -1.0f);
		glVertex2f(26.0f, 1.0f);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glColor4ub(255, 255, 255, 255);
}

#undef UPPER_LEFT
#undef LOWER_LEFT
#undef UPPER_RIGHT
#undef LOWER_RIGHT
_L_END