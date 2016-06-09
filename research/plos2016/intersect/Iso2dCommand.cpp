#include "Iso2dCommand.hpp"
#include <mi/VolumeData.hpp>
#include <mi/VolumeDataImporter.hpp>
#include <mi/VolumeDataExporter.hpp>
#include <mi/SvgRenderer.hpp>

template<typename T>
Iso2dCommand<T>::Iso2dCommand ( void ) : mi::CommandTemplate()
{
        mi::AttributeSet& attrSet = this->getAttributeSet();
        attrSet.createDoubleNumericAttribute<int>( "-size", this->_size.x(), this->_size.y()).setMin( 1,1).setMandatory();
        attrSet.createNumericAttribute<int>( "-h", this->_header_size ).setMin( 0 );
	attrSet.createNumericAttribute<T>( "-iso", this->_iso ).setDefaultValue( 0 );

        attrSet.createStringAttribute( "-i", this->_input_file ).setMandatory();
        attrSet.createStringAttribute( "-o", this->_output_file ).setMandatory();
	
        return;
}
template<typename T>
Iso2dCommand<T>::~Iso2dCommand ( void )
{
        return;
}

template<typename T>
bool
Iso2dCommand<T>::init ( const mi::Argument& arg )
{
        mi::AttributeSet& attrSet = this->getAttributeSet();
        if( !attrSet.parse( arg ) ) {
                attrSet.printError();
                return false;
        }
	mi::Point3i& size = this->_size;
	size.z() = 1;

	mi::VolumeInfo info(size);
	this->_data.init(info);
	this->_mask.init(info);
	mi::VolumeDataImporter<char>( this->_mask ).read("mask.raw") ;//
        return mi::VolumeDataImporter<T>( this->_data ).read( this->_input_file ) ;
}

template<typename T>
bool
Iso2dCommand<T>::run ( void )
{
	mi::VolumeData<T>& data = this->_data;
	mi::Point3i& size = this->_size;
	mi::SvgRenderer renderer( size.x(), size.y(), this->_output_file);
	
	renderer.setStrokeWidth(1);
	renderer.setStrokeColor("Red");
	renderer.setViewBox(0,0,size.x(), size.y());
	for( int y = 0 ; y < size.y() -1 ; ++y ) {
		for ( int x = 0 ; x < size.x() -1; ++x ) {
			int index = 0;
			bool mask = false;
			for( int dy = 0 ; dy < 2 ; ++dy) {
				for ( int dx = 0 ; dx< 2 ; ++dx) {
					if ( data.get( x + dx, y + dy, 0) >=  this->_iso ) {
						index += static_cast<int>(std::pow (2, dx + 2* dy ) ) ;
					}
					if ( this->_mask.get( x + dx, y + dy, 0) == 2 ) mask  = true;//
				}
			}
			if (!mask) continue; //
			switch ( index ) {
			case 0 :
				break;
			case 1://fd
			case 14:
				renderer.drawLine(x , y + 0.5 , x +0.5 , y); //NW
				break;
			case 2://fd
			case 13:
				renderer.drawLine(x + 0.5 , y , x + 1, y + 0.5); //NE
				break;
			case 3://fd
			case 12:
				renderer.drawLine(x , y + 0.5, x + 1, y + 0.5); //EW
				break;
			case 4://fd
			case 11:
				renderer.drawLine(x , y + 0.5, x + 0.5 , y + 1); //SW
				break;
			case 5://fd
			case 10:
				renderer.drawLine(x + 0.5 , y , x + 0.5, y + 1); //NS
				break;
			case 6:
				renderer.drawLine(x , y + 0.5 , x +0.5 , y); //NW
				renderer.drawLine(x + 0.5 , y + 1, x + 1, y + 0.5); //SE
				break;
			case 7://fd
			case 8:
				renderer.drawLine(x + 0.5 , y + 1, x + 1, y + 0.5); //SE
				break;
			case 9:
				renderer.drawLine(x + 0.5 , y , x + 1, y + 0.5); //NE
				renderer.drawLine(x , y + 0.5, x + 0.5 , y + 1); //SW
				break;
			
			}
		}
	}
	// save raw
	for( int y = 0 ; y < size.y(); ++y ) {
		for ( int x = 0 ; x < size.x(); ++x ) {
			if ( data.get( x, y , 0) >=  this->_iso ) {
				data.set(x, y, 0, 1);
			}
			else {
				data.set(x, y, 0, 0);
			}
		}
	}
	if( !mi::VolumeDataExporter<T>( data ).write( "binarized_result.raw" ) ) return false;
	return true;
}

template<typename T>
bool
Iso2dCommand<T>::term ( void )
{
        return true;
}

template class Iso2dCommand<char>;
template class Iso2dCommand<unsigned char>;
template class Iso2dCommand<short>;
template class Iso2dCommand<unsigned short>;
template class Iso2dCommand<int>;
template class Iso2dCommand<unsigned int>;
template class Iso2dCommand<float>;
template class Iso2dCommand<double>;
