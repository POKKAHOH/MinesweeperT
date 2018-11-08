#ifndef CELL_H
# define CELL_H

//! одна клетка поля
class Cell {

public:
  Cell (int i, int j);
  int i();          //индекс строки
  int j();          //индекс столбца
  bool isMine();    //мина
  void setMine();   //init мина
  void incValue();  //set счетчик мин
  int value();      //возвращает счетчик мин
  void setOpen();   //открывает ячейку
  bool isOpen();    //ячейка открыта?
  bool isFlag();    //ячейка отмечена?
  void swapFlag();  //сапёр ошибается один раз, а сомневаться может долго;)

// define brushes ;)
  const char* delim_l=" ";
  const char* delim_r=" ";
  const char* mine_c="*";
  const char* empty_c=".";
  const char* closed_c="#";
  const char* flag_c=">";

protected:
  void paint();
  int m_i, m_j;     //координаты
  int m_value;      //что в ячейке?
  bool m_isMine;    //мина?
  bool m_isOpen;    //ячейка открыта?
  bool m_isFlag;    //Осторожно мины!

};

#endif // DOT_H
