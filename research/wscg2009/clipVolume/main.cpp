#define _USE_MATH_DEFINES
#include <mi/Range.hpp>
#include <mi/VolumeInfo.hpp>
#include <iostream>

// implementation of WSCG09 methods.
void get_range ( const mi::VolumeInfo& info, const mi::Point3i& p0, const mi::Point3i& p1, const double dist, mi::Range& range) {
	const mi::Vector3d center = 0.5 * (info.getPointInSpace(p0) + info.getPointInSpace(p1) );
	const double r = dist * 0.5; // distance
	const mi::Vector3d d(r, r, r);
	const mi::Point3i bmin = info.getPointInVoxel(center - d);
	const mi::Point3i bmax = info.getPointInVoxel(center + d);
	return range.init( bmin, bmax);
}



int main ( int argc, char** argv ) {
	mi::VolumeInfo info ( mi::Point3i (128, 128, 128) , mi::Point3d ( 0.4, 0.4, 1) );
	const mi::Point3i p0 (3, 0, 0);
	const mi::Point3i p1 (0, 3, 0);

	const double r = 10; // range
	mi::Range range;
	get_range( info, p0, p1, r, range);
	std::cerr<<range.getMin().transpose()<<" "
		 <<range.getMax().transpose()<<std::endl;
	double d = 1;
	for ( auto&& p : info ) {
		if ( range.isValid(p)) continue;
		const double dist0 = info.getLength(p0-p);
		const double dist1 = info.getLength(p1-p);
		
		double dist = dist0 + dist1;
		if ( dist < r ) {
			std::cerr<<"error "<<dist0<<" "<<dist1<<" "<<p.transpose()<<" "<<dist<<std::endl;
			return -1;
		}
	}
	std::cerr<<"ok"<<std::endl;
	return 0;
}
