#pragma once

#include <irrklang/irrKlang.h>

#include <string>
namespace Audio {

	class AudioEngine
	{
	public:
		~AudioEngine() {
			soundEngine->drop();
		}

		static void PlayAudio(std::string_view path, bool repeat)
		{
			soundEngine->play2D(path.data(), repeat);
		}

		static void PlaySound(std::string_view path)
		{
			PlayAudio(path, false);
		}
	private:
		static inline irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();;
	};



}