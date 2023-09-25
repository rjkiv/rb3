#include <types.h>

class App {
public:
	App(int argc, char **argv);
	~App();
	void RunWithoutDebugging();
};

// found in the fxn call App::App(int, char**)
class CloseToApp {
    public:
    int unk0, unk4, unk8, unkc;
    float unk10, unk14;
    int unk18, unk1c;
    int unk20, unk24;
    float unk28;
    unsigned char unk2c;

    CloseToApp(); 					// constructor: https://decomp.me/scratch/aNp4f
	void fn_8000EEB8();				// https://decomp.me/scratch/Z7HaR
	int fn_8000DB9C();				// https://decomp.me/scratch/bWvsN
};

// https://decomp.me/scratch/oDwf6 - INCOMPLETE, PLEASE FIX!!!
void fn_803512F0(); //standalone fxn, found in App::App(int, char**)