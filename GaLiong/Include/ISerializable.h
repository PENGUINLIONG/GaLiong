//
//  ISerializable.h
//  GaLiong
//
//  Created by Liong on 15/10/27.
//

#ifndef ISerializable_hpp
#define ISerializable_hpp
#include "Preprocess.hpp"

_L_BEGIN
namespace Serialization
{
	template <typename T>
	class _L_ ISerializable
	{
	public:
		/*
		 * [warning] You should delete the pointer when you will not use it anymore.
		 */
		virtual T* Deserialize(Buffer buffer, BufferLength bufferLength) = 0;
		/*
		 * [warning] You should delete the pointer when you will not use it anymore.
		 */
		virtual Buffer Serialize() = 0;
	};
}
_L_END

#endif /* ISerializable_hpp */
