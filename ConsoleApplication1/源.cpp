#include "Entrance.hpp"
#include <iostream>
#include <thread>
#include <tuple>
#include <locale>
#include <Windows.h>

#pragma comment(lib, "winmm.lib")

#pragma comment(lib, "GaLiong.lib")

using namespace std;
using namespace LiongStudio::GaLiong;

int main()
{
	ifstream stream, wavStream;

	Window window({ 1024, 768 });
	if (!window.Create())
		return 0;

	DWORD t0 = timeGetTime();

	//WAV wav(&wavStream);
	//wav.ReadData(L"F:\\assets\\live.wav");
	//WaveOut waveOut;
	//waveOut.Write(wav.GetSelected(), wav.GetSelectedLength(), wav.GetPCMFormat());

	TextureRef texture1 = ImageFormat::DetectAndRead(stream, L"F:\\assets\\yosemite.bmp");
	TextureRef texture2 = ImageFormat::DetectAndRead(stream, L"F:\\assets\\fuckphp.bmp");
	TextureRef texture3 = ImageFormat::DetectAndRead(stream, L"F:\\assets\\button.bmp");
	TextureRef texture4 = ImageFormat::DetectAndRead(stream, L"F:\\assets\\test5.png");
	TextureRef texture5 = ImageFormat::DetectAndRead(stream, L"F:\\assets\\border.png");
	auto texture6 = ImageFormat::DetectAndRead(stream, L"F:\\assets\\mavericks.bmp");

	Log << 1 << EndLog;
	Log << L"あいうえお" << EndLog;

	LibFreeType freetype;
	Font &font = *freetype.NewFont(L"F:\\assets\\msyhl.ttc");
	font.SetSizeAbsolute({ 0, 40 });
	font.SetColor({ 0xFF, 0xFF, 0xFF, 0xFF }, { 104, 33, 122, 0xFF });
	font.SetOutlineWidth(1.25);

	Character &c = *(Character *)(window.AppendEntity(new Character()));
	c.SwitchDisplayMode(Character::DisplayMode::Normal);
	c.SwitchFX(Character::FX::Normal);
	c.BindTexture(texture2);
	c.SetPosition({ -75, 50 });
	c.SetSize({ 60.0, 50.0 });

	Button &b = *(Button *)(window.AppendEntity(new Button()));
	b.BindTexture(texture3);
	b.SetPosition({ 0.0f, 40.0f });
	b.SetSize({ 20.0, 10.0 });

	b.BindFont(font);
	b.ChangeText(L"控件内文字");

	//Label &l = *(Label *)(window.AppendEntity(new Label()));
	//l.BindFont(font);
	//l.SetPosition({ 0, 20 });
	//l.SetSize({ 80.0, 80.0 });
	//l.AppendText(L"我有姿势我自豪");

	TextBar &tb = *(TextBar *)(window.AppendEntity(new TextBar()));
	tb.BindFont(font);
	tb.SetPosition({ 0, 20 });
	tb.SetSize({ 40.0, 20.0 });
	tb.SetTextSpeed(40);
	tb.BindTexture(texture6);
	tb.Border.BindTexture(texture5, Entity::BorderComment::EveryWhere);

	Log << L"Init time cost: " << (timeGetTime() - t0) << EndLog;

	window.Resize({ 1366, 768 });


	tb.AppendText(L"123456789123456789123456789");

	MSG message;
	while (true)
	{
		window.Clear();
		
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				break;
			else
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		Renderer::DrawTestImage();

		Renderer::DrawBackGroundImage(texture1);
		window.Render();

		window.Flush();
	}
	return 0;
}