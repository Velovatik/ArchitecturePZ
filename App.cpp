// App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

enum RobotState {
    OFF,
    WAITING,
    DETECTING,
    MOVING,
    CLEANING
};

class Engine {
public:
    void on() {
        cout << "Engine is on" << endl;
    }
    void off() {
        cout << "Engine is turning off" << endl;
    }
};

class Detecting {
public:
    void get_robot_coordinates(int* r_x, int* r_y) {
        cout << "Getting robot coordinates..." << endl;
    }
    bool get_grafiti_coordinates(int* g_x, int* g_y, bool* correct_height) {
        bool check{};
        char detecting_proc;

        cout << "If camera detected grafiti, press Y, else press N" << endl;
        cin >> detecting_proc;
        if (detecting_proc == 'Y' || detecting_proc == 'y') {
            check = true;
            cout << "Place recognition" << endl;
        }
        if (detecting_proc == 'N' || detecting_proc == 'n') {
            check = false;
        }
        if (*correct_height) {
            *correct_height = false;
        }
        else {
            *correct_height = true;
        }
        return check;
    }
};

class Place {
public:
    bool move(int r_x, int r_y, int g_x, int g_y) {
        bool check;
        if (r_x == g_x && r_y == g_y) {
            cout << "Robot arrived" << endl;
            check = true;
        }
        else {
            check = false;
            cout << "Robot is moving do its destination" << endl;
        }
        return check;
    }
};

class Robotic_Arm {
public:
    void on() {
        cout << "Arm turned on" << endl;
    }

    void up() {
        cout << "Arm up" << endl;
    }

    void down() {
        cout << "Arm down" << endl;
    }
};

class Paint_sprayer {
public:
    void on() {
        cout << "Paint_sprayer turned on" << endl;
    }

    void off() {
        cout << "Paint_sprayer  turned off" << endl;
    }
};

class System {
private:
    int r_x = 0, r_y = 0;
    int g_x = 0, g_y = 0;
    bool correct_height;
    Engine en;
    Detecting dt;
    Place pl;
    Robotic_Arm arm;
    Paint_sprayer sp;

public:
    void start_robot() {
        en.on();
    }

    bool get_coord() {
        dt.get_robot_coordinates(&r_x, &r_y);
        return dt.get_grafiti_coordinates(&g_x, &g_y, &correct_height);
    }

    bool set_coord() {
        return pl.move(r_x, r_y, g_x, g_y);
    }

    void set_hand() {
        arm.on();
        if (correct_height)
            arm.up();
        else
            arm.down();
    }

    bool do_spray() {
        bool check;
        sp.on();
        sp.off();
        return check = true;
    }

    void stop_robot() {
        en.off();
    }
};

class Processing {
private:
    RobotState cleaner = OFF;
    System sys;
    bool B_OFF = false, spot;
public:
    void process_state(RobotState cleaner) {
        while (!B_OFF) {
            switch (cleaner) {
            case OFF:
                cout << "Robot is switching off" << endl;
                sys.stop_robot();
                B_OFF = true;
                break;
            case WAITING:
                cout << "Robot is turning on" << endl;
                sys.start_robot();
                cleaner = DETECTING;
                break;
            case DETECTING:
                cout << "Detecting operation" << endl;
                spot = sys.get_coord();
                if (spot) {
                    cleaner = MOVING;
                }
                else {
                    cleaner = OFF;
                }
                break;
            case MOVING:
                cout << "Robot is moving" << endl;
                if (!sys.set_coord()) {
                    cleaner = DETECTING;
                }
                else {
                    sys.set_hand();
                    cleaner = CLEANING;
                }
                break;
            case CLEANING:
                cout << "Cleaning..." << endl;
                spot = sys.do_spray();
                cleaner = DETECTING;
                break;
            }
        }
    }
};

int main() {
    Processing test;
    test.process_state(WAITING);
    std::cout << "peremoga!" << std::endl;
    return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
