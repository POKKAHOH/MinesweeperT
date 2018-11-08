#include <iostream>
#include "cell.h"

using namespace std;

Cell::Cell(int i, int j) :
   m_i(i), m_j(j), m_value(0), m_isMine(false),
   m_isOpen(false), m_isFlag(false) {}

int Cell::i() { return m_i; }
int Cell::j() { return m_j; }

int Cell::value() { return m_value; }
void Cell::incValue() { ++m_value; }

bool Cell::isMine() { return m_isMine; }
void Cell::setMine() { m_isMine = true; }

bool Cell::isOpen() { return m_isOpen; }
void Cell::setOpen() { m_isOpen = true; paint(); }

bool Cell::isFlag() { return m_isFlag; }
void Cell::swapFlag() { m_isFlag = !m_isFlag; paint(); }

void Cell::paint() {
//some black magic...
  int X,Y;
  X=3+m_j;   //3 line from top to field
  Y=3*m_i+5; //5 char from left side to field, 3 char to cell
//walk to ligth side...
  cout<<"\e["<<X<<";"<<(Y-1)<<"H"<<delim_l;
  if (m_isOpen) /*open field*/
    if (m_isMine) /*write red star*/
      if (m_isFlag) /*marked mine*/
        cout<<"\e[34m\e["<<X<<";"<<Y<<"H"<<flag_c<<"\e[0m";         
      else   /*non marked...*/
        cout<<"\e[31m\e["<<X<<";"<<Y<<"H"<<mine_c<<"\e[0m";
    else /*opening field*/
      if (m_value) /*near mine*/
        if (m_isFlag) /*wrong flag*/         
          cout<<"\e[44m\e[380m"<<flag_c<<"\e[0m";
        else /*no flag*/
          cout<<"\e[3"<<value()<<"m\e["<<X<<";"<<Y<<"H"<<value()<<"\e[0m";
      else /*empty field*/
        if (m_isFlag) /*wrong flag*/         
          cout<<"\e[44m\e[380m"<<flag_c<<"\e[0m";
        else /*no flag*/
          cout<<"\e["<<X<<";"<<Y<<"H"<<empty_c;
  else /*switch flag*/
    if (m_isFlag) /*write blue >*/
      cout<<"\e[34m\e["<<X<<";"<<Y<<"H"<<flag_c<<"\e[0m";
    else  /*write close field*/
    cout<<"\e["<<X<<";"<<Y<<"H"<<closed_c;

  cout<<"\e["<<X<<";"<<(Y+1)<<"H"<<delim_r;
  return;
}
