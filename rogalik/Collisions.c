#include <stdlib.h>
#include <stdbool.h>
/*
enum ColliderType {
	COLLIDER_RECT,
	CIRCLE
};

struct Vector2 {
	float x, y;
};

void rotateVector(struct Vector2* v, float angle) {
	float x = v->x * cos(angle) - v->y * sin(angle);
	float y = v->y * cos(angle) + v->x * sin(angle);
	v->x = x;
	v->y = y;
}

float scalar(struct Vector2 v1, struct Vector2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

typedef struct {
	float w, h, angle;
	struct Vector2 pos;
	int ID;
} RectCollider;

typedef struct {
	float r, x, y;
	int ID;
} CircleCollider;

typedef struct {
	void* collider;
	enum ColliderType colliderType;
	ColliderListElem* next;
} ColliderListElem;


ColliderListElem* staticCollidersHead = NULL, *staticCollidersLast = NULL;
ColliderListElem* dynamicCollidersHead = NULL, *dynamicCollidersLast = NULL;

void Init() {

}

void addCollider(void *col, enum ColliderType type,  bool isDynamic) {
	ColliderListElem **last;
	if (isDynamic) last = &dynamicCollidersLast;
	else last = &staticCollidersLast;
	ColliderListElem *tmp = (ColliderListElem*)malloc(sizeof(ColliderListElem));
	tmp->collider = col;
	tmp->colliderType = type;
	tmp->next = NULL;
	if (*last == NULL) {
		if (isDynamic) *last = dynamicCollidersHead = tmp;
		else *last = staticCollidersHead = tmp;
	}
	else
	{
		(*last)->next = tmp;
		(*last) = (*last)->next;
	}
}

RectCollider* addRectCollider(float w, float h, bool isDynamic) {
	RectCollider* col = (RectCollider*)malloc(sizeof(RectCollider));
	addCollider(col, COLLIDER_RECT, isDynamic);
	return col;
}


void Destroy() {
	ColliderListElem* tmp;
	while (staticCollidersHead != NULL) {
		tmp = staticCollidersHead;
		staticCollidersHead = staticCollidersHead->next;
		free(tmp);
	}
	while (dynamicCollidersHead != NULL) {
		tmp = dynamicCollidersHead;
		dynamicCollidersHead = dynamicCollidersHead->next;
		free(tmp);
	}

}

bool areOverlapping(float a, float b, float c, float d) {
	int e = 0;
	float s[2];
	s[0] = c;
	s[1] = d;
	for (int i = 0; i < 2; i++)
	{
		if (s[i] < a) e--;
		else if (s[i] > b) e++;
	}
	if (e >= -1 && e <= 1)return true;
	return false;
}

bool areColliding2Rect(RectCollider* col1, RectCollider* col2) {
	struct Vector2 relPos;
	relPos.x = col2->pos.x;
	relPos.y = col2->pos.y;
	rotateVector(&relPos, -col1->angle);
	struct Vector2 v[2];
	bool a[2];
	a[0] = a[1] = false;
	v[0].x = col2->w;
	v[0].y = col2->h;
	rotateVector(&v[0], col2->angle - col1->angle);
	v[1].x = -v[0].x;
	v[1].y = -v[0].y;
	for (int i = 0; i < 2; i++)
	{
		v[i].x += col1->w/2 + relPos.x;
		v[i].y += col1->h/2 + relPos.y;
	}

	if (areOverlapping(0, col1->w, v[0].x, v[1].x)) a[0] = true;
	if (areOverlapping(0, col1->h, v[0].y, v[1].y)) a[1] = true;

	v[0].x = -col2->w;
	v[0].y = col2->h;
	rotateVector(&v[0], col2->angle - col1->angle);
	v[1].x = -v[0].x;
	v[1].y = -v[0].y;
	for (int i = 0; i < 2; i++)
	{
		v[i].x += col1->w / 2 + relPos.x;
		v[i].y += col1->h / 2 + relPos.y;
	}

	if (areOverlapping(0, col1->w, v[0].x, v[1].x)) a[0] = true;
	if (areOverlapping(0, col1->h, v[0].y, v[1].y)) a[1] = true;


	if (a[0] && a[1]) return true;
	return false;
}


bool areColliding(ColliderListElem *col1, ColliderListElem *col2) {
	if (col1->colliderType == COLLIDER_RECT) {
		if (col2->colliderType == COLLIDER_RECT) return areColliding2Rect(col1->collider, col2->collider) && areColliding2Rect(col2->collider, col1->collider);
	}
}*/