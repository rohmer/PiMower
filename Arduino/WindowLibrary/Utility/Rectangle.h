#pragma once
#include "Point.h"
#include "Logger.h"
struct Rectangle
{
public:
	Rectangle(int x1, int y1, int x2, int y2)
		: x1(x1)
		, y1(y1)
		, x2(x2)
		, y2(y2)
	{
		if (x2 < x1)
		{
			int t = x1;
			x1 = x2;
			x2 = t;
		}
		if (y2 < y1)
		{
			int t = y1;
			y1 = y2;
			y2 = t;
		}
		width = abs(x2 - x1);
		height = abs(y2 - y1);
	}

	Rectangle()
		: x1(0)
		, y1(0)
		, x2(0)
		, y2(0)
		, width(0)
		, height(0)
	{
	}

	bool hasArea()
	{
		if (x1 == x2 && y1 == y2)
			return false;
		return true;
	}

	Point center()
	{
		return Point((abs(x2 - x1) / 2) + x1, (abs(y2 - y1) / 2) + y1);
	}

	Rectangle normalizeRect(Rectangle *r)
	{		
		if (x1 > x2)
		{
			r->x1 = x2;
			r->x2 = x1;
		}
		else
		{
			r->x1 = x1;
			r->x2 = x2;
		}
		if (y1 > y2)
		{
			r->y1 = y2;
			r->y2 = y1;
		}
		else
		{
			r->y1 = y1;
			r->y2 = y2;
		}		
		Rectangle rect(r->x1, r->y1, r->x2, r->y2);
		return rect;
	}

	Rectangle normalizeRect(Rectangle &r)
	{
		if (x1 > x2)
		{
			r.x1 = x2;
			r.x2 = x1;
		}
		else
		{
			r.x1 = x1;
			r.x2 = x2;
		}
		if (y1 > y2)
		{
			r.y1 = y2;
			r.y2 = y1;
		}
		else
		{
			r.y1 = y1;
			r.y2 = y2;
		}
		return r;
	}

	Rectangle add(Rectangle r)
	{
		Rectangle r1 = normalizeRect(this);
		Rectangle r2 = normalizeRect(r);
		if (r1.x1 > r2.x1)
			r1.x1 = r2.x1;
		if (r1.y1 > r2.y2)
			r1.y1 = r2.y2;
		if (r1.x2 < r2.x2)
			r1.x2 = r2.x2;
		if (r1.y2 < r2.y2)
			r1.y2 = r2.y2;
		return r;
	}

	void update();
	bool contains(Point pt) const;
	bool occludes(Rectangle backgroundRect);
	int x1, y1, x2, y2, width, height;	
};
