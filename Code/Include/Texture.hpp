//
//  Texture.hpp
//  GaLiong
//
//  Created by Liong on ??/??/??.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "Preprocess.hpp"
#include "File.hpp"
#include "Image.hpp"

using namespace LiongFramework::Media;
using namespace LiongFramework::IO;

_L_BEGIN
namespace Graphic
{
	typedef unsigned int TextureIndex;
	
    class _L_ Texture
    {
    public:
		/*
		 * [for who is new to OpenGL]
		 * There are two types of filter usage of this enum:
		 * One is for the 'min filter' which is used when the rendered texture is smaller than the original one, represented by GL_TEXTURE_MIN_FILTER.
		 * Another is for the 'mag filter' which is used when the rendered texture is larger than the original one, represented by GL_TEXTURE_MAG_FILTER.
		 * The mip map is a optimization for rendering far objects. GL will make several copies of a image which is smaller in size. These copies are of priority, which means they will be used instead of the original one when the target position is farther than a specific distant.
		 * In some ways, the mip maps and the original image are  by a texture.
		 * [for who is new to OpenGL]
		 */
        enum Filter
        {
            Nearest = GL_NEAREST,
            Linear = GL_LINEAR,
			// The following items are for min filter only.
			NearestWithNearestMipmap = GL_NEAREST_MIPMAP_NEAREST,
			NearestWithLinearMipmap = GL_NEAREST_MIPMAP_LINEAR,
			LinearWithNearestMipmap = GL_LINEAR_MIPMAP_NEAREST,
			LinearWithLinearMipmap = GL_NEAREST_MIPMAP_LINEAR
        };

		Texture(unsigned int count = 1);
		Texture(Filter magFilter, Filter minFilter, unsigned int count = 1);
        ~Texture();
		
		unsigned int GetIndex(unsigned int position);
		void SetMagFilter(Filter filter, unsigned int position);
		void SetMinFilter(Filter filter, unsigned int position);
		/*
		 * Update image data to texture of the specified position.
		 */
		void Update(Image& image, unsigned int position = 0);
		
		// Static
		
		static Texture FromFile(wstring& path);
    private:
		unsigned int _Count;
		TextureIndex* _Index;
		Filter _MagFilter, _MinFilter;
    };

    typedef shared_ptr<Texture> TextureStrongRef;
    typedef weak_ptr<Texture> TextureRef;

    struct TextureComponent
    {
        Rect Rect;
        Texture *Texture;
    };
}
_L_END
#endif