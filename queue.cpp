
#include "queue.h"


void queue::ensure_capacity( size_t c ) 
{
    if( current_capacity < c )
    {
        // New capacity will be the greater of c and
        // 2 * current_capacity.
        
        if( c < 2 * current_capacity )
            c = 2 * current_capacity;
        
        if( c < 8 )
            c = 8;
        
        double* newdata = new double[c];
        for( size_t s = 0; s < current_size; ++ s )
        {
            newdata[s] = data[ begin ];
            begin = next( begin );
        }
        
        current_capacity = c;
        begin = 0;
        end = current_size;
        
        delete[] data;
        data = newdata;
    }
}

queue::queue():
current_capacity{5},
current_size{0},
begin{0},
end{0},
data{new double[5]}
{
}

queue::queue( const queue& q ):
current_capacity{q.current_capacity},
current_size{q.current_size},
begin{q.begin},
end{q.end}
{
    data = new double[current_capacity];
    
    size_t j = q.begin;
    
    for(size_t i = 0; i < current_size; i++){
        
        data[j] = q.data[j];
        
        j = next(j);
    }
    
}

queue::~queue()
{
    delete [] data;
}

const queue& queue::operator=(const queue& q)
{
    ensure_capacity(q.current_capacity);
    
    current_size = q.size();
    
    begin = q.begin;
    
    end = q.end;
    
    size_t j = q.begin;
    
    for(size_t i = 0; i < current_size; i++){
        
        data[j] = q.data[j];
        
        j = next(j);
    }
    
    return q;
}

queue::queue( std::initializer_list<double> init ):
current_capacity{init.size()},
current_size{0},
begin{0},
end{0},
data{new double[current_capacity]}
{
    for (double d : init)
    {
        push(d);
    }
}


void queue::push(double d)
{
    ensure_capacity(current_size+1);
    data[end] = d;
    end = next(end);
    ++current_size;
}

void queue::pop()
{
    begin = next(begin);
    --current_size;
}

void queue::clear()
{
    current_size = 0;
    begin = 0;
    end = 0;
}

double queue::peek() const
{
    return data[begin];
}




void queue::printfields( std::ostream& out ) const
{
    out << "   current_size =     " << current_size << "\n";
    out << "   current_capacity = " << current_capacity << "\n";
    out << "   begin =            " << begin << "\n";
    out << "   end =              " << end << "\n";
}

void queue::checkinvariant( ) const 
{
    
    if( current_capacity == 0 )
    {
        std::cout << "current capacity == 0\n";
        printfields( std::cout );
        std::abort( );
    }
    
    if( begin >= current_capacity )
    {
        std::cout << "begin >= current_capacity\n";
        printfields( std::cout );
        std::abort( );
    }
    
    if( end >= current_capacity )
    {
        std::cout << "end >= current_capacity\n";
        printfields( std::cout );
        std::abort( );
    }
    
    if( current_size > current_capacity )
    {
        std::cout << "current_size > current_capacity\n";
        printfields( std::cout );
        std::abort( );
    }
    
    if( ( begin + current_size ) % current_capacity != end )
    {
        std::cout <<
        "distance between begin and end does not fit to current_size\n";
        printfields( std::cout );
        std::abort( );
    }
}



// It's a present for you:

std::ostream& operator << ( std::ostream& out, const queue& q )
{
    out << "[";
    size_t i = q. begin;
    for( size_t s = 0; s < q. size( ); ++ s )
    {
        if(s) out << ", ";
        else out << " ";
        out << q. data[i];
        
        i = q.next(i);
    }
    out << " ]";
    return out;
}

