#pragma once
#include <string>

using namespace std;

namespace Console {
    class Color {
    public:
        Color();
        Color(unsigned char v, string rep);
        unsigned char getColorValue();
        string getColorString();

    private:
        unsigned char value;
        string representation;
    };
}
