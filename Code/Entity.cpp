#include "Entity.hpp"

_L_BEGIN
Entity::Entity() : pos({ 0.0f, 0.0f }), size({ 0.0f, 0.0f }), Border(pos, size)
{
	Render += Entity_Render;
	Resize += Entity_Resize;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	MouseHover += [](void *sender, MouseEventArgs e) {
		Log << L"Hovered! At (" << e.Location.X << L", " << e.Location.Y << L")" << EndLog;
	};
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
}

Entity::~Entity()
{
	ClearTextures();
}

void Entity::BindTexture(TextureRef texture)
{
	if (texture.expired() || !texture.lock()->GetIndex())
		return;
	textures.push_back(texture);
}

void Entity::ClearTextures()
{
	if (textures.empty())
		return;
	textures.clear();
}

bool Entity::IsHover(PointD point)
{
	if (point.X < pos.X ||
		point.Y > pos.Y ||
		point.X > pos.X + size.Width ||
		point.Y < pos.Y - size.Height)
		return false;

	for (const TextureRef &texture : textures)
	{
		if (texture.expired())
		{
			Texture *targetPtr = texture.lock().get();
			textures.remove_if([targetPtr](TextureRef &texture){ return texture.lock().get() == targetPtr; });
			continue;
		}

		lock_guard<recursive_mutex> lock(texture.lock()->occupy);

		TextureStrongRef ref = texture.lock();
		if (!ref->IsInformative())
			continue;
		if (ref->SameType(Texture::PixelFormat::Ignore))
		{
			if (ref->SameType(Texture::PixelFormat::BGR) ||
				ref->SameType(Texture::PixelFormat::RGB))
				return true;
			else if (ref->SameType(Texture::PixelFormat::RGBA))
			{
				// Calculate the offset to the pixel and check the alpha.
				const Byte pixelLength = ref->GetPixelLength();
				const Size &textureSize = ref->GetSize();

				switch (pixelLength)
				{
					case 4: // Maybe I should optimize this progress?
					{
								Size offset =
								{
									static_cast<long>((point.X - pos.X) / size.Width * textureSize.Width), // X offset.
									-static_cast<long>((point.Y - pos.Y) / size.Height * textureSize.Height) // Y offset
								};
								if (*(ref->GetData() + ((offset.Width + (textureSize.Height - offset.Height) * textureSize.Width) << 2) + 3))
									return true;
								break;
					}
						// Be compatible with 16-bit depth pixel later.

						//case 8:
						//	if (*reinterpret_cast<Byte2 *>(ref->GetData() + ((point.X - x0) + (point.Y - y0) * ref->GetSize().Width) * pixelLength + 6))
						//		return true;
					default:
						break;
				}
			}
		}
	}
	return false;
}

void Entity::SetPosition(PointD position)
{
	pos = position;
}

void Entity::Entity_Render(void *sender, EventArgs e)
{
	if (!_Visible)
		return;

	if (textures.empty())
	{
		Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
		return;
	}

	for (const TextureRef &texture : textures) // The order to render the textures is to
	{
		if (texture.expired())
		{
			Texture *targetPtr = texture.lock().get();
			textures.remove_if([targetPtr](TextureRef &texture){return texture.lock().get() == targetPtr; });
			continue;
		}
		lock_guard<recursive_mutex> lock(texture.lock()->occupy);
		
		Renderer::DrawRectangle(texture.lock()->GetIndex(), { pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
	}
	Border.Render(this, e);
}

void Entity::Entity_Resize(void *sender, ResizeEventArgs e)
{
	Border.Resize(this, e);
}

void Entity::SetWindowSize(Size *windowSize)
{
	ControlBase::SetWindowSize(windowSize);
	Border.SetWindowSize(windowSize);
}

Entity::BorderImpl::BorderImpl(PointD &pos, SizeD &size) : pos(pos), size(size)
{
	for (auto &texture : textures)
	{
		texture = { TextureRef(), Renderer::ReverseMethod::None, { 0.0, 0.0, 0.0, 0.0 }, BorderComment::NoComment, { 0.0, 0.0 } };
	}
}

Entity::BorderImpl::~BorderImpl()
{
}

void Entity::BorderImpl::BindTexture(TextureRef texture, const Flag comment)
{
	if (texture.expired())
		return;
	TextureStrongRef ref = texture.lock();
	if (!ref->GetIndex() || !comment)
		return;
	Size _s = ref->GetSize();
	SizeD size_Texture = { ((double)_s.Width / (double)windowSize->Height) * 100.0, ((double)_s.Height / (double)windowSize->Height) * 100.0 };
	Size size_Control = { (long)((this->size.Width / 100.0) * windowSize->Height), (long)((this->size.Height / 100.0) * windowSize->Height) };

	ref->ChangeFilter(Texture::Filter::Nearest);

#define LEFT 0
#define TOP 1
#define RIGHT 2
#define BOTTOM 3
	if (comment & BorderComment::EveryBorder)
	{
		if (comment & BorderComment::EveryBorder == BorderComment::EveryBorder)
		{
			textures[LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y, pos.X, pos.Y - size.Height }, comment, { 1.0, ref->CalculateDuplication(size_Control).Height } };
			textures[TOP] = { texture, Renderer::ReverseMethod::None, { pos.X, pos.Y + size_Texture.Height, pos.X + size.Width + size_Texture.Width, pos.Y }, comment, { ref->CalculateDuplication(size_Control).Width, 1.0 } };
			textures[RIGHT] = { texture, Renderer::ReverseMethod::Horizontal, { pos.X + size.Width, pos.Y, pos.X + size.Width + size_Texture.Width, pos.Y - size.Height }, comment, { 1.0, ref->CalculateDuplication(size_Control).Height } };
			textures[BOTTOM] = { texture, Renderer::ReverseMethod::Vertical, { pos.X, pos.Y - size.Height, pos.X + size.Width, pos.Y - size.Height - size_Texture.Height }, comment, { ref->CalculateDuplication(size_Control).Width, 1.0 } };
			goto _;
		}
		if (comment & BorderComment::Left)
			textures[LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y, pos.X, pos.Y - size.Height }, comment, { 1.0, ref->CalculateDuplication(size_Control).Height } };
		if (comment & BorderComment::Top)
			textures[TOP] = { texture, Renderer::ReverseMethod::None, { pos.X, pos.Y + size_Texture.Height, pos.X + size.Width + size_Texture.Width, pos.Y }, comment, { ref->CalculateDuplication(size_Control).Width, 1.0 } };
		if (comment & BorderComment::Right)
			textures[RIGHT] = { texture, Renderer::ReverseMethod::None, { pos.X + size.Width, pos.Y, pos.X + size.Width + size_Texture.Width, pos.Y - size.Height }, comment, { 1.0, ref->CalculateDuplication(size_Control).Height } };
		if (comment & BorderComment::Bottom)
			textures[BOTTOM] = { texture, Renderer::ReverseMethod::None, { pos.X, pos.Y - size.Height, pos.X + size.Width, pos.Y - size.Height - size_Texture.Height }, comment, { ref->CalculateDuplication(size_Control).Width, 1.0 } };
	}
#undef LEFT
#undef TOP
#undef RIGHT
#undef BOTTOM
_:
#define UPPER_LEFT 4
#define UPPER_RIGHT 5
#define LOWER_LEFT 6
#define LOWER_RIGHT 7
	if (comment & BorderComment::EveryCorner)
	{
		if (comment & BorderComment::EveryCorner == BorderComment::EveryCorner)
		{
			textures[UPPER_LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y + size_Texture.Height, pos.X, pos.Y }, comment, { 1.0, 1.0 } };
			textures[UPPER_RIGHT] = { texture, Renderer::ReverseMethod::Horizontal, { pos.X + size.Width, pos.Y + size_Texture.Height, pos.X + size.Width + size_Texture.Width, pos.Y }, comment, { 1.0, 1.0 } };
			textures[LOWER_LEFT] = { texture, Renderer::ReverseMethod::Vertical, { pos.X - size_Texture.Width, pos.Y - size.Height, pos.X, pos.Y - size.Height - size_Texture.Height }, comment, { 1.0, 1.0 } };
			textures[LOWER_RIGHT] = { texture, Renderer::ReverseMethod::BothDirection, { pos.X + size.Width, pos.Y - size.Height, pos.X + size.Width + size_Texture.Width, pos.Y - size.Height - size_Texture.Height }, comment, { 1.0, 1.0 } };
			return;
		}
		if (comment & BorderComment::UpperLeft)
			textures[UPPER_LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y - size_Texture.Height, pos.X, pos.Y }, comment, { 1.0, 1.0 } };
		if (comment & BorderComment::UpperRight)
			textures[UPPER_RIGHT] = { texture, Renderer::ReverseMethod::None, { pos.X + size.Width, pos.Y - size_Texture.Height, pos.X + size.Width + size_Texture.Width, pos.Y }, comment, { 1.0, 1.0 } };
		if (comment & BorderComment::LowerLeft)
			textures[LOWER_LEFT] = { texture, Renderer::ReverseMethod::None, { pos.X - size_Texture.Width, pos.Y - size.Height, pos.X, pos.Y - size.Height - size_Texture.Height }, comment, { 1.0, 1.0 } };
		if (comment & BorderComment::LowerRight)
			textures[LOWER_RIGHT] = { texture, Renderer::ReverseMethod::None, { pos.X + size.Width, pos.Y - size.Height, pos.X + size.Width + size_Texture.Width, pos.Y - size.Height - size_Texture.Height }, comment, { 1.0, 1.0 } };
	}
#undef UPPER_LEFT
#undef UPPER_RIGHT
#undef LOWER_LEFT
#undef LOWER_RIGHT
}

void Entity::BorderImpl::BorderImpl_Render(void *sender, EventArgs e)
{
	if (textures.empty())
	{
		Renderer::DrawWithoutTexture({ pos.X, pos.Y, pos.X + size.Width, pos.Y - size.Height });
		return;
	}

	for (auto &texture : textures)
	{
		if (!texture.Texture.expired())
			Renderer::DrawRectangle(texture.Texture.lock()->GetIndex(),
			texture.Rect,
			texture.ReverseMethod,
			texture.TextureDuplication);
		else
			texture = { TextureRef(), Renderer::ReverseMethod::None, { 0.0, 0.0, 0.0, 0.0 }, BorderComment::NoComment, { 0.0, 0.0 } };
	}
}

void Entity::BorderImpl::BorderImpl_Resize(void *sender, ResizeEventArgs e)
{
	for (auto &texture : textures)
	{
		if (!texture.Texture.expired())
		{
			lock_guard<recursive_mutex> lock(texture.Texture.lock()->occupy);

			BindTexture(texture.Texture, texture.Comment);
		}
	}
}
_L_END