#include "UIData.h"

UIData::UIData()
{
}

/*
{
"UIData" : {
"accelX": "12345678",
"accelY": "12345678",
"accelZ": "12345678",
"heading": "12345678",
"roll": "12345678",
"pitch": "12345678",
"altitude": "12345678",
"battPct":"123",
"minutesLat": "12345678",
"degreesLat": "12345678",
"cardinalLat": "n",
"minutesLon": "12345678",
"degreesLon": "12345678",
"cardinalLon": "n",
"gpsSatNum": "123",
"frontSonorIn": "123",
"leftSonorIn": "123",
"rightSonorIn": "123",
"backSonorIn": "123",
"leftWheel": "123",
"rightWheel": "123",
"blade":true,
"frontBumper": false,
"backBumper": false,
"nextSchedule": "03/19/1973 06:30"

}
}
*/

bool UIData::FromJson(std::string jsonString, uint32_t inputHash)
{
	const size_t bufferSize = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(24) + 450;
	DynamicJsonBuffer jsonBuffer(bufferSize);	

	JsonObject& root = jsonBuffer.parseObject(jsonString.c_str());

	JsonObject& UIData = root["UIData"];
	accelX = UIData["accelX"]; // 12345678
	accelY = UIData["accelY"]; // 12345678
	accelZ = UIData["accelZ"]; // 12345678
	heading = UIData["heading"]; // 12345678
	roll = UIData["roll"]; // 12345678
	pitch = UIData["pitch"]; // 12345678
	altitude = UIData["altitude"]; // 12345678
	battPct = UIData["battPct"]; // 123
	minutesLat = UIData["minutesLat"]; // 123.555
	degreesLat = UIData["degreesLat"]; // 12345678
	cardinalLat = UIData["cardinalLat"]; // "F"
	minutesLon = UIData["minutesLon"]; // 123.555
	degreesLon = UIData["degreesLon"]; // 12345678
	cardinalLon = UIData["cardinalLon"]; // "N"
	gpsSatNum = UIData["gpsSatNum"]; // 123
	frontSonorIn=UIData["FrontSonorInches"];
	backSonorIn=UIData["BackSonorInches"] ;
	leftSonorIn=UIData["LeftSonorInches"] ;
	rightSonorIn=UIData["RightSonorInches"] ;
	leftWheel=UIData["leftWheel"] ;
	rightWheel=UIData["rightWheel"] ;
	blade = UIData["blade"];
	frontBumper = UIData["frontBumper"]; // false
	backBumper = UIData["backBumper"]; // false
	char *ns = UIData["nextSchedule"];
	nextSchedule = (std::string) ns;

	hashCode = UIData["hash"]; // 12345678
	if (genHashCode(jsonString) == hashCode)
	{
		return true;
	}
	return false;
}

std::string UIData::ToJson()
{
	const size_t bufferSize = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(22) + 400;
	DynamicJsonBuffer jsonBuffer(bufferSize);
	JsonObject &root = jsonBuffer.createObject();
	JsonObject &UIData = root["UIData"];
	UIData["accelX"] = accelX;			// 12345678
	UIData["accelY"] = accelY;			// 12345678
	UIData["accelZ"] = accelZ;			// 12345678
	UIData["heading"] = heading;		// 12345678
	UIData["roll"] = roll;				// 12345678
	UIData["pitch"] = pitch;			// 12345678
	UIData["altitude"] = altitude;		// 12345678
	UIData["battPct"] = battPct;		// 123
	UIData["minutesLat"] = minutesLat;	// 123.555
	UIData["degreesLat"] = degreesLat;	// 12345678
	UIData["cardinalLat"] = cardinalLat;// "N"
	UIData["minutesLon"] = minutesLon;	// 123.555
	UIData["degreesLon"] = degreesLon;	// 12345678
	UIData["cardinalLon"] = cardinalLon;// "F"
	UIData["gpsSatNum"] = gpsSatNum;	// 123
	UIData["FrontSonorInches"] = frontSonorIn;
	UIData["BackSonorInches"] = backSonorIn;
	UIData["LeftSonorInches"] = leftSonorIn;
	UIData["RightSonorInches"] = rightSonorIn;
	UIData["leftWheel"] = leftWheel;
	UIData["rightWheel"] = rightWheel;
	UIData["blade"] = blade;	
	UIData["nextSchedule"] = nextSchedule.c_str();
	UIData["frontBumper"] = frontBumper;
	UIData["backBumper"] = backBumper;

	char buffer[512];
	UIData.printTo(buffer, sizeof(buffer));
	std::string strReturn(buffer);

	this->hashCode = genHashCode(strReturn);
	return strReturn;
}

uint32_t UIData::genHashCode(std::string inputStr)
{
	unsigned h = FIRSTH;
	uint ptr = 0;
	while (ptr < inputStr.length())
	{
		h = (h*APRIME) ^ (inputStr[ptr] * BPRIME);
		ptr++;
	}
	return h;
}