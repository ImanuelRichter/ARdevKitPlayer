#include "stdafx.h"
#include "gtest\gtest.h"
#include "ConnectionController.h"

namespace {
	ConnectionController* controller;

	class ConnectionControllerTest : public ::testing::Test {
	protected:
		ConnectionControllerTest()
		{
			controller = new ConnectionController(0);
		}
	};

	TEST(IncomingBroadcastTest, general)
	{
		controller = new ConnectionController(0);
		controller->incomingBroadcast();
	}
}