#include "main.h"
/*
class A {
public:
    virtual int rx     ( uint8_t* data_input_array, uint16_t len ) const  = 0;
    virtual int tx     ( uint8_t* data_output_array, uint16_t len ) const = 0 ;
    virtual ~A() = 0;
};
A::~A() {}

class B : public A {
public:
    int rx     ( uint8_t* data_input_array, uint16_t len ) const {

        data_input_array[1] = 20;
        return 0;
    }
    int tx     ( uint8_t* data_output_array, uint16_t len ) const {
        data_output_array[1] = 15;
        return 0;
    }
};

class C {
public:
    C ( A* obj ) : obj(obj) {};
    int get     ( void ) const {
        obj->tx( array, 20);
        return 0;
    }

    int set     ( void ) const {
        obj->rx( array, 20 );
        return 0;
    }

private:
    A* obj;
    mutable uint8_t array[20] = { 0 };

};
*/
class base {
public:
    base() {}
    virtual ~base()=0;
};

// Provide a definition for destructor.
base::~base() {}

class derived:public base {
public:
    derived() {}
    ~derived(){}
};

derived a();

int main (void){
   //derived *pDerived;
   //pDerived =  &a;
    ayplayer_clock_init();
    ayplayer_port_init();
    ayplayer_spi_init();
    ayplayer_housekeeping_init();

    vTaskStartScheduler();
    while ( true ) {};
}
