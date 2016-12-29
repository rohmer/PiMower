#include "SensorEvents.h"

bool SensorEvents::insertPosition(sensors_gps positionEvent)
{	
	std::stringstream sql;
	time_t timeSinceEpoch = mktime(&positionEvent.time);
	sql << "INSERT INTO POSITION VALUES(" << timeSinceEpoch <<
		"," << positionEvent.latitude.degrees <<
		"," << positionEvent.latitude.minutes <<
		"," << positionEvent.longitude.degrees <<
		"," << positionEvent.latitude.minutes <<
		",'" << positionEvent.latitude.cardinal << "'" <<
		",'" << positionEvent.longitude.cardinal << "'" <<
		"," << positionEvent.altitude <<
		"," << positionEvent.geoIDHeight <<
		"," << positionEvent.speedKPH <<
		"," << positionEvent.course <<
		"," << positionEvent.magvariation <<
		"," << positionEvent.HDOP <<
		"," << positionEvent.fixquality <<
		"," << positionEvent.satellites <<
		"," << positionEvent.fix << ")";
	
	return Database::execSql(sql.str());
}	
		
		
		
		
		
		
		
		
		
		