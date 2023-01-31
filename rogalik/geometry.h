#pragma once
#include <math.h>
#include <iostream>
class Vector2 {
public:
	Vector2() {
		x = y = 0;
	}

	Vector2(float x, float y) : x(x), y(y) {

	}
	float x, y;
	float length() {
		return sqrt(pow(x, 2) + pow(y, 2));
	}
	void normalize() {
		float l = length();
		x /= l;
		y /= l;
	}

	//v1 is the hypotenuse
	static float sinBetweenVectors(Vector2& v1, Vector2& v2) {
		return (v1.y * v2.x - v1.x * v2.y) / (v1.length() * v2.length());
	}

	static float cosBetweenVectors(Vector2& v1, Vector2& v2) {
		return (v1.x * v2.x + v1.y * v2.y) / (v1.length() * v2.length());
	}
	//rotates vector anticlockwise
	static void rotateVectorByAngle(Vector2& v, float angle) {
		float x = v.x * cos(angle) - v.y * sin(angle);
		float y = v.y * cos(angle) + v.x * sin(angle);
		v.x = x;
		v.y = y;
	}

	static float distBetweenPoints(Vector2& v1, Vector2& v2) {
		return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
	}

	static float scalar(Vector2& v1, Vector2& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
};

class Line {
public:
	Vector2 origin, dir;

	Line(Vector2 &origin, Vector2 &v2, bool v2IsDir) {
		this->origin = Vector2(origin);
		if (v2IsDir) this->dir = Vector2(v2);
		else this->dir = Vector2(v2.x - origin.x, v2.y - origin.y);
	}

	//returns the second vector's multiplier to reach intersection point
	static float checkIfLinesIntersect(Line& l1, Line& l2) {
		return (l1.dir.x * (l2.origin.y - l1.origin.y) - l1.dir.y * (l2.origin.x - l1.origin.x)) / (l2.dir.x * l1.dir.y - l2.dir.y * l1.dir.x);
	}

	static float distFromPointToLine(Vector2& point, Line& line) {
		return abs((line.dir.x * (point.y - line.origin.y) - line.dir.y * (point.x - line.origin.x) / line.dir.length()));
	}
};




enum Shapes {
	SHAPE_CIRCLE,
	SHAPE_RECTANGLE
};


class Shape {
public:
	Vector2 pos;
	virtual bool isPointInside(Vector2& point) = 0;
	virtual Shapes getShape() = 0;
};


enum class TEST{

};

class Rect : public Shape {
public:
	Vector2 dimensions;
	Vector2* points[4];
	Shapes getShape() {
		
		return SHAPE_RECTANGLE;
	}
private:
	
};

class Circle : public Shape {
public:
	float radius;
	bool isPointInside(Vector2& point) { return false; }
	Shapes getShape() {
		return SHAPE_CIRCLE;
	}
};

class ShapeIntersections {
public:
	static Vector2** getIntersectionPoints(/*Shape& shape1, Shape& shape2*/) {
		
		return NULL;
	}
private:

};


class Segment {
public:
	Vector2 p1, p2;

};