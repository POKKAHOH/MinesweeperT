#ifndef FIELD_H
# define FIELD_H

class Cell;

// игровое поле
class Field {
public:
  Field();
  ~Field();
  void Play();
protected:
// константы, определяющие игру
  const static int m_n = 8;        // размер поля
  const static int m_mineNumber = 10; // количество мин на поле
  const static int m_free = m_n * m_n - m_mineNumber; // число клеток без мин
// переменные
  int m_opened = 0;                // число открытых клеток (проще проверять выигрыш)

  void openAll();                  // открывает всё поле
  bool isValidCoord(int i, int j); // i,j в поле?
  void openCell(int i, int j);     // открывает клетку
  bool isWin();                    // проверяет выигрыш
  void setFlags();                  // ставим флаги победителю

  Cell* m_field[m_n][m_n];         // игровое поле
  bool m_isGameActive;             // состояние игрового поля

};

#endif // FIELD_H
