#include "Iso2dCommand.hpp"

template<typename T>
static int executeIso2dCommand ( mi::Argument &arg )
{
        Iso2dCommand<T> cmd;
        return mi::CommandTemplate::execute( cmd,arg );
}
int main ( int argc, char** argv )
{
        mi::Argument arg( argc, argv );
        if      ( arg.exist ( "-char" )   ) return executeIso2dCommand<char> ( arg );
        else if ( arg.exist ( "-uchar" )  ) return executeIso2dCommand<unsigned char> ( arg );
        else if ( arg.exist ( "-short" )  ) return executeIso2dCommand<short> ( arg );
        else if ( arg.exist ( "-ushort" ) ) return executeIso2dCommand<unsigned short> ( arg );
        else if ( arg.exist ( "-int" )    ) return executeIso2dCommand<int> ( arg );
        else if ( arg.exist ( "-uint" )   ) return executeIso2dCommand<unsigned int> ( arg );
        else if ( arg.exist ( "-float" )  ) return executeIso2dCommand<float> ( arg );
        else if ( arg.exist ( "-double" ) ) return executeIso2dCommand<double> ( arg );
        else  {
                std::cerr << "voxel type was not specified. short is selected as default."<<std::endl;
                return executeIso2dCommand<short> ( arg );
        }

}
