#ifndef GYRO_H
#define GYRO_H

class Gyro;

class gyro {
	public:
	gyro(unsigned char port);
	~gyro();
	double getOrientation();
	
	private:
	Gyro g;
};

#endif
