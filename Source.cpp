
#include "player.cpp"
#include <iostream>
void TestPrintProgressBar() {
    // Тест 1: Прогресс 50%
    std::cout << "Тест 1:" << std::endl;
    PrintProgressBar(0.5f);
    std::cout << std::endl;

    // Тест 2: Прогресс 100%
    std::cout << "Тест 2:" << std::endl;
    PrintProgressBar(1.0f);
    std::cout << std::endl;

    // Тест 3: Прогресс 0%
    std::cout << "Тест 3:" << std::endl;
    PrintProgressBar(0.0f);
    std::cout << std::endl;

    // Тест 4: Прогресс 75%
    std::cout << "Тест 4:" << std::endl;
    PrintProgressBar(0.75f);
    std::cout << std::endl;

    // Тест 5: Прогресс 25%
    std::cout << "Тест 5:" << std::endl;
    PrintProgressBar(0.25f);
    std::cout << std::endl;
}
void TestFuncs()
{
    speedsound(1.5);  // Ожидаемый результат: Установленная скорость: 1.5
    speedsound(3.0);  // Ожидаемый результат: ВВЕДЕНО ЗНАЧЕНИЕ БОЛЬШЕ МАКСИМАЛЬНО ДОПУСТИМОГО. СКОРОСТЬ ПРОИГРЫВА
}