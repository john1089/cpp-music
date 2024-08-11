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
    S1 = C6, S2 = D6, S3 = E6, S4 = F6, S5 = G6, S6 = A6, S7 = B6,
    NOTE = 625, _ = Rest
};
int MK(int a,int b)
{
	return (a<<8)|b; 
}
int MK(int a,int b,int c)
{
	return (a<<16)|(b<<8)|c; 
}
HMIDIOUT handle;
const int volume=0x7f;
const int offset=0;//M1=C4
const int als_h[]={NOTE,_,_,H6,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H1,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE,H3,NOTE*2,H2,NOTE,M6,NOTE*2,M6,NOTE,M5,NOTE*3,H1,
NOTE*2,S1,NOTE,M5,

NOTE*2,H1,NOTE,H1,NOTE*2,H1,NOTE,H3,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE/2,H3,H2,NOTE*2,H1,NOTE,H1,NOTE*2,H3,NOTE,H5,NOTE*3,H6,
NOTE*2,H6,NOTE,H6,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H1,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE,H3,NOTE*2,H1,NOTE,M6,NOTE*2,M6,NOTE,M5,NOTE*3,H1,
NOTE*2,H1,NOTE,H6,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H1,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE,H6,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H5,NOTE*3,H6,
NOTE*2,H6,NOTE,S1,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H1,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE,H3,NOTE*2,H1,NOTE,M6,NOTE*2,M6,NOTE,M5,NOTE*3,H1,
NOTE*2,H1,NOTE,M5,

NOTE*2,H1,NOTE,H1,NOTE*2,H1,NOTE,H3,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE/2,H3,H2,NOTE*2,H1,NOTE,H1,NOTE*2,H3,NOTE,H5,NOTE*3,H6,
NOTE*2,H6,NOTE,H6,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H1,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE,H3,NOTE*2,H1,NOTE,M6,NOTE*2,M6,NOTE,M5,NOTE*3,H1,
NOTE*2,H1,NOTE,H6,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H1,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE,H6,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H5,NOTE*3,H6,
NOTE*2,H6,NOTE,S1,NOTE*2,H5,NOTE,H3,NOTE*2,H3,NOTE,H1,NOTE*2,H2,NOTE,H1,
NOTE*2,H2,NOTE,H3,NOTE*2,H1,NOTE,M6,NOTE*2,M6,NOTE,M5,NOTE*3,H1,
NOTE*2,H1,NOTE,M5,

NOTE*3,H1,NOTE*2,S1,NOTE,_
};
const int als_l[]={NOTE*3,_,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X2,X6,L1,L2+1,NOTE,L6,
NOTE/2,X3,L3,L5+1,L7,NOTE,M2,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X4,L1,L4,L6,NOTE,MK(L7,L5),NOTE/2,L1,L5,M1,M3,M5,M3,
NOTE*2,M1,NOTE,_,

NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X5,L2,L5,L7,NOTE,M2,
NOTE/2,X5,L2,L5,L7,NOTE,M2,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X1,L1,X2,L2,X3,L3,X4,L1,L4,L6,NOTE,M1,
NOTE/2,X4,L1,L4,L6,NOTE,M1,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X2,X6,L2,L4+1,NOTE,L6,
NOTE/2,X3,L3,L5+1,L7,NOTE,M2,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X4,L1,L4,L6,NOTE,MK(L7,L5),NOTE/2,L1,L5,M1,M3,M5,M3,
NOTE*2,M1,NOTE,_,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X2,X6,L2,L4+1,NOTE,L6,
NOTE/2,X5,L2,L5,L7,NOTE,M2,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X1,L1,X2,L2,X3,L3,X4,L1,L4,L6,NOTE,M1,
NOTE/2,X4,L1,L4,L6,NOTE,M1,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X2,X6,L2,L4+1,NOTE,L6,
NOTE/2,X3,L3,L5+1,L7,NOTE,M2,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X4,L1,L4,L6,NOTE,MK(L7,L5),NOTE/2,L1,L5,M1,M3,M5,M3,
NOTE*2,M1,NOTE,_,

NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X5,L2,L5,L7,NOTE,M2,
NOTE/2,X5,L2,L5,L7,NOTE,M2,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X1,L1,X2,L2,X3,L3,X4,L1,L4,L6,NOTE,M1,
NOTE/2,X4,L1,L4,L6,NOTE,M1,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X2,X6,L2,L4+1,NOTE,L6,
NOTE/2,X3,L3,L5+1,L7,NOTE,M2,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X4,L1,L4,L6,NOTE,MK(L7,L5),NOTE/2,L1,L5,M1,M3,M5,M3,
NOTE*2,M1,NOTE,_,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X2,X6,L2,L4+1,NOTE,L6,
NOTE/2,X5,L2,L5,L7,NOTE,M2,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X1,L1,X2,L2,X3,L3,X4,L1,L4,L6,NOTE,M1,
NOTE/2,X4,L1,L4,L6,NOTE,M1,NOTE/2,L1,L5,M1,M3,NOTE,M5,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X2,X6,L2,L4+1,NOTE,L6,
NOTE/2,X3,L3,L5+1,L7,NOTE,M2,NOTE/2,X6,L3,L6,M1,NOTE,M3,NOTE/2,X4,L1,L4,L6,NOTE,MK(L7,L5),NOTE/2,L1,L5,M1,M3,M5,M3,
NOTE*2,M1,NOTE,_,

NOTE/2,L1,L5,M1,M2,M3,M5,NOTE*2,M1,NOTE,_
}; 
void play_high()
{
    int voice = 0x0;
    int sleep = 300;
    int t=0;
    for(auto i:als_h)
    {
        if (i>120 && i<3000) 
        {
            sleep = i;//Sleep(i/2);
            continue;
        }
        if (i == _) 
        {
            //midiOutShortMsg(handle,0x90);
            t+=sleep;
            Sleep(sleep);
            continue;
        }
        int mask=(1<<8)-1;
        while(i)
        {
            voice = (volume << 16) + ((i&mask+offset) << 8) + 0x90;
            midiOutShortMsg(handle, voice);
            cout << (i&mask) <<endl;
            i>>=8;
        }
        t+=sleep;
        Sleep(sleep);
    }
    cout<<"THREAD 1:"<<t<<endl;
}
void play_low()
{
    int voice = 0x0;
    int sleep = 300;
    int t=0;
    for(auto i:als_l)
    {
        if (i>120 && i<3000) 
        {
            sleep = i;//Sleep(i/2);
            continue;
        }
        if (i == _) 
        {
            //midiOutShortMsg(handle,0x90);
            t+=sleep;
            Sleep(sleep);
            continue;
        }
        int mask=(1<<8)-1;
        while(i)
        {
            voice = (0x60 << 16) + ((i&mask+offset) << 8) + 0x90;
            midiOutShortMsg(handle, voice);
            cout << (i&mask) <<endl;
            i>>=8;
        }
        t+=sleep;
        Sleep(sleep);
    }
    cout<<"THREAD 2:"<<t<<endl;
}
int main()
{
    midiOutOpen(&handle,0,0,0,CALLBACK_NULL);
    thread t1(play_high);
    t1.detach();
    thread t2(play_low);
    t2.detach();
	while(1);
    midiOutClose(handle);
    return 0;
}