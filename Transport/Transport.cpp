#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <Windows.h>

using namespace std;
// ����� �����
class Wagon {
protected:
    int passengers;
    int baggage;
public:
    Wagon(int passengers, int baggage) : passengers(passengers), baggage(baggage) {} // ����������� ������

    virtual string printInfo() = 0; // ����������� �������

    int getPassengers() const { // �������� ���������� ����������
        return passengers;
    }

    int getBaggage() const { // �������� ���������� ������
        return baggage;
    }
};

class SittingWagon : public Wagon { // ����� ������� ����� ����������� �� ������ �����
public:
    SittingWagon(int passengers, int baggage) // ����������� ������
        : Wagon(passengers, baggage) {}

    string printInfo() override { // ����� ���������� � ������
        return "���: ������� ����� ����������: " + to_string(passengers) + " ������(��): " + to_string(baggage);
    }
};

class CompartmentWagon : public Wagon {// ����� ������������ ����� ����� ����������� �� ������ �����
public:
    CompartmentWagon(int passengers, int baggage)
        : Wagon(passengers, baggage) {}

    string printInfo()  override { // ����� ���������� � ������
        return "���: ����������� ����� ����������: " + to_string(passengers) + " ������(��): " + to_string(baggage);
    }
};

class CoupeWagon : public Wagon { // ����� �������� ����� ����������� �� ������ �����
public:
    CoupeWagon(int passengers, int baggage) // ����������� ������
        : Wagon(passengers, baggage) {}

    string printInfo() override { // ����� ���������� � ������
        return "���: �������� ����� ����������: " + to_string(passengers) + " ������(��): " + to_string(baggage);
    }
};

class Train { // ����� �����
private:
    vector<Wagon*> wagons; // ������ �������

public:
    ~Train() { // ���������� ������
        for (Wagon* wagon : wagons) {
            delete wagon;
        }
    }

    void addWagon(Wagon* wagon) { // �������� �����
        wagons.push_back(wagon);
    }

    void removeWagon(int index) { // ������� �����

        if (index >= 0 && index < wagons.size()) {
            delete wagons[index];
            wagons.erase(wagons.begin() + index);
        }
    }

    int getTotalPassengers() const { // �������� ����� ���������� ����������
        int total = 0;
        for (const Wagon* wagon : wagons) {
            total += wagon->getPassengers();
        }
        return total;
    }

    int getTotalBaggage() const { // �������� ����� ���������� ������
        int total = 0;
        for (const Wagon* wagon : wagons) {
            total += wagon->getBaggage();
        }
        return total;
    }

    void sortByPassengers() { // ������������� ������ �� ���������� ����������
        std::sort(wagons.begin(), wagons.end(), [](const Wagon* firstWagon, const Wagon* secondWagon) {
            return firstWagon->getPassengers() < secondWagon->getPassengers();
            });
    }

    vector<Wagon*> findWagonsByPassengersRange(int minPassengers, int maxPassengers) const { // ����� ������ �� ��������� ��������� ����������
        vector<Wagon*> foundWagons;
        for (const auto& wagon : wagons) {
            if (wagon->getPassengers() >= minPassengers && wagon->getPassengers() <= maxPassengers) {
                foundWagons.push_back(wagon);
            }
        }
        return foundWagons;
    }

    string printWagons() const { // �������� ������ �������
        string output;
        int i = 1;
        std::cout << "������ �������:" << std::endl;
        for (const auto wagon : wagons) {
            output += i + "." + wagon->printInfo() + "\n";
            ++i;
        }
        return output;
    }
};

void displayMenu() // ����� ����
{
    cout << "����:" << endl;
    cout << "1. ����������� ������ �������." << endl;
    cout << "2. �������� ����� �����." << endl;
    cout << "3. ������� �����." << endl;
    cout << "4. ��������� ����� ����������� ����������." << endl;
    cout << "5. ��������� ����� ����������� ������." << endl;
    cout << "6. ������������� ������ �� ���������� ����������." << endl;
    cout << "7. ����� ������ �� ��������� ��������� ���������� ����������." << endl;
    cout << "8. ����� �� ���������." << endl;
    cout << "�������� ��������: ";
}

int main() {

    SetConsoleCP(1251); // ��������� ��������� � �������
    SetConsoleOutputCP(1251);

    Train train; // �������� ������� ������

    // ���������� ���������
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
                cout << "�������� ��� ������ (1 - �������, 2 - �����������, 3 - ��������): ";
                cin >> wagonTypeCheck;
                if (regex_match(wagonTypeCheck, indexRegex)) // �������� �� ���� ������
                {
                    wagonType = stoi(wagonTypeCheck);

                    if (wagonType == 1 || wagonType == 2 || wagonType == 3)
                    {
                        break;
                    }
                    else
                    {
                        cout << "������ ������������ ��� ������!" << endl;
                    }
                }
                else
                {
                    cout << "������ ������������ ��� ������!" << endl;
                }


            }

            while (true)
            {
                cout << "������� ���������� ����������: ";
                cin >> passengersCheck;
                cout << "������� ���������� ������: ";
                cin >> baggageCheck;

                if (regex_match(passengersCheck, countRegex) && regex_match(baggageCheck, countRegex)) // �������� �� ���� ������
                {
                    passengers = stoi(passengersCheck);
                    baggage = stoi(baggageCheck);
                }
                else
                {
                    cout << "������� �������� ������!" << endl;
                    continue;
                }

                // �������� ������� ������� ������� � ��������� ��� � ������ ���� �������
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
            cout << "������� ������ ������ ��� ��������: ";
            cin >> indexCheck;

            while (true)
            {
                if (regex_match(indexCheck, indexRegex)) // �������� �� ���� ������
                {
                    index = stoi(indexCheck);
                    break;
                }
                else
                {
                    cout << "������������ ����!" << endl;
                }
            }
            train.removeWagon(index);

            cout << "����� �����!";
            break;
        }
        case 4: {
            int totalPassengers = train.getTotalPassengers(); // �������� ����� ���������� ����������
            cout << "����� ����������� ����������: " << totalPassengers << endl;
            break;
        }
        case 5: {
            int totalBaggage = train.getTotalBaggage(); // �������� ����� ���������� ������
            cout << "����� ����������� ������: " << totalBaggage << " ��" << endl;
            break;
        }
        case 6: {
            train.sortByPassengers(); // ������������� ������ ������� �� ����������
            cout << "������ ������������� �� ���������� ����������." << endl;
            break;
        }
        case 7: {
            string minPassengersCheck, maxPassengersCheck;
            int minPassengers, maxPassengers;

            while (true)
            {
                cout << "������� ����������� ���������� ����������: ";
                cin >> minPassengersCheck;
                cout << "������� ������������ ���������� ����������: ";
                cin >> maxPassengersCheck;

                if (regex_match(minPassengersCheck, countRegex) && regex_match(maxPassengersCheck, countRegex)) // �������� �� ���� ������
                {
                    minPassengers = stoi(minPassengersCheck);
                    maxPassengers = stoi(maxPassengersCheck);
                    break;
                }
                else
                {
                    cout << "������� �������� ������!" << endl;
                }
            }


            vector<Wagon*> foundWagons = train.findWagonsByPassengersRange(minPassengers, maxPassengers); // �������� ������ �������� �������
            cout << "��������� ������:" << endl;
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
            cout << "������������ �����." << endl;
            break;
        }
        }

        cout << endl;
    }
}
