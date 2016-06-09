#include <mi/VolumeData.hpp>
#include <mi/VolumeDataImporter.hpp>
#include "ColorMapper.hpp"
int main ( int argc , char** argv ) {
	std::string distName("dist.raw");
	std::string seedName("seed.raw");
	std::string outName("out.ply");
	mi::Point3i size ( 512, 399, 1);
	mi::Point3d pitch( 0.5, 0.5, 0.5);
	mi::VolumeInfo info( size, pitch);
	mi::VolumeData<char> seed(info);
	mi::VolumeData<float> dist(info);
	if ( !mi::VolumeDataImporter<char>(seed).read(seedName) ) return -1;
	if ( !mi::VolumeDataImporter<float>(dist).read(distName)) return -1;

	std::ofstream fout(outName.c_str());
	fout<<"ply"<<std::endl;
	fout<<"format ascii 1.0"<<std::endl;
	fout<<"element vertex "<<size.x() * size.y()<<std::endl;
	fout<<"property float x"<<std::endl;
	fout<<"property float y"<<std::endl;
	fout<<"property float z"<<std::endl;
	fout<<"property uchar red"<<std::endl;
	fout<<"property uchar green"<<std::endl;
	fout<<"property uchar blue"<<std::endl;
	fout<<"element face "<<(size.x()-1) * (size.y()-1)<<std::endl;
	fout<<"property list uchar int vertex_index"<<std::endl;
	fout<<"end_header"<<std::endl;

	for ( int y = 0 ; y < size.y() ; ++y ) {
		for( int x = 0 ; x < size.x() ; ++x ) {
			mi::Point3i p(x,y,0);
			int l = seed.get(p);
			float d = dist.get(p);
			int r,g,b;
			if ( l == 0 ) {
				if ( d < 1.0e-6 ) {
					r = 255;
					g = 255;
					b = 255;
				}
				else {
					r = 127;
					g = 127;
					b = 127;
				}
				
			}
			else if ( l == 1 ) {
				r = 255;
				g = 255;
				b = 127;
			}
			else if ( l == 2 ) {
				r = 255;
				g = 127;
				b = 127;
			}
			else {
				r = 0;
				g = 0;
				b = 0;
			}
			fout<<p.x()<<" "<<p.y()<<" "<<d * 0.5<<" "<<r<<" "<<g<<" "<<b<<std::endl;
			}
		}

	for ( int y = 0 ; y < size.y() -1; ++y ) {
		for( int x = 0 ; x < size.x()-1 ; ++x ) {
			fout<<4<<" ";
			fout<<(x + 0 )+ (y+ 0) * size.x()<<" ";
			fout<<(x + 0 )+ (y+ 1) * size.x()<<" ";
			fout<<(x + 1 )+ (y+ 1) * size.x()<<" "; 
			fout<<(x + 1 )+ (y+ 0) * size.x()<<std::endl;
		}
	}
	return 0;
}
