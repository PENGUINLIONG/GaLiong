#include "Storage.hpp"

_L_BEGIN
Storage::Storage()
{
}

void Storage::Open(char *path)
{
	if (Exists())
	{
		stream.open(path, stream.binary);
		if (stream.is_open())
		{
			this->path = path;
			//return IO_Fine;
		}
		//else return IO_StreamFailure;
	}
	//else return IO_FileNoFound;
}

void Storage::Read(char *buffer, int length)
{
	if (stream)	stream.read(buffer, length);
}

void Storage::Write(char *buffer, int length)
{
	if (stream) stream.write(buffer, length);
}

bool Storage::Exists()
{
	stream.open(path);
	if (stream) { stream.close(); return true; }
	else return false;
}

void Storage::Create(char *path)
{
	if (!Exists())
	{
		stream.open(path, stream.binary);
		stream.close();
	}
	//if (stream.good()) return IO_Fine;
	//else return IO_StreamFailure;
}

void Storage::Close()
{
	if (stream) stream.close();
}

Storage::~Storage()
{
	Close();
}
_L_END
