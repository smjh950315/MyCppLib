#pragma once
#ifndef CYH_DRAW_MATRIX_H
#define CYH_DRAW_MATRIX_H
#include "bmpconvert.hpp"
using cyh::data::Number;
using cv::Mat;
using cv::Vec3b;

namespace cyh::graph {
	class DrawMatrix {		
	private:
		using Convert = cyh::graph::BmpConvert;
		static void draw_8bit(MChMat& ph, COORDS& coords, U8C1 color) {
			for (auto& c : coords) {
				int x = (int)c.X;
				int y = (int)c.Y;
				ph[0][x][y] = color.w;
			}
		}
		static void draw_24bit(MChMat& ph, COORDS& coords, U8C3 color) {
			for (auto& c : coords) {
				int x = (int)c.X;
				int y = (int)c.Y;
				ph[0][x][y] = color.b;
				ph[1][x][y] = color.g;
				ph[2][x][y] = color.r;
			}
		}
	public:
		static void Draw(MChMat& ph, COORDS& coords, U8C3 color) {
			size_t ch = ph.Depth;
			U8C1 gray = BmpConvert::To8bit(color);
			switch (ch) {
			case 1:	
				draw_8bit(ph, coords, gray);
				break;
			case 3:
				draw_24bit(ph, coords, color);
				break;
			default:
				break;
			}
		}
	};
}

#endif // !CYH_DRAW_MATRIX_H




