#pragma once

typedef unsigned char byte;

class Image {
public:
	Image() : pixels(0), w(0), h(0), x(0), y(0), dx(0), dy(0) {}
	~Image() { delete [] pixels; }
	void load(const char * filename, int w, int h);
	void draw() const;
	void update(double dt);
	void setVelocity(double dx, double dy);
	void setStartingpts(int x, int y);
private:
	byte * pixels;
	double dx;
	double dy;
	int w;  
	int h; 
	int x;
	int y;
};
