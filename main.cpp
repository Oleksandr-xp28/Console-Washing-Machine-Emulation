// Console Washing Machine Emulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <conio.h> // For _kbhit() and _getch() on Windows

using namespace std;

class WashingMachine {
public:
    enum class State {
        IDLE,
        FILLING,
        WASHING,
        DRAINING
    };

    WashingMachine() : state(State::IDLE), animationDelay(500), isRunning(false) {}

    void start() {
        isRunning = true;
        while (isRunning) {
            clearScreen();
            displayMachine();
            updateState();
            this_thread::sleep_for(chrono::milliseconds(animationDelay));
        }
    }

    void stop() {
        isRunning = false;
    }

    void setAnimationDelay(int delay) {
        animationDelay = delay;
    }

    State getState() const {
        return state;
    }

private:
    State state;
    int animationDelay;
    atomic<bool> isRunning;

    void clearScreen() {
        cout << "\033[2J\033[1;1H";
    }

    void displayMachine() {
        cout << "Washing Machine Emulation\n\n";
        switch (state) {
        case State::IDLE:
            cout << "Idle...\n";
            cout << "   \n";
            cout << "  ===\n";
            cout << "   \n";
            break;
        case State::FILLING:
            cout << "Filling...\n";
            cout << "   \n";
            cout << "  ===\n";
            cout << "   \n";
            break;
        case State::WASHING:
            cout << "Washing...\n";
            cout << "  ====\n";
            cout << "   | \n";
            cout << "  ====\n";
            break;
        case State::DRAINING:
            cout << "Draining...\n";
            cout << "   \n";
            cout << "  ===\n";
            cout << "   \n";
            break;
        }
        cout << "Press 'q' to quit or 'd' to change delay.\n";
    }

    void updateState() {
        switch (state) {
        case State::IDLE:
            state = State::FILLING;
            break;
        case State::FILLING:
            state = State::WASHING;
            break;
        case State::WASHING:
            state = State::DRAINING;
            break;
        case State::DRAINING:
            state = State::IDLE;
            break;
        }
    }
};


class AnimationController {
public:
    AnimationController(WashingMachine& machine) : washingMachine(machine) {}

    void run() {
        while (true) {
            if (_kbhit()) {
                char key = _getch();
                switch (key) {
                case 'q':
                    washingMachine.stop();
                    return;
                case 'd':
                    changeDelay();
                    break;
                }
            }
        }
    }

private:
    WashingMachine& washingMachine;

    void changeDelay() {
        int delay;
        cout << "Enter new delay in milliseconds: ";
        cin >> delay;
        washingMachine.setAnimationDelay(delay);
    }
};

int main() {
    WashingMachine washingMachine;
    AnimationController controller(washingMachine);

    thread machineThread(&WashingMachine::start, &washingMachine);
    thread controllerThread(&AnimationController::run, &controller);

    machineThread.join();
    controllerThread.join();

    return 0;
}
