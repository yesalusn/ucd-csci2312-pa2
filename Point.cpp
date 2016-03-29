/*
Created by Nikki on 2/11/2016.
*/

#include <cmath>
#include <string>
#include <sstream>

#include "Point.h"

using std::endl;
using std::string;
//using std::stod;
using std::istream;
using std::ostream;

namespace Clustering
{
	unsigned int Point::__idGen = 0;

	Point::Point(int i) :
		__id(++__idGen),
		__dim(i)
	{
		__values = new double[__dim];
		for (int j = 0; j < __dim; ++j)
		{
			__values[j] = 0.0;
		}
	}

	Point::Point(int i, double *pDouble) :
		__id(++__idGen),
		__dim(i)
	{
		__values = new double[__dim];
		for (int j = 0; j < __dim; ++j)
		{
			__values[j] = pDouble[j];
		}
	}

	Point::Point(const Point &point) :
		__id(point.__id),
		__dim(point.__dim)
	{
		__values = new double[__dim];
		for (int i = 0; i < __dim; ++i)
		{
			__values[i] = point.getValue(i);
		}
	}

	Point& Point::operator=(const Point& point)
	{
		__id = point.__id;
		__dim = point.__dim;
		delete[]__values;
		__values = new double[__dim];
		for (int i = 0; i < __dim; ++i)
		{
			__values[i] = point.getValue(i);
		}
		return *this;
	}

	Point::~Point()
	{
		delete[]__values;
	}

	int Point::getId() const
	{
		return __id;
	}

	int Point::getDims() const
	{
		return __dim;
	}

	void Point::setValue(int i, double d)
	{
		__values[i] = d;
	}

	double Point::getValue(int i) const
	{
		return __values[i];
	}

	double Point::distanceTo(const Point &point) const
	{
		if (*this != point && __dim == point.__dim)
		{
			double sum = 0;
			double distance;
			for (int i = 0; i < __dim; ++i)
			{
				sum += pow(__values[i] - point.getValue(i), 2);
			}
			distance = sqrt(sum);
			return distance;
		}
		else
			return 0;
	}

	Point &Point::operator*=(double d)
	{
		for (int i = 0; i < __dim; ++i)
		{
			__values[i] *= d;
		}
		return *this;
	}

	Point &Point::operator/=(double d)
	{
		if(d != 0)
		{
			for (int i = 0; i < __dim; ++i)
			{
				__values[i] /= d;
			}
		}
		return *this;
	}

	const Point Point::operator*(double d) const
	{
		Point p(*this);
		p *= d;
		return p;
	}

	const Point Point::operator/(double d) const
	{
		Point p(*this);
		p /= d;
		return p;
	}

	double &Point::operator[](int index)
	{
		return __values[index];
	}

	Point &operator+=(Point &point, const Point &point1)
	{
		if (point.__dim == point1.__dim)
		{
			for (int i = 0; i < point.__dim; ++i)
			{
				point.__values[i] += point1.__values[i];
			}
		}
		return point;
	}

	Point &operator-=(Point &point, const Point &point1)
	{
		if (point.__dim == point1.__dim)
		{
			for (int i = 0; i < point.__dim; ++i)
			{
				point.__values[i] -= point1.__values[i];
			}
		}
		return point;
	}

	const Point operator+(const Point &point, const Point &point1)
	{
		Point p(point);
		p += point1;
		return p;
	}

	const Point operator-(const Point &point, const Point &point1)
	{
		Point p(point);
		p -= point1;
		return p;
	}

	bool operator==(const Point &point, const Point &point1)
	{
		if(point.__id == point1.__id)
		{
			if(point.__dim == point1.__dim)
			{
				for(int j = 0; j < point.__dim; ++j)
				{
					if (point.__values[j] != point1.__values[j])
						return false;
				}
				//iff all things are equal
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	bool operator!=(const Point &point, const Point &point1)
	{
		if (point == point1)
			return false;
		else
			return true;
	}

	bool operator<(const Point &point, const Point &point1)
	{
		if(point.__dim == point1.__dim)
		{
			for(int j = 0; j < point.__dim; ++j)
			{
				if(point.__values[j] < point1.__values[j])
					return true;
				if(point.__values[j] > point1.__values[j])
					return false;
			}
		}
		else
			return false;
	}

	bool operator>(const Point &point, const Point &point1)
	{
		if(point != point1 || !(point < point1))
			return true;
		else
			return false;
	}

	bool operator<=(const Point &point, const Point &point1)
	{
		if(point < point1 || point == point1)
			return true;
		else
			return false;
	}

	bool operator>=(const Point &point, const Point &point1)
	{
		if(point > point1 || point == point1)
			return true;
		else
			return false;
	}

	ostream &operator<<(ostream &os, const Point &point)
	{
		int i = 0;
		for (; i < (point.__dim - 1); ++i)
		{
			os<< point.__values[i] << " ,";
		}
		os << point.__values[i] << endl;
		return os;
	}

	istream &operator>>(istream &is, Point &point)
	{
		int i = 0;
		double d = 0.0;
		string value;
		while(getline(is, value, ','))
		{
			std::stringstream str(value);
			str >> d;
			point.setValue(i++, d);
		}
		return is;
	}
}