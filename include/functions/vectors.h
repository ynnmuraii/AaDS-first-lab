#pragma once

#include <iostream>
#include <stdlib.h>
#include <random>
#include <stdexcept>
#include <cmath>
#include <vector>

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
			if ((x == rhs.x)) && (y == rhs.y) {
				return true;
			}
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
		int _count;
	public:
		Line() {
			_data = new Point<T>*;
			_data[0] = new Point<T>;
			_count = 1;
		}
		Line(Point<T>& rhs) { // по координатам
			_data = new Point<T>*;
			_data[0] = new Point<T>(rhs.x, rhs.y);
			_count = 1
		}
		Line(size_t count) {
			_data = new Point<T>*[count];
			for (int i = 0; i < count; ++i) {
				_data[i] = new Point<T>;
			}
			_count = count;
		}
		Line(int count, T x1, T x2, T y1, T y2) { // по диапазону
			_data = new Point<T>*[count];
			for (int i = 0; i < count; ++i)
				_data[i] = new Point<T>(random(x1, x2), random(y1, y2));
			_count = count;
		}
		Line(Line<T>& other) { 
			_data = new Point<T>*[other._count];
			for (int i = 0; i < other._count; ++i)
				_data[i] = new Point<T>(other[i]);
			_count = other._count;
		}
		~Line() {
			for (int i = 0; i < _count; ++i) {
				delete _data[i]
			}
			delete _data;
			cout << "Line was deleted!" << endl;
		}

		int count() {
			return _count;
		}
		float lenght() { // Вычисление длины ломанной 
			float len = 0;
			for (int i = 1; i < _count; ++i) {
				len += _data[i]->len(*_data[i - 1]);
			}
			return len;
		}
		void push_back(const Point<T>& point) {
			std::vector<Point<T>*> copy(_data, _data + _size);
			copy.push_back(new Point<T>(point));

			for (Point<T>* ptr : _data)
				delete ptr;
			_data = copy.data();
			_size++;
		}
		void push_front(const Point<T>& point) {
			std::vector<Point<T>*> copy(_data, _data + _size);
			copy.insert(copy.begin(), new Point<T>(point));

			for (Point<T>* ptr : _data)
				delete ptr;
			_data = copy.data();
			_size++;
		}

		Line& operator=(Line<T>& other) {
			Line copy(other);
			swap(copy);
			return *this;
		}
		void swap(Line<T>& rhs) {
			std::swap(_count, rhs._count);
			std::swap(_data, rhs._data);
		}
		Point<T>& operator[](size_t index) {
			if (index >= _count)
				throw ("Index is out of range!");
			return *_data[index];
		}
		Line<T> operator+(Line<T>& rhs) {
			Line<T> new_line(*_data[0]);
			for (int i = 1; i < _size; ++i) {
				new_line.push_back(*_data[i]);
			}
			for (int i = 0; i < rhs._size; ++i) {
				new_line.push_back(*rhs._data[i]);
			}
			return new_line;
		}
	};

	template<typename T>
	ostream& operator<<(ostream& os, Line<T>& line) {
		for (int i = 0; i < line.count(); ++i) {
			cout << line[i] << endl;
		}
		return os;
	}
}