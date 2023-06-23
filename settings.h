#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Point2D.h"
#include <math.h>

const static bool DEBUG = false;
const static bool EYE_CORR = true;
const static float PI = 3.14159265359;

const static int W_WIDTH = 640;
const static int W_HEIGHT = 480;

const static int G_WIDTH = 640;
const static int G_HEIGHT = 480;

const static double P_RADIUS = 7.5;
const static Point2D P_POSITION = {20, 20};
const static sf::Color P_COLOR = { 105, 0, 95 };
const static int P_POINTS = 50;
const static int P_MSPEED = 150;
const static double P_RSPEED = 0.04;
const static int P_D_FOV = 75;
const static double P_R_FOV = P_D_FOV * PI / 180;
const static int DEPTH = 500;
const static int P_SCALE = 10;
const static int P_RAY_NUM = W_WIDTH / P_SCALE;

const static double M_HEIGHT = 300;
const static double M_DIST = P_RAY_NUM / (2 * tan(P_R_FOV / 2));
const static double M_PROJ_K = 1.5 * M_DIST * M_HEIGHT;

const static int O_OUTLINE_THICKNESS = 1;

const static sf::Color O_OUTLINE_COLOR = { 245, 116, 10 };
const static sf::Color O_FILL_COLOR = { 38, 0, 105 };
