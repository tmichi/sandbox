#ifndef ISO2D_COMMAND_HPP
#define ISO2D_COMMAND_HPP 1

#include <string>
#include <mi/CommandTemplate.hpp>
#include <mi/math.hpp>
#include <mi/VolumeData.hpp>
template<typename T>
class Iso2dCommand : public mi::CommandTemplate
{
private:
        mi::Point3i _size;
	int _header_size;
	mi::VolumeData<T> _data;
	mi::VolumeData<char> _mask;
        std::string _input_file;
        std::string _output_file;
	T _iso;
public:
        Iso2dCommand ( void ) ;
        ~Iso2dCommand ( void ) ;
        bool init ( const mi::Argument& arg ) ;
        bool run  ( void );
        bool term ( void );
};
#endif //ISO2D_COMMAND_HPP

