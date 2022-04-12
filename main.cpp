#include <iostream>
#include <vector>

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

} // вывод карты

bool checkOneShip (bool a[][10], int y, int x) {
    if (a[y][x]) {
        return false;
    }
    return true;
} // проверяем корабль с одним блоком
bool checkElseShip (bool a[][10], int y1, int x1, int y2, int x2 ) {
    if (y1 != y2 && x1 != x2) {
        return false;
    }

    int equal;
    int start;
    int theEnd;

    if (y1 == y2) {
        equal = y1;
        start = x1 < x2 ? x1 : x2;
        theEnd = x1 > x2 ? x1 : x2;
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
        for (int i = start; i <= theEnd; i++) {
            if (a[i][equal]) {
                return false;
            }
        }
    }

    return true;
} // проверяет координаты любой длинны

void oneShipMark (bool a[][10], int s[][2], int count, int y, int x) {

    a[y][x] = true;

    s[count][0] = y;
    s[count][1] = x;

} // помещаем координаты в одноблочного и отмечаем его на карте
void twoShipMark (bool a[][10], int s[][2][2], int count, int y1, int x1, int y2, int x2 ) {
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

    for (int i = 0; i < 1; i++) {
        for (int j = 0; j < 2;) {
            s[count][i][j] = y1;
            s[count][i][j + 1] = x1;
            j=+2;
        }
    }
    for (int i = 1; i < 2; i++) {
        for (int j = 0; j < 2;) {
            s[count][i][j] = y2;
            s[count][i][j + 1] = x2;
            j=+2;
        }
    }

} // помещаем координаты в двухблочного и отмечаем его на карте
void threeShipMark (bool a[][10], int s[][3][2], int count, int y1, int x1, int y2, int x2 ) {
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
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2;) {
                s[count][i][j] = equal;
                s[count][i][j + 1] = start;
                start++;
                j=+2;
            }
        }
    }
    else if (x1 == x2) {
        equal = x1;
        start = y1 < y2 ? y1 : y2;
        theEnd = y1 > y2 ? y1 : y2;
        for (int i = start; i <= theEnd; i++ ) {
            a[i][equal] = true;
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 2;) {
                s[count][i][j] = start;
                s[count][i][j + 1] = equal;
                start++;
                j=+2;
            }

        }
    }
} // помещаем координаты в трехблочного и отмечаем его на карте
void fourShipMark (bool a[][10], int s[][2], int y1, int x1, int y2, int x2 ) {
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
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2;) {
                s[i][j] = equal;
                s[i][j + 1] = start;
                start++;
                j=+2;
            }
        }
    }
    else if (x1 == x2) {
        equal = x1;
        start = y1 < y2 ? y1 : y2;
        theEnd = y1 > y2 ? y1 : y2;
        for (int i = start; i <= theEnd; i++ ) {
            a[i][equal] = true;
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2;) {
                s[i][j] = start;
                s[i][j + 1] = equal;
                start++;
                j=+2;
            }

        }
    }
} // помещаем координаты в четырехблочного и отмечаем его на карте

int main() {
    bool fMap1[10][10];
    bool fMap2[10][10];

    int y1, x1;
    int y2, x2;

    int oneShip1[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    int oneShip2[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

    int twoShip1[3][2][2] = {{{0, 0},{0, 0}},
                            {{0, 0},{0, 0}},
                            {{0, 0},{0, 0}}};
    int twoShip2[3][2][2] = {{{0, 0},{0, 0}},
                            {{0, 0},{0, 0}},
                            {{0, 0},{0, 0}}};

    int threeShip1[2][3][2] = {{{0, 0},{0, 0},{0, 0}},
                              {{0, 0},{0, 0},{0, 0}}};
    int threeShip2[2][3][2] = {{{0, 0},{0, 0},{0, 0}},
                              {{0, 0},{0, 0},{0, 0}}};

    int fourShip1[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    int fourShip2[4][2] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};

    beginFill(fMap1, fMap2);
    printMap(fMap1);

    std::cout << std::endl;
    std::cout << "Player 1.";
    std::cout << std::endl;

    int count = 0;
    while (count < 4) {
        std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
        std::cout << "Y X" << std::endl;
        std::cin >> y1 >> x1;
        if (!checkOneShip(fMap1, y1, x1)) {
            std::cout << "Incorrect coordinates!" << std::endl;
            printMap(fMap1);
        } else {
            oneShipMark (fMap1, oneShip1, count, y1, x1);
            count++;
            printMap(fMap1);
        }
    } // отмечаем на карте одноблочные корабли
    count = 0;
    while (count < 3) {
        std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
        std::cout << "Beginning" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y1 >> x1;
        std::cout << "  End" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y2 >> x2;
        if (!checkElseShip (fMap1, y1, x1, y2, x2 )) {
            std::cout << "Incorrect coordinates!" << std::endl;
            printMap(fMap1);
        } else {
            twoShipMark (fMap1, twoShip1, count, y1, x1, y2, x2);
            count++;
            printMap(fMap1);
        }
    } // отмечаем на карте двухблочные корабли
    count = 0;
    while (count < 2) {
        std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
        std::cout << "Beginning" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y1 >> x1;
        std::cout << "  End" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y2 >> x2;
        if (!checkElseShip (fMap1, y1, x1, y2, x2 )) {
            std::cout << "Incorrect coordinates!" << std::endl;
            printMap(fMap1);
        } else {
            threeShipMark (fMap1, threeShip1, count, y1, x1, y2, x2);
            count++;
            printMap(fMap1);
        }
    } // отмечаем на карте трехблочные корабли
    count = 0;
    while (count < 1) {
        std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
        std::cout << "Beginning" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y1 >> x1;
        std::cout << "  End" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y2 >> x2;
        if (!checkElseShip (fMap1, y1, x1, y2, x2 )) {
            std::cout << "Incorrect coordinates!" << std::endl;
            printMap(fMap1);
        } else {
            fourShipMark (fMap1, fourShip1, y1, x1, y2, x2);
            count++;
            printMap(fMap1);
        }
    } // отмечаем на карте четырехблочный корабли

    std::cout << std::endl;
    std::cout << "Player 2.";
    std::cout << std::endl;

    count = 0;
    while (count < 4) {
        std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
        std::cout << "Y X" << std::endl;
        std::cin >> y1 >> x1;
        if (!checkOneShip(fMap2, y1, x1)) {
            std::cout << "Incorrect coordinates!" << std::endl;
            printMap(fMap2);
        } else {
            oneShipMark (fMap2, oneShip2, count, y1, x1);
            count++;
            printMap(fMap2);
        }
    } // отмечаем на карте одноблочные корабли
    count = 0;
    while (count < 3) {
        std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
        std::cout << "Beginning" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y1 >> x1;
        std::cout << "  End" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y2 >> x2;
        if (!checkElseShip (fMap2, y1, x1, y2, x2 )) {
            std::cout << "Incorrect coordinates!" << std::endl;
            printMap(fMap2);
        } else {
            twoShipMark (fMap2, twoShip2, count, y1, x1, y2, x2);
            count++;
            printMap(fMap2);
        }
    } // отмечаем на карте двухблочные корабли
    count = 0;
    while (count < 2) {
        std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
        std::cout << "Beginning" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y1 >> x1;
        std::cout << "  End" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y2 >> x2;
        if (!checkElseShip (fMap2, y1, x1, y2, x2 )) {
            std::cout << "Incorrect coordinates!" << std::endl;
            printMap(fMap2);
        } else {
            threeShipMark (fMap2, threeShip2, count, y1, x1, y2, x2);
            count++;
            printMap(fMap2);
        }
    } // отмечаем на карте трехблочные корабли
    count = 0;
    while (count < 1) {
        std::cout << "Input the coordinates for " << count + 1 << " ship" << std::endl;
        std::cout << "Beginning" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y1 >> x1;
        std::cout << "  End" << std::endl;
        std::cout << "  Y X" << std::endl;
        std::cin >> y2 >> x2;
        if (!checkElseShip (fMap2, y1, x1, y2, x2 )) {
            std::cout << "Incorrect coordinates!" << std::endl;
            printMap(fMap2);
        } else {
            fourShipMark (fMap2, fourShip2, y1, x1, y2, x2);
            count++;
            printMap(fMap2);
        }
    } // отмечаем на карте четырехблочный корабли

}
