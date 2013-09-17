#include <iostream>

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

void test_struct(void)
{
	vec2f vec1(1,2);

	cout<<vec1<<endl;
}

int main(int argc,char **argv)
{
	test_struct();
	return 0;
}
