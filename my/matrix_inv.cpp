#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

/// 矩阵接口
template <class T>
class IMatrix {
   public:
    // 获得行
    virtual int cols() = 0;
    // 获得列
    virtual int rows() = 0;
    // 设置元素
    virtual void set(int row, int col, T e) = 0;
    // 获取元素
    virtual T get(int row, int col) = 0;

    virtual string to_string() {
        stringstream ss;
        for (int i = 0; i < rows(); i++) {
            ss << "[";
            for (int j = 0; j < cols(); j++) {
                ss << get(i, j);
                if (j != cols() - 1) ss << ",";
            }
            ss << "]" << endl;
        }
        return ss.str();
    }
};

/// 一般的数值矩阵
template <class T>
class NormalMatrix : public IMatrix<T> {
   private:
    vector<T> _vec;
    int _cols, _rows;

   public:
    explicit NormalMatrix(int rows, int cols, T defaultValue) {
        _cols = cols;
        _rows = rows;
        _vec = vector<T>(rows * cols, defaultValue);
    }

    explicit NormalMatrix(IMatrix<T>& mat) {
        _cols = mat.cols();
        _rows = mat.rows();
        _vec = vector<T>(_rows * _cols);
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                _vec[i * _cols + j] = mat.get(i, j);
            }
        }
    }

    // 获得行
    inline int cols() override { return _cols; }
    // 获得列
    inline int rows() override { return _rows; }
    // 设置元素
    inline void set(int row, int col, T e) override {
        _vec[row * cols() + col] = e;
    }
    // 获取元素
    inline T get(int row, int col) override { return _vec[row * cols() + col]; }
};

template <class T>
class CominorMatrix : public IMatrix<T> {
   private:
    IMatrix<T>& _mat;
    int _row;
    int _col;

   public:
    explicit CominorMatrix(IMatrix<T>& mat, int row, int col)
        : _mat(mat), _row(row), _col(col) {}

    // 获得行
    inline int cols() override { return _mat.cols() - 1; }
    // 获得列
    inline int rows() override { return _mat.rows() - 1; }
    // 设置元素
    inline void set(int row, int col, T e) override {
        __throw_runtime_error("CominorMatrix cannot be set value");
    }
    // 获取元素
    inline T get(int row, int col) override {
        return _mat.get(row < _row ? row : row + 1, col < _col ? col : col + 1);
    }
};

template <class T>
class TransposeMatrix : public IMatrix<T> {
   private:
    IMatrix<T>& _mat;

   public:
    explicit TransposeMatrix(IMatrix<T>& mat) : _mat(mat) {}
    // 获得行
    inline int cols() override { return _mat.rows(); }
    // 获得列
    inline int rows() override { return _mat.cols(); }
    // 设置元素
    inline void set(int row, int col, T e) override { _mat.set(col, row, e); }
    // 获取元素
    inline T get(int row, int col) override { return _mat.get(col, row); }
};

template <class T>
class AdjugateMatrix : public IMatrix<T> {
   private:
    IMatrix<T>& _mat;

   public:
    explicit AdjugateMatrix(IMatrix<T>& mat) : _mat(mat) {}
    // 获得行
    inline int cols() override { return _mat.rows(); }
    // 获得列
    inline int rows() override { return _mat.cols(); }
    // 设置元素
    inline void set(int row, int col, T e) override {
        __throw_runtime_error("AdjugateMatrix cannot be set value");
    }
    // 获取元素
    inline T get(int row, int col) override {
        // 当row+col为偶数时为正
        int sgn = (row + col) % 2 == 0 ? 1 : -1;
        CominorMatrix<T> cm(_mat, col, row);
        // 求余子式
        T cominor = determinant(cm);
        // 代数余子式
        return sgn * cominor;
    }
};

template <class T,class E>
class TransformMatrix : public IMatrix<E> {
   private:
    IMatrix<T>& _mat;
    function<E(int, int, T)> _proc;

   public:
    explicit TransformMatrix(IMatrix<T>& mat, function<E(int, int, T)> proc)
        : _mat(mat), _proc(proc) {}
    // 获得行
    inline int cols() override { return _mat.cols(); }
    // 获得列
    inline int rows() override { return _mat.rows(); }
    // 设置元素
    inline void set(int row, int col, E e) override {
        __throw_runtime_error("InversionMatrix cannot be set value");
    }
    // 获取元素
    inline E get(int row, int col) override {
        return _proc(row, col, _mat.get(row, col));
    }
};

template <class T>
class InversionMatrix : public IMatrix<double> {
   private:
    IMatrix<T>& _mat;

   public:
    explicit InversionMatrix(IMatrix<T>& mat) : _mat(mat) {}
    // 获得行
    inline int cols() override { return _mat.cols(); }
    // 获得列
    inline int rows() override { return _mat.rows(); }
    // 设置元素
    inline void set(int row, int col, double e) override {
        __throw_runtime_error("InversionMatrix cannot be set value");
    }
    // 获取元素
    inline double get(int row, int col) override {
        T det = determinant(_mat);
        AdjugateMatrix<T> am(_mat);
        TransformMatrix<T,double> tfm(am,
                               [det](int row, int col, T e) { return double(e) / double(det); });
        return tfm.get(row, col);
    }
};

template <class T>
T determinant(IMatrix<T>& mat) {
    if (mat.cols() != mat.rows()) {
        string s = mat.to_string();
        s += "determinant matrix columns not equal to rows";
        __throw_runtime_error(s.c_str());
    }
    if (mat.cols() == 1) {
        return mat.get(0, 0);
    }

    T sig = 1;
    T sum = 0;
    // 按第0行的每一列元素展开
    for (int c = 0; c < mat.cols(); c++) {
        // 求余子式
        CominorMatrix<T> cm(mat, 0, c);
        T cominor = determinant(cm);
        sum += sig * mat.get(0, c) * cominor;
        sig *= -1;
    }
    return sum;
}

int main() {
    const int m = 100;
    NormalMatrix<int> nm(m, m, 0);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            nm.set(i, j, i * m + j);
        }
    }

    InversionMatrix<int> im(nm);
    cout<< im.to_string()<<endl;
    return 0;
}
