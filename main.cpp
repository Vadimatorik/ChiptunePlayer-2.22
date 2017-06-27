#include "main.h"

class base {
public:
    virtual int get() { return 111; };
};

class B : public base {
public:
    int get() { return 222; };
};

class C : public base {
public:
    int get() { return 333; };
};


int main (void){
    B obj1;
    C obj2;
    int test;
    base* p;
    p = &obj1;
    test = p->get();
    p = &obj2;
    test = p->get();

    test++;
    ayplayer_clock_init();
    ayplayer_port_init();
    ayplayer_spi_init();
    ayplayer_housekeeping_init();

    vTaskStartScheduler();
    while ( true ) {};
}
