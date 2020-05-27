#include <DustMain.h>
#include <DustApi.h>

#include <iostream>

#include <vendors/dust/DustgenUnitTest01.h>

using namespace std;
using namespace DustUnitDustTest01;

int main(int argc, char **argv) {

	cout << "calling bootDust..." << endl;

	dustBoot(argc, argv);

    DustEntity e = DustData::createEntity(DustAgentTest01);

    dustLaunch();

	DustNativeLogic *pl = (DustNativeLogic*) DustData::getNative(e);

	if ( pl ) {
	pl->DustActionExecute();
	}


	cout << "Success." << endl;

	dustShutdown();

	return 0;
}
