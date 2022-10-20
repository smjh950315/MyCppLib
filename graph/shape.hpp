#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include "header.hpp"
using cyh::data::Number;
using pos = cyh::data::Coord2D;

namespace cyh::graph {

	class Shape {
	public:
		double Area = 0;
		vector<pos> pixels;
		Shape() {}
		~Shape() {}
		virtual void GetEdgeCoords(vector<pos>& v, pos coordStart) = 0;
		virtual void GetFillCoords(vector<pos>& v, pos coordStart) = 0;
		static void GetCoordsBetween(vector<pos>& v, pos pos1, pos pos2);
		static void GetCoordsVertical(vector<pos>& v, double x, double y1, double y2);
		
		static void CoordsRotate(COORDS& coords, double radias);
	};

	class Rectangle : public Shape {
	private:
		void _setArea() { Area = Width * Height; }
		void _setVertex();
	public:
		double cX = 0;
		double cY = 0;
		double Width = 0;
		double Height = 0;
		COORDS Vertex;
		COORDS Edge;
		Rectangle() {  }
		Rectangle(double w, double h) { SetSize(w, h); }
		void SetSize(double w, double h);
		void SetClientPos(pos pos_justify);
		void SetClientPos(double x, double y) { SetClientPos(pos(x, y)); }
		void GetEdgeCoords(COORDS& v);
		void GetEdgeCoords(COORDS& v, pos coordStart);
		void GetFillCoords(COORDS& v);
		void GetFillCoords(COORDS& v, pos coordStart);
		static Coord2D GetRectCenter(COORDS& coords);
	};

	class Circle :Shape {
	private:
		void _setArea() { Area = Radius * Radius * Number::PI; }
	public:
		double Radius = 0;
		Circle() {}
		Circle(double r) :Radius(r) { _setArea(); }

	};
}
#endif
