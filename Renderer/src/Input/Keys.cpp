#include "Input/Keys.h"

namespace Renderer::Input {

#if RENDERER_DEBUG
	string DebugKeyCodeText(KeyboardCode code)
	{
		string keyName = "";
		BitMask mask = static_cast<BitMask>(code);
		int bit = -1;
		while (mask > 0) {
			mask = mask >> 1;
			bit++;
		}

		switch (bit)
		{
		case 0:
			keyName = "None";
			break;
		case 27:
			keyName = "Shift";
			break;
		case 28:
			keyName = "Alt";
			break;
		case 29:
			keyName = "Cntrl";
			break;
		default:
			keyName.append(1, static_cast<char>('A' + bit - 1));
			break;
		}

		return keyName;

	}
#endif

}