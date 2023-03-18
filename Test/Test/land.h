#include "vec.h"
#include <vector>
#include <glut.h>

#ifndef LAND
#define LAND

using namespace std;
class land {
public:
	vector<vec> ground;

	void draw()
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (auto& v : ground)
		{
			glVertex2f(v.x, v.y);
			glVertex2f(v.x, 0);
		}
		glEnd();
	}
};

#endif