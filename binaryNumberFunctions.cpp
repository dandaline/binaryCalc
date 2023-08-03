/**
 * @file binaryNumberFunctions.cpp
 * @author Laila Staschenuk
 * @version 0.1
 * @date 2021-02-17
 */
#include "binaryNumber.hpp"
#include "binaryExceptions.hpp"

BinaryNumber::BinaryNumber() 
{
    bNumber.clear();
}

BinaryNumber::BinaryNumber( const std::vector<bool>& setBNumber ) 
{
    bNumber = setBNumber;
}   


BinaryNumber::BinaryNumber( const BinaryNumber& source ) 
{
    bNumber = source.bNumber;
}

BinaryNumber::~BinaryNumber() { }

void BinaryNumber::fill( const size_t& n, const bool& bit ) 
{
    bNumber.clear();
    for( size_t i = 0; i < n; i++)
    {
        bNumber.push_back( bit );
    }
}

void BinaryNumber::out() 
{
    for( size_t i = 0; i < bNumber.size(); i++ )
    {
        std::cout << bNumber.at(i);
    }
    std::cout << std::endl;
}

std::string BinaryNumber::out_table()  
{
    std::string tableBNumber;
    for(size_t i = 0; i < bNumber.size(); i++ )
    {
        if( bNumber.at(i) == true )
        {
            tableBNumber.push_back( '1' );
        }
        else if( bNumber.at(i) == false )
        {
            tableBNumber.push_back( '0' );
        }
    }
    return tableBNumber;
}

bool BinaryNumber::get_at(size_t i) const
{
    {
        return bNumber.at(i);
    }
}

BinaryNumber BinaryNumber::parity(const BinaryNumber& parity)
{
    BinaryNumber result;
    size_t trueCounter = 0;
    for( size_t i = 0; i < parity.bNumber.size(); i++)
    {
        if ( parity.get_at(i) == true )
        {
            trueCounter++;
        }
    }
    result.fill( trueCounter, true );
    return result;
}

unsigned long long int BinaryNumber::convert_to_decimal() const
{
    unsigned long long int result = 0;
    int exponent = 0;
    for( size_t i = bNumber.size(); i-- > 0; )
    {
        result += static_cast<unsigned long long int>( ( bNumber.at(i) * pow(2, exponent) ) );
        exponent++;    
    }
    return result;
} 

BinaryNumber BinaryNumber::concatenate(const BinaryNumber& lhs, const BinaryNumber& rhs)
{
    BinaryNumber result;
    result = lhs;
    for( size_t i = 0; i < rhs.bNumber.size(); i++ )
    {
        result.bNumber.push_back( rhs.bNumber.at(i) );
    }
    return result;
}

BinaryNumber BinaryNumber::operator/ ( BinaryNumber divisor ) //catch exceptions for zero
{
    BinaryNumber dividend = this->bNumber;  // 1.
    BinaryNumber quotient;
    BinaryNumber dummyFalse;
    dummyFalse.fill( 0, false );
    if( divisor == dummyFalse )
    {
        throw Error( "ERROR: only god can divide by 0!");
    }
    else if( dividend < divisor )                // 2.
    {
        std::cout << "remainder = ";
        dividend.out();
        quotient.fill( 1, false );
        return quotient;
    }
    else if( dividend == divisor )
    {
        quotient.fill( 1, true );
        return quotient;
    }
    else
    {
        while( divisor.get_at(0) == false ) // 3.
        {
            divisor.bNumber.erase(divisor.bNumber.cbegin());
        }
        while( dividend.bNumber.size() < divisor.bNumber.size() ) //4.
        {
            dividend.bNumber.insert(dividend.bNumber.cbegin(), false );
        }


        BinaryNumber subDividend;
        BinaryNumber subQuotient;
        BinaryNumber subtrahend;
        size_t dividendPosition = 0;
        for(size_t i = 0; i < divisor.bNumber.size(); i++) //5.
        {
            subDividend.bNumber.push_back( dividend.bNumber.at(i) );
            dividendPosition++;
        }
        while( dividendPosition < dividend.bNumber.size() + 1) 
        { 
            if( subDividend > divisor )                     //6. 
            {
                quotient.bNumber.push_back( true );         //7.
                subQuotient.fill(divisor.bNumber.size(), true);
            }
            else if( subDividend == divisor )               //6. 
            {
                quotient.bNumber.push_back( true );         //7.
                subQuotient.fill(divisor.bNumber.size(), true);
            }
            else if( subDividend < divisor )                //6. 
            {
                quotient.bNumber.push_back( false );        //7.
                subQuotient.fill(divisor.bNumber.size(), false);
                
            }

            subtrahend = subQuotient & divisor;             //8.
            subDividend = subDividend - subtrahend;         //9.
            
            if(dividend.bNumber.size() > dividendPosition ) //10. 
            {
                subDividend.bNumber.push_back( dividend.bNumber.at( dividendPosition ) ); //get next number from dividend to subDividend
                dividendPosition++;
            }
            else
            {
                dividendPosition++; //exceeds while loop after this increase -> returns quotient
            }
        }                                                   //11.
            std::cout << "remainder = ";                    //12.
            subDividend.out();                      
            return quotient;                                //13.
    }
}

 BinaryNumber BinaryNumber::operator- (BinaryNumber rhs) 
{
    BinaryNumber lhs = this->bNumber; //just for comparison purposes
    if( lhs > rhs || lhs == rhs ) //if negative result, throw exception //1.
    {
        BinaryNumber result;
        while( this->bNumber.size() < rhs.bNumber.size()  )             //2.
        {
            this->bNumber.insert( this->bNumber.cbegin(), false );
        }
        while( this->bNumber.size() > rhs.bNumber.size()  ) //adds "false" to subtrahend to match size of minuend
        {
            rhs.bNumber.insert( rhs.bNumber.cbegin(), false );
        }

        for( size_t i = rhs.bNumber.size(); i-- > 0; )                  //3.
        {
            if( this->get_at(i) == rhs.get_at(i) )      //1 - 1 OR 0 - 0
            {
                result.bNumber.insert( result.bNumber.cbegin(), false );
            }
            else if( this->get_at(i) > rhs.get_at(i) )  //1 - 0
            {
                result.bNumber.insert( result.bNumber.cbegin(), true );
            }
            else if( this->get_at(i) < rhs.get_at(i) )  //0 - 1         //4.
            {
                size_t i2 = 1;
                while( this->get_at(i - i2 ) != true )                  //5. 
                {
                    this->bNumber.at(i - i2) = true;
                    i2++;
                }
                this->bNumber.at( i - i2 ) = false;                     //6.
                result.bNumber.insert( result.bNumber.cbegin(), true );
            }                                                      
        }                                                               //7.
        return result;
    }
    else
    {
        throw Error("ERROR: negative results are not enabled for this operation");
    }
}

bool BinaryNumber::operator> ( const BinaryNumber& rhs )
{
    if( this->convert_to_decimal() > rhs.convert_to_decimal() )
    {
        return true;
    }
    return false;
}

bool BinaryNumber::operator< ( const BinaryNumber& rhs )
{
    if( this->convert_to_decimal() < rhs.convert_to_decimal() )
    {
        return true;
    }
    return false;
}

bool BinaryNumber::operator== ( const BinaryNumber& rhs )
{
    if( this->convert_to_decimal() == rhs.convert_to_decimal() )
    {
        return true;
    }
    return false;
}

bool BinaryNumber::operator!= ( const BinaryNumber& rhs )
{
    if( this->convert_to_decimal() != rhs.convert_to_decimal() )
    {
        return true;
    }
    return false;
}

void BinaryNumber::operator= (const BinaryNumber& rhs )
{
    this->bNumber.clear();
    for( size_t i = 0; i < rhs.bNumber.size(); i++ )
    {
        bNumber.push_back( rhs.get_at(i) );
    }
}

BinaryNumber BinaryNumber::operator!()
{
    bNumber.flip();
    return bNumber;
}

BinaryNumber BinaryNumber::operator& ( BinaryNumber rhs ) 
{
    BinaryNumber result;
    while( this->bNumber.size() > rhs.bNumber.size() ) //make both numbers the same bit size
    {
        rhs.bNumber.insert( rhs.bNumber.cbegin(), false );
    }
    while( this->bNumber.size() < rhs.bNumber.size() )
    {
        this->bNumber.insert(this->bNumber.cbegin(), false );
    }

    for( size_t i = 0; i < rhs.bNumber.size(); i++ )
    {
        result.bNumber.push_back( this->get_at(i) & rhs.get_at(i) );
    }
    return result;
}

BinaryNumber BinaryNumber::operator| ( BinaryNumber rhs )
{
    BinaryNumber result;
    while( this->bNumber.size() > rhs.bNumber.size() ) //make both numbers the same bit size
    {
        rhs.bNumber.insert( rhs.bNumber.cbegin(), false );
    }
    while( this->bNumber.size() < rhs.bNumber.size() )
    {
        this->bNumber.insert(this->bNumber.cbegin(), false );
    }
    
    for( size_t i = 0; i < rhs.bNumber.size(); i++ )
    {
        result.bNumber.push_back( this->get_at(i) | rhs.get_at(i) );
    }
    return result;
}






