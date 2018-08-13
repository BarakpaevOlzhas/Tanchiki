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


int main() {	
	HideCursor();
	start(1000, 1000, 5, 4);		
	Map m;	
	int key;	
	m.download_Bin("resume");	
	m.start_game(1);	
}
