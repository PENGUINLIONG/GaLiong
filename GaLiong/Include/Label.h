#pragma once
#include "Preprocess.h"
#include "Font.h"
#include "Renderer.h"
#include "Entity.h"
#include "TextureBase.h"

_L_BEGIN
class TextureBase;

class _L_ Label : public Entity
{
	friend class TextEntity;
public:
	Label();
	bool AppendText(const wchar_t *text);
	inline void BindFont(Font &font)
	{
		this->font = &font;
		visible = available = true;
		ClearText();
	}
	virtual void BindTexture(TextureBase *texture){}
	bool ChangeText(const wchar_t *text)
	{
		if (!available)
			return false;

		ClearText();
		AppendText(text);
		return true;
	}
	inline void ClearText()
	{
		empty = true;
		text.clear();
		fontSize = { 0, 0 };
		ClearTextures();
	}
	virtual void Render() override;
	~Label();
private:
	bool available = false;
	bool empty = true;
	PointD fontPos;
	SizeD fontSize;
	wstring text = L"";
	Font *font = nullptr;
};
_L_END