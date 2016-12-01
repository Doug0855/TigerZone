#pragma once

#include <GL/glew.h>

namespace Bengine {
	struct ColorRGBA8 {
		ColorRGBA8() : r(0), g(0), b(0), a(0) { }
		ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
			r(R), g(G), b(B), a(A) { }
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
}