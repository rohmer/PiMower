#pragma once
#include <math.h>

class node
{
    // current position
	int xPos;
	int yPos;
	// total distance already travelled to reach the node
	int level;
	// priority=level+remaining distance estimate
	int priority;  // smaller: higher priority

public:
	node(int xp, int yp, int d, int p) 
	    {xPos = xp; yPos = yp; level = d; priority = p; }
    
	int getxPos() const {return xPos;}
	int getyPos() const {return yPos;}
	int getLevel() const {return level;}
	int getPriority() const {return priority;}

	void updatePriority(const int & xDest, const int & yDest)
	{
		priority = level + estimate(xDest, yDest) * 10; //A*
	}

	        // give better priority to going strait instead of diagonally
	void nextLevel(const int & i) // i: direction
	{
		level += (8 == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
	}
        
	// Estimation function for the remaining distance to the goal.
	const int & estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - xPos;
		yd = yDest - yPos;         

		            // Euclidian Distance
		d = static_cast<int>(sqrt(xd*xd + yd*yd));

		            // Manhattan distance
		            //d=abs(xd)+abs(yd);
            
		            // Chebyshev distance
		            //d=max(abs(xd), abs(yd));

		return (d);
	}
};
