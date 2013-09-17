#include <iostream>
#include <vector>
#include <string>


using namespace std;

struct vec2f
{
	float x;
	float y;

	vec2f(float _x = 0,float _y = 0):
		x(_x),
		y(_y)
	{
	}

	friend vec2f operator*(vec2f vec,float lambda)
	{
		return {vec.x*lambda,vec.y*lambda};
	}

	friend vec2f operator*(float lambda,vec2f vec)
	{
		return vec*lambda;
	}

	friend vec2f operator*(vec2f va,vec2f vb)
	{
		return {va.x*vb.x,va.y*vb.y};
	}

	friend vec2f operator+(vec2f va,vec2f vb)
	{
		return {va.x+vb.x,va.y+vb.y};
	}

	friend vec2f operator-(vec2f va,vec2f vb)
	{
		return {va.x-vb.x,va.y-vb.y};
	}

	friend vec2f operator-(vec2f va)
	{
		return -1.0f*va;
	}

	friend ostream &operator<<(ostream &str,vec2f const &vec)
	{
		str<<"( "<<vec.x<<" ; "<<vec.y<<" )";
		return str;
	}
};

class quad_curve
{
protected:
	vector<vec2f> base_points;
	vector<vec2f> correction_points;

public:
	vec2f getPoint(size_t segment,float t)
	{
	}

	void addStartPoint(vec2f pt)
	{
		if(base_points.empty())
			base_points.push_back(pt);
		else
			throw string("curve already contains start point");
	}

	void addSegment(vec2f base_pt,vec2f correction_pt)
	{
		if(!base_points.empty())
		{
			base_points.push_back(base_pt);
			correction_points.push_back(correction_pt);
		}
		else
			throw string("first you need to add start point");
	}
};

void test_struct(void)
{
	vec2f vec1(1,2);

	cout<<vec1<<endl;
}

int main(int argc,char **argv)
{
	try
	{
		test_struct();
	}
	catch(string &msg)
	{
		cout<<msg<<endl;
	}

	return 0;
}
