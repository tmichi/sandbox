#include "IntersectCommand.hpp"
#include <mi/VolumeData.hpp>
#include <mi/VolumeDataImporter.hpp>
#include <mi/VolumeDataExporter.hpp>
template<typename T>
IntersectCommand<T>::IntersectCommand ( void ) : mi::CommandTemplate()
{
        mi::AttributeSet& attrSet = this->getAttributeSet();
        attrSet.createTripleNumericAttribute<int>( "-size", this->_size.x(), this->_size.y(), this->_size.z() ).setMin( 1,1,1 ).setMandatory();
        attrSet.createNumericAttribute<int>( "-h", this->_header_size ).setMin( 0 );

        attrSet.createStringAttribute( "-i", this->_input_file ).setMandatory();
        attrSet.createStringAttribute( "-o", this->_output_file ).setMandatory();
	attrSet.createNumericAttribute<int>( "-cutx", this->_dim.x());
	attrSet.createNumericAttribute<int>( "-cuty", this->_dim.y());
	attrSet.createNumericAttribute<int>( "-cutz", this->_dim.z());

        return;
}
template<typename T>
IntersectCommand<T>::~IntersectCommand ( void )
{
        return;
}

template<typename T>
bool
IntersectCommand<T>::init ( const mi::Argument& arg )
{
        mi::AttributeSet& attrSet = this->getAttributeSet();
        if( !attrSet.parse( arg ) ) {
                attrSet.printError();
                return false;
        }
	
	if      ( arg.exist("-cutx") ) this->_dimension = 0;
	else if ( arg.exist("-cuty") ) this->_dimension = 1;
	else if ( arg.exist("-cutz") ) this->_dimension = 2;
	else return false; // invalid;
	int& d = this->_dimension;
	this->_coordinate = this->_dim[d];
	mi::Point3i& size = this->_size;
	int& c = this->_coordinate;
	std::cerr<<"cut: ";
	if ( d == 0 ) std::cerr<<"x";
	if ( d == 1 ) std::cerr<<"y";
	if ( d == 2 ) std::cerr<<"z";
	std::cerr<<"="<< c <<std::endl;

	if ( !(0 <= c && c < size[this->_dimension]) ) {
		std::cerr<<"Invalid cut ";
		return false; 
	}

	mi::VolumeInfo info(size);
	this->_data.init(info);
        return mi::VolumeDataImporter<T>( this->_data ).read( this->_input_file ) ;
}

template<typename T>
bool
IntersectCommand<T>::run ( void )
{
	int& d = this->_dimension;
	mi::Point3i& size = this->_size;
	int& c = this->_coordinate;

	mi::Point3i nsize = size;
	nsize[d] = 1;
	mi::VolumeData<T> outData(nsize);


	if ( d == 0 ) {
		for( int z = 0 ; z < size.z() ; ++z ) {
			for( int y = 0 ; y < size.y() ; ++y ) {
				int x = c;
				outData.set( 0,y,z, this->_data.get(x,y,z));
			}
		}
	}
	else if ( d == 1 ) {
		for( int z = 0 ; z < size.z() ; ++z ) {
			for( int x = 0 ; x < size.x() ; ++x ) {
				int y = c;
				outData.set( x,0,z, this->_data.get(x,y,z));
			}
		}
	}
	else if ( d == 2 ) {
		for( int y = 0 ; y < size.y() ; ++y ) {
			for( int x = 0 ; x < size.x() ; ++x ) {
				int z = c;
				outData.set( x,y,0, this->_data.get(x,y,z));
			}
		}
	}
	else {
		std::cerr<<"invalid dimension"<<std::endl;
		return false;
	}
	std::cerr<<nsize.transpose()<<std::endl;
        if( !mi::VolumeDataExporter<T>( outData ).write( this->_output_file ) ) return false;
        return true;
}

template<typename T>
bool
IntersectCommand<T>::term ( void )
{
        return true;
}

template class IntersectCommand<char>;
template class IntersectCommand<unsigned char>;
template class IntersectCommand<short>;
template class IntersectCommand<unsigned short>;
template class IntersectCommand<int>;
template class IntersectCommand<unsigned int>;
template class IntersectCommand<float>;
template class IntersectCommand<double>;
