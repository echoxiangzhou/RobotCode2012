#ifndef DISPLAY_H
#define DISPLAY_H

class DriverStationLCD;

class Display {
	public:
	Display();
	~Display();
	void Printf(const char *format, ...);
	void PrintfLine(int line, const char *format, ...);
	void Update();
	void Clear();
	
	private:
	DriverStationLCD *dstation;
	string lines[6];
};

#endif
