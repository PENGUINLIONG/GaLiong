#pragma once
#include "Preprocess.h"
#include "Entity.h"
#include "Font.h"
#include "Renderer.h"
#include "Texture.h"

_L_BEGIN
class _L_ Label : public Entity
{
public:
	Label();
	virtual void Render() override;
	virtual void BindTexture(TextureBase *texture){}
	inline void BindFont(Font &font)
	{
		this->font = &font;
		visible = available = true;
		Clear();
	}
	bool AppendText(const wchar_t *text);
	bool ChangeText(const wchar_t *text);
	inline void Clear()
	{
		empty = true;
		text.clear();
		fontSize = { 0, 0 };
		ClearTextures();
	}
	~Label();
private:
	bool available = false, empty = true;
	SizeD fontSize;
	wstring text = L"";
	Font *font;
};
_L_END