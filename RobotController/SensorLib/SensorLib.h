#pragma once
#include <wiringPiI2C.h>
#include "stdint.h"
#include <time.h>
#include <string>
#include <vector>
#include "ArduCamDriver/arducamDriver.h"
#include "../../RobotLib/guid.h"

#define SENSORS_GRAVITY_EARTH             (9.80665F)              /**< Earth's gravity in m/s^2 */
#define SENSORS_GRAVITY_MOON              (1.6F)                  /**< The moon's gravity in m/s^2 */
#define SENSORS_GRAVITY_SUN               (275.0F)                /**< The sun's gravity in m/s^2 */
#define SENSORS_GRAVITY_STANDARD          (SENSORS_GRAVITY_EARTH)
#define SENSORS_MAGFIELD_EARTH_MAX        (60.0F)                 /**< Maximum magnetic field on Earth's surface */
#define SENSORS_MAGFIELD_EARTH_MIN        (30.0F)                 /**< Minimum magnetic field on Earth's surface */
#define SENSORS_PRESSURE_SEALEVELHPA      (1013.25F)              /**< Average sea level pressure is 1013.25 hPa */
#define SENSORS_DPS_TO_RADS               (0.017453293F)          /**< Degrees/s to rad/s multiplier */
#define SENSORS_GAUSS_TO_MICROTESLA       (100)                   /**< Gauss to micro-Tesla multiplier */

/** Sensor types */

typedef enum sensors_type_t
{
	SENSOR_TYPE_ACCELEROMETER       = (1),   /**< Gravity + linear acceleration */
	SENSOR_TYPE_MAGNETIC_FIELD      = (2),
	SENSOR_TYPE_ORIENTATION         = (3),
	SENSOR_TYPE_GYROSCOPE           = (4),
	SENSOR_TYPE_LIGHT               = (5),
	SENSOR_TYPE_PRESSURE            = (6),
	SENSOR_TYPE_PROXIMITY           = (8),
	SENSOR_TYPE_GRAVITY             = (9),
	SENSOR_TYPE_LINEAR_ACCELERATION = (10),  /**< Acceleration not including gravity */
	SENSOR_TYPE_ROTATION_VECTOR     = (11),
	SENSOR_TYPE_RELATIVE_HUMIDITY   = (12),
	SENSOR_TYPE_AMBIENT_TEMPERATURE = (13),
	SENSOR_TYPE_VOLTAGE             = (15),
	SENSOR_TYPE_CURRENT             = (16),
	SENSOR_TYPE_COLOR               = (17),
	SENSOR_TYPE_GPS					= (18),
	SENSOR_TYPE_IMAGING				= (19),
	SENSOR_TYPE_LINEAR_DISTANCE	    = (20),
	SENSOR_TYPE_COUNTER				= (21)
} sensors_type_t;

/** struct sensors_vec_s is used to return a vector in a common format. */
typedef struct sensors_vec {
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
        /* Orientation sensors */
        struct {
            float roll;    /**< Rotation around the longitudinal axis (the plane body, 'X axis'). Roll is positive and increasing when moving downward. -90�<=roll<=90� */
            float pitch;   /**< Rotation around the lateral axis (the wing span, 'Y axis'). Pitch is positive and increasing when moving upwards. -180�<=pitch<=180�) */
            float heading; /**< Angle between the longitudinal axis (the plane body) and magnetic north, measured clockwise when viewing from the top of the device. 0-359� */
        };
    };
    int8_t status;
    uint8_t reserved[3];
} sensors_vec_t;

typedef char nmea_cardinal_t;
#define NMEA_CARDINAL_DIR_NORTH		(nmea_cardinal_t) 'N'
#define NMEA_CARDINAL_DIR_EAST		(nmea_cardinal_t) 'E'
#define NMEA_CARDINAL_DIR_SOUTH		(nmea_cardinal_t) 'S'
#define NMEA_CARDINAL_DIR_WEST		(nmea_cardinal_t) 'W'
#define NMEA_CARDINAL_DIR_UNKNOWN	(nmea_cardinal_t) '\0'

/* GPS Position Structure */
typedef struct
{
	double minutes;
	int degrees;
	nmea_cardinal_t cardinal;
} nmea_position;

typedef enum
{
	NMEA_UNKNOWN,
	NMEA_GPGGA,
	NMEA_GPGLL,
	NMEA_GPRMC
} nmea_msg_t;

typedef enum 
{
	DATA_OK,
	WARNING,
	UNKNOWN		
} nmea_data_quality_t;

typedef enum
{
	UNK=0,
	INVALID=-1,
	GPS_FIX=1,
	DGPS_FIX=2
} nmea_fix_quality_t;

typedef struct sensors_gps_sat
{
	uint8_t msgTotal;
	uint8_t msgNum;
	uint8_t totalSVsInView;
	uint8_t svPRNNum1;
	uint8_t elevation1;
	uint8_t azimuth1;
	uint8_t SNR1;
	uint8_t svPRNNum2;
	uint8_t elevation2;
	uint8_t azimuth2;
	uint8_t SNR2;
	uint8_t svPRNNum3;
	uint8_t elevation3;
	uint8_t azimuth3;
	uint8_t SNR3;
	uint8_t svPRNNum4;
	uint8_t elevation4;
	uint8_t azimuth4;
	uint8_t SNR4;
} sensors_gps_sat_t;

typedef struct sensors_gps
{
	std::vector<nmea_msg_t> messageType;
	nmea_data_quality_t dataQuality;
		// Date and Time 
	struct tm time;
		
	// Location information 
	struct
	{
		nmea_position latitude;
		nmea_position longitude;
		double geoIDHeight;
		double altitude;
		double speedKPH;
		double speedKTS;
		double course;
		double magvariation;
		double HDOP;
	};
	
	nmea_fix_quality_t fixquality;
	int satellites;
	bool fix;		
	sensors_gps_sat_t sateliteInfo;
} sensors_gps_t;


/** struct sensors_color_s is used to return color data in a common format. */
typedef struct {
    union {
        float c[3];
        /* RGB color space */
        struct {
            float r;		/**< Red component */
            float g;		/**< Green component */
            float b;		/**< Blue component */
        };
    };
	uint16_t colorTemp;		/**< Color Temp */	

    uint32_t rgba;			/**< 24-bit RGBA value */
} sensors_color_t;

typedef struct
{
	std::string filename;
	jpeg_size_t imageSize;
	image_format_t imageFormat;
} sensors_image_t;

typedef struct
{
	bool objectDetected;
	float pctCertainty;
} sensors_object_detection_t;

/** struct sensor_event_s is used to provide a single sensor event in a common format. */
typedef struct 
{
    int32_t version;                          /**< must be sizeof(struct sensors_event_t) */
    int32_t sensor_id;                        /**< unique sensor identifier */
    int32_t type;                             /**< sensor type */
    int32_t reserved0;                        /**< reserved */
    int32_t timestamp;                        /**< time is in milliseconds */
    union
    {
        float           data[4];
        sensors_vec_t   acceleration;         /**< acceleration values are in meter per second per second (m/s^2) */
        sensors_vec_t   magnetic;             /**< magnetic vector values are in micro-Tesla (uT) */
        sensors_vec_t   orientation;          /**< orientation values are in degrees */
        sensors_vec_t   gyro;                 /**< gyroscope values are in rad/s */
        float           temperature;          /**< temperature is in degrees centigrade (Celsius) */
        float           distanceCM;           /**< distance in centimeters */
	    float			distanceIN;			  /**< distance in inches */
        float           light;                /**< light in SI lux units */
        float           pressure;             /**< pressure in hectopascal (hPa) */
        float           relative_humidity;    /**< relative humidity in percent */
        float           current;              /**< current in milliamps (mA) */
        float           voltage;              /**< voltage in volts (V) */
        sensors_color_t color;                /**< color in RGB component values */	    	    
    };
	sensors_image_t image;				  /**< Image file information */
	sensors_gps_t		gps;				  /**< location information */
	sensors_object_detection_t objectDetection;		/**< Object detection */	
} sensors_event_t;

/* Sensor details (40 bytes) */
/** struct sensor_s is used to describe basic information about a specific sensor. */
typedef struct
{
    char     name[12];                        /**< sensor name */
    int32_t  version;                         /**< version of the hardware + driver */
    int32_t  sensor_id;                       /**< unique sensor identifier */
    int32_t  type;                            /**< this sensor's type (ex. SENSOR_TYPE_LIGHT) */
    float    max_value;                       /**< maximum value of this sensor's value in SI units */
    float    min_value;                       /**< minimum value of this sensor's value in SI units */
    float    resolution;                      /**< smallest difference between two values reported by this sensor */
    int32_t  min_delay;                       /**< min delay in microseconds between events. zero = not a constant rate */
} sensor_t;
