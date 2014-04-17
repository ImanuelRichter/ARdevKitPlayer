#include "stdafx.h"
#include "gtest\gtest.h"
#include <TestMain.h>
#include <windows.h>
#include <direct.h>
#include <string>
#include <QMessageBox>

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
			msgboxID2 =	MessageBox(NULL, (LPCWSTR)L"Wurde der Player im Fullscreen gestartet, aber ein schwarzer Bildschirm angezeigt?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);
			break;
		case IDYES:
			msgboxID2 =	MessageBox(NULL, (LPCWSTR)L"Wurde der Player im Fullscreen gestartet, und das aktuelle Bild ihrer Webcam angezeigt?", (LPCWSTR)L"LoadNothingTest", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	
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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das Verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadPicture", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 200x200 Pixel groﬂen Fenster mit dem IDMarker1 als Hintergrundbild gestartet?", (LPCWSTR)L"loadPicture", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadVideo", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

		char name[] = "Player.exe";
		char width[] = "-800";
		char height[] = "-600";
		char projectPath[] = "-currentProject";
		char mode[] = "-1";
		std::string testFile = "-";
		testFile.append(_pgmptr);
		testFile.erase(testFile.find_last_of("\\", std::string::npos), std::string::npos);
		testFile.append("\\testFiles\\videos\\imageVideo\\");
		char fps[] = "-2";
		char* argv[] = {&name[0], &width[0], &height[0], &projectPath[0], &mode[0], &testFile[0], &fps[0], NULL};
		int argc = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

		init(argc, argv);
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit einem Video von dem MetaioMan als Hintergrundbild mit zwei fps gestartet?", (LPCWSTR)L"loadVideo", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadNotValidPicturePath", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit einem schwarzen Hintergrundbild gestartet und die Fehlermeldung: \" Debug: Invalid test file path: [individuellerPfad]\\testFiles\\images\\IDMarker-001.png\" ung¸ltiger Pfad ausgegeben?", (LPCWSTR)L"loadNotValidPicturePath", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadNotValidVideoPath", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit einem schwarzen Hintergrundbild gestartet und die Fehlermeldung: \"Debug: Invalid test file path: [individuellerPfad]\\testFiles\\images\\IDMarker-001.png \" ausgegeben", (LPCWSTR)L"loadNotValidVideoPath", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players, klicken sie auf das Bild der Stadt, falls es rechts erscheint und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadIDMarkerProjectPicture", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x800 Pixel groﬂen Fenster mit dem IDMarker1 als Hintergrundbild gestartet und Szene1 aus dem IDMarkerProject angezeigt? Das bedeutet: \n1)Das Standbild einer Frau um 90 Grad nach rechts gedreht in der linken oberen Ecke.\n2)Das Bild einer Stadt rechts neben dem Marker, stark verzerrt.\n3)Im rechten unteren Bereich des Markers wird ein Diagramm angezeigt, dass einen Temperaturverlauf anzeigt\n4)Wenn man auf das Bild klickt erscheint ein Popup mit TestAlert als Text.", (LPCWSTR)L"loadIDMarkerProjectPicture", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);
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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players, klicken sie auf das Bild der Stadt, falls es rechts neben Marker Nr.3 erscheint und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadIDMarkerProjectVideo", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem IDMarkerVideo als Hintergrund gestartet und alle Szenen des IDMarkerProject korrekt dargestellt? Das heiﬂt:\n1)Der erste Marker wird von einem Rahmen in etwa umgeben, rechts oberhalb befindet sich ein Diagramm und links unterhalb ein sehr verdrehtes Video.\n2)Beim zweiten Marker werden zwei Diagramme darunter und links davon angezeigt.\n3)beim dritten Marker wird ein Video um 90 Grad nach Rechts gedreht links, ein Diagramm rechts und ein verzerrtes Bild einer Stadt, welches bei Klick darauf eine Nachrichtenbox anzeigt, rechts vom ersten Marker angezeigt.", (LPCWSTR)L"loadIDMarkerProjectVideo", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadPictureMarkerProjectPicture", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem PictureMarker001 als Hintergrundbild gestartet und Szene 1 des PictureMarkerProjects korrekt dargestellt? Das heiﬂt:\n Es wird ein kleiner Rahmen im Zentrum angezeigt, links unten befindet sich ein Daigramm und rechts oben das doppelte Standbild einer Frau 90 Grad nach rechts gedreht.", (LPCWSTR)L"loadPictureMarkerProjectPicture", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadImageTrackableProjectPicture", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem Markerless001 als Hintergrundbild gestartet und Szene 1 des ImageTrackableProjects korrekt darauf dargestellt? Das heiﬂt: Es befindet sich ein um 90 Grad gedrehtes Standbild einer Frau, im Zentrum, das skalierte Bild einer Eule links oben und ein TemperaturDiagramm links unten.", (LPCWSTR)L"loadImageTrackableProjectPicture", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadImageTrackableProjectVideo", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);

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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem Video des ImageTrackable001 als Hintergrund gestartet und das ImageTrackableProject korrekt angezeigt?", (LPCWSTR)L"loadImageTrackableProjectVideo", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadCorruptedProject", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem IDMarkerVideo als Hintergrund gestartet, aber keine Szene angezeigt und auf der Konsole werden Fehlermeldungen ausgegeben.", (LPCWSTR)L"loadCorruptedProject", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		MessageBox(NULL, (LPCWSTR)L"Beobachten sie das Verhalten des Players und schlieﬂen sie ihn anschlieﬂend, um das Verhalten auszuwerten", (LPCWSTR)L"loadMultipleMarkerProject", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST);
		
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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem IDMarker1 und IDMarker2 als Hintergrundbild gestartet und die Szenen korrekt angezeigt, das heiﬂt bei Marker ID1 ein auf der Seite stehendes VideoStandbild, ein Diagramm und das verzerrte Bild einer Stadt und bei Marker ID3 zwei Diagramme.", (LPCWSTR)L"loadMultipleMarkerProject", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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
		int msgboxID1 = MessageBox(NULL, (LPCWSTR)L"Haben Sie Zugriff auf http://cumulus.teco.edu:4242/api/query?start=1392741669001&m=avg:temperature%7bresource_id=Heater_Living%7d&ms=true ?", (LPCWSTR)L"loadDatabaseChartCheckProject", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	
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
		int msgboxID = MessageBox(NULL, (LPCWSTR)L"Wurde der Player in einem 800x600 Pixel groﬂen Fenster mit dem IDMarker3 als Hintergrundbild gestartet und die Daten aus http://cumulus.teco.edu:4242/api/query?start=1392741669001&m=avg:temperature%7bresource_id=Heater_Living%7d&ms=true auf dem Diagramm und Nachrichten zur Datensammlung werden angezeigt im StandaradOutput.", (LPCWSTR)L"loadDatabaseChartCheckProjectb v ", MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST);	

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