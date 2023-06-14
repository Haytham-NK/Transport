#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <Windows.h>

using namespace std;
// Класс Вагон
class Wagon {
protected:
    int passengers;
    int baggage;
public:
    Wagon(int passengers, int baggage) : passengers(passengers), baggage(baggage) {} // конструктор класса

    virtual string printInfo() = 0; // виртуальная функция

    int getPassengers() const { // получить количество пассажиров
        return passengers;
    }

    int getBaggage() const { // получить количество багажа
        return baggage;
    }
};

class SittingWagon : public Wagon { // класс сидячий вагон наследуется от класса Вагон
public:
    SittingWagon(int passengers, int baggage) // конструктор класса
        : Wagon(passengers, baggage) {}

    string printInfo() override { // вывод информации о вагоне
        return "Тип: Сидячий вагон Пассажиров: " + to_string(passengers) + " Багажа(кг): " + to_string(baggage);
    }
};

class CompartmentWagon : public Wagon {// класс платцкартный вагон вагон наследуется от класса Вагон
public:
    CompartmentWagon(int passengers, int baggage)
        : Wagon(passengers, baggage) {}

    string printInfo()  override { // вывод информации о вагоне
        return "Тип: Плацкартный вагон Пассажиров: " + to_string(passengers) + " Багажа(кг): " + to_string(baggage);
    }
};

class CoupeWagon : public Wagon { // класс купейный вагон наследуется от класса Вагон
public:
    CoupeWagon(int passengers, int baggage) // конструктор класса
        : Wagon(passengers, baggage) {}

    string printInfo() override { // вывод информации о вагоне
        return "Тип: Купейный вагон Пассажиров: " + to_string(passengers) + " Багажа(кг): " + to_string(baggage);
    }
};

class Train { // класс поезд
private:
    vector<Wagon*> wagons; // список вагонов

public:
    ~Train() { // деструктор класса
        for (Wagon* wagon : wagons) {
            delete wagon;
        }
    }

    void addWagon(Wagon* wagon) { // добавить вагон
        wagons.push_back(wagon);
    }

    void removeWagon(int index) { // удалить вагон

        if (index >= 0 && index < wagons.size()) {
            delete wagons[index];
            wagons.erase(wagons.begin() + index);
        }
    }

    int getTotalPassengers() const { // получить общее количество пассажиров
        int total = 0;
        for (const Wagon* wagon : wagons) {
            total += wagon->getPassengers();
        }
        return total;
    }

    int getTotalBaggage() const { // получить общее количество багажа
        int total = 0;
        for (const Wagon* wagon : wagons) {
            total += wagon->getBaggage();
        }
        return total;
    }

    void sortByPassengers() { // отсортировать вагоны по количеству пассажиров
        std::sort(wagons.begin(), wagons.end(), [](const Wagon* firstWagon, const Wagon* secondWagon) {
            return firstWagon->getPassengers() < secondWagon->getPassengers();
            });
    }

    vector<Wagon*> findWagonsByPassengersRange(int minPassengers, int maxPassengers) const { // найти вагоны по выбраному диапазону пассажиров
        vector<Wagon*> foundWagons;
        for (const auto& wagon : wagons) {
            if (wagon->getPassengers() >= minPassengers && wagon->getPassengers() <= maxPassengers) {
                foundWagons.push_back(wagon);
            }
        }
        return foundWagons;
    }

    string printWagons() const { // Получить список вагонов
        string output;
        int i = 1;
        std::cout << "Список вагонов:" << std::endl;
        for (const auto wagon : wagons) {
            output += i + "." + wagon->printInfo() + "\n";
            ++i;
        }
        return output;
    }
};

void displayMenu() // вывод меню
{
    cout << "Меню:" << endl;
    cout << "1. Просмотреть список вагонов." << endl;
    cout << "2. Добавить новый вагон." << endl;
    cout << "3. Удалить вагон." << endl;
    cout << "4. Посчитать общую численность пассажиров." << endl;
    cout << "5. Посчитать общую численность багажа." << endl;
    cout << "6. Отсортировать вагоны по количеству пассажиров." << endl;
    cout << "7. Найти вагоны по заданному диапазону количества пассажиров." << endl;
    cout << "8. Выход из программы." << endl;
    cout << "Выберите действие: ";
}

int main() {

    SetConsoleCP(1251); // установка кодировки в консоли
    SetConsoleOutputCP(1251);

    Train train; // создание объекта поезда

    // регулярные выражения
    regex indexRegex("[0-9]{1,5}$");
    regex choiceRegex("^(?:[1-9]|10)$");
    regex countRegex("^(100000|[0-9]{1,5})$");

    while (true) {

        displayMenu();

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            cout << train.printWagons();
            break;
        }
        case 2: {
            string wagonTypeCheck, passengersCheck, baggageCheck;
            int wagonType, passengers, baggage;

            while (true)
            {
                cout << "Выберите тип вагона (1 - Сидячий, 2 - Плацкартный, 3 - Купейный): ";
                cin >> wagonTypeCheck;
                if (regex_match(wagonTypeCheck, indexRegex)) // проверка на ввод данных
                {
                    wagonType = stoi(wagonTypeCheck);

                    if (wagonType == 1 || wagonType == 2 || wagonType == 3)
                    {
                        break;
                    }
                    else
                    {
                        cout << "Выбран некорректный тип вагона!" << endl;
                    }
                }
                else
                {
                    cout << "Выбран некорректный тип вагона!" << endl;
                }


            }

            while (true)
            {
                cout << "Введите количество пассажиров: ";
                cin >> passengersCheck;
                cout << "Введите количество багажа: ";
                cin >> baggageCheck;

                if (regex_match(passengersCheck, countRegex) && regex_match(baggageCheck, countRegex)) // проверка на ввод данных
                {
                    passengers = stoi(passengersCheck);
                    baggage = stoi(baggageCheck);
                }
                else
                {
                    cout << "Введены неверные данные!" << endl;
                    continue;
                }

                // создание объекта классов вагонов и занесение его в список всех вагонов
                if (wagonType == 1) {

                    train.addWagon(new SittingWagon(passengers, baggage));
                }
                else if (wagonType == 2) {
                    train.addWagon(new CompartmentWagon(passengers, baggage));
                }
                else if (wagonType == 3) {
                    train.addWagon(new CoupeWagon(passengers, baggage));
                }
                break;
            }
            break;
        }
        case 3: {
            string indexCheck;
            int index;
            cout << "Введите индекс вагона для удаления: ";
            cin >> indexCheck;

            while (true)
            {
                if (regex_match(indexCheck, indexRegex)) // проверка на ввод данных
                {
                    index = stoi(indexCheck);
                    break;
                }
                else
                {
                    cout << "Некорректный ввод!" << endl;
                }
            }
            train.removeWagon(index);

            cout << "Вагон удалён!";
            break;
        }
        case 4: {
            int totalPassengers = train.getTotalPassengers(); // получить общее количество пассажиров
            cout << "Общая численность пассажиров: " << totalPassengers << endl;
            break;
        }
        case 5: {
            int totalBaggage = train.getTotalBaggage(); // получить общее количество багажа
            cout << "Общая численность багажа: " << totalBaggage << " кг" << endl;
            break;
        }
        case 6: {
            train.sortByPassengers(); // отсортировать список вагонов по пассажирам
            cout << "Вагоны отсортированы по количеству пассажиров." << endl;
            break;
        }
        case 7: {
            string minPassengersCheck, maxPassengersCheck;
            int minPassengers, maxPassengers;

            while (true)
            {
                cout << "Введите минимальное количество пассажиров: ";
                cin >> minPassengersCheck;
                cout << "Введите максимальное количество пассажиров: ";
                cin >> maxPassengersCheck;

                if (regex_match(minPassengersCheck, countRegex) && regex_match(maxPassengersCheck, countRegex)) // проверка на ввод данных
                {
                    minPassengers = stoi(minPassengersCheck);
                    maxPassengers = stoi(maxPassengersCheck);
                    break;
                }
                else
                {
                    cout << "Введены неверные данные!" << endl;
                }
            }


            vector<Wagon*> foundWagons = train.findWagonsByPassengersRange(minPassengers, maxPassengers); // создание списка найденых вагонов
            cout << "Найденные вагоны:" << endl;
            for (const auto& wagon : foundWagons) {
                wagon->printInfo();
                cout << endl;
            }
            break;
        }
        case 8: {
            return 0;
        }
        default: {
            cout << "Некорректный выбор." << endl;
            break;
        }
        }

        cout << endl;
    }
}
