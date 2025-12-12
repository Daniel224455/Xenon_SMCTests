#include "common.h"

void SMCUndo()
{
	smc smc;

    TRAY_STATE tray = smc.GetTrayState();
    const char* trayStr2 = "UNKNOWN";
    switch(tray) {
        case OPEN:    trayStr2 = "OPEN"; break;
        case CLOSED:  trayStr2 = "CLOSED"; break;
        case OPENING: trayStr2 = "OPENING"; break;
        case CLOSING: trayStr2 = "CLOSING"; break;
        case UNKNOWN: trayStr2 = "UNKNOWN"; break;
    }
    if (tray == OPEN)
        printf("[SMC] Closing Tray\n");
	    smc.CloseTray();

	smc.SetFanSpeed(1, 40);
	smc.SetFanSpeed(2, 40);
	smc.SetPowerLED(POWER_LED_DEFAULT, true);
	smc.SetLEDS(GREEN, OFF, OFF, OFF);

	return;
}

void TestSMC()
{
    smc smc;

    smc.SetLEDS(GREEN, ORANGE, RED, OFF);
    smc.SetPowerLED(POWER_LED_BLINK, true);

    TILT_STATE tilt = smc.GetTiltState();
    const char* tiltStr = (tilt == VERTICAL) ? "VERTICAL" : "HORIZONTAL";
    printf("[SMC] Tilt Status: %s\n", tiltStr);

    TRAY_STATE tray = smc.GetTrayState();
    const char* trayStr = "UNKNOWN";
    switch(tray) {
        case OPEN:    trayStr = "OPEN"; break;
        case CLOSED:  trayStr = "CLOSED"; break;
        case OPENING: trayStr = "OPENING"; break;
        case CLOSING: trayStr = "CLOSING"; break;
        case UNKNOWN: trayStr = "UNKNOWN"; break;
    }
    printf("[SMC] Tray Status: %s\n", trayStr);

    smc.SetFanSpeed(1, 100);
	smc.SetFanSpeed(2, 100);

    const char* avPack = smc.GetAVPackName();
    printf("[SMC] AV Pack Name: %s\n", avPack);
	
	Sleep(10000);
	SMCUndo();

	return;
}

void __cdecl main()
{
	smc smc;

    printf("[SMC] Entry\n");

    ShowNotification("SMC Test");

	printf("[SMC] SMC Version: %s\n", smc.GetSMCVersion());
	printf("[SMC] Intiating SMC calls\n");

	TestSMC();

	ShowNotification("Finished");

    return;
}

