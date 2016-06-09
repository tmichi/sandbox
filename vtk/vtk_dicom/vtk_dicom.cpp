#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkStringArray.h>
#include <vtkImageData.h>
#include <iostream>
int main(int argc, char* argv[])
{
	if ( argc != 2 )
	{
		std::cout << "Usage: " << argv[0]
			  << " FolderName" << std::endl;
		return EXIT_FAILURE;
	}
 
	std::string folder = argv[1];
	vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName(folder.c_str());
	reader->Update();

	vtkImageData* image = reader->GetOutput();
	int* size = image->GetDimensions(); // volume size
	double* pitch = image->GetSpacing(); // voxel pitch
	float* origin =	reader->GetImagePositionPatient(); // origin point
	std::cerr<<"size:"<<size[0]<<" "<<size[1]<<" "<<size[2]<<std::endl;
	std::cerr<<"pitch:"<<pitch[0]<<" "<<pitch[1]<<" "<<pitch[2]<<std::endl;
	std::cerr<<"origin:"<<origin[0]<<" "<<origin[1]<<" "<<origin[2]<<std::endl;

	float minv = image->GetScalarComponentAsFloat(0,0,0,0);
	float maxv = minv;
	for( int z = 0 ; z < size[2] ; ++z ) {
		for ( int y = 0 ; y < size[1] ; ++y ) {
			for ( int x = 0 ; x < size[0] ; ++x ) {
				float v = image->GetScalarComponentAsFloat(x,y,z, 0);
				if ( v < minv ) minv = v;
				if ( maxv < v ) maxv = v;
			}
		}
	}
	std::cerr<<"minv : "<< minv<<", maxv:"<<maxv<<std::endl;
	return EXIT_SUCCESS;
}
