#include <crtdbg.h>
#include <stdio.h>
#include <regex>
#include <iostream>

#include "CFileSystem.h"
#include "wowEnvironment.h"
#include "function.h"

#pragma comment(lib, "CascLib.lib")
#pragma comment(lib, "pugixml.lib")

void testWowEnvironment();

int main(int argc, char* argv[])
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	testWowEnvironment();

	getchar();
	return 0;
}

void testWowEnvironment()
{
	CFileSystem* fs = new CFileSystem(R"(E:\World Of Warcraft)");
	wowEnvironment* wowEnv = new wowEnvironment(fs);

	if (!wowEnv->init())
		printf("init fail!\n");
	else
		printf("init success!\n");

	if (!wowEnv->loadCascListFiles())
		printf("listfile fail!\n");
	else
		printf("listfile success!\n");

	delete wowEnv;
	delete fs;


}