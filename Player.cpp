#include <iostream> //нужен для вывода строк "cout<<"
#include "conio.h" //нужен намеренно для "getche()" , а не "cin>>"
#include "windows.h" //библиотека audiere её требует
#include "audiere.h" //сама библиотека
#include <thread>// потоков
#include <chrono>
#include <atomic>
#include <string>

//определяем пространства имён для более короткой записи кода
using namespace std;
using namespace audiere; 
using namespace chrono;

//объявлем глобальные переменные
const int kProgressBarWidth = 50;
string answer;
float speed;
float volume;
atomic<bool> isPlaying(true);
atomic<bool> isPaused(false);
AudioDevicePtr device = OpenDevice();
OutputStreamPtr sound = OpenSound(device, "song.mp3", false);

int audiolength()
// функия получает длину аудио файла методом из библиотеки audiere
{
    int lengthInSeconds = sound->getLength() / 50000;

    return lengthInSeconds;
}

int devicecheck()
//Функия обработки ошибок 
{
    if (!device) 
    {
        cout << "Ошибка открытия AudioDevice. Нажмите любую клавишу для выхода..";
        _getche();

        return 0;
    }
}
int soundcheck()
//Функия обработки ошибок 
{
    if (!sound) 
    {
        cout << "Ошибка открытия файла! Для выхода нажмите любую клавишу..";
        _getche();

        return 0;
    }
}
void speedsound(float speed)
//функия установки скорости воспроизведения с возможностью избежания неккоректного значения переменной
{
    if (speed > 2.0) 
    {
        cout << "ВВЕДЕНО ЗНАЧЕНИЕ БОЛЬШЕ МАКСИМАЛЬНО ДОПУСТИМОГО. СКОРОСТЬ ПРОИГРЫВАНИЯ БУДЕТ В ДВА РАЗА БЫСТРЕЕ" << endl;
        float speed = 2.0;
    }
    if (speed < 0.5)
    {
        cout << "ВВЕДЕНО ЗНАЧЕНИЕ МЕНЬШЕ МИНИМАЛЬНО ДОПУСТИМОГО. СКОРОСТЬ ПРОИГРЫВАНИЯ БУДЕТ В ДВА РАЗА МЕДЛЕНЕЕ" << endl;
        float speed = 0.5;
    }
    sound->setPitchShift(speed);
}
void volumesound(float volume)
//функия установки громкости воспроизведения с возможностью избежания неккоректного значения переменной
{
    if (volume > 1.0) 
    {
        cout << "ВВЕДЕНО ЗНАЧЕНИЕ БОЛЬШЕ МАКСИМАЛЬНО ДОПУСТИМОГО. ФАЙЛ БУДЕТ ПРОИГРВАТЬСЯ С МАСКИМАЛЬНОЙ ГРОМКОСТЬЮ" << endl;
        float volume = 1.0;
    }
    if (volume < 0)
    {
        cout << "ВВЕДЕНО ЗНАЧЕНИЕ МЕНЬШЕ МИНИМАЛЬНО ДОПУСТИМОГО. ФАЙЛ БУДЕТ ПРОИГРВАТЬСЯ С МАСКИМАЛЬНОЙ ГРОМКОСТЬЮ" << endl;
        float volume = 0;
    }

    sound->setVolume(volume);
}



void PrintProgressBar(float progress) 
// функция отображения шкалы проигрывания, выводит ее в консоль. Шкала заполняется по мере проигрывания трека 
{
    int filledWidth = static_cast<int>(progress * kProgressBarWidth);
    int emptyWidth = kProgressBarWidth - filledWidth;

    cout << "[";
    for (int i = 0; i < filledWidth; ++i) 
    {
        cout << "#";
    }
    for (int i = 0; i < emptyWidth; ++i) 
    {
        cout << " ";
    }
    cout << "] " << static_cast<int>(progress * 100) << "%" << endl;
}

void UpdateProgressBar(OutputStreamPtr sound)
//функция обновляет переменную прогресса проигрывания пока оно идет. Функция работает когда значение булевой переменной равно false, иначе функция не берет значения прогресса
{
    while (isPlaying) 
    {
        if (!isPaused) 
        {
            float progress = sound->getPosition() / static_cast<float>(sound->getLength());
            PrintProgressBar(progress);
        }
          
        this_thread::sleep_for(milliseconds(100));
    }
}

void PlaySound(AudioDevicePtr device, OutputStreamPtr sound)
//функция проигрывания трека. Играет пока с клавиатуры не будет введен символ "p". Идет отдельным потоком
{
    isPaused = false;
    sound->play();

    //создвем отдельный поток чтобы можно было остановить во время проигрывания
    thread progressBarThread(UpdateProgressBar, sound);

    cout << "Нажмите 'p' для приостановки воспроизведения" << std::endl;
    cout << "Воспроизведение звука" << std::endl;

    while (true) 
    {
        if (cin.get() == 'p') 
        {
            isPaused = !isPaused;
            if (isPaused) 
            {
                sound->stop();
            }
            else 
            {
                sound->play();
            }
        }
    }

    // Прекращаем считавать прогресс после окончания проигрывания трека. Закрываем поток
    isPlaying = false;
    progressBarThread.join();
}

int main() 
{
    string output;
    //Обрабатываем возможные ошибки
    soundcheck();
    devicecheck();

    // Устанавливаем русскую локаль
    setlocale(0, "Russian"); 
    
    cout << "Хотели бы вы изменить настройки проигрывания?(y/n): ";
    cin >> answer;

    if (answer == "y")
    {
        //Запрашиваем у пользователя скоростью с которой он хочет проиграть трек(ускорение/замедление)
        cout << "Введите скорость воспроизведения: ";
        cin >> speed;

        //назначаем скороть исходя из полученного значения
        speedsound(speed);

        //Запрашиваем у пользователя громкостью с которой он хочет проиграть трек
        cout << "Введите громкость воспроизведения: ";
        cin >> volume;

        //назначаем громкость исходя из полученного значения
        volumesound(volume);
    }
    else if (answer == "n")
    {
        string output = "Трек будет проигрываться со стандартными настройками";
        cout << output << endl;
    }
    // Выводим название трека
    cout << "song.mp3" << endl;
    
    //Выводим длину аудиофайла при помощи функции audiolength()
    cout << "Длительность аудиофайла: " << audiolength() << " секунд" << endl;
    
    //Проигрываем наш звук
    PlaySound(device, sound);

    return 0;
}