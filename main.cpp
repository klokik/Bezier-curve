#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>


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
	// look wikipedia's article for description
	vec2f getPoint(size_t segment_num,float t)
	{
		//number of segments is equal to num. of correction points (one point per segment)
		if(correction_points.size()>=segment_num && base_points.size()>=2)
		{
			// pivot points
			vec2f P[] = {
				base_points[segment_num],
				correction_points[segment_num],
				base_points[segment_num+1]
			};

			// Bernstain's polynomials
			float b[] = {
				pow(1-t,2),
				2*t*(1-t),
				pow(t,2)
			};

			vec2f sum;
			size_t cnt = 3;

			for(size_t i=0;i<cnt;++i)
				sum = sum + b[i]*P[i];

			return sum;
		}
		else
			throw out_of_range("not enought point to calculate provided segment_num");
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

bool test_struct(void)
{
	vec2f vec1(1,2);

	cout<<vec1<<endl;

	quad_curve tcurve;

	try{
		// out to fail
		tcurve.getPoint(0,0.5f);
		cout<<"empty FAIL"<<endl;
		return false;
	}
	catch(...)
	{ cout<<"empty OK"<<endl;}
	
	tcurve.addStartPoint(vec2f(0.0f,0.0f));

	try{
		tcurve.addSegment(vec2f(1.0f,0.0f),vec2f(0.7f,1.0f));

		for(float q=0;q<1.0f;q+=0.1f)
		{
			cout<<tcurve.getPoint(0,q)<<endl;
		}

		cout<<"access test LOOKS_LIKE_OK :)"<<endl;
	}
	catch(string const &msg)
	{
		cout<<msg<<endl;
		throw 0;
	}
	catch(out_of_range const &oor)
	{
		cout<<oor.what()<<endl;
		throw 0;
	}
	catch(...)
	{
		cout<<"access test FAIL"<<endl;
		return false;
	}

	return true;
	
}

int main(int argc,char **argv)
{
	try
	{
		if(test_struct())
			cout<<"Tests PASSED"<<endl;
		else
			cout<<"Tests FAILED"<<endl;
	}
	catch(string const &msg)
	{
		cout<<msg<<endl;
	}
	catch(out_of_range const &oor)
	{
		cout<<oor.what()<<endl;
	}

	return 0;
}
