#pragma once
#include "win10.h"
#include <iostream>
using namespace std;
class Map;

class object {
protected:
  char Type[5][5];
  int posX;
  int posY;
  int Color[5][5];
public:
  object() :posX(), posY() {}
  virtual void obres() = 0;
  virtual void show() = 0;
};

class base : object {
public:
  base() : object() { posX = 5; posY = 5; obres(); }
  virtual void obres() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (i == 0 || i == 4) { Type[i][j] = char(4); Color[i][j] = 10; }
        else if (j == 0 || j == 4) { Type[i][j] = char(4); Color[i][j] = 10; }
        else { Type[i][j] = char(4); Color[i][j] = 11; }
      }
    }
  }
  virtual void show() {
    for (int i = 0; i < 5; i++) {
      SetPos(this->posX, this->posY + i);
      for (int j = 0; j < 5; j++) {
        if (Color[i][j] == 10)SetColor(0x0A);
        else if (Color[i][j] == 11)SetColor(0x0B);
        cout << Type[i][j];
        SetColor(0x07);
      }
    }
  }
  void moveUp(char m[100][100]) {
    this->obres();
    if (m[posY - 5][posX] != '#')
      posY -= 5;
  }
  void moveDown(char m[100][100]) {
    this->obres();
    if (m[posY + 7][posX] != '#')
      posY += 5;
  }
  void moveLeft(char m[100][100]) {
    this->obres();
    if (m[posY][posX - 5] != '#')
      posX -= 5;
  }
  void moveRight(char m[100][100]) {
    this->obres();
    if (m[posY][posX + 5] != '#')
      posX += 5;
  }
  int getX()const {
    return posX;
  }
  int getY()const {
    return posY;
  }
  int getColor(int i, int j) const {
    return Color[i][j];
  }
};

class PosEnemy : object {
public:
  int getX()const {
    return posX;
  }
  int getY()const {
    return posY;
  }
  void setPos(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
  }
  PosEnemy() :object() {
    posX = 5; posY = 5; obres();
  }
  virtual void obres() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type[i][j] = (char)14;
        Color[i][j] = 11;
      }
    }
  }
  virtual void show() {
    for (int i = 0; i < 5; i++) {
      SetPos(posX, posY + i);
      for (int j = 0; j < 5; j++) {
        if (Color[i][j] == 4)SetColor(0x0B);
        else if (Color[i][j] == 12)SetColor(0x0C);
        cout << Type[i][j];
        SetColor(07);
      }
    }
  }
  void moveUp(char m[100][100]) {
    this->obres();
    if (m[posY - 5][posX] != '#')
      posY -= 5;
  }
  void moveDown(char m[100][100]) {
    this->obres();
    if (m[posY + 7][posX] != '#')
      posY += 5;
  }
  void moveLeft(char m[100][100]) {
    this->obres();
    if (m[posY][posX - 5] != '#')
      posX -= 5;
  }
  void moveRight(char m[100][100]) {
    this->obres();
    if (m[posY][posX + 5] != '#')
      posX += 5;
  }
};

class enemy : virtual object {
  char Type2[5][5];
  int Color2[5][5];
  char Type3[5][5];
  int Color3[5][5];
  char Type4[5][5];
  int Color4[5][5];
  int storona;
  static int live;
  bool living;
  bool existing;
  static int ram[20][20];
  int map_of_the_area_in_memory[20][20];
  void Strart_ram() {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        ram[i][j] = 0;
        map_of_the_area_in_memory[i][j] = 0;
      }
    }
  }
public:
  void save_e(string name) {
    ofstream file_e_w(name, ios::binary);
    file_e_w.write((char*)this->Color, sizeof(int));
    file_e_w.write((char*)this->Color2, sizeof(int));
    file_e_w.write((char*)this->Color3, sizeof(int));
    file_e_w.write((char*)this->Color4, sizeof(int));
    file_e_w.write((char*)this->Type, sizeof(char));
    file_e_w.write((char*)this->Type2, sizeof(char));
    file_e_w.write((char*)this->Type3, sizeof(char));
    file_e_w.write((char*)this->Type4, sizeof(char));
    file_e_w.write((char*)this->ram, sizeof(this->ram));
    file_e_w.write((char*)this->map_of_the_area_in_memory, sizeof(this->map_of_the_area_in_memory));
    file_e_w.write((char*)&this->storona, sizeof(this->storona));
    file_e_w.write((char*)&this->live, sizeof(this->live));
    file_e_w.write((char*)&this->living, sizeof(this->living));
    file_e_w.write((char*)&this->existing, sizeof(this->existing));
    file_e_w.write((char*)&this->posX, sizeof(this->posX));
    file_e_w.write((char*)&this->posY, sizeof(this->posY));
    file_e_w.close();
  }
  void download_e(string name) {
    ifstream file_e_r(name, ios::binary);
    file_e_r.read((char*)this->Color, sizeof(int));
    file_e_r.read((char*)this->Color2, sizeof(int));
    file_e_r.read((char*)this->Color3, sizeof(int));
    file_e_r.read((char*)this->Color4, sizeof(int));
    file_e_r.read((char*)this->Type, sizeof(char));
    file_e_r.read((char*)this->Type2, sizeof(char));
    file_e_r.read((char*)this->Type3, sizeof(char));
    file_e_r.read((char*)this->Type4, sizeof(char));
    file_e_r.read((char*)this->ram, sizeof(this->ram));
    file_e_r.read((char*)this->map_of_the_area_in_memory, sizeof(this->map_of_the_area_in_memory));
    file_e_r.read((char*)&this->storona, sizeof(this->storona));
    file_e_r.read((char*)&this->live, sizeof(this->live));
    file_e_r.read((char*)&this->living, sizeof(this->living));
    file_e_r.read((char*)&this->existing, sizeof(this->existing));
    file_e_r.read((char*)&this->posX, sizeof(this->posX));
    file_e_r.read((char*)&this->posY, sizeof(this->posY));
    file_e_r.close();
  }

  void setRam(int i, int j, int l) {
    this->ram[i][j] = l;
  }
  int getMemory(int i, int j) {
    return this->ram[i][j];
  }
  void setmap_of_the_area_in_memory(int i, int j, int l) {
    this->map_of_the_area_in_memory[i][j] = l;
  }
  void delete_map_of_the_area_in_memory() {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        this->map_of_the_area_in_memory[i][j] == 0;
      }
    }
  }
  void deadlock(int i, int j) {
    this->map_of_the_area_in_memory[i][j] = 0;
    if (this->map_of_the_area_in_memory[i + 1][j] == 4)setmap_of_the_area_in_memory(i + 1, j, 0);
    if (this->map_of_the_area_in_memory[i - 1][j] == 4)setmap_of_the_area_in_memory(i - 1, j, 0);
    if (this->map_of_the_area_in_memory[i][j + 1] == 4)setmap_of_the_area_in_memory(i, j + 1, 0);
    if (this->map_of_the_area_in_memory[i][j - 1] == 4)setmap_of_the_area_in_memory(i, j - 1, 0);
    if (this->map_of_the_area_in_memory[i + 1][j] == 2)deadlock(i + 1, j);
    if (this->map_of_the_area_in_memory[i - 1][j] == 2)deadlock(i - 1, j);
    if (this->map_of_the_area_in_memory[i][j + 1] == 2)deadlock(i, j + 1);
    if (this->map_of_the_area_in_memory[i][j - 1] == 2)deadlock(i, j - 1);
  }
  int getMap_of_the_area_in_memory(int i, int j) {
    return this->map_of_the_area_in_memory[i][j];
  }
  void switchExisting() {
    if (existing)existing = !existing;
    else existing = 1;
  }
  bool getExisting() const {
    return existing;
  }
  int &operator--() {
    live--;
    return live;
  }
  int getStor() {
    return storona;
  }
  void setStor(int p) {
    storona = p;
  }
  virtual void obres() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (j == 0 || j == 4) { Type[i][j] = char(177); Color[i][j] = 8; }
        else if (j == 2 && i != 4) { Type[i][j] = char(219); Color[i][j] = 7; }
        else if ((i == 2 && j != 0) || (i == 2 && j != 4)) { Type[i][j] = char(219); Color[i][j] = 7; }
        else if ((i == 1 && (j == 1 || 3)) || (i == 3 && (j == 1 || 3))) { Type[i][j] = char(219); Color[i][j] = 13; }
        else {
          if (i == 0 || i == 4) {
            Type[i][j] = ' ';
            Color[i][j] = 0;
          }
        }

      }
    }
  }
  void Levo() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type2[i][j] = Type[i][j];
        Color2[i][j] = Color[i][j];
      }
    }
    int buf;
    int bufC;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        buf = Type2[i][j];
        bufC = Color2[i][j];
        Type2[i][j] = Type2[j][5 - 1 - i];
        Color2[i][j] = Color2[j][5 - 1 - i];
        Type2[j][5 - 1 - i] = buf;
        Color2[j][5 - 1 - i] = bufC;
      }
    }
  }
  void Vniz() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type3[i][j] = Type[i][j];
        Color3[i][j] = Color[i][j];
      }
    }
    swap(Type3[0][2], Type3[4][2]);
    swap(Color3[0][2], Color3[4][2]);
  }
  void Pravo() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type4[i][j] = Type[i][j];
        Color4[i][j] = Color[i][j];
      }
    }
    int buf;
    int bufC;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (i == 0 || i == 4) {
          buf = Type4[i][j];
          bufC = Color4[i][j];
          Type4[i][j] = Type4[j][5 - 1 - i];
          Color4[i][j] = Color4[j][5 - 1 - i];
          Type4[j][5 - 1 - i] = buf;
          Color4[j][5 - 1 - i] = bufC;
        }
      }
    }
  }
  enemy() :object() { Strart_ram(); existing = 0; living = 1; setPos(35, 90); this->obres(); this->Levo(); this->Vniz(); this->Pravo(); storona = 0; }

  void deadХ() {
    if (living)living = !living;
  }
  void reverdeadХ() {
    if (!living)living = true;
  }
  bool getLiving() {
    return living;
  }

  int getX() {
    return posX;
  }
  int getY() {
    return posY;
  }
  void setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
  }
  void moveUp() {
    posY -= 5;
  }
  void moveDown() {
    posY += 5;
  }
  void moveLeft() {
    posX -= 5;
  }
  void moveRight() {
    posX += 5;
  }
  int stor() {
    return this->storona;
  }
  int getColor(int i, int j) {
    if (storona == 0)return Color[i][j];
    if (storona == 1)return Color2[i][j];
    if (storona == 2)return Color3[i][j];
    if (storona == 3)return Color4[i][j];
  }
  char getP(int i, int j) {
    if (storona == 0)return Type[i][j];
    if (storona == 1)return Type2[i][j];
    if (storona == 2)return Type3[i][j];
    if (storona == 3)return Type4[i][j];
  }
  int getLive() const {
    return live;
  }
  virtual void show() {
    for (int i = 0; i < 5; i++) {
      SetPos(posX, posY + i);
      for (int j = 0; j < 5; j++) {
        if (Color[i][j] == 8)SetColor(0x08);
        if (Color[i][j] == 13)SetColor(0x0D);
        if (Color[i][j] == 0)SetColor(00);
        if (Color[i][j] == 7)SetColor(07);
        cout << Type[i][j];
        SetColor(07);
      }
    }
  }
};

int enemy::live = 10;
int enemy::ram[20][20];

class Blok :virtual object {
public:
  Blok() :object() {
    posX = 5; posY = 5; obres();
  }
  virtual void obres() {
    int h = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type[i][j] = (char)178;
        if (h % 2 == 0) Color[i][j] = 4;
        else Color[i][j] = 12;
        h++;
      }
      h -= 5;
      h++;
    }
  }
  int getColor(int i, int j) {
    return Color[i][j];
  }
  int getX()const {
    return posX;
  }
  int getY()const {
    return posY;
  }
  virtual void show() {
    for (int i = 0; i < 5; i++) {
      SetPos(posX, posY + i);
      for (int j = 0; j < 5; j++) {
        if (Color[i][j] == 4)SetColor(0x04);
        else if (Color[i][j] == 12)SetColor(0x0C);
        cout << Type[i][j];
        SetColor(07);
      }
    }
  }
  void setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
  }
  void moveUp(char m[100][100]) {
    this->obres();
    if (m[posY - 5][posX] != '#')
      posY -= 5;
  }
  void moveDown(char m[100][100]) {
    this->obres();
    if (m[posY + 7][posX] != '#')
      posY += 5;
  }
  void moveLeft(char m[100][100]) {
    this->obres();
    if (m[posY][posX - 5] != '#')
      posX -= 5;
  }
  void moveRight(char m[100][100]) {
    this->obres();
    if (m[posY][posX + 5] != '#')
      posX += 5;
  }
};

class immortol_Blok :virtual object {
public:
  immortol_Blok() :object() {
    posX = 5; posY = 5; obres();
  }
  virtual void obres() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type[i][j] = (char)219;
        Color[i][j] = 15;
      }
    }
  }
  int getColor(int i, int j) {
    return Color[i][j];
  }
  int getX()const {
    return posX;
  }
  int getY()const {
    return posY;
  }
  virtual void show() {
    for (int i = 0; i < 5; i++) {
      SetPos(posX, posY + i);
      for (int j = 0; j < 5; j++) {
        SetColor(0x0F);
        cout << Type[i][j];
        SetColor(07);
      }
    }
  }
  void setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
  }
  void moveUp(char m[100][100]) {
    this->obres();
    if (m[posY - 5][posX] != '#')
      posY -= 5;
  }
  void moveDown(char m[100][100]) {
    this->obres();
    if (m[posY + 7][posX] != '#')
      posY += 5;
  }
  void moveLeft(char m[100][100]) {
    this->obres();
    if (m[posY][posX - 5] != '#')
      posX -= 5;
  }
  void moveRight(char m[100][100]) {
    this->obres();
    if (m[posY][posX + 5] != '#')
      posX += 5;
  }
};

class water_Blok :virtual object {
public:
  water_Blok() :object() {
    posX = 5; posY = 5; obres();
  }
  virtual void obres() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type[i][j] = (char)176;
        Color[i][j] = 9;
      }
    }
  }
  int getColor(int i, int j) {
    return Color[i][j];
  }
  int getX()const {
    return posX;
  }
  int getY()const {
    return posY;
  }
  virtual void show() {
    for (int i = 0; i < 5; i++) {
      SetPos(posX, posY + i);
      for (int j = 0; j < 5; j++) {
        SetColor(0x09);
        cout << Type[i][j];
        SetColor(07);
      }
    }
  }
  void setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
  }
  void moveUp(char m[100][100]) {
    this->obres();
    if (m[posY - 5][posX] != '#')
      posY -= 5;
  }
  void moveDown(char m[100][100]) {
    this->obres();
    if (m[posY + 7][posX] != '#')
      posY += 5;
  }
  void moveLeft(char m[100][100]) {
    this->obres();
    if (m[posY][posX - 5] != '#')
      posX -= 5;
  }
  void moveRight(char m[100][100]) {
    this->obres();
    if (m[posY][posX + 5] != '#')
      posX += 5;
  }
};

class Player_Tank : object {
  char Type2[5][5];
  int Color2[5][5];
  char Type3[5][5];
  int Color3[5][5];
  char Type4[5][5];
  int Color4[5][5];
  int storona;
  static int live;
  bool living;
public:
  void save_pt(string name) {
    ofstream file_pt_w(name, ios::binary);
    file_pt_w.write((char*)this->Color, sizeof(int));
    file_pt_w.write((char*)this->Color2, sizeof(int));
    file_pt_w.write((char*)this->Color3, sizeof(int));
    file_pt_w.write((char*)this->Color4, sizeof(int));
    file_pt_w.write((char*)this->Type, sizeof(char));
    file_pt_w.write((char*)this->Type2, sizeof(char));
    file_pt_w.write((char*)this->Type3, sizeof(char));
    file_pt_w.write((char*)this->Type4, sizeof(char));
    file_pt_w.write((char*)&this->storona, sizeof(this->storona));
    file_pt_w.write((char*)&this->live, sizeof(this->live));
    file_pt_w.write((char*)&this->living, sizeof(this->living));
    file_pt_w.write((char*)&this->posX, sizeof(this->posX));
    file_pt_w.write((char*)&this->posY, sizeof(this->posY));
    file_pt_w.close();
  }
  void download_pt(string name) {
    ifstream file_pt_r(name, ios::binary);
    file_pt_r.read((char*)this->Color, sizeof(int));
    file_pt_r.read((char*)this->Color2, sizeof(int));
    file_pt_r.read((char*)this->Color3, sizeof(int));
    file_pt_r.read((char*)this->Color4, sizeof(int));
    file_pt_r.read((char*)this->Type, sizeof(char));
    file_pt_r.read((char*)this->Type2, sizeof(char));
    file_pt_r.read((char*)this->Type3, sizeof(char));
    file_pt_r.read((char*)this->Type4, sizeof(char));
    file_pt_r.read((char*)&this->storona, sizeof(this->storona));
    file_pt_r.read((char*)&this->live, sizeof(this->live));
    file_pt_r.read((char*)&this->living, sizeof(this->living));
    file_pt_r.read((char*)&this->posX, sizeof(this->posX));
    file_pt_r.read((char*)&this->posY, sizeof(this->posY));
    file_pt_r.close();
  }

  bool getLiving() const {
    return living;
  }
  int &operator--() {
    live--;
    return live;
  }
  int getLive() const {
    return live;
  }
  void setLiving(bool b) {
    this->living = b;
  }
  int getStor() {
    return storona;
  }
  void setStor(int p) {
    storona = p;
  }
  virtual void obres() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (j == 0 || j == 4) { Type[i][j] = char(177); Color[i][j] = 8; }
        else if (j == 2 && i != 4) { Type[i][j] = char(219); Color[i][j] = 7; }
        else if ((i == 2 && j != 0) || (i == 2 && j != 4)) { Type[i][j] = char(219); Color[i][j] = 7; }
        else if ((i == 1 && (j == 1 || 3)) || (i == 3 && (j == 1 || 3))) { Type[i][j] = char(219); Color[i][j] = 10; }
        else {
          if (i == 0 || i == 4) {
            Type[i][j] = ' ';
            Color[i][j] = 0;
          }
        }

      }
    }
  }

  void show_hp(int x, int y) {
    for (int i = 0; i < 3; i++) {
      if (i < this->getLive()) {
        SetPos(x + i * 8, y);
        SetColor(0x0C);	cout << " #   #"; SetColor(0x07);
        SetPos(x + i * 8, y + 1);
        SetColor(0x0C); cout << "### ###"; SetColor(0x07);
        SetPos(x + i * 8, y + 2);
        SetColor(0x0C); cout << " #####"; SetColor(0x07);
        SetPos(x + i * 8, y + 3);
        SetColor(0x0C); cout << "   # "; SetColor(0x07);
      }
      else {
        SetPos(x + i * 8, y);
        cout << "      ";
        SetPos(x + i * 8, y + 1);
        cout << "       ";
        SetPos(x + i * 8, y + 2);
        cout << "       ";
        SetPos(x + i * 8, y + 3);
        cout << "      ";
      }
    }
  }


  void Levo() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type2[i][j] = Type[i][j];
        Color2[i][j] = Color[i][j];
      }
    }
    int buf;
    int bufC;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        buf = Type2[i][j];
        bufC = Color2[i][j];
        Type2[i][j] = Type2[j][5 - 1 - i];
        Color2[i][j] = Color2[j][5 - 1 - i];
        Type2[j][5 - 1 - i] = buf;
        Color2[j][5 - 1 - i] = bufC;
      }
    }
  }
  void Vniz() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type3[i][j] = Type[i][j];
        Color3[i][j] = Color[i][j];
      }
    }
    swap(Type3[0][2], Type3[4][2]);
    swap(Color3[0][2], Color3[4][2]);
  }
  void Pravo() {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        Type4[i][j] = Type[i][j];
        Color4[i][j] = Color[i][j];
      }
    }
    int buf;
    int bufC;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        if (i == 0 || i == 4) {
          buf = Type4[i][j];
          bufC = Color4[i][j];
          Type4[i][j] = Type4[j][5 - 1 - i];
          Color4[i][j] = Color4[j][5 - 1 - i];
          Type4[j][5 - 1 - i] = buf;
          Color4[j][5 - 1 - i] = bufC;
        }
      }
    }
  }
  void Delete() {
    for (int j = 0; j < 5; j++) {
      for (int i = 0; i < 5; i++) {
        Type[j][i] = 'M';
      }
    }
  }
  Player_Tank() :object() { setPos(35, 90); this->obres(); this->Levo(); this->Vniz(); this->Pravo(); storona = 0; }
  int getX() {
    return posX;
  }
  int getY() {
    return posY;
  }
  void setPos(int x, int y) {
    this->posX = x;
    this->posY = y;
  }
  void moveUp() {
    posY -= 5;
  }
  void moveDown() {
    posY += 5;
  }
  void moveLeft() {
    posX -= 5;
  }
  void moveRight() {
    posX += 5;
  }
  int stor() {
    if (Type[0][2] == char(219)) return 0;
    if (Type[2][0] == char(219)) return 1;
    if (Type[4][2] == char(219)) return 2;
    if (Type[2][4] == char(219)) return 3;
  }
  int getColor(int i, int j, int stor) {
    if (stor == 0)return Color[i][j];
    if (stor == 1)return Color2[i][j];
    if (stor == 2)return Color3[i][j];
    if (stor == 3)return Color4[i][j];
  }
  char getP(int i, int j, int stor) {
    if (stor == 0)return Type[i][j];
    if (stor == 1)return Type2[i][j];
    if (stor == 2)return Type3[i][j];
    if (stor == 3)return Type4[i][j];
  }
  virtual void show() {
    for (int i = 0; i < 5; i++) {
      SetPos(posX, posY + i);
      for (int j = 0; j < 5; j++) {
        if (Color[i][j] == 8)SetColor(0x08);
        if (Color[i][j] == 10)SetColor(0x0A);
        if (Color[i][j] == 0)SetColor(00);
        if (Color[i][j] == 7)SetColor(07);
        cout << Type[i][j];
        SetColor(07);
      }
    }
  }
};
int Player_Tank::live = 3;
class Map {
private:
  char Map_main[100][100];
  int Color_Map[100][100];
  int posX1, posY1;
  int posX2, posY2;
  int posX3, posY3;
  int posX4, posY4;
  int mode;
  time_t year[5];
  time_t day[5];
  time_t month[5];
  time_t second[5];
  time_t minute[5];
  time_t hour[5];
  int getYear(int i) {
    if (i >= 0 && i < 5) return year[i];
  }
  int getDay(int i) {
    if (i >= 0 && i < 5) return day[i];
  }
  int getMonth(int i) {
    if (i >= 0 && i < 5) return month[i];
  }

  void saveGame(string name, Player_Tank &pt, enemy &e1, enemy &e2, enemy &e3, enemy &e4) {
    this->save_Bin_not_name(name);
    name += '1';
    pt.save_pt(name);
    name += '2';
    e1.save_e(name);
    name += '3';
    e2.save_e(name);
    name += '4';
    e3.save_e(name);
    name += '5';
    e4.save_e(name);
    system("cls");
  }
  void download_game(string name, Player_Tank &pt, enemy &e1, enemy &e2, enemy &e3, enemy &e4) {
    this->download_Bin(name, 0);
    name += '1';
    pt.download_pt(name);
    name += '2';
    e1.download_e(name);
    name += '3';
    e2.download_e(name);
    name += '4';
    e3.download_e(name);
    name += '5';
    e4.download_e(name);
  }

  int menu_in_game(int i, int j) {
    int key;
    int choise = 1;
    SetPos(i, j);		 cout << "########################################################";
    SetPos(i, j + 1);    cout << "#                                                      #"; SetColor(0x0A); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 2);	 cout << "#       ###  #     ##   #   #                          #"; SetColor(0x0A); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 3);	 cout << "#       #  # #    #  #   # #                           #"; SetColor(0x0A); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 4);	 cout << "#       ###  #    ####    #                            #"; SetColor(0x0A); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 5);	 cout << "#       #    #### #  #    #                            #"; SetColor(0x0A); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 6);	 cout << "#                                                      #";
    SetPos(i, j + 7);	 cout << "#   #  # #### #   #   #   ####  ###  #    ##  #   #    #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 8);	 cout << "#   #### #  # #   #  ###  #  #  #  # #   #  #  # #     #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 9);	 cout << "#   #  # #  # # # #   #   #  #  # #  #   ####   #      #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 10);	 cout << "#   #  # ####  # #    ##  ####  #    ### #  #   #      #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 11);	 cout << "#                                                      #";
    SetPos(i, j + 12);	 cout << "#       ##   ##  #   # ####                            #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 13);	 cout << "#      #  # #  # #   # #                               #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 14);	 cout << "#       #   ####  # #  ####                            #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 15);	 cout << "#     #  #  #  #  # #  #                               #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 16);	 cout << "#      ##   #  #   #   ####                            #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 17);	 cout << "#                                                      #";
    SetPos(i, j + 18);	 cout << "#      #### #   #   #   #                              #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 19);	 cout << "#      #     # #       ###                             #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 20);	 cout << "#      ####   #     #   #                              #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 21);	 cout << "#      #     # #    #   #                              #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 22);	 cout << "#      #### #   #   #   ##                             #"; SetColor(0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
    SetPos(i, j + 23);	 cout << "#                                                      #";
    SetPos(i, j + 24);   cout << "########################################################";
    while (1) {
      if (_kbhit()) {
        key = _getch();
        if (key == 72) {
          if (choise != 1)choise--;
          else choise = 4;
        }
        else if (key == 80) {
          if (choise != 4)choise++;
          else choise = 1;
        }
        else if (key == 13) {
          if (choise == 1)return 1;
          if (choise == 2)return 2;
          if (choise == 3)return 3;
          if (choise == 4)return 4;
        }
        else if (key == 27) {
          return 1;
        }

        SetPos(i, j);		 cout << "########################################################";
        SetPos(i, j + 1);    cout << "#                                                      #"; SetColor(choise == 1 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 2);	 cout << "#       ###  #     ##   #   #                          #"; SetColor(choise == 1 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 3);	 cout << "#       #  # #    #  #   # #                           #"; SetColor(choise == 1 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 4);	 cout << "#       ###  #    ####    #                            #"; SetColor(choise == 1 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 5);	 cout << "#       #    #### #  #    #                            #"; SetColor(choise == 1 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 6);	 cout << "#                                                      #";
        SetPos(i, j + 7);	 cout << "#   #  # #### #   #   #   ####  ###  #    ##  #   #    #"; SetColor(choise == 2 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 8);	 cout << "#   #### #  # #   #  ###  #  #  #  # #   #  #  # #     #"; SetColor(choise == 2 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 9);	 cout << "#   #  # #  # # # #   #   #  #  # #  #   ####   #      #"; SetColor(choise == 2 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 10);	 cout << "#   #  # ####  # #    ##  ####  #    ### #  #   #      #"; SetColor(choise == 2 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 11);	 cout << "#                                                      #";
        SetPos(i, j + 12);	 cout << "#       ##   ##  #   # ####                            #"; SetColor(choise == 3 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 13);	 cout << "#      #  # #  # #   # #                               #"; SetColor(choise == 3 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 14);	 cout << "#       #   ####  # #  ####                            #"; SetColor(choise == 3 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 15);	 cout << "#     #  #  #  #  # #  #                               #"; SetColor(choise == 3 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 16);	 cout << "#      ##   #  #   #   ####                            #"; SetColor(choise == 3 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 17);	 cout << "#                                                      #";
        SetPos(i, j + 18);	 cout << "#      #### #   #   #   #                              #"; SetColor(choise == 4 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 19);	 cout << "#      #     # #       ###                             #"; SetColor(choise == 4 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 20);	 cout << "#      ####   #     #   #                              #"; SetColor(choise == 4 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 21);	 cout << "#      #     # #    #   #                              #"; SetColor(choise == 4 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 22);	 cout << "#      #### #   #   #   ##                             #"; SetColor(choise == 4 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
        SetPos(i, j + 23);	 cout << "#                                                      #";
        SetPos(i, j + 24);   cout << "########################################################";


      }
      else {
        Sleep(1);
      }
    }
  }
  void gameover(int i, int j) {
    SetPos(i, j);
    cout << "########################################################################";
    SetPos(i, j + 1);
    cout << "#                                                                      #";
    SetPos(i, j + 2);
    cout << "#      ###### ###### #     # ######    ###### #     # ###### # ####    #";
    SetPos(i, j + 3);
    cout << "#      #    # #    # ##   ## #         #    #  #   #  #      ##    #   #";
    SetPos(i, j + 4);
    cout << "#      #      ###### # # # # ######    #    #  #   #  ###### #         #";
    SetPos(i, j + 5);
    cout << "#      #   ## #    # #  #  # #         #    #   # #   #      #         #";
    SetPos(i, j + 6);
    cout << "#      #    # #    # #     # #         #    #   # #   #      #         #";
    SetPos(i, j + 7);
    cout << "#      ###### #    # #     # ######    ######    #    ###### #         #";
    SetPos(i, j + 8);
    cout << "#                                                                      #";
    SetPos(i, j + 9);
    cout << "#                                                                      #";
    SetPos(i, j + 10);
    cout << "########################################################################";
  }
  void showStatforgame(enemy e, int x, int y) {
    for (int i = 0; i < 20; i++) {
      if (i < e.getLive()) {
        SetPos(x, y + i * 5);
        cout << " #   #";
        SetPos(x, y + i * 5 + 1);
        cout << "### ###";
        SetPos(x, y + i * 5 + 2);
        cout << " #####";
        SetPos(x, y + i * 5 + 3);
        cout << "   # ";
      }
      else {
        SetPos(x, y + i * 5);
        cout << "      ";
        SetPos(x, y + i * 5 + 1);
        cout << "       ";
        SetPos(x, y + i * 5 + 2);
        cout << "       ";
        SetPos(x, y + i * 5 + 3);
        cout << "      ";
      }
    }
  }

  void showStat_for_Reda(int i, int j, int num) {
    if (num == 1) {
      SetPos(i - 6, j);
      cout << " GG  ";
      SetPos(i - 6, j + 1);
      cout << "GGG  ";
      SetPos(i - 6, j + 2);
      cout << "  G  ";
      SetPos(i - 6, j + 3);
      cout << "  G  ";
      SetPos(i - 6, j + 4);
      cout << "GGGGG";
      if (this->posX1 != 0) {
        SetPos(i + 12, j);
        SetColor(0x0A); cout << "    #"; SetColor(0x07);
        SetPos(i + 12, j + 1);
        SetColor(0x0A); cout << "   # "; SetColor(0x07);
        SetPos(i + 12, j + 2);
        SetColor(0x0A); cout << "#  # "; SetColor(0x07);
        SetPos(i + 12, j + 3);
        SetColor(0x0A); cout << " ##  "; SetColor(0x07);
        SetPos(i + 12, j + 4);
        SetColor(0x0A); cout << "  #  "; SetColor(0x07);
      }
      else {
        SetPos(i + 12, j);
        SetColor(0x0C); cout << "#   #"; SetColor(0x07);
        SetPos(i + 12, j + 1);
        SetColor(0x0C); cout << " # # "; SetColor(0x07);
        SetPos(i + 12, j + 2);
        SetColor(0x0C); cout << "  #  "; SetColor(0x07);
        SetPos(i + 12, j + 3);
        SetColor(0x0C); cout << " # # "; SetColor(0x07);
        SetPos(i + 12, j + 4);
        SetColor(0x0C); cout << "#   #"; SetColor(0x07);
      }
    }
    else if (num == 2) {
      SetPos(i - 6, j);
      cout << " GGG ";
      SetPos(i - 6, j + 1);
      cout << "G   G";
      SetPos(i - 6, j + 2);
      cout << "   G ";
      SetPos(i - 6, j + 3);
      cout << " G   ";
      SetPos(i - 6, j + 4);
      cout << "GGGGG";
      if (this->posX2 != 0) {
        SetPos(i + 12, j);
        SetColor(0x0A); cout << "    #"; SetColor(0x07);
        SetPos(i + 12, j + 1);
        SetColor(0x0A); cout << "   # "; SetColor(0x07);
        SetPos(i + 12, j + 2);
        SetColor(0x0A); cout << "#  # "; SetColor(0x07);
        SetPos(i + 12, j + 3);
        SetColor(0x0A); cout << " ##  "; SetColor(0x07);
        SetPos(i + 12, j + 4);
        SetColor(0x0A); cout << "  #  "; SetColor(0x07);
      }
      else {
        SetPos(i + 12, j);
        SetColor(0x0C); cout << "#   #"; SetColor(0x07);
        SetPos(i + 12, j + 1);
        SetColor(0x0C); cout << " # # "; SetColor(0x07);
        SetPos(i + 12, j + 2);
        SetColor(0x0C); cout << "  #  "; SetColor(0x07);
        SetPos(i + 12, j + 3);
        SetColor(0x0C); cout << " # # "; SetColor(0x07);
        SetPos(i + 12, j + 4);
        SetColor(0x0C); cout << "#   #"; SetColor(0x07);
      }
    }
    else if (num == 3) {
      SetPos(i - 6, j);
      cout << " GGG ";
      SetPos(i - 6, j + 1);
      cout << "G   G";
      SetPos(i - 6, j + 2);
      cout << "   G ";
      SetPos(i - 6, j + 3);
      cout << "G   G";
      SetPos(i - 6, j + 4);
      cout << " GGG ";
      if (this->posX3 != 0) {
        SetPos(i + 12, j);
        SetColor(0x0A); cout << "    #"; SetColor(0x07);
        SetPos(i + 12, j + 1);
        SetColor(0x0A); cout << "   # "; SetColor(0x07);
        SetPos(i + 12, j + 2);
        SetColor(0x0A); cout << "#  # "; SetColor(0x07);
        SetPos(i + 12, j + 3);
        SetColor(0x0A); cout << " ##  "; SetColor(0x07);
        SetPos(i + 12, j + 4);
        SetColor(0x0A); cout << "  #  "; SetColor(0x07);
      }
      else {
        SetPos(i + 12, j);
        SetColor(0x0C); cout << "#   #"; SetColor(0x07);
        SetPos(i + 12, j + 1);
        SetColor(0x0C); cout << " # # "; SetColor(0x07);
        SetPos(i + 12, j + 2);
        SetColor(0x0C); cout << "  #  "; SetColor(0x07);
        SetPos(i + 12, j + 3);
        SetColor(0x0C); cout << " # # "; SetColor(0x07);
        SetPos(i + 12, j + 4);
        SetColor(0x0C); cout << "#   #"; SetColor(0x07);
      }
    }
    else if (num == 4) {
      SetPos(i - 6, j);
      cout << "G   G";
      SetPos(i - 6, j + 1);
      cout << "G   G";
      SetPos(i - 6, j + 2);
      cout << "GGGGG";
      SetPos(i - 6, j + 3);
      cout << "    G";
      SetPos(i - 6, j + 4);
      cout << "    G";
      if (this->posX4 != 0) {
        SetPos(i + 12, j);
        SetColor(0x0A); cout << "    #"; SetColor(0x07);
        SetPos(i + 12, j + 1);
        SetColor(0x0A); cout << "   # "; SetColor(0x07);
        SetPos(i + 12, j + 2);
        SetColor(0x0A); cout << "#  # "; SetColor(0x07);
        SetPos(i + 12, j + 3);
        SetColor(0x0A); cout << " ##  "; SetColor(0x07);
        SetPos(i + 12, j + 4);
        SetColor(0x0A); cout << "  #  "; SetColor(0x07);
      }
      else {
        SetPos(i + 12, j);
        SetColor(0x0C); cout << "#   #"; SetColor(0x07);
        SetPos(i + 12, j + 1);
        SetColor(0x0C); cout << " # # "; SetColor(0x07);
        SetPos(i + 12, j + 2);
        SetColor(0x0C); cout << "  #  "; SetColor(0x07);
        SetPos(i + 12, j + 3);
        SetColor(0x0C); cout << " # # "; SetColor(0x07);
        SetPos(i + 12, j + 4);
        SetColor(0x0C); cout << "#   #"; SetColor(0x07);
      }
    }
    SetPos(i, j);
    cout << "X   X";
    SetPos(i, j + 1);
    cout << " X X ";
    SetPos(i, j + 2);
    cout << "  X  ";
    SetPos(i, j + 3);
    cout << " X X ";
    SetPos(i, j + 4);
    cout << "X   X";

    SetPos(i + 6, j);
    cout << "Y   Y";
    SetPos(i + 6, j + 1);
    cout << " X X ";
    SetPos(i + 6, j + 2);
    cout << "  X  ";
    SetPos(i + 6, j + 3);
    cout << "  X  ";
    SetPos(i + 6, j + 4);
    cout << "  X  ";

  }

  void showMap() {
    for (int i = 0; i < 100; i++) {
      SetPos(0, 0 + i);
      for (int j = 0; j < 100; j++) {
        if (Color_Map[i][j] == 4) SetColor(04);
        else if (Color_Map[i][j] == 12) SetColor(0x0C);
        else if (Color_Map[i][j] == 15) SetColor(0x0F);
        else if (Color_Map[i][j] == 9) SetColor(0x09);
        else if (Color_Map[i][j] == 8) SetColor(0x08);
        else if (Color_Map[i][j] == 10) SetColor(0x0A);
        else if (Color_Map[i][j] == 7) SetColor(0x07);
        else if (Color_Map[i][j] == 0) SetColor(0x00);
        else if (Color_Map[i][j] == 13)SetColor(0x0D);
        cout << Map_main[i][j];
        SetColor(07);
      }
    }
  }
public:
  Map() {
    posX1 = 0; posY1 = 0;
    posX2 = 0; posY2 = 0;
    posX3 = 0; posY3 = 0;
    posX4 = 0; posY4 = 0;
    mode = 2;
    for (int i = 0; i < 5; i++) {
      this->year[i] = 0;
      this->month[i] = 0;
      this->day[i] = 0;
      this->second[i] = 0;
      this->minute[i] = 0;
      this->hour[i] = 0;
    }
  }
  ~Map() {
    this->save_Bin_just();
  }
  void redact_interface(int index) {
    start(1000, 1000, 5, 4);
    int key = 1;
    Blok b;
    immortol_Blok ib;
    water_Blok wb;
    PosEnemy pe;
    base ba;
    for (int i = 1; i < 5; i++) {
      this->showStat_for_Reda(140, i * 6, i);
    }
    this->showMap();
    while (1) {
      if (_kbhit()) {
        key = _getch();
        if (key != 224) {
          if (key == 72) {
            if (index == 1)	b.moveUp(Map_main);
            else if (index == 2)ib.moveUp(Map_main);
            else if (index == 3)wb.moveUp(Map_main);
            else if (index == 4)pe.moveUp(Map_main);
            else if (index == 5)ba.moveUp(Map_main);
          }
          else if (key == 80) {
            if (index == 1) b.moveDown(Map_main);
            else if (index == 2)ib.moveDown(Map_main);
            else if (index == 3)wb.moveDown(Map_main);
            else if (index == 4)pe.moveDown(Map_main);
            else if (index == 5)ba.moveDown(Map_main);
          }
          else if (key == 77) {
            if (index == 1) b.moveRight(Map_main);
            else if (index == 2)ib.moveRight(Map_main);
            else if (index == 3)wb.moveRight(Map_main);
            else if (index == 4)pe.moveRight(Map_main);
            else if (index == 5)ba.moveRight(Map_main);
          }
          else if (key == 75) {
            if (index == 1) b.moveLeft(Map_main);
            else if (index == 2)ib.moveLeft(Map_main);
            else if (index == 3)wb.moveLeft(Map_main);
            else if (index == 4)pe.moveLeft(Map_main);
            else if (index == 5)ba.moveLeft(Map_main);
          }
          else if (key == 13) {
            if (index == 1)this->rebild(b.getX(), b.getY(), index);
            else if (index == 2)this->rebild(ib.getX(), ib.getY(), index);
            else if (index == 3)this->rebild(wb.getX(), wb.getY(), index);
            else if (index == 4) {
              if (this->posX1 == 0) { this->posX1 = pe.getX(); this->posY1 = pe.getY(); }
              else if (this->posX2 == 0) { this->posX2 = pe.getX(); this->posY2 = pe.getY(); }
              else if (this->posX3 == 0) { this->posX3 = pe.getX(); this->posY3 = pe.getY(); }
              else if (this->posX4 == 0) { this->posX4 = pe.getX(); this->posY4 = pe.getY(); }
              for (int i = 1; i < 5; i++) {
                this->showStat_for_Reda(140, i * 6, i);
              }
            }
            else if (index == 5) this->rebild(ba.getX(), ba.getY(), index);
          }
          else if (key == 9) {
            this->posX1 = 0; this->posY1 = 0;
            this->posX2 = 0; this->posY2 = 0;
            this->posX3 = 0; this->posY3 = 0;
            this->posX4 = 0; this->posY4 = 0;
            for (int i = 1; i < 5; i++) {
              this->showStat_for_Reda(140, i * 6, i);
            }
          }
          else if (key == 27) { start(1000, 1000, 15, 20); break; }
          this->showMap();
          if (index == 1)b.show();
          else if (index == 2)ib.show();
          else if (index == 3)wb.show();
          else if (index == 4)pe.show();
          else if (index == 5)ba.show();
          Sleep(1);
        }
      }
    }
  }
  bool save_menu(Player_Tank &pt, enemy &e1, enemy &e2, enemy &e3, enemy &e4, int nu) {
    system("cls");
    time_t t = time(0);
    struct tm * now = localtime(&t);
    int key;
    int choise = 0;
    start(1000, 1000, 15, 20);
    for (int i = 0; i < 5; i++) {
      SetPos(5 + 15 * i, 5); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
      SetPos(5 + 15 * i, 5 + 1); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
      SetPos(5 + 15 * i, 5 + 2); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
      SetPos(5 + 15 * i, 5 + 3); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
      SetPos(5 + 15 * i, 5 + 4); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
      SetPos(5 + 15 * i, 5 + 5); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
      SetPos(5 + 15 * i, 5 + 6); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
      SetPos(5 + 15 * i, 5 + 7); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
      SetPos(5 + 15 * i, 5 + 8); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
      SetPos(5 + 15 * i, 5 + 9); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
      SetPos(5 + 15 * i, 5 + 10); SetColor(i == 0 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
      SetPos(5 + 15 * i, 5 + 11); SetColor(i == 0 ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
      SetPos(5 + 15 * i + 3, 5 + 3); cout << this->getDay(i) << "." << this->getMonth(i) << "." << this->getYear(i);
      SetPos(5 + 15 * i + 3, 5 + 5); cout << this->hour[i] << "." << this->minute[i] << "." << this->second[i];
    }
    while (1) {
      if (_kbhit()) {
        key = _getch();
        if (key == 75) {
          if (choise != 0) choise--;
          else choise = 4;
        }
        else if (key == 77) {
          if (choise != 4) choise++;
          else choise = 0;
        }
        else if (key == 13) {
          if (choise == 0 && nu == 1) {
            this->day[0] = now->tm_mday; this->month[0] = now->tm_mon + 1; this->year[0] = now->tm_year + 1900; this->second[0] = now->tm_sec; this->minute[0] = now->tm_min; this->hour[0] = now->tm_hour;
            this->saveGame("0.g.", pt, e1, e2, e3, e4);
            return 1;
          }
          else if (choise == 1 && nu == 1) {
            this->day[1] = now->tm_mday; this->month[1] = now->tm_mon + 1; this->year[1] = now->tm_year + 1900; this->second[1] = now->tm_sec; this->minute[1] = now->tm_min; this->hour[1] = now->tm_hour;
            this->saveGame("1.g.", pt, e1, e2, e3, e4);
            return 1;
          }
          else if (choise == 2 && nu == 1) {
            this->day[2] = now->tm_mday; this->month[2] = now->tm_mon + 1; this->year[2] = now->tm_year + 1900; this->second[2] = now->tm_sec; this->minute[2] = now->tm_min; this->hour[2] = now->tm_hour;
            this->saveGame("2.g.", pt, e1, e2, e3, e4);
            return 1;
          }
          else if (choise == 3 && nu == 1) {
            this->day[3] = now->tm_mday; this->month[3] = now->tm_mon + 1; this->year[3] = now->tm_year + 1900; this->second[3] = now->tm_sec; this->minute[3] = now->tm_min; this->hour[3] = now->tm_hour;
            this->saveGame("3.g.", pt, e1, e2, e3, e4);
            return 1;
          }
          else if (choise == 4 && nu == 1) {
            this->day[4] = now->tm_mday; this->month[4] = now->tm_mon + 1; this->year[4] = now->tm_year + 1900; this->second[4] = now->tm_sec; this->minute[4] = now->tm_min; this->hour[4] = now->tm_hour;
            this->saveGame("4.g.", pt, e1, e2, e3, e4);
            return 1;
          }
          if (choise == 0 && nu == 0) { this->download_game("0.g.", pt, e1, e2, e3, e4); return 1; }
          else if (choise == 1 && nu == 0) { this->download_game("1.g.", pt, e1, e2, e3, e4); return 1; }
          else if (choise == 2 && nu == 0) { this->download_game("2.g.", pt, e1, e2, e3, e4); return 1; }
          else if (choise == 3 && nu == 0) { this->download_game("3.g.", pt, e1, e2, e3, e4);	return 1; }
          else if (choise == 4 && nu == 0) { this->download_game("4.g.", pt, e1, e2, e3, e4);	return 1; }
        }
        else if (key == 27) {
          return 0;
        }
        else {
          Sleep(1);
        }
        for (int i = 0; i < 5; i++) {
          SetPos(5 + 15 * i, 5); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
          SetPos(5 + 15 * i, 5 + 1); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
          SetPos(5 + 15 * i, 5 + 2); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
          SetPos(5 + 15 * i, 5 + 3); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
          SetPos(5 + 15 * i, 5 + 4); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
          SetPos(5 + 15 * i, 5 + 5); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
          SetPos(5 + 15 * i, 5 + 6); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
          SetPos(5 + 15 * i, 5 + 7); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
          SetPos(5 + 15 * i, 5 + 8); cout << char(219) << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << " " << char(219);
          SetPos(5 + 15 * i, 5 + 9); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219);
          SetPos(5 + 15 * i, 5 + 10); SetColor(i == choise ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
          SetPos(5 + 15 * i, 5 + 11); SetColor(i == choise ? 0x0A : 0x0C); cout << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219) << char(219); SetColor(0x07);
          SetPos(5 + 15 * i + 3, 5 + 3); cout << this->getDay(i) << "." << this->getMonth(i) << "." << this->getYear(i);
          SetPos(5 + 15 * i + 3, 5 + 5); cout << this->hour[i] << "." << this->minute[i] << "." << this->second[i];
        }

      }
    }
    start(1000, 1000, 5, 4);
  }

  void rebild(int y, int x, int nu) {
    Blok b;
    immortol_Blok ib;
    water_Blok wb;
    base ba;
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        if (i == x + 4 && j == y + 4 && nu != 5) {
          for (int h = 0; h < 5; h++) {
            for (int hh = 0; hh < 5; hh++) {
              if (nu == 1) {
                Map_main[x + h][y + hh] = char(178);
                Color_Map[x + h][y + hh] = b.getColor(h, hh);
              }
              else if (nu == 2) {
                Map_main[x + h][y + hh] = char(219);
                Color_Map[x + h][y + hh] = ib.getColor(h, hh);
              }
              else if (nu == 3) {
                Map_main[x + h][y + hh] = char(176);
                Color_Map[x + h][y + hh] = wb.getColor(h, hh);
              }
            }
          }
        }
        else if (nu == 5) {
          if (this->Map_main[i][j] == char(4) && (i != x || j != y)) {
            for (int c = 0; c < 5; c++) {
              for (int cc = 0; cc < 5; cc++) {
                this->Map_main[i + c][j + cc] = ' ';
                this->Color_Map[i + c][j + cc] = 7;
              }
            }
          }
          else if (i == x + 4 && j == y + 4) {
            for (int h = 0; h < 5; h++) {
              for (int hh = 0; hh < 5; hh++) {
                Map_main[x + h][y + hh] = char(4);
                Color_Map[x + h][y + hh] = ba.getColor(h, hh);
              }
            }
          }
        }
      }
    }
  }
  bool getM(int i, int j, char pp) {
    if (this->Map_main[i][j] == pp)	return 1;
    else return 0;
  }
  void download(string name) {
    char buf[100];
    int i = 0;
    ifstream file_Map_r(name);
    while (!file_Map_r.eof()) {
      file_Map_r.getline(buf, 100);
      for (int j = 0; j < 100; j++) {
        Map_main[i][j] = buf[j];
      }
      i++;
    }
  }
  void download_Bin(string name, int bre) {
    ifstream file_Map_r(name, ios::binary);
    if (bre == 1) {
      file_Map_r.read((char*)this->second, sizeof(this->second));
      file_Map_r.read((char*)this->minute, sizeof(this->minute));
      file_Map_r.read((char*)this->hour, sizeof(this->hour));
      file_Map_r.read((char*)this->day, sizeof(this->day));
      file_Map_r.read((char*)this->month, sizeof(this->month));
      file_Map_r.read((char*)this->year, sizeof(this->year));
    }
    else if (bre == 0) {
      file_Map_r.read((char*)this->Color_Map, sizeof(this->Color_Map));
      file_Map_r.read((char*)this->Map_main, sizeof(this->Map_main));
      file_Map_r.read((char*)&this->posX1, sizeof(this->posX1));
      file_Map_r.read((char*)&this->posX2, sizeof(this->posX2));
      file_Map_r.read((char*)&this->posX3, sizeof(this->posX3));
      file_Map_r.read((char*)&this->posX4, sizeof(this->posX4));
      file_Map_r.read((char*)&this->posY1, sizeof(this->posY1));
      file_Map_r.read((char*)&this->posY2, sizeof(this->posY2));
      file_Map_r.read((char*)&this->posY3, sizeof(this->posY3));
      file_Map_r.read((char*)&this->posY4, sizeof(this->posY4));
      file_Map_r.read((char*)&this->mode, sizeof(this->mode));
    }
  }
  void save_Bin() {
    string name;
    start(1000, 1000, 15, 20);
    cout << "The name of the map" << endl;
    getline(cin, name);
    ofstream file_Map_w(name, ios::binary);
    file_Map_w.write((char*)this->Color_Map, sizeof(this->Color_Map));
    file_Map_w.write((char*)this->Map_main, sizeof(this->Map_main));
    file_Map_w.write((char*)&this->posX1, sizeof(this->posX1));
    file_Map_w.write((char*)&this->posX2, sizeof(this->posX2));
    file_Map_w.write((char*)&this->posX3, sizeof(this->posX3));
    file_Map_w.write((char*)&this->posX4, sizeof(this->posX4));
    file_Map_w.write((char*)&this->posY1, sizeof(this->posY1));
    file_Map_w.write((char*)&this->posY2, sizeof(this->posY2));
    file_Map_w.write((char*)&this->posY3, sizeof(this->posY3));
    file_Map_w.write((char*)&this->posY4, sizeof(this->posY4));
    file_Map_w.write((char*)&this->mode, sizeof(this->mode));
    system("cls");
  }
  void save_Bin_not_name(string name) {
    ofstream file_Map_w(name, ios::binary);
    file_Map_w.write((char*)this->Color_Map, sizeof(this->Color_Map));
    file_Map_w.write((char*)this->Map_main, sizeof(this->Map_main));
    file_Map_w.write((char*)&this->posX1, sizeof(this->posX1));
    file_Map_w.write((char*)&this->posX2, sizeof(this->posX2));
    file_Map_w.write((char*)&this->posX3, sizeof(this->posX3));
    file_Map_w.write((char*)&this->posX4, sizeof(this->posX4));
    file_Map_w.write((char*)&this->posY1, sizeof(this->posY1));
    file_Map_w.write((char*)&this->posY2, sizeof(this->posY2));
    file_Map_w.write((char*)&this->posY3, sizeof(this->posY3));
    file_Map_w.write((char*)&this->posY4, sizeof(this->posY4));
    file_Map_w.write((char*)&this->mode, sizeof(this->mode));
    system("cls");
  }
  void save_Bin_just() {
    ofstream file_Map_w("resume", ios::binary);
    file_Map_w.write((char*)this->second, sizeof(this->second));
    file_Map_w.write((char*)this->minute, sizeof(this->minute));
    file_Map_w.write((char*)this->hour, sizeof(this->hour));
    file_Map_w.write((char*)this->day, sizeof(this->day));
    file_Map_w.write((char*)this->month, sizeof(this->month));
    file_Map_w.write((char*)this->year, sizeof(this->year));
    system("cls");
  }
  void the_selection_interface() {
    start(1000, 1000, 15, 20);
    SetColor(0xA); cout << "brick wall\n";
    SetColor(0x7); cout << "immortal wall\n";
    SetColor(0x7); cout << "waterblock\n";
    SetColor(0x7); cout << "spawn_enemy\n";
    SetColor(0x7); cout << "Base\n";
    SetColor(0x7); cout << "save\n";
    SetColor(0x7); cout << "exit";
    int key = 0;
    int choice = 1;
    while (1) {
      if (_kbhit()) {
        key = _getch_nolock();
        if (key == 72) {
          if (choice != 1) {
            choice--;
          }
          else if (choice == 1) {
            choice = 7;
          }
        }
        else if (key == 80) {
          if (choice < 7) {
            choice++;
          }
          else if (choice == 7) {
            choice = 1;
          }
        }
        else if (key == 13) {
          if (choice == 1) {
            this->redact_interface(1);
          }
          else if (choice == 2) {
            this->redact_interface(2);
          }
          else if (choice == 3) {
            this->redact_interface(3);
          }
          else if (choice == 4) {
            this->redact_interface(4);
          }
          else if (choice == 5) {
            this->redact_interface(5);
          }
          else if (choice == 6) {
            this->save_Bin();
          }
          else if (choice == 7) {
            break;
          }
        }
        SetPos(0, 0);
        SetColor(choice == 1 ? 0xA : 0x7);
        cout << "brick wall\n";
        SetColor(choice == 2 ? 0xA : 0x7);
        cout << "immortal wall\n";
        SetColor(choice == 3 ? 0xA : 0x7);
        cout << "waterblock\n";
        SetColor(choice == 4 ? 0xA : 0x7);
        cout << "spawn_enemy\n";
        SetColor(choice == 5 ? 0xA : 0x7);
        cout << "Base\n";
        SetColor(choice == 6 ? 0xA : 0x7);
        cout << "save\n";
        SetColor(choice == 7 ? 0xA : 0x7);
        cout << "exit";
      }
      else {
        Sleep(1);
      }
    }
  }
  bool sra(Player_Tank pt, enemy e1, enemy e2, enemy e3, enemy e4, int stor) {
    if (stor == 0) {
      if (pt.getY() - 5 == e1.getY() && pt.getX() == e1.getX())return 0;
      if (pt.getY() - 5 == e2.getY() && pt.getX() == e2.getX())return 0;
      if (pt.getY() - 5 == e3.getY() && pt.getX() == e3.getX())return 0;
      if (pt.getY() - 5 == e4.getY() && pt.getX() == e4.getX())return 0;
      else return 1;
    }
    else if (stor == 1) {
      if (pt.getY() == e1.getY() && pt.getX() - 5 == e1.getX())return 0;
      if (pt.getY() == e2.getY() && pt.getX() - 5 == e2.getX())return 0;
      if (pt.getY() == e3.getY() && pt.getX() - 5 == e3.getX())return 0;
      if (pt.getY() == e4.getY() && pt.getX() - 5 == e4.getX())return 0;
      else return 1;
    }
    else if (stor == 2) {
      if (pt.getY() + 5 == e1.getY() && pt.getX() == e1.getX())return 0;
      if (pt.getY() + 5 == e2.getY() && pt.getX() == e2.getX())return 0;
      if (pt.getY() + 5 == e3.getY() && pt.getX() == e3.getX())return 0;
      if (pt.getY() + 5 == e4.getY() && pt.getX() == e4.getX())return 0;
      else return 1;
    }
    else if (stor == 3) {
      if (pt.getY() == e1.getY() && pt.getX() + 5 == e1.getX())return 0;
      if (pt.getY() == e2.getY() && pt.getX() + 5 == e2.getX())return 0;
      if (pt.getY() == e3.getY() && pt.getX() + 5 == e3.getX())return 0;
      if (pt.getY() == e4.getY() && pt.getX() + 5 == e4.getX())return 0;
      else return 1;
    }
  }
  bool sraE(Player_Tank pt, enemy e1, enemy e2, enemy e3, enemy e4, int stor) {
    if (stor == 0) {
      if (e1.getY() - 5 == pt.getY() && e1.getX() == pt.getX())return 0;
      if (e1.getY() - 5 == e2.getY() && e1.getX() == e2.getX())return 0;
      if (e1.getY() - 5 == e3.getY() && e1.getX() == e3.getX())return 0;
      if (e1.getY() - 5 == e4.getY() && e1.getX() == e4.getX())return 0;
      else return 1;
    }
    else if (stor == 1) {
      if (e1.getY() == pt.getY() && e1.getX() - 5 == pt.getX())return  0;
      if (e1.getY() == e2.getY() && e1.getX() - 5 == e2.getX())return  0;
      if (e1.getY() == e3.getY() && e1.getX() - 5 == e3.getX())return  0;
      if (e1.getY() == e4.getY() && e1.getX() - 5 == e4.getX())return  0;
      else return 1;
    }
    else if (stor == 2) {
      if (e1.getY() + 5 == pt.getY() && e1.getX() == pt.getX())return 0;
      if (e1.getY() + 5 == e2.getY() && e1.getX() == e2.getX())return 0;
      if (e1.getY() + 5 == e3.getY() && e1.getX() == e3.getX())return 0;
      if (e1.getY() + 5 == e4.getY() && e1.getX() == e4.getX())return 0;
      else return 1;
    }
    else if (stor == 3) {
      if (e1.getY() == pt.getY() && e1.getX() + 5 == pt.getX())return  0;
      if (e1.getY() == e2.getY() && e1.getX() + 5 == e2.getX())return  0;
      if (e1.getY() == e3.getY() && e1.getX() + 5 == e3.getX())return  0;
      if (e1.getY() == e4.getY() && e1.getX() + 5 == e4.getX())return  0;
      else return 1;
    }
  }
  void scan_to_memory(enemy &e1) {
    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 20; j++) {
        if (this->getM(i * 5, j * 5, ' ')) {
          e1.setRam(i, j, 1);
        }
        else if (this->getM(i * 5, j * 5, char(178))) {
          e1.setRam(i, j, 2);
        }
        else if (this->getM(i * 5, j * 5, char(176))) {
          e1.setRam(i, j, 4);
        }
      }
    }
  }
  void setMode(int m) {
    this->mode = m;
  }
  bool start_game(int rezh) {
    Player_Tank pt;
    enemy e1;
    enemy e2;
    enemy e3;
    enemy e4;
    bool annd;
    if (this->mode == 2 || this->mode == 3) {
      this->scan_to_memory(e1);
    }
    if (rezh == 2) {
      annd = this->save_menu(pt, e1, e2, e3, e4, 0);
      if (annd == 0) {
        return 0;
      }
      else  start(1000, 1000, 5, 4);
    }
    time_t NewTimeMove, OldTimeMove = 0, NewTimeRespawn, OldTimeRespawn = 0, NewTimeRespawnPT, OldTimeRespawnPT = 0;
    NewTimeMove = clock();
    bool gg = 0;
    _COORD a = { 1,1 };
    int menu;
    if (this->posX1 != 0 && rezh != 2) { e1.setPos(this->posX1, this->posY1); e1.switchExisting(); }
    if (this->posX2 != 0 && rezh != 2) { e2.setPos(this->posX2, this->posY2); e2.switchExisting(); }
    if (this->posX3 != 0 && rezh != 2) { e3.setPos(this->posX3, this->posY3); e3.switchExisting(); }
    if (this->posX4 != 0 && rezh != 2) { e4.setPos(this->posX4, this->posY4); e4.switchExisting(); }
    this->showStatforgame(e1, 140, 0);
    do {
      NewTimeRespawnPT = NewTimeRespawn = NewTimeMove = clock();
      if (kbhit()) {
        int key = getch();
        if (key == 224)key = getch();
        if (key == 72) {
          pt.setStor(0);
          if (this->getM(pt.getY() - 5, pt.getX(), ' ')) {
            if (sra(pt, e1, e2, e3, e4, 0)) {
              this->zater(pt.getY(), pt.getX(), pt, e1, e2, e3, e4, 0);
              e1.setRam(pt.getY() / 5, pt.getX() / 5, 1);
              pt.moveUp();
              e1.setRam(pt.getY() / 5, pt.getX() / 5, 6);
            }
          }
        }
        else if (key == 80) {
          pt.setStor(2);
          if (sra(pt, e1, e2, e3, e4, 2)) {
            if (this->getM(pt.getY() + 5, pt.getX(), ' ')) {
              this->zater(pt.getY(), pt.getX(), pt, e1, e2, e3, e4, 0);
              e1.setRam(pt.getY() / 5, pt.getX() / 5, 1);
              pt.moveDown();
              e1.setRam(pt.getY() / 5, pt.getX() / 5, 6);
            }
          }
        }
        else if (key == 77) {
          pt.setStor(3);
          if (sra(pt, e1, e2, e3, e4, 3)) {
            if (this->getM(pt.getY(), pt.getX() + 5, ' ')) {
              this->zater(pt.getY(), pt.getX(), pt, e1, e2, e3, e4, 0);
              e1.setRam(pt.getY() / 5, pt.getX() / 5, 1);
              pt.moveRight();
              e1.setRam(pt.getY() / 5, pt.getX() / 5, 6);
            }
          }
        }
        else if (key == 75) {
          pt.setStor(1);
          if (sra(pt, e1, e2, e3, e4, 1)) {
            if (this->getM(pt.getY(), pt.getX() - 5, ' ')) {
              this->zater(pt.getY(), pt.getX(), pt, e1, e2, e3, e4, 0);
              e1.setRam(pt.getY() / 5, pt.getX() / 5, 1);
              pt.moveLeft();
              e1.setRam(pt.getY() / 5, pt.getX() / 5, 6);
            }
          }
        }
        else if (key == 13) {
          this->ob(pt, pt.getStor(), 1);
        }
        else if (key == 27) {
          menu = menu_in_game(15, 15);
          if (menu == 2) {}
          else if (menu == 3) { save_menu(pt, e1, e2, e3, e4, 1); start(1000, 1000, 5, 4); }
          else if (menu == 4) { start(1000, 1000, 15, 20); return 1; }
        }
      }

      if (e1.getLiving() && e1.getExisting())this->ob_enemy(e1, 0);
      if (e2.getLiving() && e2.getExisting())this->ob_enemy(e2, 0);
      if (e3.getLiving() && e3.getExisting())this->ob_enemy(e3, 0);
      if (e4.getLiving() && e4.getExisting())this->ob_enemy(e4, 0);
      if (pt.getLiving())this->ob(pt, pt.getStor(), 0);
      this->showMap();
      this->zater(pt.getY(), pt.getX(), pt, e1, e2, e3, e4, 1);
      if (NewTimeMove - OldTimeMove >= 450) {
        if (this->mode == 1) {
          if (e1.getExisting())this->move_enemy(pt, e1, e2, e3, e4, OldTimeMove, 1);
          if (e2.getExisting())this->move_enemy(pt, e1, e2, e3, e4, OldTimeMove, 2);
          if (e3.getExisting())this->move_enemy(pt, e1, e2, e3, e4, OldTimeMove, 3);
          if (e4.getExisting())this->move_enemy(pt, e1, e2, e3, e4, OldTimeMove, 4);
        }
        else if (this->mode == 2) {
          if (e1.getExisting())this->move_enemy_hard(pt, e1, e2, e3, e4, OldTimeMove);
          if (e2.getExisting())this->move_enemy_hard(pt, e2, e1, e3, e4, OldTimeMove);
          if (e3.getExisting())this->move_enemy_hard(pt, e3, e2, e1, e4, OldTimeMove);
          if (e4.getExisting())this->move_enemy_hard(pt, e4, e2, e3, e1, OldTimeMove);
        }
        else if (this->mode == 3) {
          if (e1.getExisting())this->move_eneny_very_hard(pt, e1, e2, e3, e4, OldTimeMove);
          if (e2.getExisting())this->move_eneny_very_hard(pt, e2, e1, e3, e4, OldTimeMove);
          if (e3.getExisting())this->move_eneny_very_hard(pt, e3, e2, e1, e4, OldTimeMove);
          if (e4.getExisting())this->move_eneny_very_hard(pt, e4, e2, e3, e1, OldTimeMove);
        }
      }
      if (e1.getLive() > 0) {
        if (!e1.getLiving() && e1.getExisting()) {
          if (NewTimeRespawn - OldTimeRespawn >= 10000) { e1.reverdeadХ(); e1.setPos(posX1, posY1); }
        }
        else if (!e2.getLiving() && e2.getExisting()) {
          if (NewTimeRespawn - OldTimeRespawn >= 10000) { e2.reverdeadХ(); e2.setPos(posX2, posY2); }
        }
        else if (!e3.getLiving() && e3.getExisting()) {
          if (NewTimeRespawn - OldTimeRespawn >= 10000) { e3.reverdeadХ(); e3.setPos(posX3, posY3); }
        }
        else if (!e4.getLiving() && e4.getExisting()) {
          if (NewTimeRespawn - OldTimeRespawn >= 10000) { e4.reverdeadХ(); e4.setPos(posX4, posY4); }
        }
      }
      if (pt.getLive() > 0) {
        if (!pt.getLiving()) {
          if (NewTimeRespawnPT - OldTimeRespawnPT >= 5000) { pt.setLiving(true); pt.setPos(35, 90); }
        }
      }
      if (pt.getLiving())OldTimeRespawnPT = clock();
      if (e1.getLiving() && e2.getLiving() && e3.getLiving() && e4.getLiving()) OldTimeRespawn = clock();
      this->showStatforgame(e1, 140, 0);
      pt.show_hp(0, 120);
      this->serch_base(gg);
      if (!gg || pt.getLive() <= 0) { this->gameover(15, 50); }

    } while (1);
  }
private:
  void serch_base(bool &gg) {
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        if (this->Map_main[i][j] == char(4)) { gg = 1; break; }
        else { gg = 0; }
      }
      if (gg == 1) break;
    }
  }
  void move_enemy(Player_Tank &pt, enemy &e1, enemy &e2, enemy &e3, enemy &e4, time_t &t, int num) {
    int kos;
    kos = rand() % 5;
    if (kos == 0) {
      if (this->getM(e1.getY() - 5, e1.getX(), ' ') && num == 1) {
        if (sraE(pt, e1, e2, e3, e4, 0)) {
          this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
          e1.setStor(0);
          e1.moveUp();
        }
      }
      else if (this->getM(e2.getY() - 5, e2.getX(), ' ') && num == 2) {
        if (sraE(pt, e2, e1, e3, e4, 0)) {
          this->zater(e2.getY(), e2.getX(), pt, e1, e2, e3, e4, 0);
          e2.setStor(0);
          e2.moveUp();
        }
      }
      else if (this->getM(e3.getY() - 5, e3.getX(), ' ') && num == 3) {
        if (sraE(pt, e3, e2, e1, e4, 0)) {
          this->zater(e3.getY(), e3.getX(), pt, e1, e2, e3, e4, 0);
          e3.setStor(0);
          e3.moveUp();
        }
      }
      else if (this->getM(e4.getY() - 5, e4.getX(), ' ') && num == 4) {
        if (sraE(pt, e4, e2, e3, e1, 0)) {
          this->zater(e4.getY(), e4.getX(), pt, e1, e2, e3, e4, 0);
          e4.setStor(0);
          e4.moveUp();
        }
      }
    }
    else if (kos == 1) {
      if (this->getM(e1.getY(), e1.getX() - 5, ' ') && num == 1) {
        if (sraE(pt, e1, e2, e3, e4, 1)) {
          this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
          e1.setStor(1);
          e1.moveLeft();
        }
      }
      else if (this->getM(e2.getY(), e2.getX() - 5, ' ') && num == 2) {
        if (sraE(pt, e2, e1, e3, e4, 1)) {
          this->zater(e2.getY(), e2.getX(), pt, e1, e2, e3, e4, 0);
          e2.setStor(1);
          e2.moveLeft();
        }
      }
      else if (this->getM(e3.getY(), e3.getX() - 5, ' ') && num == 3) {
        if (sraE(pt, e3, e2, e1, e4, 1)) {
          this->zater(e3.getY(), e3.getX(), pt, e1, e2, e3, e4, 0);
          e3.setStor(1);
          e3.moveLeft();
        }
      }
      else if (this->getM(e4.getY(), e4.getX() - 5, ' ') && num == 4) {
        if (sraE(pt, e4, e2, e3, e1, 1)) {
          this->zater(e4.getY(), e4.getX(), pt, e1, e2, e3, e4, 0);
          e4.setStor(1);
          e4.moveLeft();
        }
      }
    }
    else if (kos == 2) {
      if (this->getM(e1.getY() + 5, e1.getX(), ' ') && num == 1) {
        if (sraE(pt, e1, e2, e3, e4, 2)) {
          this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
          e1.setStor(2);
          e1.moveDown();
        }
      }
      else if (this->getM(e2.getY() + 5, e2.getX(), ' ') && num == 2) {
        if (sraE(pt, e2, e1, e3, e4, 2)) {
          this->zater(e2.getY(), e2.getX(), pt, e1, e2, e3, e4, 0);
          e2.setStor(2);
          e2.moveDown();
        }
      }
      else if (this->getM(e3.getY() + 5, e3.getX(), ' ') && num == 3) {
        if (sraE(pt, e3, e2, e1, e4, 2)) {
          this->zater(e3.getY(), e3.getX(), pt, e1, e2, e3, e4, 0);
          e3.setStor(2);
          e3.moveDown();
        }
      }
      else if (this->getM(e4.getY() + 5, e4.getX(), ' ') && num == 4) {
        if (sraE(pt, e4, e2, e3, e1, 2)) {
          this->zater(e4.getY(), e4.getX(), pt, e1, e2, e3, e4, 0);
          e4.setStor(2);
          e4.moveDown();
        }
      }
    }
    else if (kos == 3) {
      if (this->getM(e1.getY(), e1.getX() + 5, ' ') && num == 1) {
        if (sraE(pt, e1, e2, e3, e4, 3)) {
          this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
          e1.setStor(3);
          e1.moveRight();
        }
      }
      else if (this->getM(e2.getY(), e2.getX() + 5, ' ') && num == 2) {
        if (sraE(pt, e2, e1, e3, e4, 3)) {
          this->zater(e2.getY(), e2.getX(), pt, e1, e2, e3, e4, 0);
          e2.setStor(3);
          e2.moveRight();
        }
      }
      else if (this->getM(e3.getY(), e3.getX() + 5, ' ') && num == 3) {
        if (sraE(pt, e3, e2, e1, e4, 3)) {
          this->zater(e3.getY(), e3.getX(), pt, e1, e2, e3, e4, 0);
          e3.setStor(3);
          e3.moveRight();
        }
      }
      else if (this->getM(e4.getY(), e4.getX() + 5, ' ') && num == 4) {
        if (sraE(pt, e4, e2, e3, e1, 3)) {
          this->zater(e4.getY(), e4.getX(), pt, e1, e2, e3, e4, 0);
          e4.setStor(3);
          e4.moveRight();
        }
      }
    }
    else if (kos == 4) {
      if (num == 1) this->ob_enemy(e1, 1);
      else if (num == 2)this->ob_enemy(e2, 1);
      else if (num == 3)this->ob_enemy(e3, 1);
      else if (num == 4)this->ob_enemy(e4, 1);
    }
    t = clock();
    if (!e1.getLiving() && num == 1) { this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0); e1.setPos(0, 0); }
    if (!e2.getLiving() && num == 2) { this->zater(e2.getY(), e2.getX(), pt, e1, e2, e3, e4, 0); e2.setPos(0, 0); }
    if (!e3.getLiving() && num == 3) { this->zater(e3.getY(), e3.getX(), pt, e1, e2, e3, e4, 0); e3.setPos(0, 0); }
    if (!e4.getLiving() && num == 4) { this->zater(e4.getY(), e4.getX(), pt, e1, e2, e3, e4, 0); e4.setPos(0, 0); }
  }
  int attack_enemy(enemy e1, Player_Tank pt) {
    int kos = rand() % 3;
    for (int i = 0; i < 5; i++) {
      if (e1.getY() + 5 * i == pt.getY() && e1.getX() == pt.getX() || this->Map_main[e1.getY() + 5 * i][e1.getX()] == char(4)) {
        for (; i >= 0; i--) {
          if (this->getM(e1.getY() + 5 * i, e1.getX(), char(219)))return 0;
        }
        return 3;
      }
      else if (this->Map_main[e1.getY() + 5 * i][e1.getX()] == char(178) && kos == 2) {
        for (; i >= 0; i--) {
          if (this->getM(e1.getY() + 5 * i, e1.getX(), char(219)))return 0;
        }
        return 3;
      }
      else if (e1.getX() + 5 * i == pt.getX() && e1.getY() == pt.getY() || this->Map_main[e1.getY()][e1.getX() + 5 * i] == char(4)) {
        for (; i >= 0; i--) {
          if (this->getM(e1.getY(), e1.getX() + 5 * i, char(219)))return 0;
        }
        return 4;
      }
      else if (this->Map_main[e1.getY()][e1.getX() + 5 * i] == char(178) && kos == 2) {
        for (; i >= 0; i--) {
          if (this->getM(e1.getY(), e1.getX() + 5 * i, char(219)))return 0;
        }
        return 4;
      }
      else if (e1.getY() - 5 * i == pt.getY() && e1.getX() == pt.getX() || this->Map_main[e1.getY() - 5 * i][e1.getX()] == char(4)) {
        for (; i >= 0; i--) {
          if (this->getM(e1.getY() - 5 * i, e1.getX(), char(219)))return 0;
        }
        return 1;
      }
      else if (this->Map_main[e1.getY() - 5 * i][e1.getX()] == char(178) && kos == 2) {
        for (; i >= 0; i--) {
          if (this->getM(e1.getY() - 5 * i, e1.getX(), char(219)))return 0;
        }
        return 1;
      }
      else if (e1.getX() - 5 * i == pt.getX() && e1.getY() == pt.getY() || this->Map_main[e1.getY()][e1.getX() - 5 * i] == char(4)) {
        for (; i >= 0; i--) {
          if (this->getM(e1.getY(), e1.getX() - 5 * i, char(219)))return 0;
        }
        return 2;
      }
      else if (this->Map_main[e1.getY()][e1.getX() - 5 * i] == char(178) && kos == 2) {
        for (; i >= 0; i--) {
          if (this->getM(e1.getY(), e1.getX() - 5 * i, char(219)))return 0;
        }
        return 2;
      }
    }
    return 0;
  }
  void move_eneny_very_hard(Player_Tank &pt, enemy &e1, enemy &e2, enemy &e3, enemy &e4, time_t &t) {
    e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 2);
    e1.setRam(e1.getY() / 5, e1.getX() / 5, 5);
    int h = this->attack_enemy(e1, pt);
    if (h) {
      if (h == 1) { e1.setStor(0); this->ob_enemy(e1, 1); }
      else if (h == 2) { e1.setStor(1); this->ob_enemy(e1, 1); }
      else if (h == 3) { e1.setStor(2); this->ob_enemy(e1, 1); }
      else if (h == 4) { e1.setStor(3); this->ob_enemy(e1, 1); }
    }
    else if (e1.getMemory(e1.getY() / 5 + 1, e1.getX() / 5) == 1 && e1.getY() < pt.getY()) {
      this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
      e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
      e1.setStor(2);
      e1.moveDown();
    }
    else if (e1.getMemory(e1.getY() / 5 - 1, e1.getX() / 5) == 1 && e1.getY() > pt.getY()) {
      this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
      e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
      e1.setStor(0);
      e1.moveUp();
    }
    else if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 + 1) == 1 && e1.getX() < pt.getX()) {
      this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
      e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
      e1.setStor(3);
      e1.moveRight();
    }
    else if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 - 1) == 1 && e1.getX() > pt.getX()) {
      this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
      e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
      e1.setStor(1);
      e1.moveLeft();
    }
    else {
      int ran = rand() % 4;
      if (ran == 0 && e1.getMemory(e1.getY() / 5 + 1, e1.getX() / 5) == 1) {
        this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
        e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
        e1.setStor(2);
        e1.moveDown();
      }
      else if (ran == 1 && e1.getMemory(e1.getY() / 5 - 1, e1.getX() / 5) == 1) {
        this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
        e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
        e1.setStor(0);
        e1.moveUp();
      }
      else if (ran == 2 && e1.getMemory(e1.getY() / 5, e1.getX() / 5 + 1) == 1) {
        this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
        e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
        e1.setStor(3);
        e1.moveRight();
      }
      else if (ran == 3 && e1.getMemory(e1.getY() / 5, e1.getX() / 5 - 1) == 1) {
        this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
        e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
        e1.setStor(1);
        e1.moveLeft();
      }
    }
    t = clock();
    if (!e1.getLiving()) { this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0); e1.setPos(0, 0); }
  }
  void move_enemy_hard(Player_Tank &pt, enemy &e1, enemy &e2, enemy &e3, enemy &e4, time_t &t) {
    e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 2);
    e1.setRam(e1.getY() / 5, e1.getX() / 5, 5);
    int h = this->attack_enemy(e1, pt);
    if (h) {
      if (h == 1) { e1.setStor(0); this->ob_enemy(e1, 1); }
      else if (h == 2) { e1.setStor(1); this->ob_enemy(e1, 1); }
      else if (h == 3) { e1.setStor(2); this->ob_enemy(e1, 1); }
      else if (h == 4) { e1.setStor(3); this->ob_enemy(e1, 1); }
    }
    else if (e1.getMemory(e1.getY() / 5 + 1, e1.getX() / 5) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 + 1, e1.getX() / 5) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 + 1, e1.getX() / 5) != 4) {
      if (e1.getMemory(e1.getY() / 5 - 1, e1.getX() / 5) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 - 1, e1.getX() / 5) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 - 1, e1.getX() / 5) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 + 1) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 + 1) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 + 1) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 - 1) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 - 1) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 - 1) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
      e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
      e1.setStor(2);
      e1.moveDown();
    }
    else if (e1.getMemory(e1.getY() / 5 - 1, e1.getX() / 5) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 - 1, e1.getX() / 5) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 - 1, e1.getX() / 5) != 4) {
      if (e1.getMemory(e1.getY() / 5 + 1, e1.getX() / 5) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 + 1, e1.getX() / 5) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 + 1, e1.getX() / 5) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 + 1) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 + 1) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 + 1) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 - 1) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 - 1) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 - 1) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
      e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
      e1.setStor(0);
      e1.moveUp();
    }
    else if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 + 1) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 + 1) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 + 1) != 4) {
      if (e1.getMemory(e1.getY() / 5 - 1, e1.getX() / 5) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 - 1, e1.getX() / 5) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 - 1, e1.getX() / 5) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      if (e1.getMemory(e1.getY() / 5 + 1, e1.getX() / 5) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 + 1, e1.getX() / 5) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 + 1, e1.getX() / 5) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 - 1) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 - 1) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 - 1) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5, 4);
      this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
      e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
      e1.setStor(3);
      e1.moveRight();
    }
    else if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 - 1) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 - 1) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 - 1) != 4) {
      if (e1.getMemory(e1.getY() / 5 - 1, e1.getX() / 5) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 - 1, e1.getX() / 5) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 - 1, e1.getX() / 5) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getY() / 5, 4);
      if (e1.getMemory(e1.getY() / 5, e1.getX() / 5 + 1) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 + 1) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5, e1.getX() / 5 + 1) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getY() / 5, 4);
      if (e1.getMemory(e1.getY() / 5 + 1, e1.getX() / 5) == 1 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 + 1, e1.getX() / 5) != 2 && e1.getMap_of_the_area_in_memory(e1.getY() / 5 + 1, e1.getX() / 5) != 4)e1.setmap_of_the_area_in_memory(e1.getY() / 5, e1.getY() / 5, 4);
      this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0);
      e1.setRam(e1.getY() / 5, e1.getX() / 5, 1);
      e1.setStor(1);
      e1.moveLeft();
    }
    else {
      e1.deadlock(e1.getY() / 5, e1.getX() / 5);
    }
    if (e1.getMap_of_the_area_in_memory(e1.getY(), e1.getX()) == 4) {

    }
    t = clock();
    if (!e1.getLiving()) { this->zater(e1.getY(), e1.getX(), pt, e1, e2, e3, e4, 0); e1.setPos(0, 0); }
  }

  void ob(Player_Tank pt, int stor, int ar) {
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        if (ar == 0) {
          if (i == pt.getY() + 4 && j == pt.getX() + 4) {
            for (int h = 0; h < 5; h++) {
              for (int hh = 0; hh < 5; hh++) {
                this->Map_main[pt.getY() + h][pt.getX() + hh] = pt.getP(h, hh, stor);
                this->Color_Map[pt.getY() + h][pt.getX() + hh] = pt.getColor(h, hh, stor);
              }
            }
          }
        }
        else {
          if (stor == 0 && !this->getM(pt.getY() - 2, pt.getX() + 2, char(219))) { this->Map_main[pt.getY() - 2][pt.getX() + 2] = char(223); }
          if (stor == 1 && !this->getM(pt.getY() + 2, pt.getX() - 2, char(219))) { this->Map_main[pt.getY() + 2][pt.getX() - 2] = char(221); }
          if (stor == 2 && !this->getM(pt.getY() + 6, pt.getX() + 2, char(219))) { this->Map_main[pt.getY() + 6][pt.getX() + 2] = char(220); }
          if (stor == 3 && !this->getM(pt.getY() + 2, pt.getX() + 6, char(219))) { this->Map_main[pt.getY() + 2][pt.getX() + 6] = char(222); }
        }
      }
    }
  }
  void ob_enemy(enemy e, int ar) {
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        if (ar == 0) {
          if (i == e.getY() + 4 && j == e.getX() + 4) {
            for (int h = 0; h < 5; h++) {
              for (int hh = 0; hh < 5; hh++) {
                this->Map_main[e.getY() + h][e.getX() + hh] = e.getP(h, hh);
                this->Color_Map[e.getY() + h][e.getX() + hh] = e.getColor(h, hh);
              }
            }
          }
        }
        else {
          if (e.stor() == 0 && !this->getM(e.getY() - 2, e.getX() + 2, char(219))) { this->Color_Map[e.getY() - 2][e.getX() + 2] = 15; this->Map_main[e.getY() - 2][e.getX() + 2] = char(223); break; }
          if (e.stor() == 1 && !this->getM(e.getY() + 2, e.getX() - 2, char(219))) { this->Color_Map[e.getY() + 2][e.getX() - 2] = 15; this->Map_main[e.getY() + 2][e.getX() - 2] = char(221); break; }
          if (e.stor() == 2 && !this->getM(e.getY() + 6, e.getX() + 2, char(219))) { this->Color_Map[e.getY() + 6][e.getX() + 2] = 15; this->Map_main[e.getY() + 6][e.getX() + 2] = char(220); break; }
          if (e.stor() == 3 && !this->getM(e.getY() + 2, e.getX() + 6, char(219))) { this->Color_Map[e.getY() + 2][e.getX() + 6] = 15; this->Map_main[e.getY() + 2][e.getX() + 6] = char(222); break; }
        }
      }
    }
  }
  void zater(int x, int y, Player_Tank &pt, enemy &e, enemy &e2, enemy &e3, enemy &e4, int bre) {
    int bufI = 0;
    int bufJ = 0;
    for (int i = 0; i < 100; i++) {
      for (int j = 0; j < 100; j++) {
        if (i == x + 4 && j == y + 4) {
          for (int h = 0; h < 5; h++) {
            for (int hh = 0; hh < 5; hh++) {
              this->Map_main[x + h][y + hh] = ' ';
            }
          }
        }
        if (bre == 1) {
          if (this->Map_main[i][j] == char(223)) {//char(223)	
            if ((this->getM(i - 5, j, char(176)) || this->getM(i - 5, j, ' ')) && !this->getM(i - 1, j, char(178)) && !(pt.getX() == j - 2 && pt.getY() == i - 8)) {
              this->Map_main[i - 5][j] = char(223); this->Color_Map[i - 5][j] = this->Color_Map[i][j];
            }
            else if (this->getM(i - 1, j, char(178))) {
              if (this->Color_Map[i - 3][j - 1] == 12) {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 3][j + bb - 2] = 4;
                  }
                }
              }
              else {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 3][j + bb - 2] = 7;
                    this->Map_main[i + b - 3][j + bb - 2] = ' ';
                  }
                }
              }
            }
            else if (this->getM(i - 5, j, char(4))) {
              for (int b = 0; b < 5; b++) {
                for (int bb = 0; bb < 5; bb++) {
                  this->Color_Map[i + b - 8][j + bb - 2] = 7;
                  this->Map_main[i + b - 8][j + bb - 2] = ' ';
                }
              }
            }
            else if (pt.getX() == j - 2 && pt.getY() == i - 8) {
              pt.setLiving(false);
              --pt; pt.setPos(0, 0);
            }

            else if (e.getX() == j - 2 && e.getY() == i - 8 && this->Color_Map[i][j] != 15) {
              e.deadХ();
              --e;
              e.delete_map_of_the_area_in_memory();
            }

            else if (e2.getX() == j - 2 && e2.getY() == i - 8 && this->Color_Map[i][j] != 15) {
              e2.deadХ();
              --e2;
              e2.delete_map_of_the_area_in_memory();
            }

            else if (e3.getX() == j - 2 && e3.getY() == i - 8 && this->Color_Map[i][j] != 15) {
              e3.deadХ();
              --e3;
              e3.delete_map_of_the_area_in_memory();
            }

            else if (e4.getX() == j - 2 && e4.getY() == i - 8 && this->Color_Map[i][j] != 15) {
              e4.deadХ();
              --e4;
              e4.delete_map_of_the_area_in_memory();
            }

            else if (this->getM(i - 5, j, char(178))) {
              if (this->Color_Map[i - 8][j - 1] == 12) {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 8][j + bb - 2] = 4;
                  }
                }
              }
              else {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 8][j + bb - 2] = 7;
                    this->Map_main[i + b - 8][j + bb - 2] = ' ';
                  }
                }
              }
            }
            this->Map_main[i][j] = this->Map_main[i][j + 1];
            this->Color_Map[i][j] = this->Color_Map[i][j + 1];
          }//char(223)
          if (this->Map_main[i][j] == char(221)) {//char(221)	
            if ((this->getM(i, j - 5, char(176)) || this->getM(i, j - 5, ' ')) && !this->getM(i, j - 1, char(178))) {
              this->Map_main[i][j - 5] = char(221); this->Color_Map[i][j - 5] = this->Color_Map[i][j];
            }
            else if (this->getM(i, j - 1, char(178))) {
              if (this->Color_Map[i - 2][j - 2] == 12) {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 2][j + bb - 3] = 4;
                  }
                }
              }
              else {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 2][j + bb - 3] = 7;
                    this->Map_main[i + b - 2][j + bb - 3] = ' ';
                  }
                }
              }
            }
            else if (this->getM(i, j - 5, char(4))) {
              for (int b = 0; b < 5; b++) {
                for (int bb = 0; bb < 5; bb++) {
                  this->Color_Map[i + b - 2][j + bb - 8] = 7;
                  this->Map_main[i + b - 2][j + bb - 8] = ' ';
                }
              }
            }
            else if (pt.getX() == j - 8 && pt.getY() == i - 2) {
              pt.setLiving(false);
              --pt; pt.setPos(0, 0);
            }

            else if (e.getX() == j - 8 && e.getY() == i - 2 && this->Color_Map[i][j] != 15) {
              e.deadХ();
              --e;
              e.delete_map_of_the_area_in_memory();
            }

            else if (e2.getX() == j - 8 && e2.getY() == i - 2 && this->Color_Map[i][j] != 15) {
              e2.deadХ();
              --e2;
              e2.delete_map_of_the_area_in_memory();
            }

            else if (e3.getX() == j - 8 && e3.getY() == i - 2 && this->Color_Map[i][j] != 15) {
              e3.deadХ();
              --e3;
              e3.delete_map_of_the_area_in_memory();
            }

            else if (e4.getX() == j - 8 && e4.getY() == i - 2 && this->Color_Map[i][j] != 15) {
              e4.deadХ();
              --e4;
              e4.delete_map_of_the_area_in_memory();
            }

            else if (this->getM(i, j - 5, char(178))) {
              if (this->Color_Map[i - 2][j - 7] == 12) {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 2][j + bb - 8] = 4;
                  }
                }
              }
              else {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 2][j + bb - 8] = 7;
                    this->Map_main[i + b - 2][j + bb - 8] = ' ';
                  }
                }
              }
            }
            this->Map_main[i][j] = this->Map_main[i][j + 1];
            this->Color_Map[i][j] = this->Color_Map[i][j + 1];
          }//char(221)					
          if (this->Map_main[i][j] == char(220) && i != bufI) {//char(220)	
            if ((this->getM(i + 5, j, char(176)) || this->getM(i + 5, j, ' ')) && !this->getM(i + 1, j, char(178)) && !(pt.getX() == j - 2 && pt.getY() == i + 4)) { this->Color_Map[i + 5][j] = this->Color_Map[i][j]; this->Map_main[i + 5][j] = char(220); bufI = i + 5; }

            else if (this->getM(i + 1, j, char(178))) {
              if (this->Color_Map[i - 1][j - 1] == 12) {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 1][j + bb - 2] = 4;
                  }
                }
              }
              else {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 1][j + bb - 2] = 7;
                    this->Map_main[i + b - 1][j + bb - 2] = ' ';
                  }
                }
              }
            }
            else if (this->getM(i + 5, j, char(4))) {
              for (int b = 0; b < 5; b++) {
                for (int bb = 0; bb < 5; bb++) {
                  this->Color_Map[i + b + 4][j + bb - 2] = 7;
                  this->Map_main[i + b + 4][j + bb - 2] = ' ';
                }
              }
            }
            else if (pt.getX() == j - 2 && pt.getY() == i + 4) {
              pt.setLiving(false);
              --pt;
              pt.setPos(0, 0);
            }
            else if (e.getX() == j - 2 && e.getY() == i + 4 && this->Color_Map[i][j] != 15) {
              e.deadХ();
              --e;
              e.delete_map_of_the_area_in_memory();
            }
            else if (e2.getX() == j - 2 && e2.getY() == i + 4 && this->Color_Map[i][j] != 15) {
              e2.deadХ();
              --e2;
              e2.delete_map_of_the_area_in_memory();
            }
            else if (e3.getX() == j - 2 && e3.getY() == i + 4 && this->Color_Map[i][j] != 15) {
              e3.deadХ();
              --e3;
              e3.delete_map_of_the_area_in_memory();
            }
            else if (e4.getX() == j - 2 && e4.getY() == i + 4 && this->Color_Map[i][j] != 15) {
              e4.deadХ();
              --e4;
              e4.delete_map_of_the_area_in_memory();
            }
            else if (this->getM(i + 5, j, char(178))) {
              if (this->Color_Map[i + 7][j] == 12) {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b + 4][j + bb - 2] = 4;
                  }
                }
              }
              else {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b + 4][j + bb - 2] = 7;
                    this->Map_main[i + b + 4][j + bb - 2] = ' ';
                  }
                }
              }
            }
            this->Map_main[i][j] = this->Map_main[i][j + 1];
            this->Color_Map[i][j] = this->Color_Map[i][j + 1];
          }//char(220)
          if (this->Map_main[i][j] == char(222) && j != bufJ) {//char(222)	
            if ((this->getM(i, j + 5, char(176)) || this->getM(i, j + 5, ' ')) && !this->getM(i, j + 1, char(178)) && !(pt.getX() == j + 8 && pt.getY() == i - 2)) { this->Color_Map[i][j + 5] = this->Color_Map[i][j]; this->Map_main[i][j + 5] = char(222); bufJ = j + 5; }

            else if (this->getM(i, j + 1, char(178))) {
              if (this->Color_Map[i - 2][j] == 12) {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 2][j + bb - 1] = 4;
                  }
                }
              }
              else {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 2][j + bb - 1] = 7;
                    this->Map_main[i + b - 2][j + bb - 1] = ' ';
                  }
                }
              }
            }
            else if (this->getM(i, j + 5, char(4))) {
              for (int b = 0; b < 5; b++) {
                for (int bb = 0; bb < 5; bb++) {
                  this->Color_Map[i + b - 2][j + bb + 4] = 7;
                  this->Map_main[i + b - 2][j + bb + 4] = ' ';
                }
              }
            }
            else if (pt.getX() == j + 4 && pt.getY() == i - 2) {
              pt.setLiving(false);
              --pt; pt.setPos(0, 0);
            }
            else if (e.getX() == j + 4 && e.getY() == i - 2 && this->Color_Map[i][j] != 15) {
              e.deadХ();
              --e;
              e.delete_map_of_the_area_in_memory();
            }
            else if (e2.getX() == j + 4 && e2.getY() == i - 2 && this->Color_Map[i][j] != 15) {
              e2.deadХ();
              --e2;
              e2.delete_map_of_the_area_in_memory();
            }
            else if (e3.getX() == j + 4 && e3.getY() == i - 2 && this->Color_Map[i][j] != 15) {
              e3.deadХ();
              --e3;
              e3.delete_map_of_the_area_in_memory();
            }
            else if (e4.getX() == j + 4 && e4.getY() == i - 2 && this->Color_Map[i][j] != 15) {
              e4.deadХ();
              --e4;
              e4.delete_map_of_the_area_in_memory();
            }
            else if (this->getM(i, j + 5, char(178))) {
              if (this->Color_Map[i][j + 5] == 12) {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 2][j + bb + 4] = 4;
                  }
                }
              }
              else {
                for (int b = 0; b < 5; b++) {
                  for (int bb = 0; bb < 5; bb++) {
                    this->Color_Map[i + b - 2][j + bb + 4] = 7;
                    this->Map_main[i + b - 2][j + bb + 4] = ' ';
                  }
                }
              }
            }
            this->Map_main[i][j] = this->Map_main[i][j + 1];
            this->Color_Map[i][j] = this->Color_Map[i][j + 1];
          }//char(222)		
        }
      }

    }
  };

};
