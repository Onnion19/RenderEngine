#pragma once
#include "Core/types.h"
#include "Type/Color.h"
#include "OpenGl/Buffer.h"
#include "OpenGl/VertexAttributeObject.h"
#include "Geometry/BasicShapes.h"
namespace Renderer::GL {

	/**
	*	QUAD BATCHER will use a single draw call to render all provided quads.
	*	The indice that it will generate for eac quad follows the next pattern
	*
	*    tl					tr
	*	╭――――――――――――――――――╮
	*	│                  │
	*	│                  │ --> indices = tl bl br , br tr tl
	*	│                  │
	*	╰――――――――――――――――――╯
	*	bl					br
	*
	* In order to add a new quad, vertices range must start from tl and go clockwise.
	* (tl, tr, br, bl)
	* Notes: Vertex data is static, meaning all data is send once and never changed.
	* Notes: if a quad is deleted, it will only remove the indices from ibo.
	*/
	template<typename ... VBOTypes>
	class QuadBatcher {
	public:
		using VertexData = std::tuple<VBOTypes...>;
		QuadBatcher() : vbo(OpenGLUtils::Buffer::BufferType::ARRAY) {
			InitializeVAO();
		}

		// this should take a VBOType data and index should be auto computed
		template<typename QuadVertexDataRange = std::vector<VertexData>>
		void AddQuad(QuadVertexDataRange&& data, bool updateGpu = false) {
			assert(data.size() == 4);
			vbo.Insert(data);
			assert(vbo.size() % 4 == 0 && "Invalid ammount of vbo, not mutilple by 4");

			const auto indices = ComputeNewQuadIndices();
			ibo.AddIndices(indices);
			if (updateGpu)
			{
				SendQuadDataToGPU();
			}
			dirty = true;
		}

		void SendQuadDataToGPU() {
			vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
		}



		void RemoveQuad(uint32 index) {
			auto offset = 6u * index;
			assert(offset <= ibo.size() - 6 && "Trying to remove an invalid quad");
			auto begin = ibo.begin() + offset;
			auto end = begin + 6;
			ibo.RemoveIndicesAt(begin, end);
			dirty = true;
		}
		void Draw()
		{
			HandleDirtyFlag();
			vbo.Bind();
			vao.Bind();
			ibo.Bind();

			const auto gltype = EnumToGLEnum(OpenGLUtils::Buffer::GLType::UNSIGNED_INT);
			glDrawElements(GL_TRIANGLES, static_cast<uint32>(ibo.size()), gltype, nullptr);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			vbo.Unbind();
			ibo.Unbind();
			vao.Unbind();
		}
	private:
		void InitializeVAO() {
			vbo.Bind();
			// This attributes probably needs to be updated by shader or something
			vao.Bind();
			Renderer::GL::VertexAtributeObject::AttributePointer<decltype(vbo)::bufferTy, Geometry::Point2D> properties{ 0 ,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
			vao.EnableAndDefineAttributePointer(properties);
		}
		void HandleDirtyFlag() {
			if (!dirty) return;
			ibo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
			dirty = false;
		}

		auto ComputeNewQuadIndices() const
		{
			// Verify there are vertices ready
			assert(vbo.size() >= 4);
			const auto tl = static_cast<uint32>(vbo.size() - 4);
			const auto tr = static_cast<uint32>(vbo.size() - 3);
			const auto br = static_cast<uint32>(vbo.size() - 2);
			const auto bl = static_cast<uint32>(vbo.size() - 1);

			return std::array<uint32, 6>{ tl, tr, br, tl, br, bl};
		}
	private:
		OpenGlBuffer<VBOTypes...> vbo;
		VertexAtributeObject vao;
		IndexBuffer ibo;
		bool dirty = true;
	};
}