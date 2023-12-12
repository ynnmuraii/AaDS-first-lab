#include <functions/vectors.h>

using namespace std;
using namespace vectors;

int main() {
    Line<float> triangle = draw_broken_line_triangle<float>();
    cout << triangle;

    return 0;
}
