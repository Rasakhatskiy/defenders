#include <iostream>
#include <vector>
#include "globals.h"



//air     - 0
//stone   - 1024
//wall    - 1  -  9
//arbalet - 10 - 19
//cannon  - 20 - 29
//tree    - 66,67,68,69
//stone   - 70, 71


int main() {
	RenderWindow window(_Mode1280x720_, "Defenders");
	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);
	menu(window);
}
