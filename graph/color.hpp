#pragma once
#ifndef CYH_COLOR_H
#define CYH_COLOR_H

namespace cyh::graph {

	struct Color8b {
		unsigned w;
		Color8b():w(0){}
		Color8b(unsigned white):w(white){}
	};
	struct Color24b {
		unsigned b, g, r;
		Color24b() :r(0), g(0), b(0) {}
		Color24b(unsigned red, unsigned green, unsigned blue) :r(red), g(green), b(blue) {}
		
	
	};
}


#endif // !CYH_COLOR_H

