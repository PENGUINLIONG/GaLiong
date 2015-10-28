//
//  MemoryStream.cpp
//  GaLiong
//
//  Created by Liong on 15/10/25.
//

#include "MemoryStream.hpp"

_L_BEGIN
namespace IO
{
	MemoryStream::MemoryStream()
	: _Size(DEFAULT_BUFFER_CHUNK_SIZE)
	, _Position(0)
	, _Buffer(::new Byte[DEFAULT_BUFFER_CHUNK_SIZE])
	, _Permission(StreamAccessPermission::ReadWrite)
	, _ShouldDeleteBuffer(true)
	{
	}
	MemoryStream::MemoryStream(MemoryStream& instance)
	: _Size(instance._Size)
	, _Position(instance._Position)
	, _Buffer(instance._Buffer)
	, _Permission(instance._Permission)
	, _ShouldDeleteBuffer(false)
	{
	}
	MemoryStream::MemoryStream(StreamAccessPermission permission)
	: _Size(DEFAULT_BUFFER_CHUNK_SIZE)
	, _Position(0)
	, _Buffer(::new Byte[DEFAULT_BUFFER_CHUNK_SIZE])
	, _Permission(permission)
	, _ShouldDeleteBuffer((true))
	{
	}
	MemoryStream::MemoryStream(Buffer buffer, BufferLength length)
	: _Size(length)
	, _Position(0)
	, _Buffer(buffer)
	, _Permission(StreamAccessPermission::ReadWrite)
	, _ShouldDeleteBuffer(false)
	{
	}
	MemoryStream::MemoryStream(Buffer buffer, BufferLength length, StreamAccessPermission permission)
	: _Size(length)
	, _Position(0)
	, _Buffer(buffer)
	, _Permission(permission)
	, _ShouldDeleteBuffer(false)
	{
	}
	
	MemoryStream::~MemoryStream()
	{
		Close();
	}
	
	Buffer MemoryStream::Abandon()
	{
		_ShouldDeleteBuffer = false;
		return _Buffer;
	}
	
	bool MemoryStream::CanRead()
	{
		return _Permission != StreamAccessPermission::WriteOnly || _IsClosed;
	}
	
	bool MemoryStream::CanWrite()
	{
		return _Permission != StreamAccessPermission::ReadOnly || _IsClosed;
	}
	
	bool MemoryStream::CanSeek()
	{
		return _IsClosed;
	}
	
	void MemoryStream::Close()
	{
		if (!_IsClosed)
		{
			_IsClosed = true;

			if (_ShouldDeleteBuffer && _IsClosed)
				::delete [] _Buffer;
		}
	}
	
	void MemoryStream::CopyTo(ostream stream)
	{
		stream.write(_Buffer + _Position, _Size - _Position);
	}
	void MemoryStream::CopyTo(ostream stream, BufferLength length)
	{
		long available = _Size - _Position;
		stream.write(_Buffer + _Position, length > available ? available : length);
	}
	
	void MemoryStream::Flush()
	{
	}
	
	long MemoryStream::GetCapacity()
	{
		return _Size;
	}
	
	BufferLength MemoryStream::GetLength()
	{
		return _Size;
	}
	
	long MemoryStream::GetPosition()
	{
		return _Position;
	}
	
	bool MemoryStream::IsEndOfStream()
	{
		return _Size == _Position + 1;
	}
	
	Buffer MemoryStream::Read(BufferLength length)
	{
		Buffer buffer = new Byte[length];
		Read(buffer, length);
		return buffer;
	}
	
	void MemoryStream::Read(Buffer buffer, BufferLength length)
	{
		// If available data is less than which is requested, just copy the available part.
		BufferLength available = length > (_Size - _Position) ? (_Size - _Position) : length;
		memcpy(buffer, _Buffer, available);
	}
	
	Byte MemoryStream::ReadByte()
	{
		return _Buffer[_Position++];
	}
	
	void MemoryStream::Seek(long distance, LiongFramework::IO::SeekOrigin position)
	{
		
		switch (position)
		{
			case SeekOrigin::Begin:
				_Position = 0;
				break;
			case SeekOrigin::Current:
				break;
			case SeekOrigin::End:
				_Position = _Size - 1;
				break;
			default:
				break;
		}
		_Position += distance;
		
		if (_Position < 0)
			_Position = 0;
		else if (_Position >= _Size)
			_Position = _Size - 1;
	}
	
	bool MemoryStream::SetCapacity(long capacity)
	{
		if (!_ShouldDeleteBuffer)
			return false;
		
		if (capacity > _Size) // Need to reallocate.
		{
			Buffer newBuffer = ::new Byte[capacity];
			memcpy(newBuffer, _Buffer, _Size);
		}
		_Size = capacity; // Reset capacity.
		
		return true;
	}
	
	long MemoryStream::Write(Buffer data, BufferLength length)
	{
		if (length > _Size - _Position)
			length = _Size - _Position;
		memcpy(_Buffer + _Position, data, length);
		return length;
	}
	
	bool MemoryStream::WriteByte(Byte data)
	{
		if (IsEndOfStream())
			return false;
		
		_Buffer[_Position++] = data;
		return true;
	}
}

_L_END