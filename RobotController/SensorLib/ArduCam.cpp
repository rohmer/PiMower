#include "ArduCam.h"
#include "ArduCamDriver/ov2640_regs.h"
#include "ArduCamDriver/ov5642_regs.h"
#include "ArduCamDriver/arducam_arch.h"
#include "../../3rdParty/wiringPi/wiringPi/wiringPiI2C.h"
#include <cstring>

sensor_model_t ArduCam::cameraSensor;
uint8_t ArduCam::i2cfd;
uint8_t ArduCam::spifd;
uint8_t ArduCam::spiCS;
uint8_t ArduCam::sensorAddr;

#define BUF_SIZE (384*1024)

ArduCam::ArduCam(RobotLib *robotLib)
	: SensorBase(robotLib)
{
	if (robotLib->getEmulator())
	{
		return;
	}
	getDeviceStatus(robotLib);
	initialize(sensorAddr);
}

void ArduCam::initialize(uint8_t i2caddress)
{
	i2cfd = DeviceManager::getI2CFD(i2caddress);
	if (i2cfd == -1)
	{
		std::stringstream ss;
		ss << "Could not initialize device: " << i2caddress << " on I2C bus";
		robotLib->LogError(ss.str());
		initialized = false;
		return;
	}
	spifd = DeviceManager::getSPIFD(0, 1000000);
	if (spifd == -1)
	{
		std::stringstream ss;
		ss << "Could not initialize SPI";
		robotLib->LogError(ss.str());
		initialized = false;
		return;
	}

	if (!initSensor())
	{
		robotLib->LogError("Could not initialize sensor");
		initialized = false;
		return;
	}
	if (!initSPI())
	{
		robotLib->LogError("Could not find ArduCam on SPI");
		initialized = false;
		return;
	}
	arducam_write_reg(ARDUCHIP_MODE, 0x00, spiCS);

	if (!chipTest())
	{
		robotLib->LogError("Could not verify the camera module");
		initialized = false;
		return;
	}
}

bool ArduCam::initSPI()
{
	arducam_write_reg(ARDUCHIP_TEST1, 0x55, CAM1_CS);
	uint8_t temp;
	temp = arducam_read_reg(ARDUCHIP_TEST1, CAM1_CS);
	if (temp == 0x55)
	{
		spiCS = CAM1_CS;
		return true;
	}
	arducam_write_reg(ARDUCHIP_TEST1, 0x55, CAM2_CS);

	temp = arducam_read_reg(ARDUCHIP_TEST1, CAM2_CS);
	if (temp == 0x55)
	{
		spiCS = CAM2_CS;
		return true;
	}
	arducam_write_reg(ARDUCHIP_TEST1, 0x55, CAM3_CS);

	temp = arducam_read_reg(ARDUCHIP_TEST1, CAM3_CS);
	if (temp == 0x55)
	{
		spiCS = CAM3_CS;
		return true;
	}
	arducam_write_reg(ARDUCHIP_TEST1, 0x55, CAM4_CS);

	temp = arducam_read_reg(ARDUCHIP_TEST1, CAM4_CS);
	if (temp == 0x55)
	{
		spiCS = CAM4_CS;
		return true;
	}

	return false;
}

bool ArduCam::initSensor()
{
	if (cameraSensor == sensor_model_t::smOV2640)
	{
		robotLib->Log("Initalizing OV2640 sensor");
		arducam_i2c_write(0xff, 0x01);
		arducam_i2c_write(0x12, 0x80);
		arducam_delay_ms(100);
		if (imageFormat == fmtJPEG)
		{
			arducam_i2c_write_regs(OV2640_JPEG_INIT);
			arducam_i2c_write_regs(OV2640_YUV422);
			arducam_i2c_write_regs(OV2640_JPEG);
			arducam_i2c_write(0xff, 0x01);
			arducam_i2c_write(0x15, 0x00);
			arducam_i2c_write_regs(OV2640_320x240_JPEG);
		}
		else
		{
			arducam_i2c_write_regs(OV2640_QVGA);
		}
		return true;
	}
	if (cameraSensor == sensor_model_t::smOV5642)
	{
		uint8_t reg_val;
		arducam_i2c_word_write(0x3008, 0x80);
		arducam_delay_ms(100);
		if (imageFormat == fmtJPEG)
		{
			arducam_i2c_write_word_regs(ov5642_dvp_fmt_global_init);
			arducam_delay_ms(100);
			arducam_i2c_write_word_regs(ov5642_dvp_fmt_jpeg_qvga);
		}
		else
		{
			arducam_i2c_write_word_regs(OV5642_RGB_QVGA);
			arducam_i2c_word_read(0x3818, &reg_val);
			arducam_i2c_word_write(0x3818, (reg_val | 0x60) & 0xff);
			arducam_i2c_word_read(0x3621, &reg_val);
			arducam_i2c_word_write(0x3621, reg_val & 0xdf);
		}
	}

	std::stringstream ss;
	ss << "Sensor Model: " << cameraSensor << " is not currently supported";
	robotLib->LogError(ss.str());
	return false;
}

bool ArduCam::chipTest()
{
	uint8_t vid, pid;
	arducam_write_reg(ARDUCHIP_MODE, 0x00, spiCS);
	if (cameraSensor == sensor_model_t::smOV5642)
	{
		arducam_i2c_word_read(OV5642_CHIPID_HIGH, &vid);
		arducam_i2c_word_read(OV5642_CHIPID_LOW, &pid);
		if ((vid != 0x56) || (pid != 0x42))
		{
			return false;
		}
		return true;
	}

	if (cameraSensor == sensor_model_t::smOV2640)
	{
		arducam_i2c_word_read(OV2640_CHIPID_HIGH, &vid);
		arducam_i2c_word_read(OV2640_CHIPID_LOW, &pid);
		if ((vid != 0x26) || (pid != 0x42))
		{
			return false;
		}
		return true;
	}
	return false;
}

void ArduCam::setImageSize(jpeg_size_t imageSize)
{
	if (cameraSensor == sensor_model_t::smOV2640)
	{
		arducam_set_jpeg_size(imageSize);
	}
	if (cameraSensor == sensor_model_t::smOV5642)
	{
		arducam_OV5642_set_jpeg_size(imageSize);
	}
	this->imageSize = imageSize;
	sleep(1);
}

void ArduCam::setCameraSensor(sensor_model_t cameraSensor)
{
	this->cameraSensor = cameraSensor;
}

void ArduCam::setImageFormat(image_format_t imageFormat)
{
	this->imageFormat = imageFormat;
}

device_status_t ArduCam::getDeviceStatus(RobotLib *robotLib)
{
	sensorAddr = 0;
	if (initI2C(0x3c))
	{
		cameraSensor = sensor_model_t::smOV5642;
		sensorAddr = 0x3c;
	}
	if (initI2C(0x30))
	{
		cameraSensor = sensor_model_t::smOV2640;
		sensorAddr = 0x30;
	}
	if (sensorAddr != 0)
	{
		if (initSPI())
			return device_status_t::DEVICE_CONNECTED;
		return device_status_t::DEVICE_UNCONFIGURED;
	}
	return device_status_t::DEVICE_UNAVAILBLE;
}

bool ArduCam::initI2C(uint8_t i2cAddr)
{
	int fd = wiringPiI2CSetup(i2cAddr);
	if (fd == -1)
		return false;
	return true;
}

bool ArduCam::getEvent(sensors_event_t *event)
{
	uint8_t buffer[BUF_SIZE] = { 0xFF };
	arducam_set_format(imageFormat);
	arducam_flush_fifo(spiCS);
	arducam_clear_fifo_flag(spiCS);
	robotLib->Log("Starting Image Capture");
	arducam_start_capture(spiCS);
	while (!(arducam_read_reg(ARDUCHIP_TRIG, spiCS) && CAP_DONE_MASK))
		;
	robotLib->Log("Capture Complete");
	char sfn[19] = "";
	if (imageFormat == image_format_t::fmtBMP)
	{
		strcpy(sfn, "/tmp/img.XXXXXX.bmp");
	}
	else
	{
		strcpy(sfn, "/tmp/img.XXXXXX.jpg");
	}

	FILE *fp1 = fopen(sfn, "w+");
	if (!fp1)
	{
		std::stringstream ss;
		ss << "Could not open " << sfn << " for writing";
		robotLib->LogError(ss.str());
		return false;
	}

	size_t len = read_fifo_length(spiCS);
	if (len >= 393216)
	{
		robotLib->LogError("File over size");
		return false;
	}
	if (len == 0)
	{
		robotLib->LogError("File size is 0");
		return false;
	}
	digitalWrite(spiCS, LOW);
	set_fifo_burst(BURST_FIFO_READ);
	int32_t i = 0;
	while (len > 4096)
	{
		arducam_transfers(&buffer[i], 4096);
		len -= 4096;
		i += 4096;
	}
	arducam_spi_transfers(&buffer[i], len);

	fwrite(buffer, len + i, 1, fp1);
	digitalWrite(CAM1_CS, HIGH);
	delay(100);
	fclose(fp1);
	arducam_clear_fifo_flag(CAM1_CS);
	std::string sFilename(sfn);
	event->image.filename = sFilename;
	event->image.imageFormat = imageFormat;
	event->image.imageSize = imageSize;
	return true;
}

// Add to auto registry so the device manager can know about it
AUTO_REGISTER_DEVICE(ArduCam);