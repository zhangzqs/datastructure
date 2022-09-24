#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class AlphaMatrix {
   private:
    vector<char> data{};
    unordered_map<char, int> index;

   public:
    AlphaMatrix(string key) : data(vector<char>(25)) {
        // 用于记录某个字符是否已经被添加过字母矩阵
        unordered_set<char> m;
        
        // 认为i与j为同一个字符
        // 故一开始就再集合m种添加字母j视作已添加
        m.insert('j'); 

        // ss作为一个字符队列可以不断向队尾添加元素
        stringstream ss;

        // 准备将密钥串添加至队列
        for (int i = 0; i < key.size(); i++) {
            // 如果已经添加过了，即出现重复字符，那么跳过本字符
            if (m.count(key[i])) continue;
            
            // 追加字符至队列
            ss << key[i];

            // 并记录该字符已添加
            m.insert(key[i]);
        }
        // 将密钥串中需要添加到字母矩阵的字符添加到矩阵中去
        string s = ss.str();
        for (int i = 0; i < s.size(); i++) data[i] = s[i];

        // 记录矩阵插入位置的指针p
        // 初始状态应当指向密钥串的最后一个添加到字母矩阵中的位置的下一个位置
        // 即p = s.size()
        int p = s.size();

        // 遍历字母a-z
        for (char c = 'a'; c <= 'z'; c++) {
            // 若字母矩阵种已存在，则跳过
            if (m.count(c)) continue;
            data[p++] = c; // 添加
        }

        // 后续需要频繁使用到根据字母查询行号和列号的操作
        // 故直接在此处建立索引表，即map实现快速查询
        for (int i = 0; i < 25; i++) index[data[i]] = i;
        
        // 当查询字母时，视作查询字母i
        index['j'] = index['i'];
    }

    // 获取指定行列的字符
    char get(int row, int col) {
        row = (row+5) % 5;
        col = (col+5) % 5;
        return data[row * 5 + col];
    }

    // 获取指定字符的行号
    int row(char ch) {
        int idx = index[ch];
        return idx / 5;
    }

    // 获取指定字符的列号
    int column(char ch) {
        int idx = index[ch];
        return idx % 5;
    }

    // 打印输出该字母矩阵
    void display() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << data[i * 5 + j] << ' ';
            }
            cout << endl;
        }
    }
};
// 暂时不考虑p1=p2与奇数字母数的情况下的加密算法
void encryptTwoChar(char p1, char p2, char& c1, char& c2, AlphaMatrix& key) {
    // p1,p2同一行
    if (key.row(p1) == key.row(p2)) {
        // 获取所在行
        int r = key.row(p1); 

        // 获取密文c1,c2所在列
        int c1c = key.column(p1) + 1;
        int c2c = key.column(p2) + 1;

        // 读取密文c1,c2
        // get函数已经自动完成了越界时回卷处理
        c1 = key.get(r, c1c);
        c2 = key.get(r, c2c);
    }
    // p1,p2同一列
    else if (key.column(p1) == key.column(p2)) {
        // 获取所在列
        int c = key.column(p1);

        // 获取密文c1,c2所在行
        int c1r = key.row(p1) + 1;
        int c2r = key.row(p2) + 1;

        // 读取密文c1,c2
        // get函数已经自动完成了越界时回卷处理
        c1 = key.get(c1r, c);
        c2 = key.get(c2r, c);
    }
    // 不同行不同列
    else {
        // 确定p1, p2构成的矩阵
        int row1 = key.row(p1);
        int col1 = key.column(p1);
        int row2 = key.row(p2);
        int col2 = key.column(p2);

        // 取别于p1,p2的另一条对角线上的字符
        // 作为c1,c2
        c1 = key.get(row1, col2);
        c2 = key.get(row2, col1);
    }
}

string encrypt(string message, char Q, char X, AlphaMatrix& key) {
    stringstream ss;

    int p = 0;
    while(p<message.size()) {
        char p1 = message[p++];

        // 跳过空格
        while(p1 == ' ') {
            p1 = message[p++];
            ss << ' ';
        }
        char p2;
        if(p<message.size()) {
            p2 = message[p++];
            while(p2 == ' ') {
                p2 = message[p++];
                ss << ' ';
            }
        }else{
            p2 = X;
        }
        if(p1 == p2) {
            // 插入一个字母Q
            p2 = Q;
            // 此时指针p需要回退
            p--;
        }
        char c1,c2;
        encryptTwoChar(p1,p2,c1,c2,key);
        ss<<c1<<c2;
    }
    return ss.str();
}

int main() {
    AlphaMatrix am("hello");
    am.display();

    string src = "enjoy your life";
    string result = encrypt(src, 'x', 'z', am);
    cout << result<<endl;
    // string r2 = decrypt(result, ' ', ' ', am);
    // cout<<r2<<endl;
    // cout<< r2.size()<<endl;
    // for(int i=0;i<8;i++) {
    //     cout<<r2[i]<<", ";
    // }
    return 0;
}