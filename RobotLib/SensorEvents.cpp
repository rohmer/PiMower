#include "SensorEvents.h"

bool SensorEvents::insertPositionEvent(Guid sessionID, sensors_event_t *positionEvent)
{
	std::stringstream sql;
	time_t rawTime;
	time(&rawTime);
	struct tm * t = localtime(&rawTime);
	time_t timeSinceEpoch = mktime(t);
	sql << "INSERT INTO POSITION VALUES(" << sessionID <<
		"," << timeSinceEpoch <<
		"," << positionEvent->gps.latitude.degrees <<
		"," << positionEvent->gps.latitude.minutes <<
		"," << positionEvent->gps.longitude.degrees <<
		"," << positionEvent->gps.latitude.minutes <<
		",'" << positionEvent->gps.latitude.cardinal << "'" <<
		",'" << positionEvent->gps.longitude.cardinal << "'" <<
		"," << positionEvent->gps.altitude <<
		"," << positionEvent->gps.geoIDHeight <<
		"," << positionEvent->gps.speedKPH <<
		"," << positionEvent->gps.course <<
		"," << positionEvent->gps.magvariation <<
		"," << positionEvent->gps.HDOP <<
		"," << positionEvent->gps.fixquality <<
		"," << positionEvent->gps.satellites <<
		"," << positionEvent->gps.fix <<
		"," << positionEvent->gyro.heading <<
		"," << positionEvent->gyro.pitch <<
		"," << positionEvent->gyro.roll <<
		"," << positionEvent->gyro.x <<
		"," << positionEvent->gyro.y <<
		"," << positionEvent->gyro.z << ")";

	return Database::getInstance().execSql(sql.str());
}