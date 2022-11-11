#pragma once 

#include <ranges>
namespace Renderer {

	template<typename ... Ty>
	class MultiTypeBuffer {
	public:
		using bufferTy = std::tuple<Ty...>;
		using container = std::vector<bufferTy>;
		using iter = container::iterator;
		using const_iter = container::const_iterator;
		using reference = container::reference;
	public:
		//Get data
		template<typename T>
		[[nodiscard]] auto GetDataAs() const
		{
			constexpr auto index = TupleHelper::Index<T, bufferTy>::value;
			return GetDataByIndice<index>();
		}

		template<typename T>
		[[nodiscard]] auto GetDataAs()
		{
			constexpr auto index = TupleHelper::Index<T, bufferTy>::value;
			return GetDataByIndice<index>();
		}

		[[nodiscard]] const container& GetContainer() const { return mBufferData; }
		[[nodiscard]] container& GetContainer() { return mBufferData; }

	private:
		template<int i>
		[[nodiscard]] auto GetDataByIndice() const { return std::views::elements<i>(mBufferData); }

		template<int i>
		[[nodiscard]] auto GetDataByIndice() { return std::views::elements<i>(mBufferData); }
	private:
		container mBufferData;
	};
}