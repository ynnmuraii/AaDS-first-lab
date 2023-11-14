#pragma once

#include <iostream>
#include <stdlib.h>
#include <random>
#include <stdexcept>
#include <cmath>

using namespace std;

namespace vectors {

	template<typename T>
	T random(T a, T b) {
		std::random_device random_device;
		std::mt19937 generator(random_device());
		std::uniform_int_distribution<> distribution(a, b);
		T x = distribution(generator);
		return x;
	}

	template<typename T>
	struct Point {
		T x, y;

		Point() : x(0), y(0) {}
		Point(T _x, T _y) : x(_x), y(_y) {}
		Point(const Point<T>& rhs) : x(rhs.x), y(rhs.y) {}

		float lenght(Point& rhs) {
			return static_cast<float>(sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y)));
		}

		void print() {
			cout << x << " " << y << endl;
		}

		bool operator == (Point<T> rhs) {
			if ((x == rhs.x)) && (y == rhs.y)
				return true;
			return false;
		}
	};

	template<typename T>
	ostream& operator<<(ostream& os, Point<T>& point) {
		cout << point.x << " " << point.y << endl;
		return os;
	}

	template<typename T>
	class Line {
	private:
		Point<T>** _data;
		int _size;
	public:
		Line() {
			_data = new Point<T>*;
			_data[0] = new Point<T>;
			_size = 1;
		}

		Line(Point<T>& rhs) {
			
		}

	};

}