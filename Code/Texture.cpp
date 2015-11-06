#include "Include/Texture.hpp"

_L_BEGIN
namespace Graphic
{
	Texture::Texture(unsigned int count)
	: _Count(count)
	, _Index(::new TextureIndex[count])
	, _MagFilter(Filter::Linear)
	, _MinFilter(Filter::Linear)
	{
		glGenTextures(count, _Index);
		while (count > 0)
		{
			--count;
			glBindTexture(GL_TEXTURE_2D, _Index[count]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter::Linear);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter::Linear);
		}
	}
	Texture::Texture(Filter magFilter, Filter minFilter, unsigned int count)
	: _Count(count)
	, _Index(::new unsigned int[count])
	, _MagFilter(magFilter)
	, _MinFilter(minFilter)
	{
		glGenTextures(count, _Index);
		while (count > 0)
		{
			--count;
			glBindTexture(GL_TEXTURE_2D, _Index[count]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		}
	}
	Texture::~Texture()
	{
		glDeleteTextures(_Count, _Index);
		delete [] _Index;
	}
	
	TextureIndex Texture::GetIndex(unsigned int position)
	{
		return _Index[position];
	}

	void Texture::SetMagFilter(Filter filter, unsigned int position)
	{
		glBindTexture(GL_TEXTURE_2D, _Index[position]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	}
	
	void Texture::SetMinFilter(Filter filter, unsigned int position)
	{
		glBindTexture(GL_TEXTURE_2D, _Index[position]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	}

	void Texture::Update(Image& image, unsigned int position)
	{
		Buffer buffer = image.Interpret(PixelType::Rgba);
		glBindTexture(GL_TEXTURE_2D, _Index[position]);
		//gluBuild2DMipmapsIO_TEXTURE_2D, 3, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data); // Cannot work properly.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)image.GetSize().Width, (GLsizei)image.GetSize().Height, 0, GL_RGBA, GL_BYTE, buffer); // Alternative.
		::delete [] buffer;
	}
	
	// Static
	
	Texture Texture::FromFile(wstring& path)
	{
		switch(File::Detect(path.c_str()))
		{
			case FileFormat::Bmp:
		}
	}
}
_L_END