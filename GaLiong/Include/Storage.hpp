#pragma once
#include "Preprocess.hpp"

_L_BEGIN
class _L_ Storage
{
public:
	Storage();
	void Open(char *path);
	void Read(char *buffer, int length);
	void Write(char *buffer, int length);
	bool Exists();
	void Create(char *path);
	void Close();
	~Storage();
protected:
	char *path = nullptr;
	fstream stream;
};
_L_END
