#include "VoskSAPI.h"

int main() {
	VoskSAPI recognizer;
	recognizer.StartListening();
	
	// Keep the program running
	while (true) {}

	return 0;
}
