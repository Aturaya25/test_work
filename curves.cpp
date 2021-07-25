#include <iostream>
#include <array>
#include <cmath>
#include <vector>
#include <memory>

using namespace std;

class Curve {
public:
    virtual array<float,2> getPoint(float t) = 0;
    virtual array<float,2> getDerivative(float t) = 0;
    virtual ~Curve() {}
};      


class Line : public Curve {
    array<float, 2> o_;
    array<float, 2> d_;
public:
    Line(array<float, 2> o, array<float, 2> d) : o_(o), d_(d) {}
    array<float, 2> getPoint(float t) {
        return {o_[0] + d_[0] * t, o_[1] + d_[1] * t};
    }
    array<float, 2> getDerivative(float t) {
        return d_;
    }
    ~Line() {}
};

class Ellipse : public Curve {
    float a_, b_;
public:
    Ellipse(float a, float b) : a_(a), b_(b) {}
    array<float, 2> getPoint(float t) {
        return {a_ * cos(t), b_ * sin(t)};
    }
    array <float, 2> getDerivative(float t) {
        return {-a_ * sin(t), b_ * cos(t)};
    }
    ~Ellipse() {}
};


int main() {
    vector<shared_ptr<Curve>> curves;
    for (int i = 1; i < 6; i++)
        for (int j = 1; j < 6; j++) {
            if (j % 2)
                curves.push_back(make_shared<Ellipse>(i, j));
            else {
		array<float, 2> o = {(float)i, (float)j};
		array<float, 2> d = {(float)j, (float)i};
                curves.push_back(make_shared<Line>(o, d));
	    }
	}
    for (auto curve : curves) {
        array<float, 2> point = curve->getPoint(M_PI/4);
        array<float, 2> deriv = curve->getDerivative(M_PI/4);
        cout << "Point: {" << point[0] << ", " << point[1] << "}; ";
        cout << "Derivative: {" << deriv[0] << ", " << deriv[1] << "}" << endl;
    }

    return 0;
}

