#include "Type/Color.h"
#include <algorithm>
namespace Renderer::Type
{
	ColorHSV ColorRGB::ToHSV()const
	{
		//https://gist.github.com/fairlight1337/4935ae72bcbcc1ba5c72
		const float rgbMax = std::max(std::max(Red(), Green()), Blue());
		if (rgbMax <= static_cast<float>(1e-4))
		{
			return{};
		}
		const float rgbMin = std::min(std::min(Red(), Green()), Blue());
		const float delta = rgbMax - rgbMin;

		ColorHSV hsv;
		hsv.Value() = rgbMax;

		if (delta > 0.f)
		{
			if (rgbMax == Red())
			{
				hsv.Hue() = 60.f * static_cast<float>(fmod(((Green() - Blue()) / delta), 6));
			}
			else if (rgbMax == Green())
			{
				hsv.Hue() = 60.f * (((Blue() - Red()) / delta) + 2);
			}
			else {
				hsv.Hue() = 60.f * (((Red() - Green()) / delta) + 4);
			}

			hsv.Hue() += (hsv.Hue() < 0.f) ? 360.f : 0.f;
		}

		hsv.Saturation() = delta / rgbMax;

		return hsv;
	}


	ColorRGB ColorHSV::ToRGB()const
	{
		//https://gist.github.com/fairlight1337/4935ae72bcbcc1ba5c72
		if (Saturation() <= 0.f)
		{
			return ColorRGB(Value());
		}

		const int H = static_cast<int>(Hue() / 60.f) %6;
		const float F = Hue() / 60 - H;
		const float P = Value() * (1 - Saturation());
		const float Q = Value() * (1 - F * Saturation());
		const float T = Value() * (1 - (1 - F) * Saturation());
		ColorRGB rgb = {};
		switch (H)
		{
		case 0: 
			 rgb.Red() = Value();
			 rgb.Green() = T;
			 rgb.Blue() = P;
			break;
		case 1:
			rgb.Red() = Q;
			rgb.Green() = Value();
			rgb.Blue() = P;
			break;
		case 2:
			rgb.Red() = P;
			rgb.Green() = Value();
			rgb.Blue() = T;
			break;
		case 3:
			rgb.Red() = P;
			rgb.Green() = Q;
			rgb.Blue() = Value();
			break;
		case 4:
			rgb.Red() = T;
			rgb.Green() = P;
			rgb.Blue() = Value();
			break;
		case 5:
			rgb.Red() = Value();
			rgb.Green() = P;
			rgb.Blue() = P;
			break;
		}

		return rgb;
	}
}