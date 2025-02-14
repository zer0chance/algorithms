#include <iostream>
#include <iomanip>
#include <sstream>

struct Fraction {
    long long num;
    long long den;

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
        return os << f.to_string();
    }
    friend std::ostream& operator<<(std::ostream& os, const Fraction&& f) {
        return os << f.to_string();
    }
    friend std::istream& operator>>(std::istream& is, Fraction& f) {
        return is >> f.num;
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
const bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num == rhs.num && lhs.den == rhs.den;
}
const bool operator!=(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num != rhs.num;
}

#ifdef DEBUG
// Gauss test
// Fraction Matrix[3][4] = {
//     {-3, 1, 2, 1},  // 1
//     {2, 1, -3, -4}, // 0
//     {-4, 2, 1, -2}  // 2
// };

// #2 HW
// Fraction Matrix [3][5] = {
//     {4, -3, -2, 1, -2},
//     {3, -1, -2, 0, 1},
//     {2, 1, -2, -1, 4}
// };

// #3 HW
Fraction Matrix[4][5] = {
    {1, 4, 0, -1, 5},
    {2, -3, 1, 1, 3},
    {1, 0, 2, -1, 3},
    {0, 2, -3, 2, 3}
};

// #1 team
// Fraction Matrix[5][6] = {
//     {3, 1, 5, -2, 3, 35},  
//     {4, 3, -7, 5, 6, 54},
//     {-7, 5, 4, 1, -1, -96},
//     {1, 4, 1, -3, -10, -71},
//     {6, -9, -8, -8, -2, 59}
// };

// #6 team
// Fraction Matrix[5][6] = {
//     {6, 9, -2, -8, -8, -144},
//     {14, 11, 4, 7, 3, -32},
//     {8, 10, 2, 4, -1, -59},
//     {8, -4, 6, -5, -3, -10},
//     {-1, 6, -7, 7, 7, 14}
// };

// #8 team
// Fraction Matrix[5][6] = {
//     {-1, 13, -16, -6, 8, 152},  
//     {5, 16, 12, 11, -7, 62},
//     {17, 12, 1, 18, 9, 298},
//     {15, -15, 3, 1, -7, -127},
//     {-14, -13, -7, -5, -11, -190}
// };

// Fraction Matrix[2][4] = {
//     {1, 2, 3, 4},
//     {4, 3, 4, 7},
// };

// Fraction Matrix [3][5] = {
//     {3, 2, 5, 4, 3},
//     {1, -1, -1, -4, -2},
//     {4, 1, 4, 0, 2}
// };

constexpr unsigned int M = sizeof(*Matrix) / sizeof(Fraction);
constexpr unsigned int N = sizeof(Matrix) / sizeof(Fraction) / M;
#else
Fraction** Matrix;
unsigned int N;
unsigned int M;
#endif

#define IGNORE_ZERO_LINE(i) \
    bool zero_line = true; \
    for(int x = 0; x < M - 1; x++) { \
        if (Matrix[i][x] != 0) { \
            zero_line = false; \
            break; \
        } \
    } \
    if (zero_line && Matrix[i][M - 1].num != 0) { \
        std::cout << "\n\n"; \
        throw std::logic_error("No solutions"); } \
    if (zero_line) continue;

void print_matrix() {
    for (int i = 0; i < N; i++) {
        IGNORE_ZERO_LINE(i)
        std::cout << '\n';
        for (int j = 0; j < M - 1; j++) {
            std::cout << std::setw(12) <<  Matrix[i][j];
        }
        std::cout << "  |" << std::setw(12) << Matrix[i][M - 1];
    }
    std::cout << '\n';
}

void gauss() {
    // Forward part
    for (int k = 0; k < N - 1; k++) {
        for (int i = k + 1; i < N; i++) {
            if (Matrix[k][k] != 0) {
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
        if (elem != 0) {
            for (int i = k; i < M; i++) {
                Matrix[k][i] /= elem;
            }
        }
    }
    print_matrix();

    // Backward part
    for (int k = N - 1; k >= 0; k--) {
        for (int i = k - 1; i >= 0; i--) {
            if (Matrix[k][k] != 0) { // Not a 0-line
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
#ifndef DEBUG
    std::cout << "Rows: ";
    std::cin >> N;
    std::cout << "Columns: ";
    std::cin >> M;

    Matrix = new Fraction*[N];
    for (int i = 0; i < N; i++) {
        Matrix[i] = new Fraction[M];
    }

    for (int i = 0; i < N; i++) {
        std::cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < M; j++)
            std::cin >> Matrix[i][j];
    }
#endif

    print_matrix();
    gauss();
    std::cout << "\n\nAnswer:\n";
    
    for (int i = 0; i < N; i++) {
        IGNORE_ZERO_LINE(i)
        std::cout << 'x' << i + 1 << " = " << Matrix[i][M-1];
        for (int j = 0; j < M - 1; j++) {
            if (j != i && Matrix[i][j] != 0) {
                if (Matrix[i][j].num > 0)
                    std::cout << " - " << Matrix[i][j] << 'x' << j + 1;
                else
                    std::cout << " + " << -1 * Matrix[i][j] << 'x' << j + 1;
            }
        }
        std::cout << '\n';
    }

#ifndef DEBUG
    for (int i = 0; i < N; i++) {
        delete[] Matrix[i]; 
    }
    delete[] Matrix;
#endif
}
