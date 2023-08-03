/**
 * @file binaryNumber.hpp
 * @author Laila Staschenuk
 * @version 0.1
 * @date 2021-02-17
 */

#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <exception>

/**
 * @class BinaryNumber
 * @brief a class to represent a binary digit system
 * @details An object of this class (here referred to as "binary" - see glossary in binaryMain.cpp)
 * holds true and false boolean statements in std::vector<bool> bNumber.
 * This is the only private datatype of the class. All binaries are held in std::vector<BinaryNumber> data,
 * declared at the beginning of int main(). The operations applied here can be used idependently of the digit size /// A!
 * of the binaries, since the respected operations match size automatically, i.e. operator& . 
 */
class BinaryNumber
{
    public:
    /**
     * @brief Construct a new BinaryNumber object, standard constructor 
     */
    BinaryNumber();

    /**
     * @brief Construct a new BinaryNumber object, parameterized constructor
     * @param setBNumber > true and false statements assigned to bNumber
     */
    BinaryNumber(const std::vector<bool>& setBNumber);  

    /**
     * @brief Construct a new BinaryNumber object, copy constructor
     * @param source > copies and assigns booleans from one binary to another
     */
    BinaryNumber(const BinaryNumber& source);

    /**
     * @brief Destroy the BinaryNumber object
     */
    ~BinaryNumber();

    /**
     * @brief assignes (n * bit) to bNumber
     * @details I realy don't know what to add
     * @param n > how many bits should this binary contain?
     * @param bit > type of bit, either false or true?
     */
    void fill(const size_t& n, const bool& bit );

    /**
     * @brief displays binary in a line in terminal
     * @details uses for loop to output each bit in the console with std::endl at the end, 
     * faster option to test code
     */
    void out();

    /**
     * @brief special case for console output of binary
     * @details used by menu option (d show data in memory), 
     * function: void data_out( std::vector<BinaryNumber>& dataOut ) for proper presentation
     * in data table using std::setw(). 
     * @return std::string > is used by data_out( std::vector<BinaryNumber>& dataOut ) in binaryMenu.hpp
     */
    std::string out_table();

    /**
     * @brief what bit at position i
     * @details returns single bit at position i in bNumber, necessery for operands
     * @param i > index in bNumber of binary
     * @return true bit of bNumber
     * @return false bit of bNumber
     */
    bool get_at(size_t i) const;

    /**
     * @brief counts true in binary /// A!
     * @details returns a new binary consisting of the true bits of the passed binary, 
     * @param parity the binary to perform true counting with
     * @return BinaryNumber new binary made up only of true bits
     */
    BinaryNumber parity(const BinaryNumber& parity);

    /**
     * @brief converts a binary to decimal /// A!
     * @details calculation: (bit * 2 ^ n) + (bit * 2 ^ n+1) + ... + (bit * 2 ^ N), 
     * n is increased by 1 for every iteration of the for loop running backwards,
     * performs loop to bits in bNumber,
     * maximum displayable decimal number = 18446744073709551615.
     * @return unsigned long long int decimal number as result
     */
    unsigned long long int convert_to_decimal() const;

    /**
     * @brief concatenates two binaries to a new one /// A!
     * @details lhs is assigned to result, than rhs is "pushed back" on to result,
     * result is returned a new binary
     * @param lhs > assigned to result
     * @param rhs > added to result via .push_back()
     */
    BinaryNumber concatenate(const BinaryNumber& lhs, const BinaryNumber& rhs);

    /**
     * @brief divides one binary by another /// A!
     * @details implementation of written division on two binaries
     * 1. checking for error
     * 2. checking for results that don't require application of division
     * 3. truncation of all false bits in divisor for
     * 4. adding false bits to dividend to match number of digits of divisor
     *    3. and 4. enable divisions of binaries given any length of digits/// /// A! ///    
     * 5. matches subDividend digits to divisor for first sub division operation
     * 6. applies relational comparison to subDividend and divisor
     * 7. assignes result to quotient (end result) and result * digits of divisor to subQuotient
     * 8. AND operation performed with divisor and subQuotient to generate subtrahent
     * 9. subtrahend is subtracted from subDividend for new subDividend (operation performed in seperate function operator-)
     *    subDividend is now the remainder to perform next relational comparison
     * 10. next digit of dividend is added to subDivisor
     * 11. operation is looped starting at 6. step after first iteration until last digit
     * 12. subDividend will be outputted as remainder in console (will not be retunred at binary)
     * 13. quotient will be returned as new binary as end result
     * @param divisor > rhs of the equation
     * @return BinaryNumber binary without remainder, remainder outputted solely over console
     * @pre !(divisor == 0)
     * @throw ERROR: only god can divide by 0!""
     */
    BinaryNumber operator/ ( BinaryNumber divisor );


    /**
     * @brief subtracts one binary from another /// A! needed for division
     * @details implementation of written subtraction
     * 1. checks for positive or equal result, if false, throws exception
     * 2. adds false digits to both binaries to match size
     * 3. starts reversed loop and applies relational comparison
     * 4. in case of 0 - 1, get next 1 from a higher digit in minuend, 
     * 5. flip all false on the way (quasi (true, false) on one digit), there must be a next true due to initial comparison in function
     * 6. flip the found true to false
     * 7. repeat operation from point 3 on until last digit
     * @param rhs > subtrahend of lhs binary (minuend)
     * @return BinaryNumber (positive) difference returned as new binary
     * @pre ( lhs > rhs || lhs == rhs )
     * @throw if( lhs < rhs ) "ERROR: negative results are not enabled for this operation" (because it was only intended to be used within the division overload)
     */
    BinaryNumber operator- (BinaryNumber rhs);  

    /**
     * @brief bigger than operation /// A!
     * @details converts both binaries to decimal and compares
     * @param rhs > binary
     * @return true if assumed relation holds true
     * @return false if assumed relation is false
     */
    bool operator> ( const BinaryNumber& rhs );

    /**
     * @brief smaller than operation /// A!
     * @details converts both binaries to decimal and compares
     * @param rhs > binary
     * @return true if assumed relation holds true
     * @return false if assumed relation is false
     */
    bool operator< ( const BinaryNumber& rhs );

    /**
     * @brief qual to operation /// A!
     * @details converts both binaries to decimal and compares
     * @param rhs > binary
     * @return true if assumed relation holds true
     * @return false if assumed relation is false
     */
    bool operator== ( const BinaryNumber& rhs );

    /**
     * @brief NOT equal to operation /// A!
     * @details converts both binaries to decimal and compares
     * @param rhs > binary
     * @return true if assumed relation holds true
     * @return false if assumed relation is false
     */
    bool operator!= ( const BinaryNumber& rhs );
    
    /**
     * @brief assigned rhs binary to lhs binary
     * @details clears bNumber of lhs first, than uses for loop to assign rhs to lhs 
     * @param rhs > binary which is assigned to lhs of =  
     */
    void operator= (const BinaryNumber& rhs );

    /**
     * @brief NOT operation /// A!
     * @details applies .flip() member function of std::vector<bool> to bNumber
     * @return BinaryNumber with flipped bits as new binary
     */
    BinaryNumber operator!();

    /**
     * @brief AND operation /// A!
     * @details performs AND digit by digit from front to back, after matching digit size
     * @param rhs > binary to perform AND with lhs 
     * @return BinaryNumber new binary
     */
    BinaryNumber operator&( BinaryNumber rhs );
    
    /**
     * @brief OR operation /// A!
     * @details performs OR digit by digit from front to back, after matching digit size
     * @param rhs > binary to perform OR with lhs
     * @return BinaryNumber 
     */
    BinaryNumber operator|( BinaryNumber rhs );

    private:
    /**
     * @brief vector holding the true and false bits of a binary /// A!
     */
    std::vector<bool> bNumber;

    //friend functions to read and write directly to and from BinaryNumber
    friend void operator>>( const std::string& console, std::vector<BinaryNumber>& daten );
    friend std::istream& operator>>( std::istream& in, BinaryNumber &obj );
    friend std::ostream& operator<< ( std::ostream& out, BinaryNumber obj );
    
    
};


