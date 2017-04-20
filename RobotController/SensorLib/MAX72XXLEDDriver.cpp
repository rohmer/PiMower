#include "MAX72XXLEDDriver.h"

MAX72XXLEDDriver::MAX72XXLEDDriver(RobotLib *robotLib)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	initialized = false;
	if (robotLib->getEmulator())
		return;
	initialize(MAX_SID, MAX_SCK, MAX_A0, MAX_nRST, MAX_nCS, 0);
}

MAX72XXLEDDriver::MAX72XXLEDDriver(RobotLib *robotLib, int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS, uint8_t spiChannel)
	: DeviceBase(robotLib, DEVICE_TYPE_T::DEVICE)
{
	shutdown = false;
	startDriverThread(this);
	initialized = true;
	if (robotLib->getEmulator())
		return;
	initialize(SID, SCLK, A0, RST, CS, spiChannel);
}

void MAX72XXLEDDriver::initialize(int8_t SID, int8_t SCLK, int8_t A0, int8_t RST, int8_t CS, uint8_t spiChannel)
{
	this->sid = SID;
	this->sclk  = SCLK;
	this->a0 = A0;
	this->rst = RST;
	this->cs = CS;

	pinMode(sid, OUTPUT);
	pinMode(sclk, OUTPUT);
	pinMode(a0, OUTPUT);
	pinMode(rst, OUTPUT);
	pinMode(cs, OUTPUT);
	spiFD = robotLib->getDeviceManager()->getSPIFD(spiChannel, 1000000);
}

MAX72XXLEDDriver::~MAX72XXLEDDriver()
{
	shutdown = true;
}

void MAX72XXLEDDriver::startDriverThread(MAX72XXLEDDriver *maxLED)
{
	maxLED->driverThread();
}

void MAX72XXLEDDriver::driverThread()
{
	std::map<std::string, std::pair <uint8_t, uint8_t>>::iterator ledIterator;
	while (!shutdown)
	{
		for (ledIterator = ledMapping.begin(); ledIterator != ledMapping.end(); ledIterator++)
		{
			std::pair<uint8_t, uint8_t> rcPair = ledIterator->second;
			LED_BEHAVIOR_T behavior = ledBehavior[rcPair];
			uint8_t row = rcPair.first;
			uint8_t col = rcPair.second;
			if (behavior == LED_BEHAVIOR_T::Off)
			{
				if (status[((row * 8) + col)])
				{
					controlLED(row, col, false);
					status[((row * 8) + col)] = true;
				}
			}
			if (behavior == LED_BEHAVIOR_T::On)
			{
				if (!status[((row * 8) + col)])
				{
					controlLED(row, col, true);
					status[((row * 8) + col)] = false;
				}
			}
			if (behavior == LED_BEHAVIOR_T::Blink)
			{
				if (blinkCountdown[rcPair])
				{
					blinkCountdown[rcPair]--;
					if (blinkCountdown[rcPair] <= 0)
					{
						if (status[((row * 8) + col)])
						{
							status[((row * 8) + col)] = false;
							controlLED(row, col, false);
						}
						else
						{
							status[((row * 8) + col)] = true;
							controlLED(row, col, true);
						}
					}
					if (!ledBlinkInterval[rcPair])
					{
						ledBlinkInterval[rcPair] = 2;
					}
					if (ledBlinkInterval[rcPair] > 10)
					{
						ledBlinkInterval[rcPair] = 10;
					}
					blinkCountdown[rcPair] = 500 / ledBlinkInterval[rcPair];
				}
			}
		}
		delayMicroseconds(1000);
	}
}

void MAX72XXLEDDriver::clear()
{
	for (uint8_t col = 1; col <= 8; col++)
	{
		uint8_t tx[] = { col, 0 };
		wiringPiSPIDataRW(spiFD, tx, 2);
	}
}

void MAX72XXLEDDriver::addLED(std::string ledName, uint8_t row, uint8_t col)
{
	std::pair<uint8_t, uint8_t> rcPair = std::make_pair(row, col);
	ledMapping.emplace(ledName, rcPair);
	ledBehavior.emplace(rcPair, LED_BEHAVIOR_T::Off);

	if (!initialized)
	{
		shutdown = false;
		startDriverThread(this);
		initialized = true;
	}
}

void MAX72XXLEDDriver::addLED(std::string ledName, uint8_t row, uint8_t col, LED_BEHAVIOR_T behavior, uint8_t blinkInterval)
{
	std::pair<uint8_t, uint8_t> rcPair = std::make_pair(row, col);
	ledMapping.emplace(ledName, rcPair);
	if (behavior == LED_BEHAVIOR_T::Off)
	{
		controlLED(row, col, false);
		ledBehavior.emplace(rcPair, LED_BEHAVIOR_T::Off);
		return;
	}
	if (behavior == LED_BEHAVIOR_T::On)
	{
		controlLED(row, col, true);
		ledBehavior.emplace(rcPair, LED_BEHAVIOR_T::On);
		return;
	}

	// Deal with blinking
	if (blinkInterval <= 0)
		blinkInterval = 1;
	if (blinkInterval > 10)
		blinkInterval = 10;
	ledBlinkInterval.emplace(rcPair, blinkInterval);
	blinkCountdown.emplace(rcPair, 500 / ledBlinkInterval[rcPair]);
	controlLED(row, col, true);
	ledBehavior.emplace(rcPair, behavior);
	if (!initialized)
	{
		shutdown = false;
		startDriverThread(this);
		initialized = true;
	}
}

void MAX72XXLEDDriver::controlLED(uint8_t row, uint8_t col, bool powerMode)
{
	status[(row - 1) * 8 + col] = powerMode;

	uint8_t val;

	for (int col = 0; col < 8; col++)
	{
		val = 0;
		for (int row = 0; row < 8; row++)
		{
			if (status[(row * 8) + col])
			{
				controlLED(row, col, true);
			}
			else
			{
				controlLED(row, col, false);
			}
		}
	}
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(MAX72XXLEDDriver);