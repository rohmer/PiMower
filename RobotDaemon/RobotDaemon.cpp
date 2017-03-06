#include "RobotDaemon.h"

RobotDaemon::RobotDaemon() : helpRequested(false)
{	
}

RobotDaemon::~RobotDaemon()
{
}

void RobotDaemon::initialize(Poco::Util::Application &self)
{
	Poco::Util::ServerApplication::initialize(self);
}

void RobotDaemon::defineOptions(Poco::Util::OptionSet &options)
{
	Poco::Util::ServerApplication::defineOptions(options);
	options.addOption(
		Poco::Util::Option("help", "h", "Display help information on command line arguments")
		.required(false)
		.repeatable(false)
		.callback(Poco::Util::OptionCallback<RobotDaemon>(this, &RobotDaemon::handleHelp));
}

void RobotDaemon::handleHelp(const std::string& name, const std::string& value)
{
	helpRequested = true;
	displayHelp();
	stopOptionsProcessing();
}

void RobotDaemon::displayHelp()
{
	Poco::Util::HelpFormatter helpFormatter(options());
	helpFormatter.setCommand(commandName());
	helpFormatter.setUsage("RobotDaemon");
	helpFormatter.setHeader("RobotDaemon application help options");
	helpFormatter.format(std::cout);
}