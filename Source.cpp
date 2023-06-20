
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
void TestFuncs()
{
    speedsound(1.5);  // ��������� ���������: ������������� ��������: 1.5
    speedsound(3.0);  // ��������� ���������: ������� �������� ������ ����������� �����������. �������� ���������
}