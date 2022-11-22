#include "BaseTest.h"

BaseTest::BaseTest()
{}

BaseTest::~BaseTest()
{}

void BaseTest::_run()
{}

bool BaseTest::run()
{
	std::string status;
	bool success = true;
	try
	{
		this->_run();
		status = "✔️";
	}
	catch(int error)
	{
		status = "❌";
		success = false;
	}
	std::cout << this->name << " " << status << std::endl;

	return success;
}
