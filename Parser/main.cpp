#include "parser.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " filename" << endl;
		return 1;
	}
	ifstream inputFile(argv[1]);
	if (! inputFile) {
		cout << "Unable to open input file " << argv[1] << endl;
		return 1;
	}

	Parser parser(inputFile);
	parser.parse();
	inputFile.close();
}

