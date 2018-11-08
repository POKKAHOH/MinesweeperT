#define DEBUG

#include <iostream>
#include "field.h"
#include "cell.h"

using namespace std;

Field::Field(){
  m_isGameActive = true;
// clear screen, hide cursor
  cout << "\e[2J\e[?25l\e[1;1H";
// show header
  cout <<"  ";
  for (int i=0;i<m_n;i++){
    cout << "  "<<char(i+65);
  }
  cout <<endl<<"  ";
  for (int i=0;i<m_n;i++){
    cout << "  V";
  }
  cout <<endl;
// show field
  for (int i = 0; i < m_n; ++i) {
    cout<<(i+1)<<" >";
    for (int j = 0; j < m_n; ++j) {
      m_field[i][j] = new Cell (i, j);
      cout<<m_field[i][j]->delim_l<<m_field[i][j]->closed_c<<m_field[i][j]->delim_r;
   }
    cout<<endl;
  }
#ifndef DEBUG
  srand (time(NULL));
#endif
  for (int i = 0; i < m_mineNumber;) {
    Cell* p = m_field[rand() % m_n][rand() % m_n];
    if (p->isMine())
      continue;
    else {
      p->setMine();
      ++i;
    }
  }
  for(int i=0;i<m_n;i++){
  for(int j=0;j<m_n;j++){
    if(m_field[i][j]->isMine()){
      for (int dx=-1;dx<=1;dx++){
      for (int dy=-1;dy<=1;dy++){
        if ((!((dx==0)&&(dy==0)))&&(isValidCoord(i+dx,j+dy)))
          m_field[i+dx][j+dy]->incValue();
      }
      }
    }
  }
  }
}

Field::~Field(){
//destroy m_field
  for (int i = 0; i < m_n; ++i) {
    for (int j = 0; j < m_n; ++j) {
      delete m_field[i][j];
   }
  }
//go down & show cursor
  cout << "\e["<<m_n+7<<";1H\e[?25h";
}

bool Field::isValidCoord(int i, int j) {
  return i >= 0 && j >= 0 && i < m_n && j < m_n;
}

bool Field::isWin() {
  return 0 == (m_free - m_opened);
}

void Field::openCell(int i, int j) {
  if (m_field[i][j]->isOpen())
    return;
  if (m_field[i][j]->value())
    return;
  if (m_field[i][j]->isMine())
    return;
  m_field[i][j]->setOpen();
  m_opened++;
  for (int dx=-1;dx<=1;dx++){
  for (int dy=-1;dy<=1;dy++){
    if ((!((dx==0)&&(dy==0)))&&(isValidCoord(i+dx,j+dy)))
      openCell(i+dx,j+dy);
  }
  }
}

void Field::openAll() {
  for (int i = 0; i < m_n; ++i)
    for (int j = 0; j < m_n; ++j)
      m_field[i][j]->setOpen();
}

void Field::Play(){
  int xCoord,yCoord;
  char s[4];
  while(m_isGameActive){
    cout << "\e["<<m_n+3<<";0H"
         << "Введите координаты клетки (А1 - открыть; А1* - отметить флажком): "
         << endl<<endl<<endl<< "\e["<<(m_n+4)<<";0H";
    cin>>s;

#ifdef DEBUG
m_isGameActive=false;
openAll();
#endif
    // переводим координаты в цифровой вид
    if ((s[0]>=65)&&(s[0]<=90)) 
      xCoord=(int) s[0]-65;        // большая буква
    else 
      if((s[0]>=97)&&(s[0]<=122))   
        xCoord=(int) s[0]-97;  // малая буква
      else continue;
    if((s[1]>=49)&&(s[1]<=57)) // координаты с единицы 
      yCoord=s[1]-49;
    else continue;
    if (s[2]==42){
      if (m_field[xCoord][yCoord]->isOpen())
        continue;
      m_field[xCoord][yCoord]->swapFlag();
      continue;
    }
    if (m_field[xCoord][yCoord]->isMine()) {
      m_isGameActive = false;
      openAll();
    }
    if (isValidCoord(xCoord,yCoord)) 
      openCell(xCoord,yCoord);
    if (isWin()) 
      m_isGameActive = false;
  }
  if (isWin()) 
    cout << "\e["<<m_n+6<<";0H"
         << "Вы победили! Поздравляю!!!";
  else 
    cout << "\e["<<m_n+6<<";0H"
         << "Не огорчайтесь! Попробуйте ещё раз!!!";
  
}
