#include "Core/AliveToken.h"


namespace Renderer::Core
{
	TokenObserver::TokenObserver(const TokenOwner& owner)
	{
		mToken = owner.mToken;
	}

	bool TokenObserver::operator==(const TokenOwner& o)const
	{
		return  o.mToken == mToken.lock();
	}

	bool TokenObserver::IsValid()const
	{
		return !mToken.expired();
	}

	TokenObserver::operator bool()const {
		return IsValid();
	}

	TokenOwner::TokenOwner()
	{
		mToken = std::shared_ptr<bool>(new bool());
	}

	TokenOwner::~TokenOwner() {
		Cancel();
	}

	void TokenOwner::Cancel()
	{
		mToken.reset();
	}


}

