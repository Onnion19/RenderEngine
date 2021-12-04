#pragma once 

#include <memory>


namespace Renderer::Core {


	class TokenObserver {
	public:
		TokenObserver() = delete;
		explicit TokenObserver(const class TokenOwner& owner);
		TokenObserver(const TokenObserver&) = delete;
		TokenObserver& operator=(const TokenObserver&) = delete;
		TokenObserver(TokenObserver&&) = default;
		TokenObserver& operator=(TokenObserver&&) = default;

		[[nodiscard]] bool IsValid()const;
		explicit operator bool()const;
		bool operator==(const class TokenOwner& o)const;
	private:
		std::weak_ptr<bool> mToken;
	};


	class TokenOwner {
		using TokenType = std::shared_ptr<bool>;
	public:
		TokenOwner();
		~TokenOwner();

		explicit TokenOwner(const TokenOwner&) = delete;
		TokenOwner(TokenOwner&&) = default;

		TokenOwner& operator=(const TokenOwner&) = delete;
		TokenOwner& operator=(TokenOwner&&) = default;

		void Cancel();
	protected:
		std::shared_ptr<bool> mToken;

		friend TokenObserver;


	};





}