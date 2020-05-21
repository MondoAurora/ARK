#include <DustMain.h>
#include <DustApi.h>

#include <iostream>

#include <vendors/dust/DustgenUnitTest01.h>

using namespace std;
using namespace DustUnitDustTest01;

int main(int argc, char **argv) {

	cout << "calling bootDust..." << endl;

	bootDust(argc, argv);

	DustNativeLogic *pl = (DustNativeLogic*) DustData::getNative(0, DustAgentTest01);

	if ( pl ) {
	pl->DustActionExecute();
	}

	cout << "Success." << endl;

	return 0;
}
