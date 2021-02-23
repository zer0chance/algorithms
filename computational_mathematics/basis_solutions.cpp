#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

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
const bool operator>=(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num * rhs.den >= rhs.num * lhs.den;
}
const bool operator<=(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num * rhs.den >= rhs.num * lhs.den;
}
const bool operator>(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num * rhs.den > rhs.num * lhs.den;
}
const bool operator<(const Fraction& lhs, const Fraction& rhs) {
    return lhs.num * rhs.den < rhs.num * lhs.den;
}

// #6 team
// Fraction Matrix[5][6] = {
//     {6, 9, -2, -8, -8, -144},
//     {14, 11, 4, 7, 3, -32},
//     {8, 10, 2, 4, -1, -59},
//     {8, -4, 6, -5, -3, -10},
//     {-1, 6, -7, 7, 7, 14}
// };

// #7 team
// Fraction Matrix[4][6] = {
//     {-15,  24, -16,  17, 18,  85},
//     { 23,   6,  -9,  -6,  5,  33},
//     { 13, -20,  17, -19, -9, -48},
//     {-14, -18,  28, -17,  4,  -7}
// };

// #8 team
Fraction Matrix[4][6] = {
    {   9,  -8,  17,  12,  24,  44},
    { -16, -11,  19,   4,  16,  22},
    { -21,  10,  -6, -15, -17, -16},
    { -29,  25,  -3, -25, -19,  18}
};

// Lecture
// Fraction Matrix [3][5] = {
//     {1, 1, 2, -6, -3},
//     {1, 1, 1, -4,  0},
//     {1, 1, 0, -2,  3}
// };

constexpr unsigned int M = sizeof(*Matrix) / sizeof(Fraction);
constexpr unsigned int N = sizeof(Matrix) / sizeof(Fraction) / M;

Fraction** Basis;
int zero_lines;

#define IGNORE_ZERO_LINE(i)                         \
    bool zero_line = true;                          \
    for(int x = 0; x < M - 1; x++) {                \
        if (Matrix[i][x] != 0) {                    \
            zero_line = false;                      \
            break;                                  \
        }                                           \
    }                                               \
    if (zero_line && Matrix[i][M - 1] != 0) {       \
        std::cout << "\n\n";                        \
        throw std::logic_error("No solutions");     \
    }                                               \
    if (zero_line) {                                \
        zero_lines++;                               \
        continue;                                   \
    }

// TODO: unify printing methods
void print_matrix() {
    zero_lines = 0;
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

void print_basis(int n) {
    for (int i = 0; i < n; i++) {
        std::cout << '\n';
        for (int j = 0; j < M - 1; j++) {
            std::cout << std::setw(12) <<  Basis[i][j];
        }
        std::cout << "  |" << std::setw(12) << Basis[i][M - 1];
    }
    std::cout << '\n';
}

void print_copy(Fraction** Copy, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << '\n';
        for (int j = 0; j < M - 1; j++) {
            std::cout << std::setw(12) << Copy[i][j];
        }
        std::cout << "  |" << std::setw(12) << Copy[i][M - 1];
    }
    std::cout << '\n';
}

void gauss() {
    // Forward part
    for (int k = 0; k < N - 1; k++) {
        if (Matrix[k][k] != 0) {
            for (int i = k + 1; i < N; i++) {           
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
        if (Matrix[k][k] != 0) { // Not a 0-line
            for (int i = k - 1; i >= 0; i--) {
                Fraction ratio = Matrix[i][k] / Matrix[k][k];
                for (int j = M - 1; j >= k; j--) {
                    Matrix[i][j] += Matrix[k][j] * ratio * -1;
                }
                print_matrix();
            }
        }
    }
}

int allocate_basis() {
    if (zero_lines == 0) {
        Basis = (Fraction**) Matrix;
        return N;
    }

    int N1 = N - zero_lines;
    Basis = new Fraction*[N1];
    for (int i = 0; i < N1; i++) {
        Basis[i] = new Fraction[M];
    }

    int ib = 0;
    for (int i = 0; i < N; i++) {
        IGNORE_ZERO_LINE(i)
        for (int j = 0; j < M; j++) {
            Basis[ib][j] = Matrix[i][j];
        }
        ib++;
    }

    return N1;
}

// Returns true if at least one more set exists 
bool get_set(int *a, int n, int m) {
    int k = m;
    for (int i = k - 1; i >= 0; --i) {
        if (a[i] < n - k + i + 1) {
            ++a[i];
            for (int j = i + 1; j < k; ++j)
                a[j] = a[j - 1] + 1;
            return true;
        }
    }

    return false;
}

void print_set(int *a, int n) {
    std::cout << "Basis: ";
    for (int i = 0; i < n; i++)
        std::cout << 'x' << a[i] + 1 << " ";
    std::cout << '\n';
}

Fraction** get_basis_copy(int m) {
    Fraction **Copy = new Fraction*[m];
    for (int i = 0; i < m; i++) {
        Copy[i] = new Fraction[M];
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < M; j++) {
            Copy[i][j] = Basis[i][j];
        }
    }

    return Copy;
}

void find_basis_solution(int* a, /*rows*/ int m) {
    // Making a copy of matrix to not override original
    Fraction **Copy = get_basis_copy(m);

    // Check for solutions: basis column
    // must containt non-zero elements
    for (int i = 0; i < m; i++) {
        if (Copy[i][a[i]] == 0) {
            int j = i + 1;
            for ( ; j < m; j++) {
                if (Basis[j][a[i]] != 0) {         // Maybe it is better to 
                    for (int k = 0; k < M; k++) {  // choose suitable elem
                        Copy[i][k] += Copy[j][k];
                    }
                    break;
                }
            }
            if (j == m) {
                std::cout << "\nNo solutions in this basis\n\n";
                for (int i = 0; i < m; i++) {
                    delete[] Copy[i];
                }
                delete[] Copy;
                return;
            }
        }
    }
    print_copy(Copy, m);

    // Set all basis elements to 1
    for (int i = 0; i < m; i++) {
        if (Copy[i][a[i]] != 1) {
            Fraction divisor = Copy[i][a[i]];
            for (int j = 0; j < M; j++) {
                Copy[i][j] /= divisor;
            }
            print_copy(Copy, m);
        }
    }

    // All other vars in column a[i] must be 0
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i == j) continue;
            if (Copy[j][a[i]] != 0) {
                Fraction ratio = Copy[j][a[i]] / Copy[i][a[i]];
                for (int k = 0; k < M; k++) {
                    Copy[j][k] += Copy[i][k] * ratio * -1;
                }
            }
            print_copy(Copy, m);
        }
    }

    // Check for possible breaks in main diagonal
    for (int i = 0; i < m; i++) {
        if (Copy[i][a[i]] != 1) {
            Fraction divisor = Copy[i][a[i]];
            for (int j = 0; j < M; j++) {
                Copy[i][j] /= divisor;
            }
            print_copy(Copy, m);
        }
    }
    
    Fraction solution[M - 2];
    
    for (int i = 0; i < m; i++) {
        solution[a[i]] = Copy[i][M - 1]; 
    }


    std::cout << '\n' << std::setw(22) << "Solution: (";
    for (int i = 0; i < M - 2; i++) {
        std::cout << solution[i] << ", ";
    }
    std::cout << solution[M - 2] << ")\n\n";

    for (int i = 0; i < m; i++) {
        delete[] Copy[i];
    }
    delete[] Copy;
}

int main() {
    print_matrix();
    gauss();
    int N1 = allocate_basis();

    std::cout << "\n\nAnswer:\n";
    print_basis(N1);

    int *a;
    int n = M - 2; // from how
    int m = N1;    // by how

    a = new int[n];

    for (int i = 0; i < n; i++)
        a[i] = i;

    std::cout << "\n\nBasis solutions:\n\n";
    print_set(a, m);
    find_basis_solution(a, m);

    if (n >= m) {
        while (get_set(a, n, m)) {
            print_set(a, m);
            find_basis_solution(a, m);
        }
    }
}
