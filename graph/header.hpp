#pragma once
#pragma comment(lib,"gdiplus.lib")
#include <objidl.h>
#include <gdiplus.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/matx.hpp>
#include "../Data/Tuples.hpp"
#include "../Data/Coord.hpp"
#include "color.hpp"
using namespace Gdiplus;
using std::vector;
using cyh::data::Phalanx;
using COORDS = std::vector<Coord2D>;
using SMat = cyh::data::Matrix<uchar>;
using MChMat = cyh::data::Phalanx<uchar>;
using U8C3 = cyh::graph::Color24b;
using U8C1 = cyh::graph::Color8b;

