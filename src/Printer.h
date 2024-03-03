#ifndef UNTITLED_PRINTER_H
#define UNTITLED_PRINTER_H
#include <string>

class Printer {
private:
    std::string name;
    int emission;
    int speed; // pages per minute
public:
    Printer(std::string n, int e, int s) : name(n), emission(e), speed(s) {};
};


#endif //UNTITLED_PRINTER_H
