#pragma once

#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<stdexcept>
#include<vector>
#include<complex>
#include<random>

#define M_PI 3.14159

using namespace std;

namespace vectors {

	template<typename T>
	struct Point {
		T x, y;

		Point() : x(0), y(0) {}
		Point(T _x, T _y) : x(_x), y(_y) {}
		Point(std::complex<T> _x, std::complex<T> _y) : x(_x), y(_y) {} // Добавил комплексн.
		Point(const Point<T>& rhs) : x(rhs.x), y(rhs.y) {}

		void print() {
			cout << x << " " << y << endl;
		}

		bool operator == (Point<T> rhs) {
			if ((x == rhs.x) && (y == rhs.y)) {
				return true;
			}
			return false;
		}

		bool operator!=(const Point<T>& a) {
			return !(*this == a);
		}
	};

	template<typename U>
	double length(Point<complex<U>>& a, Point<complex<U>>& b) {
		return fabs(sqrt(pow(a._x.real() - b._x.real(), 2) + pow(a._y.real() - b._y.real(), 2)));
	}
	template<typename T>
	double length(Point<T>& a, Point<T>& b) {
		return sqrt(pow(a._x - b._x, 2) + pow(a._y - b._y, 2));
	}

	template<typename T>
	ostream& operator<<(ostream& os, Point<T>& point) {
		cout << point.x << " " << point.y << endl;
		return os;
	}
	template<typename T>
	T random(T x, T y) {
		std::random_device random_device;
		std::mt19937 generator(random_device());
		std::uniform_int_distribution<> distribution(x, y);
		T x = distribution(generator);
		return x;
	}

	template<typename T>
	complex<T> random(complex<T> m1, complex<T> m2) {
		std::random_device random_device;
		std::mt19937 generator(random_device());
		std::uniform_real_distribution<> real_distribution(m1.real(), m2.real());
		std::uniform_real_distribution<> imag_distribution(m1.imag(), m2.imag());

		T real_part = real_distribution(generator);
		T imag_part = imag_distribution(generator);

		return complex<T>(real_part, imag_part);
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
			_count = 1;
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
				delete _data[i];
			}
			delete _data;
			cout << "Line was deleted!" << endl;
		}

		int count() {
			return _count;
		}
		double length_line () {
			double lenght = 0;
			for (size_t i = 1; i < _count; i++)
			{
				lenght += length(_data[i], _data[i - 1]);
			}
			return lenght;
		}
		void push_back(Point<T>&& point) { // Сложение ломаной и вершины
			Point<T>** copy = new Point<T>*[_count + 1];
			for (int i = 0; i < _count; ++i)
				copy[i] = new Point<T>(*_data[i]);
			copy[_count] = new Point<T>(point);
			for (int i = 0; i < _count; ++i)
				delete _data[i];
			delete[] _data;
			_data = copy;
			_count++;
		}
		void push_front(Point<T>&& point) { // Сложение вершины и ломаной
			Point<T>** copy = new Point<T>*[_count + 1];
			for (int i = 1; i < _count + 1; ++i)
				copy[i] = new Point<T>(*_data[i - 1]);
			copy[0] = new Point<T>(point);
			for (int i = 0; i < _count; ++i)
				delete _data[i];
			delete[] _data;
			_data = copy;
			_count++;
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
		Line<T> operator+(const Line<T>& rhs) const {
			Line<T> result(*this);
			for (int i = 0; i < rhs._count; ++i) {
				result.push_back(*rhs._data[i]);
			}
			return result;
		}
		Line<T>& operator+=(Point<T>&& point) {
			push_back(std::move(point));
			return *this;
		}
		Line<T>& operator+(Point<T>&& point) {
			push_front(std::move(point));
			return *this;
		}
	};

	template<typename T>
	ostream& operator<<(ostream& os, Line<T>& line) {
		for (int i = 0; i < line.count(); ++i) {
			cout << line[i] << endl;
		}
		return os;
	}

	template<typename T>
	Line<T> draw_broken_line_triangle() {
		T a;
		float alpha;

		cout << "Enter the length of the side (a): ";
		cin >> a;
		cout << "Enter the vertex angle (alpha) in degrees: ";
		cin >> alpha;

		double angle = alpha * M_PI / 180.0;

		Line<T> triangle;

		Point<T> vertex(0, 0);
		triangle.push_back(std::move(vertex));

		float x1 = a * cos(angle);
		float y1 = a * sin(angle);
		Point<T> point1(x1, y1);
		triangle.push_back(std::move(point1));

		float x2 = -a * cos(angle);
		float y2 = a * sin(angle);
		Point<T> point2(x2, y2);
		triangle.push_back(std::move(point2));

		return triangle;
	}
}