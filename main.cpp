#include <iostream>
#include <string>
#include "HuffmanTree.hpp"

int main(){

	HuffmanTree t;
	help();
    for(;;){
        char code;
        std::cout << "Enter operation code:" << std::endl;
        std::cin >> code;
		std::cout << std::endl;

		while(std::cin.get() != '\n')
			;

        switch (code) {
			case 'h':
				help();
				break;
			case 'c':
				userInput(t);
                break;
            case 'q':
				return 0;
			default:
				std::cout << ("Illegal operation code!") << std::endl;
		}
		std::cout << std::endl;
    }

    return 0;
}