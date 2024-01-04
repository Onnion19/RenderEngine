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
		static constexpr auto ActiveQuad = true;
		static constexpr auto InactiveQuad = !ActiveQuad;
	public:
		using VertexData = std::tuple<VBOTypes...>;
		QuadBatcher() :vao(), vbo(OpenGLUtils::Buffer::BufferType::ARRAY), ibo(){
			InitializeVAO();
			vbo.Unbind();
			ibo.Unbind();
			vao.Unbind();
		}

		// this should take a VBOType data and index should be auto computed
		template<typename QuadVertexDataRange = std::vector<VertexData>>
		uint32 AddQuad(QuadVertexDataRange&& data, bool updateGpu = false) {
			assert(data.size() == 4);
			const auto quadIndex = quadStatus.size();

			vbo.Insert(data);
			assert(vbo.size() % 4 == 0 && "Invalid ammount of vbo, not mutilple by 4");
			quadStatus.push_back(ActiveQuad);
			if (updateGpu)
			{
				SendQuadDataToGPU();
			}
			dirty = true;
			return static_cast<uint32>(quadIndex);
		}

		void SendQuadDataToGPU() {
			vao.Bind();
			vbo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::STATIC_DRAW);
			vao.Unbind();
		}

		void RemoveQuad(uint32 index) {
			if (index >= quadStatus.size()) return;
			quadStatus[index] = InactiveQuad;
			dirty = true;
		}

		void Draw()
		{
			HandleDirtyFlag();
			ibo.Bind();
			vao.Bind();
			vbo.Bind();
			const auto gltype = OpenGLUtils::EnumToGLEnum(OpenGLUtils::Buffer::GLType::UNSIGNED_INT);
			glDrawElements(GL_TRIANGLES, static_cast<uint32>(ibo.size()), gltype, nullptr);

		}
	private:
		void InitializeVAO() {
			vao.Bind();
			// This attributes probably needs to be updated by shader or something
			vbo.Bind();
			Renderer::GL::VertexAtributeObject::AttributePointer<decltype(vbo)::bufferTy, Renderer::Geometry::Point2D> position{ 0 ,2, OpenGLUtils::Buffer::GLType::FLOAT, false };
			Renderer::GL::VertexAtributeObject::AttributePointer<decltype(vbo)::bufferTy, Renderer::Type::RawColor> color{ 1,4, OpenGLUtils::Buffer::GLType::FLOAT, false };
			vao.EnableAndDefineAttributePointer(position);
			vao.EnableAndDefineAttributePointer(color);
			vbo.Unbind();
			vao.Unbind();
		}
		void HandleDirtyFlag() {
			if (!dirty) return;
			BuildIbo();
			ibo.SendDataGPU(OpenGLUtils::Buffer::BufferUsage::DYNAMIC_DRAW);
			dirty = false;
		}

		void BuildIbo() {
			ibo.clear();
			for (uint32 i = 0; i < quadStatus.size(); i++)
			{
				if (quadStatus[i] != ActiveQuad) continue;
				const auto indices = ComputeQuadIndices(i);
				ibo.AddIndices(indices);
			}
		}

		auto ComputeQuadIndices(uint32 quadIndex) const
		{
			const auto offset = quadIndex * 4;
			const auto tl = static_cast<uint32>(offset);
			const auto tr = static_cast<uint32>(offset + 1);
			const auto br = static_cast<uint32>(offset + 2);
			const auto bl = static_cast<uint32>(offset + 3);

			return std::array<uint32, 6>{ tl, tr, br, tl, br, bl};
		}
	private:
		VertexAtributeObject vao;
		OpenGlBuffer<VBOTypes...> vbo;
		IndexBuffer ibo;
		std::vector<bool> quadStatus;
		bool dirty = true;
	};
}