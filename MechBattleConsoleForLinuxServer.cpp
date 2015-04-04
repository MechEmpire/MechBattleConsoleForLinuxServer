//MechBattleConsoleForLinuxServer
//@author: shrekshao
//@date: 2014/08/03


#include <dlfcn.h>
#include <iostream>
#include <string>
//#include "RobotAI_Interface.h"		//include path should be in makefile
#include "BattleCoreOutput.h"
//#include "/home/shrekshao/MechEmpireII/BattleCoreGit/BattleCore/Basic_Battle/Robot/RobotAI_Interface.h"
//#include "/home/shrekshao/MechEmpireII/BattleCoreGit/BattleCore/Basic_Battle/BattleCoreOutput.h"

using namespace std;

#define MAX_AI_NUM 4


int main(int argc,char *argv[])
{
	//the command line input is provided by server program
	//seems no need to prove its correctness
	//command line: route_for_battleMode_config  numAIs  route_for_ai_0  route_for_ai_1 ...
	//				0 							 1 			2				3

	if(argc<5)
	{
		//error occurs
		//cout<<"too few inputs!\n";
		return -1;
	}

	//cout<<"converting AI nums...\n";


	int numAIs;

	numAIs=atoi(argv[2]);
	//cout<<argc<<'\n';
	//cout<<argv[0]<<'\n';
	//cout<<argv[1]<<'\n';
	//cout<<numAIs<<'\n';
	if(numAIs<=1 || numAIs>MAX_AI_NUM)
	{
		//error occurs
		//cout<<"numAIs input error!\n";
		return -2;
	}

    /*
	if(numAIs!=argc-3)
	{
		//error occurs
		//cout<<"num of input AI routes is not consistent with numAIs!\n";
		return -3;
	}
    */


    if (argc >=7)
    {
        SetBattleModeNew(argv[1],argv[5],argv[6]);
    }
    else
    {
        SetBattleModeWithConfigFile(argv[1]);
    }



	//cout<<"loading game lua data...\n";

	//TODO: load battleMode config
	LoadGameData();

	//cout<<"initializing new battle...\n";
	InitNewBattle();

	//StartTestingBattleWithRandomEquipment();

	//cout<<"setting config file...\n";

	//SetBattleModeWithConfigFile(argv[1]);



	//cout<<"loading AI agents...\n";
	//load AIs
	int i;
	void * ai_handle[MAX_AI_NUM];
	typedef RobotAI_Interface* (*Export)();
	typedef void (*FreeRobotAIPointer)(RobotAI_Interface*);
	Export exportAIFunction[MAX_AI_NUM];
	FreeRobotAIPointer freeAIFunction[MAX_AI_NUM];
	RobotAI_Interface* pAI[MAX_AI_NUM];

	for(i=0;i<numAIs;i++)
	{
		ai_handle[i]=dlopen(argv[i+3], RTLD_LAZY);
		exportAIFunction[i] = (Export)dlsym(ai_handle[i], "Export");
		freeAIFunction[i] = (FreeRobotAIPointer)dlsym(ai_handle[i],"FreeRobotAIPointer");
		pAI[i]=(*exportAIFunction[i])();
	}


	//TODO: Add AIs to battlefield and
	for(i=0;i<numAIs;i++)
	{
		AddRobotAI(pAI[i]);		//??return ai index? need to store?
	}

	//cout<<"launching battle...\n";
	LaunchBattle();


	//free
	for(i=0;i<numAIs;i++)
	{
		(*freeAIFunction[i])(pAI[i]);
		dlclose(ai_handle[i]);
	}


	return 0;
}


