BATTLEOUPUT_PATH=../BattleCoreGit/BattleCore
BATTLECORESO_PATH=../BattleCoreGit/BattleCore/

all:
	g++ -O2 -Wall -I${BATTLEOUPUT_PATH} -L${BATTLECORESO_PATH} \
		MechBattleConsoleForLinuxServer.cpp -o MechBattleConsoleForLinuxServer -lBattleCore -llua -ldl

debug:
	g++ -g -Wall -I${BATTLEOUPUT_PATH} -L${BATTLECORESO_PATH}\
		MechBattleConsoleForLinuxServer.cpp -o MechBattleConsoleForLinuxServerDebug -lBattleCore -llua -ldl
