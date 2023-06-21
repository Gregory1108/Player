#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <sstream>
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


void PrintProgressBar(float progress) {
    // Реализация функции PrintProgressBar
    // ...

    // Пример реализации для теста:
    int filledWidth = static_cast<int>(progress * 10);
    int emptyWidth = 10 - filledWidth;

    std::stringstream ss;
    ss << "[";
    for (int i = 0; i < filledWidth; ++i) {
        ss << "#";
    }
    for (int i = 0; i < emptyWidth; ++i) {
        ss << " ";
    }
    ss << "] " << static_cast<int>(progress * 100) << "%";

    std::cout << ss.str() << std::endl;
}

TEST_CASE("PrintProgressBar Test") {
    std::stringstream output;

    // Перенаправляем вывод в output
    doctest::Context().setStream(&output);

    SUBCASE("Progress 0.5") {
        PrintProgressBar(0.5f);
        CHECK_EQ(output.str(), "[#####     ] 50%\n");
    }

    SUBCASE("Progress 1.0") {
        PrintProgressBar(1.0f);
        CHECK_EQ(output.str(), "[##########] 100%\n");
    }

    SUBCASE("Progress 0.0") {
        PrintProgressBar(0.0f);
        CHECK_EQ(output.str(), "[          ] 0%\n");
    }
}

void TestFuncs()
{
    speedsound(1.5);  // Ожидаемый результат: Установленная скорость: 1.5
    speedsound(3.0);  // Ожидаемый результат: ВВЕДЕНО ЗНАЧЕНИЕ БОЛЬШЕ МАКСИМАЛЬНО ДОПУСТИМОГО. СКОРОСТЬ ПРОИГРЫВА
}