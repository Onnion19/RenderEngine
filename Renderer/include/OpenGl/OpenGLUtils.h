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


		/**
		https://www.khronos.org/opengl/wiki/OpenGL_Type 
		C Type	Bitdepth		Description											Common Enum
		GLboolean	1+			A boolean value, either GL_TRUE or GL_FALSE	
		GLbyte		8			Signed, 2's complement binary integer				GL_BYTE
		GLubyte		8			Unsigned binary integer								GL_UNSIGNED_BYTE
		GLshort		16			Signed, 2's complement binary integer				GL_SHORT
		GLushort	16			Unsigned binary integer								GL_UNSIGNED_SHORT
		GLint		32			Signed, 2's complement binary integer				GL_INT
		GLuint		32			Unsigned binary integer								GL_UNSIGNED_INT
		GLfixed		32			Signed, 2's complement 16.16 integer				GL_FIXED
		GLint64		64			Signed, 2's complement binary integer	
		GLuint64	64			Unsigned binary integer	
		GLsizei		32			A non-negative binary integer, for sizes.	
		GLenum		32			An OpenGL enumerator value	
		GLintptr	ptrbits?1	Signed, 2's complement binary integer	
		GLsizeiptr	ptrbits?1	Non-negative binary integer size, for memory offsets and ranges	
		GLsync		ptrbits?1	Sync Object handle	
		GLbitfield	32			A bitfield value	
		GLhalf		16			An IEEE-754 floating-point value					GL_HALF_FLOAT
		GLfloat		32			An IEEE-754 floating-point value					GL_FLOAT
		GLclampf	32			An IEEE-754 floating-point value, clamped to the range [0,1]	
		GLdouble	64			An IEEE-754 floating-point value					GL_DOUBLE
		GLclampd	64			An IEEE-754 floating-point value, clamped to the range [0,1]	
		**/

		enum class GLType : uint32 {
			BYTE = GL_BYTE,
			UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
			SHORT = GL_SHORT,
			UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
			INT = GL_INT,
			UNSIGNED_INT = GL_UNSIGNED_INT,
			FLOAT = GL_FLOAT
		};
	}

	namespace Shader {
		enum class Type : uint32{
			VERTEX = GL_VERTEX_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
			COMPUTE = GL_COMPUTE_SHADER
		};
	}

	template<class T>
	constexpr uint32 EnumToGLEnum(T&& t) { return GetEnumValue(t); }
}
