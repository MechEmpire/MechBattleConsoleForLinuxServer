MechBattleConsoleForLinuxServer
====
机甲战斗控制台（Linux服务器版）
====

By 狄学长

----

* 当前版本描述：<br/>
测试版，供服务器调用调试。与最终版本功能可能会有出入。
<br></br>

* 编译方法：
	* 需要的文件：
		* `MechBattleConsoleForLinuxServer.cpp`（需要与makefile在同一目录）
		* `BattleCoreOutput.h`
		* `libBattleCore.so`
		* `liblua.a`
		* `makefile`
	* 步骤：
		* 将makefile中的-I（包含路径）-L（链接路径）做修改以使编译器能够找到`BattleCoreOutput.h`, `libBattleCore.so`, `liblua.a`.
		* 控制台，在当前目录下输入

				makefile all

		* 获得输出的可执行文件`MechBattleConsoleForLinuxServer`
<br></br>

* 运行方法：
	* 需要的文件（位于同一目录下）：
		* `MechBattleConsoleForLinuxServer`
		* 若干战斗模式设置文件`BattleModeConfig0.conf`, `BattleModeConfig1.conf`, ...
		* 若干机甲智能体动态库`libRobotAI0.so`, `libRobotAI1`, ...
		* `battle_xml_format.xml` （该文件名称不能改动）
	* 步骤：
		* 控制台，在当前目录下命令行输入

				./MechBattleConsoleForLinuxServer BattleModeConfig0.conf 2 ./libRobotAI0.so ./libRobotAI1.so [./to/path/battle_record.txt ./to/path/battle_statistics.xml]
		* 命令行参数说明

				./MechBattleConsoleForLinuxServer BattleModeConfigFileName numAIs ./AIsofilename0 [./AIsofilename1] ...
<br></br>

* 配置和输出：
	* `BattleModeConfig.conf`格式

				BattleModeType;IsTimeLimited;LimitTimeFrame;IsGenerateBattleRecord;BattleRecordRoute;IsGenerateBattleStatistics;BSR
				1v1
				1
				4000
				1
				./
				1
				./
				test.map
                ./GameData.lua
                ./battle_xml_format.xml

<br></br> 对应的解释：

				各输入项说明:string
				战斗类型名称:string
				是否限时:bool(0/1)
				限时帧数:int(<10000)
				是否生成录像:bool(0/1)
				录像文件输出路径（请使用绝对路径）
				是否生成战斗统计文件:bool(0/1)
				统计文件输出路径（请使用绝对路径）
				地图文件名
                Gamedata.lua
                battle_xml_format



	* 输出：
		* 战斗录像文件.txt，可由游戏动画程序打开播放
		* 战斗统计文件.xml，供服务器使用的战斗相关数据



