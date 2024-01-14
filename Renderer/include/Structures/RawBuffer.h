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

		template<typename T, class iter, class sentinel>
		[[nodiscard]] auto GetDataAs(iter begin, sentinel end)
		{
			constexpr auto index = TupleHelper::Index<T, bufferTy>::value;
			auto range = std::ranges::subrange(begin, end);
			return GetDataByIndice<index>(range);
		}

		template<typename T, class iter, class sentinel>
		[[nodiscard]] auto GetDataAs(iter begin, sentinel end) const
		{
			constexpr auto index = TupleHelper::Index<T, bufferTy>::value;
			auto range = std::ranges::subrange(begin, end);
			return GetDataByIndice<index>(range);
		}

		iter begin() { return mBufferData.begin(); }
		const_iter begin() const { return mBufferData.begin(); }

		iter end() { return mBufferData.end(); }
		const_iter end() const { return mBufferData.end(); }

		[[nodiscard]] const container& GetContainer() const { return mBufferData; }
		[[nodiscard]] container& GetContainer() { return mBufferData; }

		void clear() {
			mBufferData.clear();
		}

	private:
		template<int i>
		[[nodiscard]] auto GetDataByIndice() const { return std::views::elements<i>(mBufferData); }

		template<int i>
		[[nodiscard]] auto GetDataByIndice() { return std::views::elements<i>(mBufferData); }

		template<int i, class Subrange>
		[[nodiscard]] auto GetDataByIndice(Subrange& s) { return std::views::elements<i>(s); }

		template<int i, class Subrange>
		[[nodiscard]] auto GetDataByIndice(const Subrange& s) const { return std::views::elements<i>(s); }
	private:
		container mBufferData;
	};
}