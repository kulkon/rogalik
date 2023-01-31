#pragma once
#include <stdlib.h>
#include <exception>
#include <list>
/*
typedef struct BoundingBox {
	void* object;
	float x1, x2, y1, y2;
} BoundingBox;

typedef struct BoundingBoxListElement{
	BoundingBox* bb;
	BBLE* next;
} BBLE;

typedef struct ElemY {
	float height, start, end;
	ElemY* prev, * next;
	BBLE* Bboxes;
} ElemY;

typedef struct ElemX {
	float width, start, end;
	ElemX* prev, * next;
	ElemY* middleElemY;
} ElemX;




bool compBBbylowerX(BoundingBox *b1, BoundingBox *b2) {
	return b1->x1 < b2->x1;
}






class MyDataStructure
{
	std::list<BoundingBox*> boxList;

	float updateThreshold;
	int desiredCount, desiredCountSquared;
	ElemX* start;

public:
	void Init() {
		boxList.sort(compBBbylowerX);
		
		std::list<BoundingBox*>::iterator it = boxList.begin();

		ElemX** tmpElemX = &start;


		while (it != boxList.end()) {
			
			it++;
		}
	}
};

*/