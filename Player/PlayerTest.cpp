#include "stdafx.h"
#include "gtest\gtest.h"
#include <TestMain.h>
#include <windows.h>
#include <direct.h>
#include <string>

namespace {

	class ManuelPlayerTest : public ::testing::Test {
	protected:
		ManuelPlayerTest()
		{
		}
	};

	TEST(ManualPlayerTest, loadNothing)
	{
		int msgboxID1 = MessageBox(NULL, (LPCWSTR)L"Haben Sie eine aktive Webcam mit ihrem Testger‰t verbunden?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	
		int msgboxID2 = 0;

		init(0,0);
		
		switch (msgboxID1)
		{
		case IDNO:
			msgboxID2 =	MessageBox(NULL, (LPCWSTR)L"Wurde der Player gestartet, aber ein schwarzer Bildschirm angezeigt?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);
			break;
		case IDYES:
			msgboxID2 =	MessageBox(NULL, (LPCWSTR)L"Wurde der Player gestartet, und das aktuelle Bild ihrer Webcam angezeigt?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	
			break;
		case 0:
			EXPECT_TRUE(FALSE);
			break;
		}
		switch (msgboxID2)
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

	TEST(ManualPlayerTest, loadPicture)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das Verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-200";
		char height[] = "-200";
		char projectPath[] = "-currentProject";
		char mode[] = "-0";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\images\\IDMarker-001.jpg");
		char fps[] = "-10";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 200x200 Pixel groﬂen Fenster mit dem IDMarker1 als Hintergrundbild gestartet?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadVideo)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		char projectPath[] = "-currentProject";
		char mode[] = "-1";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\videos\\imageVideo\\");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit einem Video von dem MetaioMan als Hintergrundbild mit einem fps gestartet?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadNotValidPicturePath)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		char projectPath[] = "-currentProject";
		char mode[] = "-1";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\images\\IDMarker-001.png");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit einem schwarzen Hintergrundbild gestartet und die Fehlermeldung: \" Debug: Invalid test file path: [individuellerPfad]\\testFiles\\images\\IDMarker-001.png\" ung¸ltiger Pfad ausgegeben?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadNotValidVideoPath)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		char projectPath[] = "-currentProject";
		char mode[] = "-2";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\projects\\IDMarker-001.jpg");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit einem schwarzen Hintergrundbild gestartet und die Fehlermeldung: \" Debug: Invalid test file path: [individuellerPfad]\\testFiles\\images\\IDMarker-001.png \" ausgegeben", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadIDMarkerProjectPicture)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-800";
		std::string projectPath = "-";
		projectPath.append(_pgmptr);
		projectPath.erase(projectPath.find_last_of("\\", std::string::npos), std::string::npos);
		projectPath.append("\\testFiles\\projects\\IDMarkerProject\\");
		char mode[] = "-0";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\images\\IDMarker-001.jpg");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x800 Pixel groﬂen Fenster mit dem IDMarker1 als Hintergrundbild gestartet und Szene1 aus dem  angezeigt.", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadIDMarkerProjectVideo)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		std::string projectPath = "-";
		projectPath.append(_pgmptr);
		projectPath.erase(projectPath.find_last_of("\\", std::string::npos), std::string::npos);
		projectPath.append("\\testFiles\\projects\\IDMarkerProject\\");
		char mode[] = "-1";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\videos\\markerVideo\\");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem IDMarkerVideo als Hintergrund gestartet und Szenen wie diese angezeigt:", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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


	TEST(ManualPlayerTest, loadPictureMarkerProjectPicture)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		std::string projectPath = "-";
		projectPath.append(_pgmptr);
		projectPath.erase(projectPath.find_last_of("\\", std::string::npos), std::string::npos);
		projectPath.append("\\testFiles\\projects\\PictureMarkerProject\\");
		char mode[] = "-0";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\images\\PictureMarker-001.jpg");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem PictureMarker001 als Hintergrundbild gestartet und Szene 1 des PictureMarkerProjects korrekt dargestellt?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadImageTrackableProjectPicture)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		std::string projectPath = "-";
		projectPath.append(_pgmptr);
		projectPath.erase(projectPath.find_last_of("\\", std::string::npos), std::string::npos);
		projectPath.append("\\testFiles\\projects\\ImageTrackableProject\\");
		char mode[] = "-0";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\images\\Markerless-001.jpg");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem Markerless001 als Hintergrundbild gestartet und Szene 1 des ImageTrackableProjects korrekt darauf angewendet?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadImageTrackableProjectVideo)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		std::string projectPath = "-";
		projectPath.append(_pgmptr);
		projectPath.erase(projectPath.find_last_of("\\", std::string::npos), std::string::npos);
		projectPath.append("\\testFiles\\projects\\ImageTrackableProject\\");
		char mode[] = "-1";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\video\\imageVideo\\");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem Video des ImageTrackable001 als Hintergrund gestartet und das ImageTrackableProject korrekt angezeigt?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadCorruptedProject)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		std::string projectPath = "-";
		projectPath.append(_pgmptr);
		projectPath.erase(projectPath.find_last_of("\\", std::string::npos), std::string::npos);
		projectPath.append("\\testFiles\\projects\\corruptedProject\\");
		char mode[] = "-1";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\videos\\markerVideo\\");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem IDMarkerVideo als Hintergrund gestartet, aber keine Szene angezeigt und auf der Konsole werden Fehlermeldungen ausgegeben.", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadMultipleMarkerProject)
	{
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das Verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"LoadNothingTest", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		std::string projectPath = "-";
		projectPath.append(_pgmptr);
		projectPath.erase(projectPath.find_last_of("\\", std::string::npos), std::string::npos);
		projectPath.append("\\testFiles\\projects\\IDMarkerProject\\");
		char mode[] = "-0";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\images\\idMarker1and2.jpg");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem IDMarker1 und IDMarker2 als Hintergrundbild gestartet und die Szenen ", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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

	TEST(ManualPlayerTest, loadDatabaseChartCheckProject)
	{
		int msgboxID1 = MessageBox(NULL, (LPCWSTR)L"Haben Sie Zugriff auf http://cumulus.teco.edu:4242/api/query?start=1392741669001&m=avg:temperature%7bresource_id=Heater_Living%7d&ms=true ?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	
		switch (msgboxID1)
		{
		case IDNO:
			return;
		case IDYES:
			break;
		case 0:
			return;
		}

		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		std::string projectPath = "-";
		projectPath.append(_pgmptr);
		projectPath.erase(projectPath.find_last_of("\\", std::string::npos), std::string::npos);
		projectPath.append("\\testFiles\\projects\\IDMarkerProject\\");
		char mode[] = "-1";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\images\\idMarker3.jpg");
		char fps[] = "-1";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem IDMarker3 als Hintergrundbild gestartet und die Daten aus http://cumulus.teco.edu:4242/api/query?start=1392741669001&m=avg:temperature%7bresource_id=Heater_Living%7d&ms=true auf dem Diagramm und Nachrichten zur Datensammlung werden angezeigt im StandaradOutput.", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
}