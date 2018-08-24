#include <iostream>
#include <string> 
#include <vector> 
#include <iterator> 
#include <algorithm>  
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <map>
#include "win10.h"
#include "Class.h"
using namespace std;
class LC { public: LC() { /*setlocale(LC_ALL, "rus"); system("chcp 1251 > nul")*/; srand(time(0)); } ~LC() {} }l;

void gd(int i, int choise, int num);

int select_main_map() {
  int choise = 0;
  int key;
  for (int i = 0; i < 3; i++) {
    gd(i, choise, i + 1);
  }
  SetPos(25, 20); cout << "Easy      ";
  while (1) {
    if (_kbhit()) {
      key = _getch();
      if (key == 75) {
        if (choise != 0) choise--;
        else choise = 2;
      }
      else if (key == 77) {
        if (choise != 2) choise++;
        else choise = 0;
      }
      else if (key == 13) {
        system("cls");
        if (choise == 0)return 1;
        else if (choise == 1)return 2;
        else if (choise == 2)return 3;
      }
      else if (key == 27) {
        system("cls");
        break;
      }
      else {
        Sleep(1);
      }
      for (int i = 0; i < 3; i++) {
        gd(i, choise, i + 1);
        if (choise == 0) {
          SetPos(25, 20); SetColor(0x0A); cout << ">>>Easy<<<      "; SetColor(0x07);
        }
        else if (choise == 1) {
          SetPos(25, 20); SetColor(0x0E); cout << ">>>Medium<<<    "; SetColor(0x07);
        }
        else if (choise == 2) {
          SetPos(25, 20); SetColor(0x0C); cout << ">>>Hard<<<      "; SetColor(0x07);
        }
      }

    }
  }
  return 0;
}

int main() {
  HideCursor();
  Map m;
  int key;
  int choise = 0;
  string na;
  m.download_Bin("resume", 1);
  start(1000, 1000, 15, 20);

  SetPos(2, 4); SetColor(0x0A); cout << "New Game"; SetColor(0x07);
  SetPos(2, 5); cout << "Continue";
  SetPos(2, 6); cout << "How to play";
  SetPos(2, 7); cout << "Download";
  SetPos(2, 8); cout << "Download Map";
  SetPos(2, 9); cout << "Level editor";
  SetPos(2, 10); cout << "Exit";
  while (1) {
    if (_kbhit()) {
      key = _getch();
      if (key == 72) {
        if (choise > 0)choise--;
        else if (choise == 0)choise = 6;
      }
      else if (key == 80) {
        if (choise < 6)choise++;
        else if (choise == 6)choise = 0;
      }
      else if (key == 13) {
        if (choise == 0) {
          system("cls"); int k = select_main_map();
          if (k == 1) {
            start(1000, 1000, 5, 4);
            m.download_Bin("front", 0);
            m.setMode(1);
            m.start_game(1); system("cls");
          }
          else if (k == 2) {
            start(1000, 1000, 5, 4);
            m.download_Bin("puzzle", 0);
            m.setMode(2);
            m.start_game(1); system("cls");
          }
          else if (k == 3) {
            start(1000, 1000, 5, 4);
            m.download_Bin("final", 0);
            m.setMode(3);
            m.start_game(1); system("cls");
          }
        }
        else if (choise == 1) { start(1000, 1000, 5, 4);	m.start_game(1); system("cls"); }
        else if (choise == 2) {}
        else if (choise == 3) { start(1000, 1000, 5, 4);	m.start_game(2); system("cls"); }
        else if (choise == 4) { system("cls"); cout << "enter the name of the card: "; getline(cin, na); m.download_Bin(na, 0); m.setMode(2); system("cls"); }
        else if (choise == 5) { m.download("2.txt"); m.the_selection_interface(); system("cls"); }
        else if (choise == 6) return 1;
      }
      else {
        Sleep(1);
      }
      SetPos(2, 4); SetColor(choise == 0 ? 0x0A : 0x07); cout << "New Game"; SetColor(0x07);
      SetPos(2, 5); SetColor(choise == 1 ? 0x0A : 0x07); cout << "Continue"; SetColor(0x07);
      SetPos(2, 6); SetColor(choise == 2 ? 0x0A : 0x07); cout << "How to play"; SetColor(0x07);
      SetPos(2, 7); SetColor(choise == 3 ? 0x0A : 0x07); cout << "Download"; SetColor(0x07);
      SetPos(2, 8); SetColor(choise == 4 ? 0x0A : 0x07); cout << "Download Map"; SetColor(0x07);
      SetPos(2, 9); SetColor(choise == 5 ? 0x0A : 0x07); cout << "Level editor"; SetColor(0x07);
      SetPos(2, 10); SetColor(choise == 6 ? 0x0A : 0x07); cout << "Exit"; SetColor(0x07);
    }
  }
}

void gd(int i, int choise, int num) {
  if (num == 1) {
    SetPos(5 + 15 * i, 5); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
    SetPos(5 + 15 * i, 5 + 1); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 2); cout << char(219) << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 3); cout << char(219) << " " << " " << " " << " " << char(219) << char(219) << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 4); cout << char(219) << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 5); cout << char(219) << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 6); cout << char(219) << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 7); cout << char(219) << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 8); cout << char(219) << " " << " " << " " << " " << char(219) << char(219) << char(219) << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 9); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 10); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
    SetPos(5 + 15 * i, 5 + 11); SetColor(i == choise ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(5 + 15 * i, 5 + 12); SetColor(i == choise ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
  }
  else if (num == 2) {
    SetPos(5 + 15 * i, 5); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
    SetPos(5 + 15 * i, 5 + 1); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 2); cout << char(219) << " " << " " << " " << " " << char(219) << char(219) << char(219) << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 3); cout << char(219) << " " << " " << " " << char(219) << " " << " " << " " << char(219) << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 4); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 5); cout << char(219) << " " << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 6); cout << char(219) << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 7); cout << char(219) << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 8); cout << char(219) << " " << " " << " " << char(219) << char(219) << char(219) << char(219) << char(219) << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 9); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 10); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
    SetPos(5 + 15 * i, 5 + 11); SetColor(i == choise ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(5 + 15 * i, 5 + 12); SetColor(i == choise ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
  }
  else if (num == 3) {
    SetPos(5 + 15 * i, 5); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
    SetPos(5 + 15 * i, 5 + 1); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 2); cout << char(219) << " " << " " << " " << " " << " " << char(219) << char(219) << char(219) << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 3); cout << char(219) << " " << " " << " " << " " << char(219) << " " << " " << " " << char(219) << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 4); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 5); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 6); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << char(219) << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 7); cout << char(219) << " " << " " << " " << " " << char(219) << " " << " " << " " << char(219) << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 8); cout << char(219) << " " << " " << " " << " " << " " << char(219) << char(219) << char(219) << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 9); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
    SetPos(5 + 15 * i, 5 + 10); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
    SetPos(5 + 15 * i, 5 + 11); SetColor(i == choise ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(5 + 15 * i, 5 + 12); SetColor(i == choise ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
  }
}
