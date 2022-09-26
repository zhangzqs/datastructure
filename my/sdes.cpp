#include <bitset>
#include <iostream>
#include <sstream>
using namespace std;

/// 循环左移size位
template <size_t N>
bitset<N> rol(bitset<N> src, int size) {
    size = (size + N) % N;
    return src << size | src >> (N - size);
}

/// 十阶置换
bitset<10> P10(bitset<10> in) {
    const int table[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    bitset<10> out;
    for (int i = 0; i < 10; i++) out[i] = in[table[i] - 1];
    return out;
}

/// 8阶置换
bitset<8> P8(bitset<10> in) {
    const int table[] = {6, 3, 7, 4, 8, 5, 10, 9};
    bitset<8> out;
    for (int i = 0; i < 8; i++) out[i] = in[table[i] - 1];
    return out;
}

bitset<10> SL(bitset<10> in, int s) {
    // 5位一组分组
    bitset<5> left, right;
    for (int i = 0; i < 5; i++) left[i] = in[i];
    for (int i = 0; i < 5; i++) right[i] = in[i + 5];

    // 循环左移(实际上计算机上是循环右移)
    left = rol<5>(left, -s);
    right = rol<5>(right, -s);

    // 分组合并
    bitset<10> out;
    for (int i = 0; i < 5; i++) out[i] = left[i];
    for (int i = 0; i < 5; i++) out[i + 5] = right[i];

    return out;
}

bitset<8> IP(bitset<8> in) {
    const int table[] = {2, 6, 3, 1, 4, 8, 5, 7};
    bitset<8> out;
    for (int i = 0; i < 8; i++) out[i] = in[table[i] - 1];
    return out;
}

bitset<8> IP_rev(bitset<8> in) {
    const int table[] = {4, 1, 3, 5, 7, 2, 8, 6};
    bitset<8> out;
    for (int i = 0; i < 8; i++) out[i] = in[table[i] - 1];
    return out;
}


bitset<8> E_P(bitset<4> in) {
    const int table[] = {4, 1, 2, 3, 2, 3, 4, 1};
    bitset<8> out;
    for (int i = 0; i < 8; i++) out[i] = in[table[i] - 1];
    return out;
}

bitset<2> S0(bitset<4> in) {
    const int table[4][4] = {
        {1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
    int i = in[0] << 1 | in[3];
    int j = in[1] << 1 | in[2];
    return table[i][j];
}

bitset<2> S1(bitset<4> in) {
    const int table[4][4] = {
        {0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 1}};
    int i = in[0] << 1 | in[3];
    int j = in[1] << 1 | in[2];
    return table[i][j];
}

bitset<4> S(bitset<8> in) {
    bitset<4> in_L, in_R;
    for (int i = 0; i < 4; i++) in_L[i] = in[i];
    for (int i = 0; i < 4; i++) in_R[i] = in[4 + i];
    bitset<2> S0_out = S0(in_L);
    bitset<2> S1_out = S1(in_R);
    bitset<4> out;
    out[0] = S0_out[1];
    out[1] = S0_out[0];
    out[2] = S1_out[1];
    out[3] = S1_out[0];
    return out;
}

bitset<4> P4(bitset<4> in) {
    const int table[] = {2, 4, 3, 1};
    bitset<4> out;
    for (int i = 0; i < 8; i++) out[i] = in[table[i] - 1];    
    return out;
}

template <int T>
string reverse(bitset<T> src) {
    stringstream ss;
    for (int i = 0; i < src.size(); i++) ss << src[i];
    return ss.str();
}

bitset<8> F(bitset<8> in, bitset<8> k) {
    bitset<4> in_L, in_R;
    for (int i = 0; i < 4; i++) in_L[i] = in[i];
    for (int i = 0; i < 4; i++) in_R[i] = in[4 + i];

    bitset<4> out_L = in_L ^ P4(S(E_P(in_R) ^ k));
    bitset<4> out_R = in_R;
    bitset<8> out;
    for (int i = 0; i < 4; i++) out[i] = out_L[i];
    for (int i = 0; i < 4; i++) out[i+4] = out_R[i];
    return out;
}

bitset<8> SW(bitset<8> in) {
    bitset<4> in_L, in_R;
    for (int i = 0; i < 4; i++) in_L[i] = in[i];
    for (int i = 0; i < 4; i++) in_R[i] = in[4 + i];
    bitset<4> out_L = in_R;
    bitset<4> out_R = in_L;
    bitset<8> out;
    for (int i = 0; i < 4; i++) out[i] = out_L[i];
    for (int i = 0; i < 4; i++) out[i+4] = out_R[i];
    return out;
}

bitset<8> crypt(bitset<8> p, bitset<8> k1, bitset<8> k2) {
    // 明文p进行IP置换得p1
    bitset<8> IP_out = IP(p);

    // 对p1进行Fk1变换
    bitset<8> Fk1_out = F(IP_out, k1);

    // 对p3进行SW交换变换
    bitset<8> SW_out = SW(Fk1_out);

    // 对p4进行Fk2变换
    bitset<8> Fk2_out = F(SW_out, k2);

    // p6进行IP逆置换得密文p7
    bitset<8> IP_rev_out = IP_rev(Fk2_out);
    return IP_rev_out;
}

/// 计算子密钥k1,k2
void subkey(bitset<10> in, bitset<8>& out_k1, bitset<8>& out_k2) {
    bitset<10> m1 = P10(in);

    bitset<10> m2 = SL(m1, 1);
    out_k1 = P8(m2);

    bitset<10> m3 = SL(m2, 2);
    out_k2 = P8(m3);
}

/// 加密
bitset<8> encrypt(bitset<8> p, bitset<10> k) {
    // 求解子密钥k1, k2
    bitset<8> k1, k2;
    subkey(k, k1, k2);
    return crypt(p, k1, k2);
}

/// 解密
bitset<8> decrypt(bitset<8> p, bitset<10> k) {
    // 求解子密钥k1, k2
    bitset<8> k1, k2;
    subkey(k, k1, k2);
    return crypt(p, k2, k1);
}

int main() {
    // 密钥k
    int _k[] = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0};
    bitset<10> k;
    for (int i = 0; i < 10; i++) k[i] = _k[i];
    // 明文p
    int _p[] = {0, 1, 0, 0, 0, 0, 0, 1};
    bitset<8> p;
    for (int i = 0; i < 8; i++) p[i] = _p[i];

    auto c = encrypt(p, k);
    cout << "密文=" << reverse<8>(c) << endl;
    auto mp = decrypt(c, k);
    cout << "明文=" << reverse<8>(mp) << endl;

    return 0;
}