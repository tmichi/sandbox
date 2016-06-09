#include "IntersectCommand.hpp"

template<typename T>
static int executeIntersectCommand ( mi::Argument &arg )
{
        IntersectCommand<T> cmd;
        return mi::CommandTemplate::execute( cmd,arg );
}
int main ( int argc, char** argv )
{
        mi::Argument arg( argc, argv );
        if      ( arg.exist ( "-char" )   ) return executeIntersectCommand<char> ( arg );
        else if ( arg.exist ( "-uchar" )  ) return executeIntersectCommand<unsigned char> ( arg );
        else if ( arg.exist ( "-short" )  ) return executeIntersectCommand<short> ( arg );
        else if ( arg.exist ( "-ushort" ) ) return executeIntersectCommand<unsigned short> ( arg );
        else if ( arg.exist ( "-int" )    ) return executeIntersectCommand<int> ( arg );
        else if ( arg.exist ( "-uint" )   ) return executeIntersectCommand<unsigned int> ( arg );
        else if ( arg.exist ( "-float" )  ) return executeIntersectCommand<float> ( arg );
        else if ( arg.exist ( "-double" ) ) return executeIntersectCommand<double> ( arg );
        else  {
                std::cerr << "voxel type was not specified. short is selected as default."<<std::endl;
                return executeIntersectCommand<short> ( arg );
        }

}
