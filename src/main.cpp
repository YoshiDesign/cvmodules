#include <iostream>
#include "Engine.h"
#include "VidCap.h"
#include "ImageFunctions.h"
#include "ScanningFunctions.h"


int main()
{
	engine::debug("Hello Lib");
	//engine::vidcap::capture4();

	engine::scanning::scan1();

	return 0;
}