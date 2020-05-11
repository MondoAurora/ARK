#include <DustMain.h>
#include <DustApi.h>

#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	cout << "calling bootDust..." << endl; // prints !!!Hello World!!!

	bootDust(argc, argv);

	DustNativeLogic *pl = (DustNativeLogic*) DustData::getNative(0, 99);

	if ( pl ) {
	pl->DustActionExecute();
	}

	cout << "Success." << endl; // prints !!!Hello World!!!

	return 0;
}
