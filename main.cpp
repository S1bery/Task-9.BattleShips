#include <iostream>
#include <limits>

void beginFill(bool a[][10], bool b[][10]) {

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            a[i][j] = false;
            b[i][j] = false;
        }
    }
} // первичное заполнение
void printMap(bool a[][10]) {

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == 0) {
                std::cout << i << " ";
            } else if (i == 0) {
                std::cout << j << " ";
            } else if (j != 0 && i != 0 && !a[i][j]) {
                std::cout << "0"
                          << " ";
            } else {
                std::cout << "H"
                          << " ";
            }
        }
        std::cout << std::endl;
    }

} // вывод карты для расстановки кораблей
void printMapBattle(bool a[][10],bool b[][10], int y, int x) {
  if (a[y][x] == true) {
      b[y][x] = true;
    }
  
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (j == 0) {
        std::cout << i << " ";
      } else if (i == 0) {
        std::cout << j << " ";
      } else if (j != 0 && i != 0 && !b[i][j]) {
        std::cout << "0"
                  << " ";
      } else {
        std::cout << "X"
                  << " ";
      }
    }
    std::cout << std::endl;
  }
} // вывод карты для битвы

bool checkOneShip (bool a[][10], int y, int x) {
    if (y < 1 || x < 1 || y > 9 || x > 9) return false;
    if (a[y][x]) return false;
  
    return true;
} // проверяем корабль с одним блоком
bool checkElseShip (bool a[][10],int lenght, int y1, int x1, int y2, int x2 ) {
  
    if (y1 < 1 || x1 < 1 || y1 > 9 || x1 > 9) return false;
    if (y2 < 1 || x2 < 1 || y2 > 9 || x2 > 9) return false;
    if (y1 != y2 && x1 != x2) return false;
    
    int equal;
    int start;
    int theEnd;
    

    if (y1 == y2) {
        equal = y1;
        start = x1 < x2 ? x1 : x2;
        theEnd = x1 > x2 ? x1 : x2;
      int totalLenght = theEnd - start + 1;
      if (totalLenght != lenght) {
        return false;
      }
        for (int i = start; i <= theEnd; i++) {
            if (a[equal][i]) {
                return false;
            }
        }
    }
    if (x1 == x2) {
        equal = x1;
        start = y1 < y2 ? y1 : y2;
        theEnd = y1 > y2 ? y1 : y2;
        int totalLenght = theEnd - start + 1;
        if (totalLenght != lenght) {
          return false;
        }
        for (int i = start; i <= theEnd; i++) {
            if (a[i][equal]) {
                return false;
            }
        }
    }

    return true;
} // проверяет координаты любой длинны

void oneShipMark (bool a[][10], int count, int y, int x) {

    a[y][x] = true;

} // отмечает на карте одноблочный корабль
void elseShipMark (bool a[][10], int y1, int x1, int y2, int x2 ) {
    int equal;
    int start;
    int theEnd;

    if (y1 == y2) {
        equal = y1;
        start = x1 < x2 ? x1 : x2;
        theEnd = x1 > x2 ? x1 : x2;
        for (int i = start; i <= theEnd; i++ ) {
            a[equal][i] = true;
        }
    }
    else if (x1 == x2) {
        equal = x1;
        start = y1 < y2 ? y1 : y2;
        theEnd = y1 > y2 ? y1 : y2;
        for (int i = start; i <= theEnd; i++ ) {
            a[i][equal] = true;
        }
    }
} // отмечает на карте  корабль любой остальных длинн

void ignoreLine () {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
} // чистит буфер cin

int main() {
  bool fMap1[10][10];
  bool fMap2[10][10];

  int y1, x1;
  int y2, x2;

  beginFill(fMap1, fMap2); // заполняем карты
  printMap(fMap1);

  std::cout << std::endl;
  std::cout << "Player 1.";
  std::cout << std::endl;

  int count = 0;
  while (count < 4) {
    int lenght = 1;
    std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y1 >> x1;
    if (std::cin.fail() || !checkOneShip(fMap1, y1, x1)) {
        std::cin.clear();
        ignoreLine();
        std::cout << "Incorrect coordinates!" << std::endl;
        printMap(fMap1);
    } else {
        oneShipMark (fMap1, count, y1, x1);
        count++;
        printMap(fMap1);
    }
  } // отмечаем на карте одноблочные корабли
  count = 0;
  while (count < 3) {
    int lenght = 2;
    std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
    std::cout << "Beginning" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y1 >> x1;
    std::cout << "End" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y2 >> x2;
    if (std::cin.fail() ||!checkElseShip (fMap1, lenght, y1, x1, y2, x2 )) {
        std::cin.clear();
        ignoreLine();
        std::cout << "Incorrect coordinates!" << std::endl;
        printMap(fMap1);
    } else {
        elseShipMark (fMap1, y1, x1, y2, x2);
        count++;
        printMap(fMap1);
    }
  } // отмечаем на карте двухблочные корабли
  count = 0;
  while (count < 2) {
    int lenght = 3;
    std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
    std::cout << "Beginning" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y1 >> x1;
    std::cout << "End" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y2 >> x2;
    if (std::cin.fail() ||!checkElseShip (fMap1, lenght, y1, x1, y2, x2 )) {
        std::cin.clear();
        ignoreLine();
        std::cout << "Incorrect coordinates!" << std::endl;
        printMap(fMap1);
    } else {
        elseShipMark (fMap1, y1, x1, y2, x2);
        count++;
        printMap(fMap1);
    }
  } // отмечаем на карте трехблочные корабли
  count = 0;
  while (count < 1) {
    int lenght = 4;
    std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
    std::cout << "Beginning" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y1 >> x1;
    std::cout << "End" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y2 >> x2;
    if (std::cin.fail() ||!checkElseShip (fMap1, lenght, y1, x1, y2, x2 )) {
        std::cin.clear();
        ignoreLine();
        std::cout << "Incorrect coordinates!" << std::endl;
        printMap(fMap1);
    } else {
        elseShipMark (fMap1, y1, x1, y2, x2);
        count++;
        printMap(fMap1);
    }
  } // отмечаем на карте четырехблочный корабли

  std::cout << std::endl;
  std::cout << "Player 2.";
  std::cout << std::endl;

  count = 0;
  while (count < 4) {
    int lenght = 1;
    std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y1 >> x1;
    if (std::cin.fail() || !checkOneShip(fMap2, y1, x1)) {
        std::cin.clear();
        ignoreLine();
        std::cout << "Incorrect coordinates!" << std::endl;
        printMap(fMap2);
    } else {
        oneShipMark (fMap2, count, y1, x1);
        count++;
        printMap(fMap2);
    }
  } // отмечаем на карте одноблочные корабли
  count = 0;
  while (count < 3) {
    int lenght = 2;
    std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
    std::cout << "Beginning" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y1 >> x1;
    std::cout << "End" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y2 >> x2;
    if (std::cin.fail() || !checkElseShip (fMap2, lenght, y1, x1, y2, x2 )) {
        std::cin.clear();
        ignoreLine();
        std::cout << "Incorrect coordinates!" << std::endl;
        printMap(fMap2);
    } else {
        elseShipMark (fMap2, y1, x1, y2, x2);
        count++;
        printMap(fMap2);
    }
  } // отмечаем на карте двухблочные корабли
  count = 0;
  while (count < 2) {
    int lenght = 3;
    std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
    std::cout << "Beginning" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y1 >> x1;
    std::cout << "End" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y2 >> x2;
    if (std::cin.fail() || !checkElseShip (fMap2, lenght, y1, x1, y2, x2 )) {
        std::cin.clear();
        ignoreLine();
        std::cout << "Incorrect coordinates!" << std::endl;
        printMap(fMap2);
    } else {
        elseShipMark (fMap2, y1, x1, y2, x2);
        count++;
        printMap(fMap2);
    }
  } // отмечаем на карте трехблочные корабли
  count = 0;
  while (count < 1) {
    int lenght = 4;
    std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
    std::cout << "Beginning" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y1 >> x1;
    std::cout << "End" << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y2 >> x2;
    if (std::cin.fail() || !checkElseShip (fMap2, lenght, y1, x1, y2, x2 )) {
        std::cin.clear();
        ignoreLine();
        std::cout << "Incorrect coordinates!" << std::endl;
        printMap(fMap2);
    } else {
        elseShipMark (fMap2, y1, x1, y2, x2);
        count++;
        printMap(fMap2);
    }
  } // отмечаем на карте четырехблочный корабли

  std::cout << std::endl;
  std::cout << "--------------"; // начало активной фазы игры
  std::cout << std::endl;

  int healthPl1 = 20; 
  int healthPl2 = 20; // "жизни игроков" (максимальное количество возможных попаданий до проигрыша)
  int x, y;
  bool sMap1[10][10];
  bool sMap2[10][10];
  beginFill(sMap1, sMap2);
  
  while (healthPl1 != 0 || healthPl2 != 0) {
    std::cout << "Player One turn: " << std::endl;
    std::cout << "Enter the coordinates: " << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y >> x;
    while (std::cin.fail()) {
      std::cin.clear();
      ignoreLine();
      std::cout << "Incorrect coordinates!" << std::endl;
      std::cout << "Y X" << std::endl;
      std::cin >> y >> x;  
    }
    if (fMap2[y][x]) {
      std::cout << "Got!" << std::endl;
      printMapBattle(fMap2, sMap2, y, x);
      healthPl2--;
    } 
    else {
      std::cout << "Miss!" << std::endl;
      printMapBattle(fMap2,sMap2, y, x);
    }

    if (healthPl2 == 0) {
      break;
    } // доп. проверка на победу первого игрока
    std::cout << "---------------" << std::endl;
    std::cout << "---------------" << std::endl;
    
    std::cout << "Player Two turn: " << std::endl;
    std::cout << "Enter the coordinates: " << std::endl;
    std::cout << "Y X" << std::endl;
    std::cin >> y >> x;
    while (std::cin.fail()) {
      std::cin.clear();
      ignoreLine();
      std::cout << "Incorrect coordinates!" << std::endl;
      std::cout << "Y X" << std::endl;
      std::cin >> y >> x;  
    }
    if (fMap1[y][x]) {
      std::cout << "Got!" << std::endl;
      printMapBattle(fMap1, sMap1, y, x);
      healthPl1--;
    } else {
      std::cout << "Miss!" << std::endl;
      printMapBattle(fMap1, sMap1, y, x);
    }
    std::cout << "---------------" << std::endl;
    std::cout << "---------------" << std::endl;
  } // поочередная перестрелка

  if (healthPl1 == 0) {
    std::cout << "Player Two Wins!" << std::endl;
  } else {
    std::cout << "Player One Wins!" << std::endl;
  }
  
  return 0; 
}
