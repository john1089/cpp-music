#include<iostream>
#include<Windows.h>
#include<thread>
#pragma comment(lib,"winmm.lib")
using namespace std;
enum Scale
{
    Rest = 0, C8 = 108, B7 = 107, A7s = 106, A7 = 105, G7s = 104, G7 = 103, F7s = 102, F7 = 101, E7 = 100,
    D7s = 99, D7 = 98, C7s = 97, C7 = 96, B6 = 95, A6s = 94, A6 = 93, G6s = 92, G6 = 91, F6s = 90, F6 = 89,
    E6 = 88, D6s = 87, D6 = 86, C6s = 85, C6 = 84, B5 = 83, A5s = 82, A5 = 81, G5s = 80, G5 = 79, F5s = 78,
    F5 = 77, E5 = 76, D5s = 75, D5 = 74, C5s = 73, C5 = 72, B4 = 71, A4s = 70, A4 = 69, G4s = 68, G4 = 67,
    F4s = 66, F4 = 65, E4 = 64, D4s = 63, D4 = 62, C4s = 61, C4 = 60, B3 = 59, A3s = 58, A3 = 57, G3s = 56,
    G3 = 55, F3s = 54, F3 = 53, E3 = 52, D3s = 51, D3 = 50, C3s = 49, C3 = 48, B2 = 47, A2s = 46, A2 = 45,
    G2s = 44, G2 = 43, F2s = 42, F2 = 41, E2 = 40, D2s = 39, D2 = 38, C2s = 37, C2 = 36, B1 = 35, A1s = 34,
    A1 = 33, G1s = 32, G1 = 31, F1s = 30, F1 = 29, E1 = 28, D1s = 27, D1 = 26, C1s = 25, C1 = 24, B0 = 23,
    A0s = 22, A0 = 21
};
enum Voice
{
    X1 = C2, X2 = D2, X3 = E2, X4 = F2, X5 = G2, X6 = A2, X7 = B2,
    L1 = C3, L2 = D3, L3 = E3, L4 = F3, L5 = G3, L6 = A3, L7 = B3,
    M1 = C4, M2 = D4, M3 = E4, M4 = F4, M5 = G4, M6 = A4, M7 = B4,
    H1 = C5, H2 = D5, H3 = E5, H4 = F5, H5 = G5, H6 = A5, H7 = B5,
    NOTE = 500, _ = Rest
};
HMIDIOUT handle;
const int volume=0x7f;
const int offset=0;//M1=C4
const int lemon_tree_h[]=
{
    NOTE*3,_,NOTE*3/4,_,NOTE/4,M3, NOTE*3/4,M3,NOTE/4,M3,NOTE*3/4,M3,NOTE,M6,NOTE*5/4,M6,
    NOTE,M2,NOTE*3/4,M2,NOTE*9/4,M5, NOTE*3/4,M3,NOTE/4,M3,NOTE*3/4,M3,NOTE/4,M3,NOTE*3/4,M3,NOTE/4,M2,NOTE*3/4,M2,NOTE/4,M1,
    NOTE,M2,NOTE*3/4,M2,NOTE*9/4,M3, NOTE*3/4,M3,NOTE/4,M3,NOTE*3/4,M3,NOTE,M6,NOTE*5/4,M6,
    NOTE*3/4,M2,NOTE/4,M2,NOTE*3/4,M2,NOTE*9/4,M5, NOTE*3/4,M3,NOTE/4,M3,NOTE*3/4,M3,NOTE/4,M3,NOTE*3/4,M3,NOTE/4,M2,NOTE*3/4,M2,NOTE/4,M1,
    NOTE,M2,NOTE*3/4,M2,NOTE,M3,M5,M3,NOTE/4,M2,NOTE*3/4,M2,NOTE/4,M1,NOTE*3/4,M2,NOTE*5/4,M3,
    NOTE*7/4,_,NOTE/4,M2,NOTE*3/4,M3,NOTE,M2,NOTE/4,M1, NOTE*3,L6,NOTE*3/4,_,NOTE/4,M3,
    NOTE,M3,NOTE*3/4,M4,NOTE*5/4,M5,NOTE*3/4,_,NOTE/4,M3, NOTE,M5,NOTE*3/4,M6,NOTE*9/4,M2,
    NOTE*3/4,M1,NOTE/4,M1,NOTE*3/4,M1,NOTE/4,M1,NOTE*3/4,M1,NOTE/4,M1,NOTE*3/4,M1,NOTE/4,M2, NOTE*3/4,M3,NOTE/4,M3,NOTE*3/4,M5,NOTE*5/4,M3,NOTE*3/4,M5,NOTE*5/4,M5,
    NOTE*3/4,M4,NOTE*3/4,M4,NOTE,M3,NOTE*5/2,M2,NOTE*3/4,M2,NOTE/4,M2,NOTE*3/4,M2,NOTE/4,M1,
    NOTE*3/4,M2,NOTE,M3,NOTE*7/4,M3,NOTE/2,L5, NOTE*3/4,M3,NOTE/4,M3,NOTE*3/4,M4,NOTE*9/4,M5,
    NOTE*3/4,M5,NOTE,M6,NOTE*7/4,M2,NOTE/2,L5, NOTE*3/4,M1,NOTE/4,M1,NOTE*3/4,M1,NOTE/4,M1,NOTE*3/4,M1,NOTE/4,M1,NOTE*3/4,M1,NOTE/4,M2,
    NOTE*3/4,M3,NOTE,M5,NOTE*5/4,M3,NOTE*3/4,M5,NOTE*5/4,M5,NOTE*3/4,M4,NOTE,M4,NOTE/4,M2,NOTE*3/4,M3,NOTE*9/4,M2,
    NOTE*3/4,M2,NOTE/4,M2,NOTE*3/4,M2,NOTE/4,M1,NOTE*3/4,M3,NOTE,M1,NOTE*5/4,M2,NOTE/2,M5,NOTE*3/2,M6,
    NOTE*3/4,M5,NOTE*3/4,H1,NOTE*5/4,M3,NOTE*13/4,M2,NOTE/2,M5,NOTE*3/2,M6,
    NOTE*3/4,M5,NOTE*3/4,H1,NOTE*5/4,M3,NOTE*9/4,M2,NOTE*3/4,M2,NOTE/4,M2,NOTE*3/4,M2,NOTE/4,M3,
    NOTE*3/4,M2,NOTE,M1,NOTE/4,M1,NOTE*2,M1
};
const int lemon_tree_l[]=
{
    NOTE,_,_,_,_,X6,L6,L6,X6,X3,L3,L3,X3,X6,L6,L6,X6,
    X3,L3,L3,X3,X6,L6,L6,X6,X3,L3,L3,X3,X2,L2,X2,L2,
    X3,L3,L3,X3,X2,L2,X2,L2,X3,L3,L3,X3,X6,X6,X6,_,
    L1,L5,L1,L5,X5,L2,X5,L2,X6,L3,X6,L3,X3,X7,X3,X7,
    X4,L1,X4,L1,X5,L2,X5,L2,L1,L5,X5,L2,L1,L5,L1,L5,
    X5,L2,X5,L2,X6,L3,X6,L3,X3,X7,X3,X7,X4,L1,X4,L1,
    X4,L1,X4,L1,X5,L2,X5,L2,X4,L1,X4,L1,X5,L2,X5,L2,
    X4,L4,L4,X4,X5,L5,L5,X5,X1,L1,L1,X1
};
void th1()
{
    int sleep=0;
    int voice=0x0;
    for(auto i:lemon_tree_h) 
    {
        if(i>120) 
        {
            sleep=i;//Sleep(i/2);
            continue;
        }
        if (i==_) 
        {
            //midiOutShortMsg(handle,0x90);
            Sleep(sleep);
            continue;
        }
        voice=(volume<<16)+((i+offset)<<8)+0x90;
        midiOutShortMsg(handle,voice);
        cout<<i<<endl;
        Sleep(sleep);
    }
}
void th2()
{
    int sleep=0;
    int voice=0x0;
    for(auto i:lemon_tree_l) 
    {
        if(i>120) 
        {
            sleep=i;//Sleep(i/2);
            continue;
        }
        if (i==_) 
        {
            //midiOutShortMsg(handle,0x90);
            Sleep(sleep);
            continue;
        }
        voice=(volume<<16)+((i+offset)<<8)+0x90;
        midiOutShortMsg(handle,voice);
        cout<<i<<endl;
        Sleep(sleep);
    }
}
int main()
{
    midiOutOpen(&handle,0,0,0,CALLBACK_NULL);
    thread t1(th1);
    t1.detach();
    thread t2(th2);
    t2.detach();
    while(1);
    midiOutClose(handle);
    return 0;
}