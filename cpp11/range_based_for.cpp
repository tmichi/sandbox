#include <iostream>
/**
 * Test code for range-based for loop
 */
class Point3i
{
public:
        int x;
        int y;
        int z;
public:
        Point3i ( const int x0 = 0, const int y0 = 0, const int z0 = 0 ) : x( x0 ), y( y0 ), z( z0 )
        {
                return;
        }

        Point3i ( const Point3i& p )
        {
                this->x = p.x;
                this->y = p.y;
                this->z = p.z;
                return;
        }

        Point3i operator = ( const Point3i& p )
        {
                this->x = p.x;
                this->y = p.y;
                this->z = p.z;
                return *this;
        }

        bool operator != ( const Point3i& that ) const
        {
                return this->x != that.x || this->y != that.y || this->z != that.z;
        }
};

std::ostream& operator << ( std::ostream& out, const  Point3i& p )
{
        out << p.x << " " << p.y << " " << p.z;
        return out;
}

class Range
{
public:

        class iterator
        {
        private:
                const Range& _range;
                Point3i _now;
        public:
                explicit iterator ( const Range& range, const bool isBegin ) : _range( range )
                {
                        this->_now  = range.getMin();
                        //end が指し示す位置は，(bmin.x, bmin.y, bmax.z+1)
                        if ( !isBegin ) this->_now.z = range.getMax().z + 1;
                }

                Point3i operator * ( void )
                {
                        return this->_now;
                }

                bool operator != ( const iterator& that )
                {
                        return this->_now != that._now;
                }

                iterator&
                operator++( void )
                {
                        this->step_forward();
                        return *this;
                }
        private :
                void step_forward( void )
                {
                        const Point3i bmin = this->_range.getMin();
                        const Point3i bmax = this->_range.getMax();

                        Point3i& pos = this->_now;
                        if ( bmax.z < pos.z ) return;

                        pos.x += 1;
                        if ( bmax.x < pos.x ) {
                                pos.x = bmin.x;
                                pos.y += 1;
                                if ( bmax.y < pos.y ) {
                                        pos.y = bmin.y;
                                        pos.z += 1;
                                }
                        }
                        return;
                }
        };
private:
        Point3i _bmin;
        Point3i _bmax;
public:
        Range ( const Point3i& bmin , const Point3i& bmax ) : _bmin ( bmin ) , _bmax( bmax )
        {
                return;
        }

        Point3i getMin( void ) const
        {
                return this->_bmin;
        }

        Point3i getMax( void ) const
        {
                return this->_bmax;
        }

        Range::iterator begin ( void )
        {
                return Range::iterator( *this, true );
        }

        Range::iterator end ( void )
        {
                return Range::iterator( *this, false );
        }
};

int main ( int argc, char** argv )
{
        Range range ( Point3i( -1, -1, -1 ), Point3i( 1, 1, 1 ) );

        for ( auto && p : range ) {
                std::cerr << p << std::endl;
        }
        /* for 文の場合こうなる 
        for ( Range::iterator p = range.begin() ; p != range.end() ; ++p ) {
                std::cerr << ( *p ) << std::endl;
        }
        */
        return 0;
}
