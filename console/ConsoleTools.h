#pragma once
#include <platform.h>

namespace Console {
	struct Size {
		Size() {
			Width = 0;
			Height = 0;
		}

		Size(int w, int h) {
			Width = w;
			Height = h;
		}

		int Width;
		int Height;
	};

	#ifdef __WIN32
		#define _getConsoleSize __getConsoleSize_W

		Size __getConsoleSize_W();
	#else 
		#define _getConsoleSize __getConsoleSize_L

		Size __getConsoleSize_L();
	#endif
}
