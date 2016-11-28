#pragma once
#include <map>
#include <windows.h>

using namespace std;

namespace Constants {

	const enum  MineralTypes {
		Boulder,
		SmallBoulder,
		Gold,
		SmallGold,
		Diamond,
		Void
	};

	const enum Levels {
		One,
		Two
	};

	const enum States {
		Menu,
		Store,
		Level,
		Results
	};

	const enum HookStates {
		Aiming,
		Forward,
		Backward
	};

	const int WIDTH = 500;
	const int HEIGHT = 500;

	const int LEVEL_TIME = 30;

	const double PI = 3.14159265;

	const map<MineralTypes, int> mineralValues = {
		{ Boulder, 20 },
		{ Gold, 300 },
		{ SmallBoulder, 10 },
		{ SmallGold, 150 },
		{ Diamond, 500 }
	};

	const map<MineralTypes, double> mineralSizes = {
		{ Boulder, 0.07 },
		{ Gold, 0.05 },
		{ SmallBoulder, 0.035 },
		{ SmallGold, 0.035 },
		{ Diamond, 0.02 }
	};

	const map<MineralTypes, double> speeds = {
		{ Boulder, 0.002 },
		{ Gold, 0.002 },
		{ SmallBoulder, 0.008 },
		{ SmallGold, 0.008 },
		{ Diamond, 0.03 },
		{ Void, 0.03 }
	};


	const COLORREF BCKGRND_COLOR = RGB(76, 153, 0);

	static TCHAR winMessage[] = TEXT("You won!");
	static TCHAR loseMessage[] = TEXT("You lost!");

}