#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <sstream>
#include "player.cpp"
#include <iostream>
void TestPrintProgressBar() {
    // ���� 1: �������� 50%
    std::cout << "���� 1:" << std::endl;
    PrintProgressBar(0.5f);
    std::cout << std::endl;

    // ���� 2: �������� 100%
    std::cout << "���� 2:" << std::endl;
    PrintProgressBar(1.0f);
    std::cout << std::endl;

    // ���� 3: �������� 0%
    std::cout << "���� 3:" << std::endl;
    PrintProgressBar(0.0f);
    std::cout << std::endl;

    // ���� 4: �������� 75%
    std::cout << "���� 4:" << std::endl;
    PrintProgressBar(0.75f);
    std::cout << std::endl;

    // ���� 5: �������� 25%
    std::cout << "���� 5:" << std::endl;
    PrintProgressBar(0.25f);
    std::cout << std::endl;
}


void PrintProgressBar(float progress) {
    // ���������� ������� PrintProgressBar
    // ...

    // ������ ���������� ��� �����:
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

    // �������������� ����� � output
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
    speedsound(1.5);  // ��������� ���������: ������������� ��������: 1.5
    speedsound(3.0);  // ��������� ���������: ������� �������� ������ ����������� �����������. �������� ���������
}