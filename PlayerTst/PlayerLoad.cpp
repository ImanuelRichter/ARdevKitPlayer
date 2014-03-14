#include <..\\Player\\main.h>
#include "gtest\gtest.h"
#include <windows.h>


TEST(LoadTest, LoadNothing)
{
	main(0, 0);
	int msgboxID = MessageBox(NULL, "Wurde der Player gestartet, aber nichts angezeigt?", "LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);

	switch (msgboxID)
	{
	case IDNO:
		ASSERT_TRUE(FALSE);
		break;
	case IDYES:
		ASSERT_TRUE(TRUE);
		break;
	case 0:
		ASSERT_TRUE(FALSE);
		break;
	}
}
