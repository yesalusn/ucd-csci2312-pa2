//
// Created by Nikki on 2/11/2016.
//
#include <iostream>
#include <sstream>
#include <algorithm>

#include "Cluster.h"

using std::endl;
using std::string;

namespace Clustering
{
	LNode::LNode(const Point& p, LNodePtr n): point(p), next(n){}

	Cluster::Cluster() : __size(0), __points(nullptr) {}

	Cluster::Cluster(const Cluster& other): __size(other.__size),
	                                        __points(nullptr)
	{
		if(other.__points != nullptr)
		{
			LNodePtr currNode = other.__points; // temp ptr to other head
			Point point(currNode->point); //copy of other data
			LNodePtr newNode = new LNode(point, nullptr); // new node to hold new data
			__points = newNode; // point this head to new node
			currNode = currNode->next; // move temp ptr
			LNodePtr thisNode = __points; // temp ptr to this head

			while(currNode != nullptr) // loop thru other data
			{
				point = currNode->point;
				newNode = new LNode(point, nullptr);
				thisNode->next = newNode;
				thisNode = thisNode->next;
				currNode = currNode->next;
			}
		}
	}

	Cluster& Cluster::operator=(const Cluster& other)
	{
		if(this != &other)
		{
			LNodePtr currNode = __points;
			LNodePtr nextNode = nullptr;
			while(currNode != nullptr && __size > 0)
			{
				LNodePtr temp = currNode;
				currNode = currNode->next;
				delete temp;
				--__size;
			}
			__points = nullptr;
			__size = other.__size;
			currNode = __points;
			nextNode = other.__points;
			while(nextNode != nullptr)
			{
				LNodePtr newNode = new LNode(nextNode->point, nullptr);
				currNode->next;
				nextNode = nextNode->next;
			}
		}
		return *this;
	}

	Cluster::~Cluster()
	{
		LNodePtr currNode = __points;
		while (currNode != nullptr && __size > 0)
		{
			LNodePtr temp = currNode;
			currNode = currNode->next;
			delete temp;
		}
		__points = nullptr;
		__size = 0;
	}

	int Cluster::getSize() const
	{
		return __size;
	}

	void Cluster::add(const Point& p)
	{
		Point point(p);
		LNodePtr newNode = new LNode(point, nullptr);
		if(__points == nullptr && __size == 0)
		{
			__points = newNode;
			++__size;
			return;
		}
		else
		{
			if(point < __points->point)
			{
				newNode->next = __points;
				__points = newNode;
				++__size;
			}
			else
			{
				LNodePtr prevNode = __points;
				LNodePtr currNode = prevNode->next;
				if(currNode != nullptr)
				{
					bool inserted = false;
					while(!(inserted) && currNode != nullptr)
					{
						if(point < currNode->point)
						{
							newNode->next = currNode;
							prevNode->next = newNode;
							inserted = true;
							++__size;
						}
						else
						{
							prevNode = currNode;
							currNode = currNode->next;
						}
					}
				}
				if(currNode == nullptr)
				{
					prevNode->next = newNode;
					++__size;
				}
			}
		}
	}

	const Point& Cluster::remove(const Point & p)
	{
		if(__points != nullptr)
		{
			if(__points->point == p)
			{
				LNodePtr temp = __points;
				__points = __points->next;
				delete temp;
				--__size;
				return p;
			}
			else
			{
				LNodePtr currNode = __points->next;
				while(currNode != nullptr)
				{
					if(currNode->point == p)
					{
						LNodePtr temp = currNode;
						currNode = currNode->next;
						delete temp;
						--__size;
						return p;
					}
					currNode = currNode->next;
				}
			}

		}
		return p;
	}

	bool Cluster::contains(const Point& p)
	{
		if(__points != nullptr)
		{
			LNodePtr currNode = __points;
			while (currNode != nullptr)
			{
				if(currNode->point == p)
					return true;
				else
					currNode = currNode->next;
			}
			return false;
		}
		else
			return false;
	}

	const Point& Cluster::operator[](unsigned int index) const
	{
		LNodePtr currNode = __points;
		for (int i = 0; i < index; ++i)
		{
			currNode = currNode->next;
		}
		return currNode->point;
	}

	Cluster& Cluster::operator+=(const Point& p)
	{
		this->add(p);
		return *this;
	}

	Cluster& Cluster::operator-=(const Point& p)
	{
		this->remove(p);
		return *this;
	}

	Cluster& Cluster::operator+=(const Cluster& c)
	{
		if (this != &c)
		{
			if(c.__points != nullptr)
			{
				if(this->__points == nullptr)
					*this = c;
				else
				{
					LNodePtr currNode = c.__points;
					while(currNode != nullptr)
					{
						if (!(this->contains(currNode->point)))
							this->add(currNode->point);
						currNode = currNode->next;
					}
				}
			}
		}
		return *this;
	}

	Cluster& Cluster::operator-=(const Cluster& c)
	{
		if (this != &c)
		{
			if(c.__points != nullptr)
			{
				if(this->__points != nullptr)
				{
					LNodePtr currNode = c.__points;
					while(currNode != nullptr)
					{
						if(this->contains(currNode->point))
							this->remove(currNode->point);
						currNode = currNode->next;
					}
				}
			}
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Cluster& c)
	{
		if(c.__points != nullptr)
		{
			LNodePtr currNode = c.__points;
			while(currNode != nullptr)
			{
				os << currNode->point;
				currNode = currNode->next;
			}
		}
		else
			os << "There is no cluster." << endl;
		return os;
	}

	std::istream& operator>>(std::istream& is, Cluster& c)
	{
		string line;
		while(getline(is, line))
		{
			std::stringstream linestream(line);
//			int d = (int)std::count(line.begin(), line.end(), " ,");
//			Point p(d);
//			linestream >> p;
		}
		return is;
	}

	bool operator==(const Cluster& c1, const Cluster& c2)
	{
		if(&c1 != &c2)
		{
			if(c1.getSize() == c2.getSize())
			{
				LNodePtr thisOne = c1.__points;
				LNodePtr thatOne = c2.__points;

				while(thisOne != nullptr && thatOne != nullptr)
				{
					if (thisOne->point != thatOne->point)
						return false;
					thisOne = thisOne->next;
					thatOne = thatOne->next;
				}
				return true;
			}
			else
				return false;
		}
		else
			return true;
	}

	bool operator!=(const Cluster& c1, const Cluster& c2)
	{
		bool notequal = true;
		if(c1 == c2)
			notequal = false;
		return notequal;
	}

	const Cluster operator+(const Cluster& c, const Point& p)
	{
		Cluster newC(c);
		newC += p;
		return newC;
	}

	const Cluster operator-(const Cluster& c, const Point& p)
	{
		Cluster newC(c);
		newC -= p;
		return newC;
	}

	const Cluster operator+(const Cluster& c, const Cluster& p)
	{
		Cluster newC(c);
		newC += p;
		return newC;
	}

	const Cluster operator-(const Cluster& c, const Cluster& p)
	{
		Cluster newC(c);
		newC -= p;
		return newC;
	}
}
