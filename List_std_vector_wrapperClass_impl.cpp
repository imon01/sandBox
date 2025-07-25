#include <vector>

#if defined( DEBUG )
#include <iostream>
#endif

template < typename T >
class List 
{
public:

    /**
     * 
     * Add type checking...
     * 
     */
    List () {}

    ~List()
    {
        for ( int i = 0; i < _vec.size(); i++ )
        {
            #if defined( DEBUG )
            std::cerr << " List::~List (freeing): " << _vec[ i ] << std::endl;
            #endif

            delete _vec[ i ];
            _vec[ i ] = nullptr;
        }
    }


    void push_back( T &t ) 
    {
        _vec.push_back( t );


        #if defined( DEBUG )
        std::cerr << " List::push_back (copy) (last item added): " << _vec[ _vec.size() -1 ] << std::endl;
        #endif
    }


    void push_back( T && t )
    {
        T tmp = t;
        _vec.push_back( std::move( tmp ) );
        t = nullptr;

        #if defined( DEBUG )
        std::cerr << " List::push_back (move) (last item added): " << _vec[ _vec.size() -1 ] << std::endl;
        #endif
    }

    template< typename... Args >
    void emplace_back ( Args&&... args )
    {
        _vec.emplace_back( std::forward<Args>( args )... );

        #if defined( DEBUG )
        std::cerr << " List::emplace_back (last item added): " << _vec[ _vec.size() -1 ] << std::endl;
        #endif
    }

    /*
    *
    * add more functions here
    * 
    */


private:
    std::vector < T > _vec;
};


int main()
{
    struct ObjSample
    {
        double a;
        int id;
        ObjSample() : _id(0) {}

        ObjSample( int id ): _id( id ) {}

    private:

        int _id;
    };


    List<ObjSample*> sampleList;

    ObjSample *obj1 = new ObjSample();
    ObjSample *obj22 = new ObjSample(22);


    sampleList.push_back( obj1 );
    sampleList.push_back( std::move( obj22 )) ;
    sampleList.emplace_back( new ObjSample() );
    sampleList.emplace_back( new ObjSample(777) );

    return 0;
}
