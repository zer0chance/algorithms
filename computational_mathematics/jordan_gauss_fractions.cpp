#include <iostream>
#include <iomanip>
#include <sstream>

struct Fraction {
    int num;  // Top
    int den;  // Bottom

    Fraction() : num(0), den(1) {}
    Fraction(int n) : num(n), den(1) {}
    Fraction(int n, int d) : num(n), den(d) {
        if (den == 0) throw std::logic_error("Denominator is 0");
        simplify();
    }

    int MCD(int x, int y) const {
        return y == 0 ? (x < 0 ? -x : x) : MCD(y, x % y);
    }

    void simplify() {
        if (den < 0) {
            num *= -1;
            den *= -1;
        }

        int mcd = MCD(num, den);
        num /= mcd;
        den /= mcd;
    }

    std::string to_string() const {
        std::stringstream ss;
        if (den != 1)
            ss << num << '/' << den;
        else
            ss << num;    
        return ss.str();
    }

    Fraction& operator+=(const Fraction& rhs) {
        this->num = this->num * rhs.den + rhs.num * this->den;
        this->den *= rhs.den;
        simplify();
        return *this;
    }
    Fraction& operator-=(const Fraction& rhs) {
        this->num = this->num * rhs.den - rhs.num * this->den;
        this->den *= rhs.den;
        simplify();
        return *this;
    }
    Fraction& operator*=(const Fraction& rhs) {
        this->num *= rhs.num;
        this->den *= rhs.den;
        simplify();
        return *this;
    }
    Fraction& operator/=(const Fraction& rhs) {
        this->num *= rhs.den;
        this->den *= rhs.num;
        simplify();
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        return os << std::setw(12) << f.to_string();
    }
    friend std::ostream& operator<<(std::ostream& os, const Fraction&& f) {
        return os << std::setw(12) << f.to_string();
    }
};

const Fraction operator+(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.num * rhs.den + rhs.num * lhs.den, lhs.den * rhs.den);
}
const Fraction operator-(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.num * rhs.den - rhs.num * lhs.den, lhs.den * rhs.den);
}
const Fraction operator*(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.num * rhs.num, lhs.den * rhs.den);
}
const Fraction operator/(const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.num * rhs.den, lhs.den * rhs.num);
}

// Gauss test
// Fraction Matrix[3][4] = {
//     {-3, 1, 2, 1},  // 1
//     {2, 1, -3, -4}, // 0
//     {-4, 2, 1, -2}  // 2
// };

// #2 HW
Fraction Matrix [3][5] = {
    {4, -3, -2, 1, -2},
    {3, -1, -2, 0, 1},
    {2, 1, -2, -1, 4}
};

// #3 HW
// Fraction Matrix[4][5] = {
//     {1, 4, 0, -1, 5},
//     {2, -3, 1, 1, 3},
//     {1, 0, 2, -1, 3},
//     {0, 2, -3, 2, 3}
// };

// #6 team
// Fraction Matrix[5][6] = {
//     {6, 9, -2, -8, -8, -144},
//     {14, 11, 4, 7, 3, -32},
//     {8, 10, 2, 4, -1, -59},
//     {8, -4, 6, -5, -3, -10},
//     {-1, 6, -7, 7, 7, 14}
// };

constexpr unsigned int M = sizeof(*Matrix) / sizeof(Fraction);
constexpr unsigned int N = sizeof(Matrix) / sizeof(Fraction) / M;

void print_matrix() {
    for (int i = 0; i < N; i++) {
        std::cout << '\n';
        for (int j = 0; j < M - 1; j++) {
            std::cout << Matrix[i][j];
        }
        std::cout << "  |" << Matrix[i][N];
    }
    std::cout << '\n';
}

void gauss() {
    // Forward part
    for (int k = 0; k < N - 1; k++) {
        for (int i = k + 1; i < N; i++) {
            if (Matrix[k][k].num != 0) {
                Fraction ratio = Matrix[i][k] / Matrix[k][k];
                for (int j = k; j < M; j++) {
                    Matrix[i][j] += Matrix[k][j] * ratio * -1;
                }
                print_matrix();
            }
        } 
    }

    // Set 1 on diagonal
    for (int k = 0; k < N; k++) {
        Fraction elem = Matrix[k][k]; // If elem == 0 -> possible 0 line
        if (elem.num != 0) {
            for (int i = k; i < M; i++) {
                Matrix[k][i] /= elem;
            }
        }
    }
    print_matrix();

    // Backward part
    for (int k = N - 1; k >= 0; k--) {
        for (int i = k - 1; i >= 0; i--) {
            if (Matrix[k][k].num != 0) { // Not a 0-line
                Fraction ratio = Matrix[i][k] / Matrix[k][k];
                for (int j = M - 1; j >= k; j--) {
                    Matrix[i][j] += Matrix[k][j] * ratio * -1;
                }
                print_matrix();
            }
        }  
    }
}

int main() {
    print_matrix();
    gauss();
}
