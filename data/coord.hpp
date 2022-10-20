#pragma once
#ifndef COORD_H
#define COORD_H
#include "../includelist.h"

namespace cyh::data {
	struct Coord2D {
		double X = 0;
		double Y = 0;
		Coord2D() {}
		Coord2D(double _x, double _y) :X(_x), Y(_y) {}
		void Set(double _x, double _y) { X = _x; Y = _y; }

		Coord2D operator+(Coord2D& coord) {
			return Coord2D(X + coord.X, Y + coord.Y);
		}
		Coord2D& operator+=(Coord2D& coord) {
			X += coord.X;
			Y += coord.Y;
			return *this;
		}
		Coord2D& operator-=(Coord2D& coord) {
			X -= coord.X;
			Y -= coord.Y;
			return *this;
		}
		double operator-(Coord2D& coord) {
			double dx2 = pow((X - coord.X), 2);
			double dy2 = pow((Y - coord.Y), 2);
			double dist = pow((dx2 + dy2), 0.5);
			return dist;
		}
	};
}
#endif