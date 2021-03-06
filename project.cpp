﻿// 魔方大作业.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
/***********************************************************
 *            -----------
 *            |         |
 *            |   Up_0  |
 *            |         |
 * ------------------------------------------
 * |          |         |         |         |
 * |  Left_1  | Front_2 | Right_3 |  Back_4 |
 * |          |         |         |         |
 * ------------------------------------------
 *            |         |
 *            |  Down_5 |
 *            |         |
 *            -----------
 * 用cube[6][3][3]表示魔方状态, [6]代指六个面, 以如上方式对应
 *                             [3][3]代指行列 |  [0][0]  [0][1]  [0][2]  |
 *                                           |  [1][0]  [1][1]  [1][2]  |
 *                                           |  [2][0]  [2][1]  [2][2]  |
 *
 * R-红色  B-蓝色  Y-黄色  G-绿色  O-橙色  W-白色
 * *******************************************************/
#include <iostream>
#include <vector>
using namespace std;

//== Global Variables and Structures ==//
char cube[6][3][3] = { 0 }; //表示魔方状态
struct edge_pieces {
    char face1;
    char face2;
    int face1_pos[6][3][3] = { {{0}} };
    int face2_pos[6][3][3] = { {{0}} };
};
struct corner_pieces {
    char face1;
    char face2;
    char face3;
    int face1_pos[6][3][3] = { {{0}} };
    int face2_pos[6][3][3] = { {{0}} };
    int face3_pos[6][3][3] = { {{0}} };
};
vector <int> out; //顺0, 1, 2, 3, 4, 5, 逆10, 11, 12, 13, 14, 15


// ==== Claim of Functions
void face_ckw(int face);
void face_ccw(int face);
void function_1();
void function_2();
void function_3();
void function_4();
void function_5();
void function_6();
void function_7();
void function_8();
void function_9();
void function_10();
//== Functions ==//

void refine()
{
    if (out.empty())
        return;
    int cnt3 = 0;
    auto i = out.begin();
    while (i != out.end())
    {
        if (i + 1 == out.end())
            break;
        if (*i != *(i + 1))
            cnt3 = 0;
        else
            cnt3++;
        if (cnt3 == 2)
        {
            int p = *i;
            i = out.erase(i - 1, i + 2);
            if (p >= 10)
                out.insert(i, p - 10);
            else
                out.insert(i, p + 10);
            cnt3 = 0;
            i = out.begin();
            continue;
        }
        if (abs(*i - *(i + 1)) == 10)
        {
            out.erase(i, i + 2);
            i = out.begin();
            continue;
        }
        i++;
    }
}
void print()
{
    for (vector<int>::iterator i = out.begin(); i != out.end(); i++)
    {
        switch (*i)
        {
        case 0:
            cout << "U ";
            break;
        case 1:
            cout << "L ";
            break;
        case 2:
            cout << "F ";
            break;
        case 3:
            cout << "R ";
            break;
        case 4:
            cout << "B ";
            break;
        case 5:
            cout << "D ";
            break;
        case 10:
            cout << "Ui ";
            break;
        case 11:
            cout << "Li ";
            break;
        case 12:
            cout << "Fi ";
            break;
        case 13:
            cout << "Ri ";
            break;
        case 14:
            cout << "Bi ";
            break;
        case 15:
            cout << "Di ";
            break;
        }
    }
}

void search_corners(corner_pieces* corner)//寻找特定角块,
{//每个块的顺序：abc,acb,bac,bca,cab,cba
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
            {
                (*corner).face1_pos[i][j][k] = 0;
                (*corner).face2_pos[i][j][k] = 0;
                (*corner).face3_pos[i][j][k] = 0;
            }
    if (cube[0][0][2] == (*corner).face1 && cube[4][0][0] == (*corner).face2 && cube[3][0][2] == (*corner).face3)//第一大种
    {
        (*corner).face1_pos[0][0][2] = 1;
        (*corner).face2_pos[4][0][0] = 1;
        (*corner).face3_pos[3][0][2] = 1;
    }
    else if (cube[0][0][2] == (*corner).face1 && cube[3][0][2] == (*corner).face2 && cube[4][0][0] == (*corner).face3)
    {
        (*corner).face1_pos[0][0][2] = 1;
        (*corner).face2_pos[3][0][2] = 1;
        (*corner).face3_pos[4][0][0] = 1;
    }
    else if (cube[4][0][0] == (*corner).face1 && cube[0][0][2] == (*corner).face2 && cube[3][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[4][0][0] = 1;
        (*corner).face2_pos[0][0][2] = 1;
        (*corner).face3_pos[3][0][2] = 1;
    }
    else if (cube[4][0][0] == (*corner).face1 && cube[3][0][2] == (*corner).face2 && cube[0][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[4][0][0] = 1;
        (*corner).face2_pos[3][0][2] = 1;
        (*corner).face3_pos[0][0][2] = 1;
    }
    else if (cube[3][0][2] == (*corner).face1 && cube[0][0][2] == (*corner).face2 && cube[4][0][0] == (*corner).face3)
    {
        (*corner).face1_pos[3][0][2] = 1;
        (*corner).face2_pos[0][0][2] = 1;
        (*corner).face3_pos[4][0][0] = 1;
    }
    else if (cube[3][0][2] == (*corner).face1 && cube[4][0][0] == (*corner).face2 && cube[0][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[3][0][2] = 1;
        (*corner).face2_pos[4][0][0] = 1;
        (*corner).face3_pos[0][0][2] = 1;
    }
    else if (cube[0][0][0] == (*corner).face1 && cube[4][0][2] == (*corner).face2 && cube[1][0][0] == (*corner).face3)//第二大种
    {
        (*corner).face1_pos[0][0][0] = 1;
        (*corner).face2_pos[4][0][2] = 1;
        (*corner).face3_pos[1][0][0] = 1;
    }
    else if (cube[0][0][0] == (*corner).face1 && cube[1][0][0] == (*corner).face2 && cube[4][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[0][0][0] = 1;
        (*corner).face2_pos[1][0][0] = 1;
        (*corner).face3_pos[4][0][2] = 1;
    }
    else if (cube[4][0][2] == (*corner).face1 && cube[0][0][0] == (*corner).face2 && cube[1][0][0] == (*corner).face3)
    {
        (*corner).face1_pos[4][0][2] = 1;
        (*corner).face2_pos[0][0][0] = 1;
        (*corner).face3_pos[1][0][0] = 1;
    }
    else if (cube[4][0][2] == (*corner).face1 && cube[1][0][0] == (*corner).face2 && cube[0][0][0] == (*corner).face3)
    {
        (*corner).face1_pos[4][0][2] = 1;
        (*corner).face2_pos[1][0][0] = 1;
        (*corner).face3_pos[0][0][0] = 1;
    }
    else if (cube[1][0][0] == (*corner).face1 && cube[0][0][0] == (*corner).face2 && cube[4][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[1][0][0] = 1;
        (*corner).face2_pos[0][0][0] = 1;
        (*corner).face3_pos[4][0][2] = 1;
    }
    else if (cube[1][0][0] == (*corner).face1 && cube[4][0][2] == (*corner).face2 && cube[0][0][0] == (*corner).face3)
    {
        (*corner).face1_pos[1][0][0] = 1;
        (*corner).face2_pos[4][0][2] = 1;
        (*corner).face3_pos[0][0][0] = 1;
    }
    else if (cube[0][2][0] == (*corner).face1 && cube[1][0][2] == (*corner).face2 && cube[2][0][0] == (*corner).face3)//第三大种002、100、402
    {
        (*corner).face1_pos[0][2][0] = 1;
        (*corner).face2_pos[1][0][2] = 1;
        (*corner).face3_pos[2][0][0] = 1;
    }
    else if (cube[0][2][0] == (*corner).face1 && cube[2][0][0] == (*corner).face2 && cube[1][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[0][2][0] = 1;
        (*corner).face2_pos[2][0][0] = 1;
        (*corner).face3_pos[1][0][2] = 1;
    }
    else if (cube[1][0][2] == (*corner).face1 && cube[0][2][0] == (*corner).face2 && cube[2][0][0] == (*corner).face3)
    {
        (*corner).face1_pos[1][0][2] = 1;
        (*corner).face2_pos[0][2][0] = 1;
        (*corner).face3_pos[2][0][0] = 1;
    }
    else if (cube[1][0][2] == (*corner).face1 && cube[2][0][0] == (*corner).face2 && cube[0][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[1][0][2] = 1;
        (*corner).face2_pos[2][0][0] = 1;
        (*corner).face3_pos[0][2][0] = 1;
    }
    else if (cube[2][0][0] == (*corner).face1 && cube[0][2][0] == (*corner).face2 && cube[1][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[2][0][0] = 1;
        (*corner).face2_pos[0][2][0] = 1;
        (*corner).face3_pos[1][0][2] = 1;
    }
    else if (cube[2][0][0] == (*corner).face1 && cube[1][0][2] == (*corner).face2 && cube[0][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[2][0][0] = 1;
        (*corner).face2_pos[1][0][2] = 1;
        (*corner).face3_pos[0][2][0] = 1;
    }
    else if (cube[0][2][2] == (*corner).face1 && cube[2][0][2] == (*corner).face2 && cube[3][0][0] == (*corner).face3)//第四大种
    {
        (*corner).face1_pos[0][2][2] = 1;
        (*corner).face2_pos[2][0][2] = 1;
        (*corner).face3_pos[3][0][0] = 1;
    }
    else if (cube[0][2][2] == (*corner).face1 && cube[3][0][0] == (*corner).face2 && cube[2][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[0][2][2] = 1;
        (*corner).face2_pos[3][0][0] = 1;
        (*corner).face3_pos[2][0][2] = 1;
    }
    else if (cube[3][0][0] == (*corner).face1 && cube[0][2][2] == (*corner).face2 && cube[2][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[3][0][0] = 1;
        (*corner).face2_pos[0][2][2] = 1;
        (*corner).face3_pos[2][0][2] = 1;
    }
    else if (cube[3][0][0] == (*corner).face1 && cube[2][0][2] == (*corner).face2 && cube[0][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[3][0][0] = 1;
        (*corner).face2_pos[2][0][2] = 1;
        (*corner).face3_pos[0][2][2] = 1;
    }
    else if (cube[2][0][2] == (*corner).face1 && cube[0][2][2] == (*corner).face2 && cube[3][0][0] == (*corner).face3)
    {
        (*corner).face1_pos[2][0][2] = 1;
        (*corner).face2_pos[0][2][2] = 1;
        (*corner).face3_pos[3][0][0] = 1;
    }
    else if (cube[2][0][2] == (*corner).face1 && cube[3][0][0] == (*corner).face2 && cube[0][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[2][0][2] = 1;
        (*corner).face2_pos[3][0][0] = 1;
        (*corner).face3_pos[0][2][2] = 1;
    }
    else if (cube[1][2][0] == (*corner).face1 && cube[4][2][2] == (*corner).face2 && cube[5][2][0] == (*corner).face3)//第五大种
    {
        (*corner).face1_pos[1][2][0] = 1;
        (*corner).face2_pos[4][2][2] = 1;
        (*corner).face3_pos[5][2][0] = 1;
    }
    else if (cube[1][2][0] == (*corner).face1 && cube[5][2][0] == (*corner).face2 && cube[4][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[1][2][0] = 1;
        (*corner).face2_pos[5][2][0] = 1;
        (*corner).face3_pos[4][2][2] = 1;
    }
    else if (cube[4][2][2] == (*corner).face1 && cube[1][2][0] == (*corner).face2 && cube[5][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[4][2][2] = 1;
        (*corner).face2_pos[1][2][0] = 1;
        (*corner).face3_pos[5][2][0] = 1;
    }
    else if (cube[4][2][2] == (*corner).face1 && cube[5][2][0] == (*corner).face2 && cube[1][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[4][2][2] = 1;
        (*corner).face2_pos[5][2][0] = 1;
        (*corner).face3_pos[1][2][0] = 1;
    }
    else if (cube[5][2][0] == (*corner).face1 && cube[1][2][0] == (*corner).face2 && cube[4][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[5][2][0] = 1;
        (*corner).face2_pos[1][2][0] = 1;
        (*corner).face3_pos[4][2][2] = 1;
    }
    else if (cube[5][2][0] == (*corner).face1 && cube[4][2][2] == (*corner).face2 && cube[1][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[5][2][0] = 1;
        (*corner).face2_pos[4][2][2] = 1;
        (*corner).face3_pos[1][2][0] = 1;
    }
    else if (cube[1][2][2] == (*corner).face1 && cube[2][2][0] == (*corner).face2 && cube[5][0][0] == (*corner).face3)//第六大种
    {
        (*corner).face1_pos[1][2][2] = 1;
        (*corner).face2_pos[2][2][0] = 1;
        (*corner).face3_pos[5][0][0] = 1;
    }
    else if (cube[1][2][2] == (*corner).face1 && cube[5][0][0] == (*corner).face2 && cube[2][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[1][2][2] = 1;
        (*corner).face2_pos[5][0][0] = 1;
        (*corner).face3_pos[2][2][0] = 1;
    }
    else if (cube[2][2][0] == (*corner).face1 && cube[1][2][2] == (*corner).face2 && cube[5][0][0] == (*corner).face3)
    {
        (*corner).face1_pos[2][2][0] = 1;
        (*corner).face2_pos[1][2][2] = 1;
        (*corner).face3_pos[5][0][0] = 1;
    }
    else if (cube[2][2][0] == (*corner).face1 && cube[5][0][0] == (*corner).face2 && cube[1][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[2][2][0] = 1;
        (*corner).face2_pos[5][0][0] = 1;
        (*corner).face3_pos[1][2][2] = 1;
    }
    else if (cube[5][0][0] == (*corner).face1 && cube[1][2][2] == (*corner).face2 && cube[2][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[5][0][0] = 1;
        (*corner).face2_pos[1][2][2] = 1;
        (*corner).face3_pos[2][2][0] = 1;
    }
    else if (cube[5][0][0] == (*corner).face1 && cube[2][2][0] == (*corner).face2 && cube[1][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[5][0][0] = 1;
        (*corner).face2_pos[2][2][0] = 1;
        (*corner).face3_pos[1][2][2] = 1;
    }
    else if (cube[2][2][2] == (*corner).face1 && cube[3][2][0] == (*corner).face2 && cube[5][0][2] == (*corner).face3)//第七大种002、100、402
    {
        (*corner).face1_pos[2][2][2] = 1;
        (*corner).face2_pos[3][2][0] = 1;
        (*corner).face3_pos[5][0][2] = 1;
    }
    else if (cube[2][2][2] == (*corner).face1 && cube[5][0][2] == (*corner).face2 && cube[3][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[2][2][2] = 1;
        (*corner).face2_pos[5][0][2] = 1;
        (*corner).face3_pos[3][2][0] = 1;
    }
    else if (cube[3][2][0] == (*corner).face1 && cube[2][2][2] == (*corner).face2 && cube[5][0][2] == (*corner).face3)
    {
        (*corner).face1_pos[3][2][0] = 1;
        (*corner).face2_pos[2][2][2] = 1;
        (*corner).face3_pos[5][0][2] = 1;
    }
    else if (cube[3][2][0] == (*corner).face1 && cube[5][0][2] == (*corner).face2 && cube[2][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[3][2][0] = 1;
        (*corner).face2_pos[5][0][2] = 1;
        (*corner).face3_pos[2][2][2] = 1;
    }
    else if (cube[5][0][2] == (*corner).face1 && cube[2][2][2] == (*corner).face2 && cube[3][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[5][0][2] = 1;
        (*corner).face2_pos[2][2][2] = 1;
        (*corner).face3_pos[3][2][0] = 1;
    }
    else if (cube[5][0][2] == (*corner).face1 && cube[3][2][0] == (*corner).face2 && cube[2][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[5][0][2] = 1;
        (*corner).face2_pos[3][2][0] = 1;
        (*corner).face3_pos[2][2][2] = 1;
    }
    else if (cube[3][2][2] == (*corner).face1 && cube[5][2][2] == (*corner).face2 && cube[4][2][0] == (*corner).face3)//第八大种
    {
        (*corner).face1_pos[3][2][2] = 1;
        (*corner).face2_pos[5][2][2] = 1;
        (*corner).face3_pos[4][2][0] = 1;
    }
    else if (cube[3][2][2] == (*corner).face1 && cube[4][2][0] == (*corner).face2 && cube[5][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[3][2][2] = 1;
        (*corner).face2_pos[4][2][0] = 1;
        (*corner).face3_pos[5][2][2] = 1;
    }
    else if (cube[4][2][0] == (*corner).face1 && cube[3][2][2] == (*corner).face2 && cube[5][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[4][2][0] = 1;
        (*corner).face2_pos[3][2][2] = 1;
        (*corner).face3_pos[5][2][2] = 1;
    }
    else if (cube[4][2][0] == (*corner).face1 && cube[5][2][2] == (*corner).face2 && cube[3][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[4][2][0] = 1;
        (*corner).face2_pos[5][2][2] = 1;
        (*corner).face3_pos[3][2][2] = 1;
    }
    else if (cube[5][2][2] == (*corner).face1 && cube[3][2][2] == (*corner).face2 && cube[4][2][0] == (*corner).face3)
    {
        (*corner).face1_pos[5][2][2] = 1;
        (*corner).face2_pos[3][2][2] = 1;
        (*corner).face3_pos[4][2][0] = 1;
    }
    else if (cube[5][2][2] == (*corner).face1 && cube[4][2][0] == (*corner).face2 && cube[3][2][2] == (*corner).face3)
    {
        (*corner).face1_pos[5][2][2] = 1;
        (*corner).face2_pos[4][2][0] = 1;
        (*corner).face3_pos[3][2][2] = 1;
    }
}

void search_edges(edge_pieces* edge)
{//寻找特定棱块
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
            {
                (*edge).face1_pos[i][j][k] = 0;
                (*edge).face2_pos[i][j][k] = 0;
            }
    if (cube[0][0][1] == (*edge).face1 && cube[4][0][1] == (*edge).face2)//第一种
    {
        (*edge).face1_pos[0][0][1] = 1;
        (*edge).face2_pos[4][0][1] = 1;
    }
    else if (cube[4][0][1] == (*edge).face1 && cube[0][0][1] == (*edge).face2)
    {
        (*edge).face1_pos[4][0][1] = 1;
        (*edge).face2_pos[0][0][1] = 1;
    }
    else if (cube[0][1][0] == (*edge).face1 && cube[1][0][1] == (*edge).face2)//第二种
    {
        (*edge).face1_pos[0][1][0] = 1;
        (*edge).face2_pos[1][0][1] = 1;
    }
    else if (cube[1][0][1] == (*edge).face1 && cube[0][1][0] == (*edge).face2)
    {
        (*edge).face1_pos[1][0][1] = 1;
        (*edge).face2_pos[0][1][0] = 1;
    }
    else if (cube[0][2][1] == (*edge).face1 && cube[2][0][1] == (*edge).face2)//第三种
    {
        (*edge).face1_pos[0][2][1] = 1;
        (*edge).face2_pos[2][0][1] = 1;
    }
    else if (cube[2][0][1] == (*edge).face1 && cube[0][2][1] == (*edge).face2)
    {
        (*edge).face1_pos[2][0][1] = 1;
        (*edge).face2_pos[0][2][1] = 1;
    }
    else if (cube[0][1][2] == (*edge).face1 && cube[3][0][1] == (*edge).face2)//第四种
    {
        (*edge).face1_pos[0][1][2] = 1;
        (*edge).face2_pos[3][0][1] = 1;
    }
    else if (cube[3][0][1] == (*edge).face1 && cube[0][1][2] == (*edge).face2)
    {
        (*edge).face1_pos[3][0][1] = 1;
        (*edge).face2_pos[0][1][2] = 1;
    }
    else if (cube[1][1][0] == (*edge).face1 && cube[4][1][2] == (*edge).face2)//第五种
    {
        (*edge).face1_pos[1][1][0] = 1;
        (*edge).face2_pos[4][1][2] = 1;
    }
    else if (cube[4][1][2] == (*edge).face1 && cube[1][1][0] == (*edge).face2)
    {
        (*edge).face1_pos[4][1][2] = 1;
        (*edge).face2_pos[1][1][0] = 1;
    }
    else if (cube[1][1][2] == (*edge).face1 && cube[2][1][0] == (*edge).face2)//第六种
    {
        (*edge).face1_pos[1][1][2] = 1;
        (*edge).face2_pos[2][1][0] = 1;
    }
    else if (cube[2][1][0] == (*edge).face1 && cube[1][1][2] == (*edge).face2)
    {
        (*edge).face1_pos[2][1][0] = 1;
        (*edge).face2_pos[1][1][2] = 1;
    }//检查至此
    else if (cube[2][1][2] == (*edge).face1 && cube[3][1][0] == (*edge).face2)//第七种
    {
        (*edge).face1_pos[2][1][2] = 1;
        (*edge).face2_pos[3][1][0] = 1;
    }
    else if (cube[3][1][0] == (*edge).face1 && cube[2][1][2] == (*edge).face2)
    {
        (*edge).face1_pos[3][1][0] = 1;
        (*edge).face2_pos[2][1][2] = 1;
    }
    else if (cube[3][1][2] == (*edge).face1 && cube[4][1][0] == (*edge).face2)//第八种
    {
        (*edge).face1_pos[3][1][2] = 1;
        (*edge).face2_pos[4][1][0] = 1;
    }
    else if (cube[4][1][0] == (*edge).face1 && cube[3][1][2] == (*edge).face2)
    {
        (*edge).face1_pos[4][1][0] = 1;
        (*edge).face2_pos[3][1][2] = 1;
    }
    else if (cube[1][2][1] == (*edge).face1 && cube[5][1][0] == (*edge).face2)//第九种
    {
        (*edge).face1_pos[1][2][1] = 1;
        (*edge).face2_pos[5][1][0] = 1;
    }
    else if (cube[5][1][0] == (*edge).face1 && cube[1][2][1] == (*edge).face2)
    {
        (*edge).face1_pos[5][1][0] = 1;
        (*edge).face2_pos[1][2][1] = 1;
    }
    else if (cube[2][2][1] == (*edge).face1 && cube[5][0][1] == (*edge).face2)//第十种
    {
        (*edge).face1_pos[2][2][1] = 1;
        (*edge).face2_pos[5][0][1] = 1;
    }
    else if (cube[5][0][1] == (*edge).face1 && cube[2][2][1] == (*edge).face2)
    {
        (*edge).face1_pos[5][0][1] = 1;
        (*edge).face2_pos[2][2][1] = 1;
    }
    else if (cube[3][2][1] == (*edge).face1 && cube[5][1][2] == (*edge).face2)//第十一种
    {
        (*edge).face1_pos[3][2][1] = 1;
        (*edge).face2_pos[5][1][2] = 1;
    }
    else if (cube[5][1][2] == (*edge).face1 && cube[3][2][1] == (*edge).face2)
    {
        (*edge).face1_pos[5][1][2] = 1;
        (*edge).face2_pos[3][2][1] = 1;
    }
    else if (cube[4][2][1] == (*edge).face1 && cube[5][2][1] == (*edge).face2)//第十二种
    {
        (*edge).face1_pos[4][2][1] = 1;
        (*edge).face2_pos[5][2][1] = 1;
    }
    else if (cube[5][2][1] == (*edge).face1 && cube[4][2][1] == (*edge).face2)
    {
        (*edge).face1_pos[5][2][1] = 1;
        (*edge).face2_pos[4][2][1] = 1;
    }
}



void face_ckw(int face) //简化旋转函数的两个函数
{
    int tmp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tmp[i][j] = cube[face][i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cube[face][i][j] = tmp[2 - j][i];
}
void face_ccw(int face)
{
    int tmp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tmp[i][j] = cube[face][i][j];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cube[face][i][j] = tmp[j][2 - i];
}

void up_ckw() //顺时针,下同
{
    face_ckw(0);
    char f[3] = { 0 };
    for (int i = 0; i < 3; i++)
        f[i] = cube[2][0][i];
    for (int i = 0; i < 3; i++)
    {
        cube[2][0][i] = cube[3][0][i];
        cube[3][0][i] = cube[4][0][i];
        cube[4][0][i] = cube[1][0][i];
        cube[1][0][i] = f[i];
    }
    out.push_back(0);
}
void up_ccw() //逆时针,下同
{
    face_ccw(0);
    char f[3] = { 0 };
    for (int i = 0; i < 3; i++)
        f[i] = cube[2][0][i];
    for (int i = 0; i < 3; i++)
    {
        cube[2][0][i] = cube[1][0][i];
        cube[1][0][i] = cube[4][0][i];
        cube[4][0][i] = cube[3][0][i];
        cube[3][0][i] = f[i];
    }
    out.push_back(10);
}
void left_ckw()
{
    face_ckw(1);
    char u[3] = { 0 };
    for (int i = 0; i < 3; i++)
        u[i] = cube[0][i][0];
    for (int i = 0; i < 3; i++)
    {
        cube[0][i][0] = cube[4][2 - i][2];
        cube[4][2 - i][2] = cube[5][i][0];
        cube[5][i][0] = cube[2][i][0];
        cube[2][i][0] = u[i];
    }
    out.push_back(1);
}
void left_ccw()
{
    face_ccw(1);
    char u[3] = { 0 };
    for (int i = 0; i < 3; i++)
        u[i] = cube[0][i][0];
    for (int i = 0; i < 3; i++)
    {
        cube[0][i][0] = cube[2][i][0];
        cube[2][i][0] = cube[5][i][0];
        cube[5][i][0] = cube[4][2 - i][2];
        cube[4][2 - i][2] = u[i];
    }
    out.push_back(11);
}
void front_ckw()
{
    face_ckw(2);
    char u[3];
    for (int i = 0; i < 3; i++)
        u[i] = cube[0][2][i];
    for (int i = 0; i < 3; i++)
    {
        cube[0][2][i] = cube[1][2 - i][2];
        cube[1][2 - i][2] = cube[5][0][2 - i];
        cube[5][0][2 - i] = cube[3][i][0];
        cube[3][i][0] = u[i];
    }
    out.push_back(2);
}
void front_ccw()
{
    face_ccw(2);
    char u[3];
    for (int i = 0; i < 3; i++)
        u[i] = cube[0][2][i];
    for (int i = 0; i < 3; i++)
    {
        cube[0][2][i] = cube[3][i][0];
        cube[3][i][0] = cube[5][0][2 - i];
        cube[5][0][2 - i] = cube[1][2 - i][2];
        cube[1][2 - i][2] = u[i];
    }
    out.push_back(12);
}
void right_ckw()
{
    char u[3] = { 0 };
    face_ckw(3);
    for (int i = 0; i < 3; i++)
        u[i] = cube[0][i][2];
    for (int i = 0; i < 3; i++)
    {
        cube[0][i][2] = cube[2][i][2];
        cube[2][i][2] = cube[5][i][2];
        cube[5][i][2] = cube[4][2 - i][0];
        cube[4][2 - i][0] = u[i];
    }
    out.push_back(3);
}
void right_ccw()
{
    char u[3] = { 0 };
    face_ccw(3);
    for (int i = 0; i < 3; i++)
        u[i] = cube[0][i][2];
    for (int i = 0; i < 3; i++)
    {
        cube[0][i][2] = cube[4][2 - i][0];
        cube[4][2 - i][0] = cube[5][i][2];
        cube[5][i][2] = cube[2][i][2];
        cube[2][i][2] = u[i];
    }
    out.push_back(13);
}
void back_ckw()
{
    char r[3] = { 0 };
    face_ckw(4);
    for (int i = 0; i < 3; i++)
        r[i] = cube[3][i][2];
    for (int i = 0; i < 3; i++)
    {
        cube[3][i][2] = cube[5][2][2 - i];
        cube[5][2][2 - i] = cube[1][2 - i][0];
        cube[1][2 - i][0] = cube[0][0][i];
        cube[0][0][i] = r[i];
    }
    out.push_back(4);
}
void back_ccw()
{
    char r[3] = { 0 };
    face_ccw(4);
    for (int i = 0; i < 3; i++)
        r[i] = cube[3][i][2];
    for (int i = 0; i < 3; i++)
    {
        cube[3][i][2] = cube[0][0][i];
        cube[0][0][i] = cube[1][2 - i][0];
        cube[1][2 - i][0] = cube[5][2][2 - i];
        cube[5][2][2 - i] = r[i]; //TODO
    }
    out.push_back(14);
}
void down_ckw()
{
    char f[3] = { 0 };
    face_ckw(5);
    for (int i = 0; i < 3; i++)
        f[i] = cube[2][2][i];
    for (int i = 0; i < 3; i++)
    {
        cube[2][2][i] = cube[1][2][i];
        cube[1][2][i] = cube[4][2][i];
        cube[4][2][i] = cube[3][2][i];
        cube[3][2][i] = f[i];
    }
    out.push_back(5);
}
void down_ccw()
{
    char f[3] = { 0 };
    face_ccw(5);
    for (int i = 0; i < 3; i++)
        f[i] = cube[2][2][i];
    for (int i = 0; i < 3; i++)
    {
        cube[2][2][i] = cube[3][2][i];
        cube[3][2][i] = cube[4][2][i];
        cube[4][2][i] = cube[1][2][i];
        cube[1][2][i] = f[i];
    }
    out.push_back(15);
}

void dbg_show() //展示魔方当前状态,debug用
{
    cout << "        =========" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "        | ";
        for (int j = 0; j < 3; j++)
            cout << cube[0][i][j] << " ";
        cout << '|' << endl;
    }
    cout << "=================================" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "| ";
        for (int k = 1; k <= 4; k++)
        {
            for (int j = 0; j < 3; j++)
                cout << cube[k][i][j] << " ";
            cout << "| ";
        }
        cout << endl;
    }
    cout << "=================================" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "        | ";
        for (int j = 0; j < 3; j++)
            cout << cube[5][i][j] << " ";
        cout << '|' << endl;
    }
    cout << "        =========" << endl;
}

void (*op[12])() = { up_ckw, left_ckw, front_ckw, right_ckw, back_ckw, down_ckw,
                    up_ccw, left_ccw, front_ccw, right_ccw, back_ccw, down_ccw }; //op[i], 0<=i<=5顺时针, 6<=i<=11逆时针, 按照上左前右后下顺序

/*
1.还原底部十字
2.还原底部角块
3.解决中间层
4.还原顶部十字
5.还原顶部角块
6 让顶部全是相同颜色
7 让顶部角块正确
8 让顶部棱块正确

12一个人 3，找角块，找棱块一个人 5678一个人

*/

void function_1()   //一个用于还原顶面十字的函数
{
    front_ckw();
    right_ckw();
    up_ckw();
    right_ccw();
    up_ccw();
    front_ccw();
}

void function_2()   //一个用于还原顶面角的函数
{
    right_ckw();
    up_ckw();
    right_ccw();
    up_ckw();
    right_ckw();
    up_ckw();
    up_ckw();
    right_ccw();
}

void function_3_1()//see from left(公式2)//ok
{
    front_ckw(); up_ckw(); up_ckw(); front_ccw(); up_ckw(); front_ckw(); up_ckw(); up_ckw();
    front_ccw(); up_ckw(); left_ccw(); up_ccw(); left_ckw();
}
void function_3_2()//see from front//ok
{
    right_ckw(); up_ckw(); up_ckw(); right_ccw(); up_ckw(); right_ckw(); up_ckw(); up_ckw();
    right_ccw(); up_ckw(); front_ccw(); up_ccw(); front_ckw();
}
void function_3_3()//see from right\\ok
{
    back_ckw(); up_ckw(); up_ckw(); back_ccw(); up_ckw(); back_ckw(); up_ckw(); up_ckw();
    back_ccw(); up_ckw(); right_ccw(); up_ccw(); right_ckw();
}
void function_3_4()//see from back//ok
{
    left_ckw(); up_ckw(); up_ckw(); left_ccw(); up_ckw(); left_ckw(); up_ckw(); up_ckw();
    left_ccw(); up_ckw(); back_ccw(); up_ccw(); back_ckw();
}
void function_4_1()//see from left(公式3)//ok
{
    up_ckw(); front_ckw(); up_ccw(); front_ccw();
    up_ccw(); left_ccw(); up_ckw(); left_ckw();
}
void function_4_2()//see from front//ok
{
    up_ckw(); right_ckw(); up_ccw(); right_ccw();
    up_ccw(); front_ccw(); up_ckw(); front_ckw();
}
void function_4_3()//see from right\\ok
{
    up_ckw(); back_ckw(); up_ccw(); back_ccw();
    up_ccw(); right_ccw(); up_ckw(); right_ckw();
}
void function_4_4()//see from back//ok
{
    up_ckw(); left_ckw(); up_ccw(); left_ccw();
    up_ccw(); back_ccw(); up_ckw(); back_ckw();
}
void function_5_1()//see from left(公式4)//其余函数ccw与ckw均需修改
{
    front_ccw();   up_ccw();   front_ccw();   up_ccw();    front_ccw();
    up_ckw();   front_ckw();   up_ckw();   front_ckw();
}
void function_5_2()//see from front\\ok
{
    right_ccw(); up_ccw(); right_ccw(); up_ccw(); right_ccw();
    up_ckw(); right_ckw(); up_ckw(); right_ckw();
}
void function_5_3()//see from right//ok
{
    back_ccw(); up_ccw(); back_ccw(); up_ccw(); back_ccw();
    up_ckw(); back_ckw(); up_ckw(); back_ckw();
}
void function_5_4()//see from back\\ok
{
    left_ccw(); up_ccw(); left_ccw(); up_ccw(); left_ccw();
    up_ckw(); left_ckw(); up_ckw(); left_ckw();
}

void function_6() //一个还原顶角的函数
{
    right_ccw();
    right_ccw();
    front_ccw();
    front_ccw();
    right_ccw();
    back_ccw();
    right_ckw();
    front_ccw();
    front_ccw();
    right_ccw();
    back_ckw();
    right_ccw();
}

void function_7()  //一个还原顶棱的函数
{
    right_ckw();
    up_ccw();
    right_ckw();
    up_ckw();
    right_ckw();
    up_ckw();
    right_ckw();
    up_ccw();
    right_ccw();
    up_ccw();
    right_ccw();
    right_ccw();
}

void function1_1(edge_pieces target) {
    if (target.face2_pos[5][2][1])
    {
        /* code */
        back_ccw();
        back_ccw();
    }
    else if (target.face2_pos[5][1][0])
    {
        /* code */
        down_ccw();
        back_ccw();
        back_ccw();
    }
    else if (target.face2_pos[5][1][2])
    {
        /* code */
        down_ckw();
        back_ccw();
        back_ccw();
    }
    else if (target.face2_pos[5][0][1])
    {
        down_ckw();
        down_ckw();
        back_ccw();
        back_ccw();
    }
    else if (target.face2_pos[1][0][1])
    {
        /* code */
        left_ccw();
        back_ckw();
    }
    else if (target.face2_pos[1][1][0])
    {
        /* code */
        back_ckw();
    }
    else if (target.face2_pos[1][1][2])
    {
        /* code */
        left_ccw();
        left_ccw();
        back_ckw();
        left_ckw();
        left_ckw();
    }
    else if (target.face2_pos[1][2][1])
    {
        /* code */
        left_ckw();
        back_ckw();
        left_ccw();
    }
    else if (target.face2_pos[2][0][1])
    {
        /* code */
        front_ckw();
        front_ckw();
        down_ckw();
        right_ccw();
        back_ccw();
        right_ckw();
    }
    else if (target.face2_pos[2][1][0])
    {
        /* code */
        left_ckw();
        down_ccw();
        back_ccw();
        back_ccw();
        left_ccw();
    }
    else if (target.face2_pos[2][1][2])
    {
        /* code */
        right_ccw();
        down_ckw();
        right_ckw();
        back_ccw();
        back_ccw();
    }
    else if (target.face2_pos[2][2][1])
    {
        /* code */
        down_ckw();
        right_ccw();
        back_ccw();
        right_ckw();
    }
    else if (target.face2_pos[3][0][1])
    {
        /* code */
        right_ckw();
        back_ccw();
    }

    else if (target.face2_pos[3][1][0])
    {
        /* code */
        right_ccw();
        right_ccw();
        back_ccw();
        right_ckw();
        right_ckw();
    }

    else if (target.face2_pos[3][1][2])
    {
        /* code */
        back_ccw();
    }

    else if (target.face2_pos[3][2][1])
    {
        /* code */
        right_ccw();
        back_ccw();
        right_ckw();
    }

    else if (target.face2_pos[4][0][1])
    {
        /* code */
        back_ccw();
        back_ccw();
        down_ccw();
        right_ccw();
        back_ccw();
        right_ckw();
    }
    else if (target.face2_pos[4][1][0])
    {
        /* code */
        back_ckw();
        down_ccw();
        right_ccw();
        back_ccw();
        right_ckw();
    }
    else if (target.face2_pos[4][1][2])
    {
        /* code */
        left_ccw();
        down_ccw();
        back_ckw();
        back_ckw();
        left_ckw();
    }
    else if (target.face2_pos[4][2][1])
    {
        /* code */
        down_ccw();
        right_ccw();
        back_ccw();
        right_ckw();
    }
}

void step1()
{
    //使得棱块和中心块颜色一致
    //转动对着自己的一层完成蓝白棱块
    //转动顶层使得侧面颜色相同，并且转动一层完成红白棱块
    char centralBlocks[6] = { cube[0][1][1], cube[1][1][1], cube[2][1][1], cube[3][1][1], cube[4][1][1], cube[5][1][1] };

    edge_pieces front;
    front.face1 = centralBlocks[2];
    front.face2 = centralBlocks[5];
    edge_pieces left;
    left.face1 = centralBlocks[1];
    left.face2 = centralBlocks[5];
    edge_pieces back;
    back.face1 = centralBlocks[4];
    back.face2 = centralBlocks[5];
    edge_pieces right;
    right.face1 = centralBlocks[3];
    right.face2 = centralBlocks[5];
    search_edges(&front);
    search_edges(&left);
    search_edges(&back);
    search_edges(&right);
    bool tmark = 0;

    //把所有白色棱块转到顶面
    while (cube[0][0][1] != centralBlocks[5] || cube[0][1][0] != centralBlocks[5] || cube[0][1][2] != centralBlocks[5] || cube[0][2][1] != centralBlocks[5])
    {
        /* 思路
            搜索顶部，看看哪个位置没有白色棱块。
                如果找到一个位置没有白色棱块，就把那个位置转到01
                之后针对这个位置，寻找一个白色棱块，将它旋转到顶部
             */
        search_edges(&front);
        search_edges(&left);
        search_edges(&back);
        search_edges(&right);

        for (size_t i = 0; i < 4; i++)
        {
            tmark = (cube[0][0][1] == centralBlocks[5]);
            /* code */
            if (tmark == 1)
            {
                /* code */
                up_ccw();
                search_edges(&front);
                search_edges(&left);
                search_edges(&back);
                search_edges(&right);
            }
            else
                break;
        }

        if (!tmark)
        {
            if (!(front.face2_pos[0][0][1] || front.face2_pos[0][1][0] || front.face2_pos[0][1][2] || front.face2_pos[0][2][1]))
                function1_1(front);
            else  if (!(left.face2_pos[0][0][1] || left.face2_pos[0][1][0] || left.face2_pos[0][1][2] || left.face2_pos[0][2][1]))
                function1_1(left);
            else  if (!(right.face2_pos[0][0][1] || right.face2_pos[0][1][0] || right.face2_pos[0][1][2] || right.face2_pos[0][2][1]))
                function1_1(right);
            else  if (!(back.face2_pos[0][0][1] || back.face2_pos[0][1][0] || back.face2_pos[0][1][2] || back.face2_pos[0][2][1]))
                function1_1(back);
        }
    }

    search_edges(&front);
    search_edges(&left);
    search_edges(&back);
    search_edges(&right);
    //复原四个棱块
    while (cube[2][0][1] != front.face1 || cube[0][2][1] != front.face2)
    {
        up_ccw();
    }
    front_ccw();
    front_ccw();
    search_edges(&front);
    search_edges(&left);
    search_edges(&back);
    search_edges(&right);

    while (cube[1][0][1] != left.face1 || cube[0][1][0] != left.face2)
    {
        up_ccw();
    }
    left_ccw();
    left_ccw();
    search_edges(&front);
    search_edges(&left);
    search_edges(&back);
    search_edges(&right);

    while (cube[3][0][1] != right.face1 || cube[0][1][2] != right.face2)
    {
        up_ccw();
         
    }
    right_ccw();
    right_ccw();
    search_edges(&front);
    search_edges(&left);
    search_edges(&back);
    search_edges(&right);

    while (cube[4][0][1] != back.face1 || cube[0][0][1] != back.face2)
    {
        up_ccw();
    }
    back_ccw();
    back_ccw();
    search_edges(&front);
    search_edges(&left);
    search_edges(&back);
    search_edges(&right);
}


void step2()
{
    corner_pieces FLD;
    FLD.face1 = cube[2][1][1];
    FLD.face2 = cube[1][1][1];
    FLD.face3 = cube[5][1][1];
    corner_pieces FRD;
    FRD.face1 = cube[2][1][1];
    FRD.face2 = cube[3][1][1];
    FRD.face3 = cube[5][1][1];
    corner_pieces BLD;
    BLD.face1 = cube[4][1][1];
    BLD.face2 = cube[1][1][1];
    BLD.face3 = cube[5][1][1];
    corner_pieces BRD;
    BRD.face1 = cube[4][1][1];
    BRD.face2 = cube[3][1][1];
    BRD.face3 = cube[5][1][1];
     
    search_corners(&FLD);
    search_corners(&FRD);
    search_corners(&BLD);
    search_corners(&BRD);

    while (!(FLD.face1_pos[2][2][0] && FLD.face2_pos[1][2][2] && FLD.face3_pos[5][0][0]))
    {
        if (FLD.face1_pos[0][0][0] || FLD.face1_pos[0][0][2] || FLD.face1_pos[0][2][0] || FLD.face1_pos[0][2][2]
            || FLD.face1_pos[1][0][0] || FLD.face1_pos[1][0][2] || FLD.face1_pos[2][0][0] || FLD.face1_pos[2][0][2]
            || FLD.face1_pos[3][0][0] || FLD.face1_pos[3][0][2] || FLD.face1_pos[4][0][0] || FLD.face1_pos[4][0][2])
        {
            /* case 1 */
            while (!(
                (FLD.face2_pos[0][2][0] && FLD.face1_pos[2][0][0] && FLD.face3_pos[1][0][2])
                || (FLD.face1_pos[0][2][0] && FLD.face3_pos[2][0][0] && FLD.face2_pos[1][0][2])
                || (FLD.face3_pos[0][2][0] && FLD.face2_pos[2][0][0] && FLD.face1_pos[1][0][2])
                ))
            {
                /* code */
                up_ccw();
                search_corners(&FLD);
            }
            while (!(FLD.face1_pos[2][2][0] && FLD.face2_pos[1][2][2] && FLD.face3_pos[5][0][0])) {
                left_ccw();
                up_ccw();
                left_ckw();
                up_ckw();
                search_corners(&FLD);
            }
        }
        else
        {
            /* code */
            if (FLD.face1_pos[5][0][0] || FLD.face2_pos[5][0][0] || FLD.face1_pos[1][2][2])
            {
                /* code */
                left_ccw();
                up_ckw();
                left_ckw();
                search_corners(&FLD);
            }
            else if (FLD.face1_pos[5][0][2] || FLD.face2_pos[5][0][2] || FLD.face3_pos[5][0][2])
            {
                /* code */
                right_ckw();
                up_ckw();
                right_ccw();
                search_corners(&FLD);
            }
            else if (FLD.face1_pos[5][2][2] || FLD.face2_pos[5][2][2] || FLD.face3_pos[5][2][2])
            {
                right_ccw();
                up_ckw();
                right_ckw();
                search_corners(&FLD);
            }
            else if (FLD.face1_pos[5][2][0] || FLD.face2_pos[5][2][0] || FLD.face3_pos[5][2][0])
            {
                left_ckw();
                up_ckw();
                left_ccw();
                search_corners(&FLD);
            }
        }
    }

    search_corners(&FRD);
    while (!(FRD.face1_pos[2][2][2] && FRD.face2_pos[3][2][0] && FRD.face3_pos[5][0][2]))
    {
        if (FRD.face1_pos[0][0][0] || FRD.face1_pos[0][0][2] || FRD.face1_pos[0][2][0] || FRD.face1_pos[0][2][2]
            || FRD.face1_pos[1][0][0] || FRD.face1_pos[1][0][2] || FRD.face1_pos[2][0][0] || FRD.face1_pos[2][0][2]
            || FRD.face1_pos[3][0][0] || FRD.face1_pos[3][0][2] || FRD.face1_pos[4][0][0] || FRD.face1_pos[4][0][2])
        {
            /* case 1 */
            while (!(
                (FRD.face1_pos[0][2][2] && FRD.face2_pos[3][0][0] && FRD.face3_pos[2][0][2])
                || (FRD.face2_pos[0][2][2] && FRD.face3_pos[3][0][0] && FRD.face1_pos[2][0][2])
                || (FRD.face3_pos[0][2][2] && FRD.face1_pos[3][0][0] && FRD.face2_pos[2][0][2])
                ))
            {
                /* code */
                up_ccw();
                search_corners(&FRD);
            }
            while (!(FRD.face1_pos[2][2][2] && FRD.face2_pos[3][2][0] && FRD.face3_pos[5][0][2])) {
                right_ckw();
                up_ckw();
                right_ccw();
                up_ccw();
                search_corners(&FRD);
            }
        }
        else
        {
            if (FRD.face1_pos[5][0][2] || FRD.face2_pos[5][0][2] || FRD.face1_pos[3][2][0])
            {
                /* code */
                right_ckw();
                up_ckw();
                right_ccw();
                search_corners(&FRD);
            }
            else if (FRD.face1_pos[5][2][2] || FRD.face2_pos[5][2][2] || FRD.face3_pos[5][2][2])
            {
                right_ccw();
                up_ckw();
                right_ckw();
                search_corners(&FRD);
            }
            else if (FRD.face1_pos[5][2][0] || FRD.face2_pos[5][2][0] || FRD.face3_pos[5][2][0])
            {
                left_ckw();
                up_ckw();
                left_ccw();
                search_corners(&FRD);
            }
        }
    }
     
    search_corners(&BLD);
    while (!(BLD.face1_pos[4][2][2] && BLD.face2_pos[1][2][0] && BLD.face3_pos[5][2][0]))
    {
        if (BLD.face1_pos[0][0][0] || BLD.face1_pos[0][0][2] || BLD.face1_pos[0][2][0] || BLD.face1_pos[0][2][2]
            || BLD.face1_pos[1][0][0] || BLD.face1_pos[1][0][2] || BLD.face1_pos[2][0][0] || BLD.face1_pos[2][0][2]
            || BLD.face1_pos[3][0][0] || BLD.face1_pos[3][0][2] || BLD.face1_pos[4][0][0] || BLD.face1_pos[4][0][2])
        {
            while (!(
                (BLD.face2_pos[0][0][0] && BLD.face1_pos[4][0][2] && BLD.face3_pos[1][0][0])
                || (BLD.face1_pos[0][0][0] && BLD.face3_pos[4][0][2] && BLD.face2_pos[1][0][0])
                || (BLD.face3_pos[0][0][0] && BLD.face2_pos[4][0][2] && BLD.face1_pos[1][0][0])
                ))
            {
                up_ccw();
                search_corners(&BLD);
            }
            while (!(BLD.face1_pos[4][2][2] && BLD.face2_pos[1][2][0] && BLD.face3_pos[5][2][0])) {
                left_ckw();
                up_ckw();
                left_ccw();
                up_ccw();
                search_corners(&BLD);
            }
        }
        else
        {
            if (BLD.face1_pos[5][2][2] || BLD.face2_pos[5][2][2] || BLD.face3_pos[5][2][2])
            {
                right_ccw();
                up_ckw();
                right_ckw();
                search_corners(&BLD);
            }
            else if (BLD.face1_pos[5][2][0] || BLD.face2_pos[5][2][0] || BLD.face1_pos[1][2][0])
            {
                left_ckw();
                up_ckw();
                left_ccw();
                search_corners(&BLD);
            }
        }
    }

    search_corners(&BRD);
    while (!(BRD.face1_pos[4][2][0] && BRD.face2_pos[3][2][2] && BRD.face3_pos[5][2][2]))
    {
        if (BRD.face1_pos[0][0][0] || BRD.face1_pos[0][0][2] || BRD.face1_pos[0][2][0] || BRD.face1_pos[0][2][2]
            || BRD.face1_pos[1][0][0] || BRD.face1_pos[1][0][2] || BRD.face1_pos[2][0][0] || BRD.face1_pos[2][0][2]
            || BRD.face1_pos[3][0][0] || BRD.face1_pos[3][0][2] || BRD.face1_pos[4][0][0] || BRD.face1_pos[4][0][2])
        {
            while (!(
                (BRD.face2_pos[0][0][2] && BRD.face1_pos[4][0][0] && BRD.face3_pos[3][0][2])
                || (BRD.face1_pos[0][0][2] && BRD.face3_pos[4][0][0] && BRD.face2_pos[3][0][2])
                || (BRD.face3_pos[0][0][2] && BRD.face2_pos[4][0][0] && BRD.face1_pos[3][0][2])
                ))
            {
                up_ccw();
                search_corners(&BRD);
            }
            while (!(BRD.face1_pos[4][2][0] && BRD.face2_pos[3][2][2] && BRD.face3_pos[5][2][2])) {
                right_ccw();
                up_ccw();
                right_ckw();
                up_ckw();
                search_corners(&BRD);
            }
        }
        else
        {
            if (BRD.face1_pos[5][2][2] || BRD.face2_pos[5][2][2] || BRD.face1_pos[3][2][2])
            {
                right_ccw();
                up_ckw();
                right_ckw();
                search_corners(&BRD);
            }
        }
    }
     
}

void step3(char a, char b, char c, char d, char e, char f)//  还原中间棱块 ,将6个面中心块具体颜色输入                                                   
{
    edge_pieces A;
    A.face1 = b;
    A.face2 = c;
    edge_pieces B;
    B.face1 = c;
    B.face2 = d;
    edge_pieces C;
    C.face1 = d;
    C.face2 = e;
    edge_pieces D;
    D.face1 = e;
    D.face2 = b;
    search_edges(&A);
    if (A.face1_pos[2][1][0] == 1 && A.face2_pos[1][1][2] == 1)
        function_3_1();
    else if (!(A.face2_pos[2][1][0] == 1 && A.face1_pos[1][1][2] == 1))
    {
        if ((A.face1_pos[3][1][0] == 1 && A.face2_pos[2][1][2] == 1) || (A.face2_pos[3][1][0] == 1 && A.face1_pos[2][1][2] == 1))
            function_4_2();
        else if ((A.face1_pos[4][1][0] == 1 && A.face2_pos[3][1][2] == 1) || (A.face2_pos[4][1][0] == 1 && A.face1_pos[3][1][2] == 1))
            function_4_3();
        else if ((A.face1_pos[1][1][0] == 1 && A.face2_pos[4][1][2] == 1) || (A.face2_pos[1][1][0] == 1 && A.face1_pos[4][1][2] == 1))
            function_4_4();
        while (!((A.face1_pos[1][0][1] == 1 && A.face2_pos[0][1][0] == 1) || (A.face1_pos[0][2][1] == 1 && A.face2_pos[2][0][1] == 1)))
        {
            up_ckw();
            search_edges(&A);
        }
        if (A.face1_pos[1][0][1] == 1 && A.face2_pos[0][1][0] == 1)
            function_4_1();
        else if (A.face1_pos[0][2][1] == 1 && A.face2_pos[2][0][1] == 1)
            function_5_1();
    }
     
    search_edges(&B);
    if (B.face1_pos[3][1][0] == 1 && B.face2_pos[2][1][2] == 1)
        function_3_2();
    else if (!(B.face2_pos[3][1][0] == 1 && B.face1_pos[2][1][2] == 1))
    {
        if ((B.face1_pos[2][1][0] == 1 && B.face2_pos[1][1][2] == 1) || (B.face2_pos[2][1][0] == 1 && B.face1_pos[1][1][2] == 1))
            function_4_1();
        else if ((B.face1_pos[4][1][0] == 1 && B.face2_pos[3][1][2] == 1) || (B.face2_pos[4][1][0] == 1 && B.face1_pos[3][1][2] == 1))
            function_4_3();
        else if ((B.face1_pos[1][1][0] == 1 && B.face2_pos[4][1][2] == 1) || (B.face2_pos[1][1][0] == 1 && B.face1_pos[4][1][2] == 1))
            function_4_4();
        while (!((B.face1_pos[2][0][1] == 1 && B.face2_pos[0][2][1] == 1) || (B.face1_pos[0][1][2] == 1 && B.face2_pos[3][0][1] == 1)))
        {
            up_ckw();
            search_edges(&B);
        }
        if (B.face1_pos[2][0][1] == 1 && B.face2_pos[0][2][1] == 1)
            function_4_2();
        else if (B.face1_pos[0][1][2] == 1 && B.face2_pos[3][0][1] == 1)
            function_5_2();
    }
     
    search_edges(&C);
    if (C.face1_pos[4][1][0] == 1 && C.face2_pos[3][1][2] == 1)
        function_3_3();
    else if (!(C.face2_pos[4][1][0] == 1 && C.face1_pos[3][1][2] == 1))
    {
        if ((C.face1_pos[2][1][0] == 1 && C.face2_pos[1][1][2] == 1) || (C.face2_pos[2][1][0] == 1 && C.face1_pos[1][1][2] == 1))
            function_4_1();
        else if ((C.face1_pos[3][1][0] == 1 && C.face2_pos[2][1][2] == 1) || (C.face2_pos[3][1][0] == 1 && C.face1_pos[2][1][2] == 1))
            function_4_2();
        else if ((C.face1_pos[1][1][0] == 1 && C.face2_pos[4][1][2] == 1) || (C.face2_pos[1][1][0] == 1 && C.face1_pos[4][1][2] == 1))
            function_4_4();
        while (!((C.face1_pos[3][0][1] == 1 && C.face2_pos[0][1][2] == 1) || (C.face1_pos[0][0][1] == 1 && C.face2_pos[4][0][1] == 1)))
        {
            up_ckw();
            search_edges(&C);
        }
        if (C.face1_pos[3][0][1] == 1 && C.face2_pos[0][1][2] == 1)
            function_4_3();
        else if (C.face1_pos[0][0][1] == 1 && C.face2_pos[4][0][1] == 1)
            function_5_3();
    }
     
    search_edges(&D);
    if (D.face1_pos[1][1][0] == 1 && D.face2_pos[4][1][2] == 1)
        function_3_4();
    else if (!(D.face2_pos[1][1][0] == 1 && D.face1_pos[4][1][2] == 1))
    {
        if ((D.face1_pos[2][1][0] == 1 && D.face2_pos[1][1][2] == 1) || (D.face2_pos[2][1][0] == 1 && D.face1_pos[1][1][2] == 1))
            function_4_1();
        else if ((D.face1_pos[3][1][0] == 1 && D.face2_pos[2][1][2] == 1) || (D.face2_pos[3][1][0] == 1 && D.face1_pos[2][1][2] == 1))
            function_4_2();
        else if ((D.face1_pos[4][1][0] == 1 && D.face2_pos[3][1][2] == 1) || (D.face2_pos[4][1][0] == 1 && D.face1_pos[3][1][2] == 1))
            function_4_3();
        while (!((D.face1_pos[4][0][1] == 1 && D.face2_pos[0][0][1] == 1) || (D.face1_pos[0][1][0] == 1 && D.face2_pos[1][0][1] == 1)))
        {
            up_ckw();
            search_edges(&D);
        }
        if (D.face1_pos[4][0][1] == 1 && D.face2_pos[0][0][1] == 1)
            function_4_4();
        else if (D.face1_pos[0][1][0] == 1 && D.face2_pos[1][0][1] == 1)
            function_5_4();
    }
     
}

void step4() //顶部十字
{
    int cnt = 0;
    if (cube[0][0][1] == cube[0][1][1])
        cnt += 1;
    if (cube[0][1][0] == cube[0][1][1])
        cnt += 2;
    if (cube[0][1][2] == cube[0][1][1])
        cnt += 2;
    if (cube[0][2][1] == cube[0][1][1])
        cnt += 1;
    if (cnt == 6)
        return;
    if (cnt == 0)
    {
        function_1();
        function_1();
        up_ckw();
        function_1();
    }
    else if (cnt % 2 == 0)   //代表两个在一条线上
    {
        while (cube[0][1][0] != cube[0][1][1])
            up_ckw();
        function_1();
    }
    else if (cnt % 2 != 0)
    {
        while (cube[0][1][0] != cube[0][1][1] || cube[0][0][1] != cube[0][1][1])
            up_ckw();
        function_1();
        function_1();
    }
}

void step5()  //顶面角
{
    while (cube[0][0][0] != cube[0][1][1] || cube[0][2][0] != cube[0][1][1] || cube[0][0][2] != cube[0][1][1] || cube[0][2][2] != cube[0][1][1])
    {
        int cnt = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (cube[0][i][j] == cube[0][1][1])
                    cnt++;
        if (cnt == 6)
        {
            while (cube[0][2][0] != cube[0][1][1])
            {
                up_ckw();
            }
            function_2();
        }
        if (cnt == 7)
        {
            while (cube[2][0][0] != cube[0][1][1])
            {
                up_ckw();
            }
            function_2();
        }
        if (cnt == 5)
        {
            while (cube[1][0][0] != cube[0][1][1] || cube[1][0][2] != cube[0][1][1])
            {
                up_ckw();
            }
            function_2();
        }
    }
}

void step6()    //还原顶角
{
    int i;
    while (cube[1][0][0] != cube[1][0][2] || cube[2][0][0] != cube[2][0][2] || cube[3][0][0] != cube[3][0][2] || cube[4][0][0] != cube[4][0][2])
    {
        for (i = 0; i < 4; i++)
        {
            if (cube[3][0][0] == cube[3][0][2])
            {
                function_6();
                break;
            }
            else
                up_ccw();
        }
        if (i == 4)
        {
            function_6();
            continue;
        }
    }
    while (cube[2][0][0] != cube[2][1][0])
        up_ccw();
}

void step7() //最后还原
{
    int cnt;
    while (1)
    {
        cnt = 0;
        for (int i = 1; i <= 4; i++)
            if (cube[i][0][1] != cube[i][1][1])
                cnt++;
        if (cnt == 3)
        {
            while (cube[2][0][1] != cube[2][0][0])
                up_ccw();
            up_ccw();
            up_ccw();
            while (cube[2][0][1] != cube[2][0][0])
                function_7();
        }
        if (cnt == 4)
            function_7();
        if (cnt == 0)
            break;
        while (cube[2][0][0] != cube[2][1][0])
            up_ccw();
    }
}

//== Main Function ==//
int main()
{
    int corres[] = { 2, 4, 1, 3, 0, 5 }; //按照前后左右上下来读入
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                cin >> cube[corres[i]][j][k];
    char A = cube[0][1][1], B = cube[1][1][1], C = cube[2][1][1], D = cube[3][1][1], E = cube[4][1][1], F = cube[5][1][1];//指示6个面中心面块颜色
    step1();
    step2();
    step3(A, B, C, D, E, F);
    step4();
    step5();
    step6();
    step7();
    refine();
    print();
    return 0;
}