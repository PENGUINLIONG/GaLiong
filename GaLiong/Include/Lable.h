#pragma once
#include "Preprocess.h"
#include "Entity.h"
#include "Font.h"
#include "Renderer.h"
#include "Texture.h"

_L_BEGIN
class _L_ Lable : public Entity
{
public:
	Lable();
	virtual void Render() override;
	virtual void BindTexture(TextureBase *texture){}
	inline void BindFont(Font &font)
	{
		this->font = &font;
		visible = available = true;
		Clear();
	}
	void AppendText(const wchar_t *text);
	void ChangeText(const wchar_t *text);
	inline void Clear()
	{
		empty = true;
		text = L"";
		fontSize = { 0, 0 };
		ClearTextures();
	}
	~Lable();
private:
	bool available = false, empty = true;
	SizeD fontSize;
	wstring text = L"";
	Font *font;
};
_L_END