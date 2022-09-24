#include <iostream>
#include <sstream>

using namespace std;

class Vector2x2 {
   public:
    int a, b;

    Vector2x2(int _a, int _b) : a(_a), b(_b) {}

    Vector2x2 mod(int n) {
        int ta = a;
        int tb = b;
        while (ta <= 0) ta += n;
        while (tb <= 0) tb += n;
        int ia = int(ta) % 26;
        int ib = int(tb) % 26;
        return Vector2x2((int)ia, (int)ib);
    }
};

// 已知 x, m
// 求(x * y) % m = 1 时 y 的值
int mul_inv(int x, int m) {
    int y = 0;

    // y 的取值范围为[0,m)
    while (y < m) {
        if ((x * y) % m == 1) {
            break;
        } else {
            y++;
            if (y == m) {
                return 0;
            }
        }
    }
    return y;
}

class Matrix2x2 {
   private:
    int a, b;
    int c, d;

   public:
    Matrix2x2(int _a, int _b, int _c, int _d) : a(_a), b(_b), c(_c), d(_d) {}

    int determinant() { return a * d - b * c; }

    // 求伴随矩阵
    Matrix2x2 getAdjugateMatrix() {
        return Matrix2x2(  //
            d, -b,         //
            -c, a          //
        );
    }

    // 求矩阵的逆
    // 注意这里伴随矩阵前的系数需要求模m乘法的逆元
    // 而不是常规的行列式倒数
    Matrix2x2 inverse() {
        return getAdjugateMatrix().mul(mul_inv(determinant(), 26));
    }

    // 矩阵x向量
    Vector2x2 mul(Vector2x2 v) {
        return Vector2x2(       //
            a * v.a + b * v.b,  //
            c * v.a + d * v.b   //
        );
    }

    // 矩阵数乘
    Matrix2x2 mul(int n) {
        return Matrix2x2(  //
            a * n, b * n,  //
            c * n, d * n   //
        );
    }

    void display() {
        cout << a << ", " << b << endl  //
             << c << ", " << d << endl;
    }
};

string encrypt(string message, Matrix2x2& key) {
    stringstream ss;
    for (int i = 0; i < message.size(); i += 2) {
        Vector2x2 m(message[i] - 'a', message[i + 1] - 'a');
        Vector2x2 c = key.mul(m).mod(26);
        ss << char(c.a + 'a') << char(c.b + 'a');
    }
    return ss.str();
}

string decrypt(string clip, Matrix2x2& key) {
    Matrix2x2 K_1 = key.inverse();
    return encrypt(clip, K_1);
}

int main() {
    Matrix2x2 K(1, 2,  //
                0, 3);

    K.inverse().display();

    string message = "thankyou";
    string clip = encrypt(message, K);
    cout << "密文：" << clip << endl;

    cout << "明文：" << decrypt(clip, K) << endl;
    return 0;
}