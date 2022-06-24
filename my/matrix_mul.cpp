#include <iostream>
using namespace std;

class Matrix {
   private:
    float* data;
    int rows, cols;

   public:
    Matrix(int _rows, int _cols) : rows(_rows), cols(_cols) {
        data = new float[rows * cols];
        for (int i = 0; i < rows * cols; i++) {
            data[i] = 0;
        }
    }

    inline int getRows() const { return rows; }
    inline int getCols() const { return cols; }

    float get(int row, int col) const { return data[row * cols + col]; }

    void set(int row, int col, float e) { data[row * cols + col] = e; }

    Matrix mul(const Matrix& mat) {
        // 第一矩阵的列数 = 第二矩阵的行数
        // mn矩阵*np矩阵 = mp矩阵
        Matrix newMat(this->rows, mat.cols);
        for (int i = 0; i < newMat.rows; i++) {
            for (int j = 0; j < newMat.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    newMat.set(i, j,
                               newMat.get(i, j) + get(i, k) * mat.get(k, j));
                }
            }
        }
        return newMat;
    }
};

ostream& operator<<(ostream& out, const Matrix& mat) {
    for (int i = 0; i < mat.getRows(); i++) {
        for (int j = 0; j < mat.getCols(); j++) {
            out << mat.get(i, j) << ", ";
        }
        out << endl;
    }
    return out;
}

int main() {
    Matrix m1(2, 2);
    m1.set(0, 0, 1);
    m1.set(0, 1, 2);
    m1.set(1, 0, 3);
    m1.set(1, 1, 4);
    cout << m1 << endl;

    Matrix m2(2, 1);
    m2.set(0, 0, 3);
    m2.set(1, 0, 4);
    cout << m2 << endl;

    Matrix m3 = m1.mul(m2);
    cout << m3 << endl;
    return 0;
}