//#include <..\\Player\\Player.h>
#include "gtest/gtest.h"
#include "main.h"
#include <windows.h>


TEST(LoadTest, LoadNothing)
{
	TestMain(0,0);
	int msgboxID = MessageBox(NULL, "Wurde der Player gestartet, aber nichts angezeigt?", "LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);

	switch (msgboxID)
	{
	case IDNO:
		EXPECT_TRUE(FALSE);
		break;
	case IDYES:
		EXPECT_TRUE(TRUE);
		break;
	case 0:
		EXPECT_TRUE(FALSE);
		break;
	}
}
