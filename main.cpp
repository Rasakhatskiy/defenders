#include <iostream>
#include <vector>
#include "globals.h"



//air     - 0
//stone   - 1024
//wall    - 1  -  9
//arbalet - 10 - 19
//cannon  - 20 - 29


int main() {
	RenderWindow window(_Mode1280x720_, "Defenders");
	menu(window);
}
