#include <iostream>  
#include <string>  
#include <cstring>  
#include <iomanip>  
#include <Windows.h>
using namespace std;

struct TreeNode {   //树结点
    string name;
    char val;   //值
    TreeNode* Rnext;    //右
    TreeNode* Lnext;    //左
};

int flag = 0;   //0——正确 1——错误
int k = 0;
char sentence[50];
TreeNode* lexp();   //lexp -> atom | list
TreeNode* atom();   //atom -> number | identifier
TreeNode* list();   //list -> ( lexp_seq )
TreeNode* lexp_seq();   //lexp_seq -> lexp lexp_seq_
TreeNode* lexp_seq_();  //lexp_seq_ -> lexp lexp_seq_ | null
void PrintTree(TreeNode* treeNode, int depth);
char ch;

int main() {
    cout << "输入：";
    cin >> sentence;
    cout << endl;
    ch = sentence[k];
    TreeNode* head = lexp();
    if (k <= strlen(sentence) - 1)
        flag = 1;
    if (flag == 0) {
        cout << "语法树生成:" << endl;
        PrintTree(head, 0);
        cout << endl << "语法正确" << endl;
    }
    else {
        cout << "语法树生成:" << endl;
        PrintTree(head, 0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        cout << "语法错误" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
    }
}

TreeNode* lexp()
{
    TreeNode* treeNode = nullptr;
    if (ch >= 'a' && ch <= 'z') {
        treeNode = atom();
    }
    else if (ch >= '0' && ch <= '9') {
        treeNode = atom();
    }
    else if (ch == '(') {
        treeNode = list();
    }
    else {
        flag = 1;
        return nullptr;
    }
    return treeNode;
}

TreeNode* atom()
{
    TreeNode* treeNode = nullptr;
    if (ch >= 'a' && ch <= 'z') {
        treeNode = new TreeNode();
        treeNode->name = "ID";
        treeNode->val = ch;
        treeNode->Lnext = nullptr;
        treeNode->Rnext = nullptr;
        k++;
        ch = sentence[k];
    }
    else if (ch >= '0' && ch <= '9') {
        treeNode = new TreeNode();
        treeNode->name = "NUM";
        treeNode->val = ch;
        treeNode->Lnext = nullptr;
        treeNode->Rnext = nullptr;
        k++;
        ch = sentence[k];
    }
    else {
        flag = 1;
        return nullptr;
    }
    return treeNode;
}

TreeNode* list()
{
    TreeNode* treeNode = nullptr;
    if (ch == '(') {
        treeNode = new TreeNode();
        treeNode->name = "LB";
        treeNode->val = ch;
        treeNode->Lnext = nullptr;
        treeNode->Rnext = nullptr;

        k++;
        ch = sentence[k];

        treeNode->Lnext = lexp_seq();

        if (ch == ')') {
            treeNode->Rnext = new TreeNode();
            treeNode->Rnext->name = "RB";
            treeNode->Rnext->val = ch;
            treeNode->Rnext->Lnext = nullptr;
            treeNode->Rnext->Rnext = nullptr;
            k++;
            ch = sentence[k];
        }
    }
    else {
        flag = 1;
        return nullptr;
    }
    return treeNode;
}

TreeNode* lexp_seq()
{
    TreeNode* treeNode = nullptr;
    if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch == '(')) {
        treeNode = lexp();
        if (flag == 0) {
            TreeNode* treeNode2 = treeNode;
            while (treeNode2->Rnext)
                treeNode2 = treeNode->Rnext;
            treeNode2->Rnext = lexp_seq_();
        }
    }
    else {
        flag = 1;
    }
    return treeNode;
}

TreeNode* lexp_seq_()
{
    TreeNode* treeNode = nullptr;
    if ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch == '(')) {
        treeNode = lexp();
        if (flag == 0) {
            TreeNode* treeNode2 = treeNode;
            while (treeNode2->Rnext)
                treeNode2 = treeNode->Rnext;
            treeNode2->Rnext = lexp_seq_();
        }
    }
    else if (ch == ')') {
        treeNode = nullptr;
    }
    else {
        flag = 1;
    }
    return treeNode;
}

void PrintTree(TreeNode* treeNode, int depth) {
    if (treeNode) {
        int d = depth;
        while (d) {
            cout << setiosflags(ios::left) << setw(7) << " " << resetiosflags(ios::left);
            d--;
        }
        cout << treeNode->name << ":" << treeNode->val << endl;
        if (treeNode->Lnext)
            PrintTree(treeNode->Lnext, depth + 1);
        if (treeNode->Rnext)
            PrintTree(treeNode->Rnext, depth);
    }
}