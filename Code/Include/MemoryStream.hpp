//
//  Stream.h
//  GaLiong
//
//  Created by Liong on 15/10/25.
//

#include "Preprocess.hpp"
#include "IOException.hpp"

#ifndef MemoryStream_h
#define MemoryStream_h

_L_BEGIN
namespace IO
{
	enum SeekOrigin
	{
		Begin,
		Current,
		End
	};
	
	enum StreamAccessPermission
	{
		ReadOnly,
		WriteOnly,
		ReadWrite
	};
	
	class _L_ MemoryStream
	{
	public:
		MemoryStream();
        MemoryStream(MemoryStream& stream);
        MemoryStream(StreamAccessPermission permission);
		MemoryStream(Buffer buffer, BufferLength length);
		MemoryStream(Buffer buffer, BufferLength length, StreamAccessPermission permission);
        ~MemoryStream();
		
		/*
		 * The management of buffer will be abandoned.
		 * [return] A pointer to the buffer.
		 * [warning] You should delete the pointer when you will not it anymore.
		 */
		Buffer Abandon();
        bool CanRead();
        bool CanWrite();
        bool CanSeek();
		/*
		 * [warning] After a MemoryStream is closed, DO NOT reuse it because the result will be UNDEFINED.
		 */
        void Close();
        void CopyTo(ostream stream);
        void CopyTo(ostream stream, BufferLength length);
        void Flush();
		long GetCapacity();
        BufferLength GetLength();
        long GetPosition();
		bool IsEndOfStream();
		/*
		 * [return] A newly allocated buffer contains a serial data section of a specific length read from stream.
		 */
        Buffer Read(BufferLength length);
		void Read(Buffer buffer, BufferLength length);
		Byte ReadByte();
		/*
		 * Seek from a specific origin for a distance. If the position touches the boundary, it will retreat to the boundary.
		 */
        void Seek(long distance, SeekOrigin position);
		/*
		 * [return] True if the capacity is changed and data is reallocated successfully. Otherwise, false, such as the capacity is fixed for it uses an external allocated buffer.
		 */
		bool SetCapacity(long capacity);
		/*
		 * [return] Number of written bytes.
		 */
		long Write(Buffer data, BufferLength length);
		/*
		 * [return] True if the byte is written successfully. Otherwise, false.
		 */
		bool WriteByte(Byte data);
	private:
		const static long DEFAULT_BUFFER_CHUNK_SIZE = 4096;
		
        BufferLength _Size;
		long _Position;
		Buffer _Buffer;
		StreamAccessPermission _Permission;
        bool _ShouldDeleteBuffer;
        bool _IsClosed;
	};
}

_L_END

#endif /* MemoryStream_h */
