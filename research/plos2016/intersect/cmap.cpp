#include <fstream>
#include <iomanip>
#include "ColorMapper.hpp"

int main ( int argc, char** argv ) {
	std::ifstream fin( "K2589-dist.raw", std::ios::binary);
	std::ofstream fout( "dist.raw", std::ios::binary);
	mi::ColorMapper mapper(0, 100);
	float v;
	unsigned char r,g,b;
	while (fin) {
		fin.read((char*)(&v), 4);
		if (!fin) break;
		mapper.convert(v, r,g,b);
		if ( v == 0 ) {
			r = 0 ; 
			g = 0;
			b = 0;
		}
		fout.write((char*)(&r), 1);
		fout.write((char*)(&g), 1);
		fout.write((char*)(&b), 1);
	}
	return 0;
}
