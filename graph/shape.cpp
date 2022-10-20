#include "shape.hpp"
#include "../math/math.hpp"
using cyh::graph::Shape;
using cyh::graph::Rectangle;
using pos = cyh::data::Coord2D;
void Shape::GetCoordsBetween(vector<pos>& v, pos pos1, pos pos2) {
	if (!(pos1.X - pos2.X)) {
		GetCoordsVertical(v, pos1.X, pos1.Y, pos2.Y);
		return;
	}
	//x is not same
	double xS = 0;
	double yS = 0;
	double xE = 0;
	double yE = 0;
	double m = (pos1.Y - pos2.Y) / (pos1.X - pos2.X);
	if (pos1.X < pos2.X) {
		xS = pos1.X;
		yS = pos1.Y;
		xE = pos2.X;
		yE = pos2.Y;
	}
	else {
		xS = pos2.X;
		yS = pos2.Y;
		xE = pos1.X;
		yE = pos1.Y;
	}
	do {
		double tempY = m * xS + yS;
		v.push_back(pos(xS, tempY));
		xS++;
	} while (xS <= xE);
}
void Shape::GetCoordsVertical(vector<pos>& v, double x, double y1, double y2) {
	if (!(y1 - y2)) {
		v.push_back(pos(x, y1));
	}
	if (y1 < y2) {
		while (y1 - y2) {
			v.push_back(pos(x, y1));
			y1++;
		}
	}
	else {
		while (y1 - y2) {
			v.push_back(pos(x, y2));
			y2++;
		}
	}
}
void Shape::CoordsRotate(COORDS& coords, double radias) {
	data::Matrix<double> Rot = data::Matrix<double>::RotationMatrix(radias);
	size_t iNow = 0;
	Coord2D center = Rectangle::GetRectCenter(coords);
	for (auto& c : coords) {
		c -= center;
	}
	for (auto& c : coords) {
		double temp[2] = { c.X,c.Y };
		data::Matrix<double> conv = Rot ^ data::Matrix<double>(temp, 1, 2);
		c.X = conv[0][0];
		c.Y = conv[0][1];
	}
	for (auto& c : coords) {
		c += center;
	}
}

void Rectangle::_setVertex() {
	Vertex.push_back(pos(0 - cX, 0 - cY));
	Vertex.push_back(pos(Width - cX, 0 - cY));
	Vertex.push_back(pos(Width - cX, Height - cY));
	Vertex.push_back(pos(0 - cY, Height - cY));
}
void Rectangle::SetClientPos(pos pos) {
	cX = pos.X;
	cY = pos.Y;
}
void Rectangle::SetSize(double w, double h) {
	Width = w;
	Height = h;
	_setArea();
}
void Rectangle::GetEdgeCoords(COORDS& v) {
	GetEdgeCoords(v, pos(cX, cY));
}
void Rectangle::GetEdgeCoords(COORDS& v, pos coord) {
	_setVertex();
	double xStart = coord.X;
	double yStart = coord.Y;
	for (auto& c : Vertex) {
		c.X += xStart;
		c.Y += yStart;
	}
	int i = 0;
	size_t size = Vertex.size();
	for (; i < size - 1; i++) {
		GetCoordsBetween(v, Vertex[i], Vertex[i + 1]);
	}
	GetCoordsBetween(v, Vertex[0], Vertex[size - 1]);
}
void Rectangle::GetFillCoords(COORDS& v) {
	GetFillCoords(v, pos(cX, cY));
}
void Rectangle::GetFillCoords(COORDS& v, pos coord) {
	_setVertex();
	double xStart = coord.X;
	double yStart = coord.Y;
	for (double x = 0; x < Width; x++) {
		for (double y = 0; y < Height; y++) {
			v.push_back(pos(xStart + x, yStart + y));
		}
	}
}
Coord2D Rectangle::GetRectCenter(COORDS& coords) {
	double xMin = coords[0].X;
	double xMax = coords[0].X;
	double yMin = coords[0].Y;
	double yMax = coords[0].Y;
	for (auto& c : coords) {
		double x = c.X;
		double y = c.Y;
		if (x < xMin) { xMin = x; }
		if (x > xMax) { xMax = x; }
		if (y < yMin) { yMin = y; }
		if (y > yMax) { yMax = y; }
	}
	double cX = (xMin + xMax) / 2;
	double cY = (yMin + yMax) / 2;
	return Coord2D(cX, cY);
}
