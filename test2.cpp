#include <bits/stdc++.h>
#include <concepts>
#include <optional>
using namespace std;

template<class type, size_t size>
class Vector {
public:
    array<type, size> ele;
    Vector() = default;
    Vector(array<type, size> arr) : ele(arr) {}

    friend istream& operator>>(istream& in, Vector& p) {
        for (size_t i = 0; i < size; i++) in >> p.ele[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const Vector& p) {
        out << "[" << p.ele[0];
        for (size_t i = 1; i < size; i++) out << ", " << p.ele[i];
        return out << "]";
    }

    Vector operator+(const Vector& other) {
        Vector tmp;
        for (size_t i = 0; i < size; i++) tmp.ele[i] = ele[i] + other.ele[i];
        return tmp;
    }
    Vector operator-(const Vector& other) {
        Vector tmp;
        for (size_t i = 0; i < size; i++) tmp.ele[i] = ele[i] - other.ele[i];
        return tmp;
    }
    Vector operator*(const type& other) {
        Vector tmp;
        for (size_t i = 0; i < size; i++) tmp.ele[i] = ele[i] * other;
        return tmp;
    }
    friend Vector operator*(const type& lhs, const Vector& rhs) { return rhs * lhs; }

    template<class T, size_t S>
    friend Vector<T, S> operator/(const Vector<T, S>& lhs, const T& rhs) {
        Vector<T, S> tmp;
        for (size_t i = 0; i < S; i++) tmp.ele[i] = lhs.ele[i] / rhs;
        return tmp;
    }

    type operator*(const Vector& other) {
        type tmp = 0;
        for (size_t i = 0; i < size; i++) tmp += ele[i] * other.ele[i];
        return tmp;
    }

    friend Vector<type, 3> operator^(const Vector<type, 3>& lhs, const Vector<type, 3>& rhs) {
        Vector<type, 3> tmp;
        tmp.ele[0] = lhs.ele[1] * rhs.ele[2] - lhs.ele[2] * rhs.ele[1];
        tmp.ele[1] = lhs.ele[2] * rhs.ele[0] - lhs.ele[0] * rhs.ele[2];
        tmp.ele[2] = lhs.ele[0] * rhs.ele[1] - lhs.ele[1] * rhs.ele[0];
        return tmp;
    }

    type getLenght() const {
        type tmp = 0;
        for (size_t i = 0; i < size; i++) tmp += ele[i] * ele[i];
        return sqrt(tmp);
    }

    std::optional<Vector> normalize() requires std::floating_point<type> {
        type len = getLenght();
        if (len == 0) return std::nullopt;
        Vector tmp;
        for (size_t i = 0; i < size; i++) tmp.ele[i] = ele[i] / len;
        return tmp;
    }

    std::optional<type> radian(const Vector& other) {
        type len1 = getLenght(), len2 = other.getLenght();
        if (len1 == 0 || len2 == 0) return std::nullopt;
        type cosTheta = (*this * other) / (len1 * len2);
        cosTheta = std::clamp(cosTheta, type(-1), type(1));
        return acos(cosTheta);
    }
};

int main() {
    Vector<double, 3> v1, v2;
    cin >> v1 >> v2;

    if (auto angle = v1.degree(v2))
        cout << "Angle: " << *angle << " degrees\n";
    else
        cout << "Angle undefined (one of the vectors is zero)\n";
}
