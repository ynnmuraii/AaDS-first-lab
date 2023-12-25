#include <functions/vectors.h>

using namespace std;
using namespace vectors;

int main() {
    /*Line<float> triangle = draw_broken_line_triangle<float>();
    cout << triangle*/;

    Point<float> vertex1(0, 0);
    Point<float> vertex2(7, 0);
    Point<float> vertex3(0.1, 3);

    Line<float> triangle(vertex1);
    Line<float> triangle1;

    cout << triangle;

    triangle1 = triangle + vertex2;

    triangle = vertex1 + triangle1 + vertex3;

    cout << triangle;

    return 0;
}
