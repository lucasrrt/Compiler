#include <iostream>
#include "lexical.h"

using namespace std;

int main() {
	declareDictionary();

	file.open("example");
	cout << reserved_words["boolean"] << endl;

}
