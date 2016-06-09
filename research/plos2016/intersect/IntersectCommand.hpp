#ifndef INTERSECT_COMMAND_HPP
#define INTERSECT_COMMAND_HPP 1

#include <string>
#include <mi/CommandTemplate.hpp>
#include <mi/math.hpp>
#include <mi/VolumeData.hpp>
template<typename T>
class IntersectCommand : public mi::CommandTemplate
{
private:
        mi::Point3i _size;
	int _header_size;
	mi::VolumeData<T> _data;
        std::string _input_file;
        std::string _output_file;
	mi::Point3i _dim;
	int _dimension; // 0 : x, 1: y,  2:z
	int _coordinate;
public:
        IntersectCommand ( void ) ;
        ~IntersectCommand ( void ) ;
        bool init ( const mi::Argument& arg ) ;
        bool run  ( void );
        bool term ( void );
};
#endif //INTERSECT_COMMAND_HPP

