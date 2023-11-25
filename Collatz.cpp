#include "Collatz.h"

Collatz::Collatz() {

}

int Collatz::next(int num) {
    if (num == 1)
    {
        return num;
    }
    else if (num % 2 == 0)
    {
        return num / 2;
    }
    else
    {
        return 3 * num + 1;
    }
}