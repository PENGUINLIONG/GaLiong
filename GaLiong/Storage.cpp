#include "Storage.h"

_L_BEGIN
Storage::Storage()
{
}

void Storage::Open(char *path)
{
	if (Exists())
	{
		stream.open(path, stream.binary | stream._Nocreate | stream._Noreplace);
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
	stream.open(path, _IOS_Nocreate | _IOS_Noreplace);
	if (stream) { stream.close(); return true; }
	else return false;
}

void Storage::Create(char *path)
{
	if (!Exists())
	{
		stream.open(path, _IOSbinary);
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
