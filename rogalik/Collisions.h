#pragma once
#include "common.h"
#include "geometry.h"
#include "GameObject.h"
#include <stdlib.h>


class Collider {
public:
	float rot, rotSpeed;
	Vector2 pos, speed;
	Shape *shape;
	float detectionRadius;
	bool isDynamic;
	virtual void getEdgesToProjectOnto(Segment** &edges, int *edgeCount) = 0;
	//returns true if projection is ovelapping
	virtual bool projectOntoEdge(Segment* edge) = 0;
};

class RectCollider : public Collider{
public:
	float w, h;
	void getEdgesToProjectOnto(Segment** &edges, int* edgeCount) {
		*edgeCount = 2;
		edges = (Segment**)malloc(sizeof(Segment*) * *edgeCount);
		for (int i = 0; i < 2; i++)
		{
			edges[i] = new Segment();
		}
		
		Vector2 v;
		v.x = -w / 2;
		v.y = -h / 2;
		v.rotateVectorByAngle(v, rot);
		edges[0]->p1.x = pos.x + v.x;
		edges[0]->p1.y = pos.y + v.y;
		v.x = w / 2;
		v.y = -h / 2;
		v.rotateVectorByAngle(v, rot);
		edges[0]->p2.x = edges[1]->p1.x = pos.x + v.x;
		edges[0]->p2.y = edges[1]->p1.y = pos.y + v.y;
		v.x = w / 2;
		v.y = h / 2;
		v.rotateVectorByAngle(v, rot);
		edges[1]->p1.x = pos.x + v.x;
		edges[1]->p1.y = pos.y + v.y;
	}

	bool projectOntoEdge(Segment *edge) {
		Vector2 v;
		v.x = edge->p2.x - edge->p1.x;
		v.y = edge->p2.y - edge->p1.y;
		Vector2 relPos;
		relPos.x = pos.x - edge->p1.x;
		relPos.y = pos.y - edge->p1.y;
		Vector2 points[4];

		points[0] = Vector2(-w / 2, -h / 2);
		points[1] = Vector2(w / 2, -h / 2);
		points[2] = Vector2(w / 2, h / 2);
		points[3] = Vector2(-w / 2, h / 2);
		for (int i = 0; i < 4; i++)
		{
			points[i].rotateVectorByAngle(points[i], rot);
			points[i].x += relPos.x;
			points[i].y += relPos.y;
		}
		Vector2 v2, v3;
		for (int i = 0; i < 2; i++)
		{
			v2.x = points[i].x;
			v2.y = points[i].y;
			v3.x = points[i + 2].x;
			v3.y = points[i + 2].y;

			float s[2];
			s[0] = Vector2::scalar(v, v2) / v.length();
			s[1] = Vector2::scalar(v, v3) / v.length();
			int a = 0;
			for (int j = 0; j < 2; j++)
			{
				if (s[i] < 0) a -= 1;
				else if (s[i] <= 1) continue;
				else a += 1;
			}
			std::cout << a << " ";
			if (a >= -1 && a <= 1) return true;


		}
		return false;
	}
};


class Collisions
{
public:
	std::list<Collider*> staticColliders;
	std::list<Collider*> dynamicColliders;

	Collisions() {
		RectCollider* col = new RectCollider();
		col->h = 1;
		col->w = 10;
		col->isDynamic = false;
		col->rot = 0;
		col->pos.x = 5;
		col->pos.y = -1;
		staticColliders.push_back(col);

		col = new RectCollider();
		col->h = 1;
		col->w = 1;
		col->isDynamic = true;
		col->rot = 0;
		col->pos.x = 0;
		col->pos.y = 0;
		dynamicColliders.push_back(col);
	}

	bool areColliding(Collider& col1, Collider& col2) {
		int edgeCount;
		Segment** edges = NULL;
		bool a = true;
		col1.getEdgesToProjectOnto(edges, &edgeCount);
		for (int i = 0; i < edgeCount; i++)
		{
			if (!col2.projectOntoEdge(edges[i])) a = false;
		}
		std::cout << a << " ";
		col2.getEdgesToProjectOnto(edges, &edgeCount);
		for (int i = 0; i < edgeCount; i++)
		{
			if (!col1.projectOntoEdge(edges[i])) a = false;
		}
		std::cout << " " << a << " ";
		return a;
	}


	void checkForCollisions() {
		std::list<Collider*>::iterator itD;
		std::list<Collider*>::iterator itS;
		for (itD = dynamicColliders.begin(); itD != dynamicColliders.end(); itD++) {
			for (itS = staticColliders.begin(); itS != staticColliders.end(); itS++) {
				if (areColliding(**itS, **itD)) std::cout << "areColliding" << std::endl;
				else std::cout << "notColliding" << std::endl;
			}
		}
	}



	
	
};