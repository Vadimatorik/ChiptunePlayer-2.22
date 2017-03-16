#include <stdint.h>
volatile uint8_t a_loop[] = {1, 2, 3, 4};

int main (void){

	while(1) {
		a_loop[0]++;
	};
}
