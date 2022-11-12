#pragma once

#include "glad/glad.h"
#include "Core/types.h"


namespace OpenGLUtils {

	namespace Buffer {

		// .------------------------------.------------------------------------.
		// |    Buffer Binding Target     |              Purpose               |
		// :------------------------------+------------------------------------:
		// | GL_ARRAY_BUFFER              | Vertex attributes                  |
		// :------------------------------+------------------------------------:
		// | GL_ATOMIC_COUNTER_BUFFER     | Atomic counter storage             |
		// :------------------------------+------------------------------------:
		// | GL_COPY_READ_BUFFER          | Buffer copy source                 |
		// :------------------------------+------------------------------------:
		// | GL_COPY_WRITE_BUFFER         | Buffer copy destination            |
		// :------------------------------+------------------------------------:
		// | GL_DISPATCH_INDIRECT_BUFFER  | Indirect compute dispatch commands |
		// :------------------------------+------------------------------------:
		// | GL_DRAW_INDIRECT_BUFFER      | Indirect command arguments         |
		// :------------------------------+------------------------------------:
		// | GL_ELEMENT_ARRAY_BUFFER      | Vertex array indices               |
		// :------------------------------+------------------------------------:
		// | GL_PIXEL_PACK_BUFFER         | Pixel read target                  |
		// :------------------------------+------------------------------------:
		// | GL_PIXEL_UNPACK_BUFFER       | Texture data source                |
		// :------------------------------+------------------------------------:
		// | GL_QUERY_BUFFER              | Query result buffer                |
		// :------------------------------+------------------------------------:
		// | GL_SHADER_STORAGE_BUFFER     | Read-write storage for shaders     |
		// :------------------------------+------------------------------------:
		// | GL_TEXTURE_BUFFER            | Texture data buffer                |
		// :------------------------------+------------------------------------:
		// | GL_TRANSFORM_FEEDBACK_BUFFER | Transform feedback buffer          |
		// :------------------------------+------------------------------------:
		// | GL_UNIFORM_BUFFER            | Uniform block storage              |
		// '------------------------------'------------------------------------'


		enum class BufferType : uint32 {
			ARRAY = GL_ARRAY_BUFFER,
			ATOMIC_COUNTER = GL_ATOMIC_COUNTER_BUFFER,
			COPY_READ = GL_COPY_READ_BUFFER,
			COPY_WRITE = GL_COPY_WRITE_BUFFER,
			DISPATCH_INDIRECT = GL_DISPATCH_INDIRECT_BUFFER,
			DRAW_INDIRECT = GL_DRAW_INDIRECT_BUFFER,
			ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
			PIXEL_PACK = GL_PIXEL_PACK_BUFFER,
			PIXEL_UNPACK = GL_PIXEL_UNPACK_BUFFER,
			QUERY = GL_QUERY_BUFFER,
			SHADER_STORAGE = GL_SHADER_STORAGE_BUFFER,
			TEXTURE = GL_TEXTURE_BUFFER,
			TRANSFORM_FEEDBACK = GL_TRANSFORM_FEEDBACK_BUFFER,
			UNIFORM = GL_UNIFORM_BUFFER
		};


		//OPENGL BUFFER MODE: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBufferData.xhtml
		//STREAM
		//	The data store contents will be modified onceand used at most a few times.

		//STATIC
		//	The data store contents will be modified onceand used many times.

		//DYNAMIC
		//	The data store contents will be modified repeatedlyand used many times.

		//The nature of access may be one of these :

		//DRAW
		//	The data store contents are modified by the application, and used as the source for GL drawingand image specification commands.

		//READ
		//	The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.

		//COPY
		//	The data store contents are modified by reading data from the GL, and used as the source for GL drawingand image specification commands.


		enum class BufferUsage : uint32
		{
			STATIC_DRAW = GL_STATIC_DRAW,
			STATIC_COPY = GL_STATIC_COPY,
			STATIC_READ = GL_STATIC_READ,

			DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
			DYNAMIC_COPY = GL_DYNAMIC_COPY,
			DYNAMIC_READ = GL_DYNAMIC_READ,

			STREAM_DRAW = GL_STREAM_DRAW,
			STREAM_COPY = GL_STREAM_COPY,
			STREAM_READ = GL_STREAM_READ,
		};

		template<class T>
		constexpr uint32 EnumToGLEnum(T t) { return GetEnumValue(t); }

	}

}
