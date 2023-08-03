/**
 * @file binaryMenu.hpp
 * @author Laila Staschenuk
 * @version 0.1
 * @date 2021-02-17
 */

#pragma once

#include "binaryNumber.hpp"
#include "binaryExceptions.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <exception>

/**
 * @brief MAIN MENU is called after declaration of "std::vector<BinaryNumber> data" in int main() 
 * @details User Interface of MAIN MENU CALCULATE. Presented first to the user after program start. User may select: (1 load & save)
 * (2 input & erase) (3 calculate) (d show data in memory) (q quit) via typing the character
 * into the console. Main menu uses while loops to keep itself and the three sub menues running. The 'b' options from the other three menues
 * have their termination cases defined here by while loops. By selecting 'q' the last while loop (in int main()) of the program will be terminated, 
 * resulting into controlled termination of the program.
 * @param c > user choice of menu option - here to acess the three sub menues
 * @param data > data is passed through every menu - here to distribute it from int main() to all sub menues, data is always passed
 * as a reference for every menu function is enabled to modulate the same data
 */
void main_menu( char& c, std::vector<BinaryNumber>& data );

/**
 * @brief displays every binary in data 
 * @details Outputs ALL data in memory to console. Can be displayed by entering 'd' in main menu and all 3 sub menus.
 * 3 columns: DATA (binary), INDEX (index for data excess), DECIMAL (conversion from binary system to decimal).
 * @param dataOut > data containing each binary
 */
void data_out( std::vector<BinaryNumber>& dataOut );

/**
 * @brief checks if any binaries are stored in data
 * @details Checks via std::vector.empty() if any binaries are stored in data. If empty is true, an Error is thrown
 * to the user during runtime. Enables and disables Menu options like erase. If empty, there is nothign to erase
 * @param dataE > data is passed through every menu - here to allow checking empty for std::vector<BinaryNumber> data
 * @pre empty() == true, no access to data, error is thrown
 * @throw "ERROR: no binaries found in data!"
 */
void isEmpty( const std::vector<BinaryNumber>& dataE );

/**
 * @brief checks if user input is a valid index for data
 * @details user input to access data needs to be checked for size of vector in ordner to prevent wrong access. 
 * Stopps process, if index > dataNoIndex
 * @param index > passed user input to check valid index access
 * @param dataNoIndex > to measure size of data
 * @pre ( index > dataNoIndex.size() ) == true, throws error
 * @throw "ERROR: no index in vector data!"
 */
void noIndex( const size_t& index, const std::vector<BinaryNumber>& dataNoIndex );

/**
 * @brief MENU LOAD & SAVE 
 * @details User Interface of sub menu LOAD & SAVE. User may select: (1 load from binaryIn.txt)
 * (2 save to binaryOut.txt) (d show data in memory) (b back) via typing the character
 * into the console. 
 * @param c1 > user choice for main menu options
 * @param data > data is passed through every menu - here to enable load to, save from, and show data
 * @pre > c == '1'
 */
void menuLoadSave( char& c1, std::vector<BinaryNumber>& data );

/**
 * @brief reads a binary from the first line of an external .txt file and adds
 * it to the end of data 
 * @details The first line of the .txt file will be copied to a string. Next this string will be read out 
 * by a for loop, converting only '0' and '1' to false and true respectivly. Other characters 
 * will be ignored. These bits will be stored in a binary. Returns an input stream containing the 
 * bits of the binary.
 * @param in > contains the input stream to the .txt file per line
 * @param obj > binary being filled with false and true bits by "in"
 * @return std::istream& > input stream containing bits of a binary
 */
std::istream& operator>>( std::istream& in, BinaryNumber &obj );

/**
 * @brief Uses overloaded >> operator in a loop to store each line of .txt file in data  /// A! 
 * @details Uses prior declard function "std::istream& operator>>( std::istream& in, BinaryNumber &obj )" 
 * in a loop to read every line of the .txt file until the end. Each valid "in" enables 
 * to store a binary to data.
 * @param in > contains the input stream to the .txt file per line
 * @param dataLoad > data to which each binary will be stored
 */
void file_in( std::istream& in, std::vector<BinaryNumber>& dataLoad );

/**
 * @brief the bits of a binary are converted to an output stream 
 * @details Converts false and true of a binary to '0' and '1' using a loop to go throug each
 * digit of the binary. Than saves each character to a string which will be outputted to the
 * return output stream.
 * @param out > contains the output stream to "binaryOut.txt" 
 * @param obj > binary from which false and true are read
 * @return std::ostream& > output stream containing only '0' and '1'
 */
std::ostream& operator<< ( std::ostream& out, BinaryNumber obj );

/**
 * @brief Writes entire data to "binaryOut.txt" us  /// A! 
 * @details Uses "std::ostream& operator<< ( std::ostream& out, BinaryNumber obj )" in loop 
 * to write each binary into one line respectivley of "binaryOut.txt".
 * @param out > contains the output stream of a single binary
 * @param dataSave > data holding all binaries in memory
 */
void file_out( std::ofstream& out, std::vector<BinaryNumber>& dataSave );

/**
 * @brief INPUT & ERASE 
 * @details User Interface of sub menu INPUT & ERASE. User may select: (1 input binary Number) (2 erase binary Number)
 * (3 erase entire memory) (d show data in memory) (b back) via typing the character
 * into the console.
 * @param c2 > user choice of menu option
 * @param data > data is passed through every menu - here to enable input and erase with indices
 * @pre > c == '2'
 */
void menuInputErase( char& c2, std::vector<BinaryNumber>& data );

/**
 * @brief reads a binary from a string and adds it to the end of data 
 * @details The string is passed through a for loop in which only characters of '0' and '1' trigger 
 * an operation, converting them into false and true. The operation adds these conversions 
 * to an instance of a binary. This binary will be added to the end of data after the
 * entire string ran through the for loop.
 * @param console > contains console user input which was assigned via std::cin to a string in prior
 * @param dataCons > binary will be added to the end of data
 * @throw "ERROR: something other than 1 or 0 was entered!"
 */
void operator>>( const std::string& console, std::vector<BinaryNumber>& dataCons );

/**
 * @brief Erases binary of index i in data  
 * @details User can select index to delete coresponding binary in data.
 * program craches with "zsh: segmentation fault ./binaryMain"
 * @param dataErase > all binaries are stored in this vector
 * @pre dataErase must contain at least one binary
 * @throw "ERROR: invalid user input, must be number!"
 */
void index_erase( std::vector<BinaryNumber>& dataErase );

/**
 * @brief erases every binary in data
 * @details Uses .clear() member function of std::vector to erase entire memory
 * @param dataEraseAll > data is passed through every menu - here to enable erase entire memory
 * @pre dataEraseAll must contain at least one binary
 */
void erase_all( std::vector<BinaryNumber>& dataEraseAll);



/**
 * @brief MENU CALCULATE  /// A! 
 * @details User Interface of sub menu CALCULATE. User may select: (1 logical, relational, division & subtraction) 
 * (2 NOT on one number) (3 concatenate) (4 parity) (d show data in memory) (b back) via typing the character
 * into the console. Menu contains switch cases for the calculations (menuCalculateCase 1-4 ) - Contains try/catch blocks for each
 * @param c3 > user choice of menu options
 * @param data > data is passed through every menu - here to enable automatic saving of binary result
 * @pre c == '3'
 */
void menuCalculate( char& c3, std::vector<BinaryNumber>& data );

/**
 * @brief MENU CALCULATE BINARY OPERANDS all binary and unary operations can be applied to two binaries in data  /// A! 
 * @details User inputs indices of two binaries from data, user may use NOT on each binary respectively.
 * Next user may choose from the following operations: (& AND) (| OR) (< smaller than) (> bigger than) 
 * (1 equal to (==) ) (0 not equal to (!=) (/ division) (- subtraction). After operation is choosen, calculation
 * will run and a result will be returned. The result will be stored in data after EVERY execution of the function.
 * @param dataCase1 > data is passed through every menu - here to enable automatic saving of binary result
 * @pre > dataCase2 has to contain at least one binary
 * @throw "ERROR: invalid user input, must be number!"
 */
void menuCalculateCase1( std::vector<BinaryNumber>& dataCase1 );

/**
 * @brief MENU CALCULATE NOT SINGLE operator NOT applied to a single binary  /// A! 
 * @details User may choose a single binary via index from data.
 * The (! NOT) operator may be used on a single binary. Result will be automatically stored to data.
 * @param dataCase2 > data is passed through every menu - here to enable automatic saving of binary result
 * @pre dataCase2 has to contain at least one binary
 * @throw "ERROR: invalid user input, must be number!"
 */
void menuCalculateCase2( std::vector<BinaryNumber>& dataCase2 );

/**
 * @brief MENU CALCULATE CONCATENATION concatenates one binary to another  /// A!  
 * @details User may choose two binaries via index from data. The second binary will be added to the end of the first.
 * This results into a new binary stored in data.
 * @param dataCase3 > data is passed through every menu - here to enable automatic saving of binary result
 * @pre data must contain at least one binary
 * @throw "ERROR: invalid user input, must be number!"
 */
void menuCalculateCase3( std::vector<BinaryNumber>& dataCase3 );

/**
 * @brief MENU CALCULATE PARITY counts only the true bits of a binary  /// A! 
 * @details User may choose one binary from data, of which only the true bits are counted and summed up into a new benary.
 * The result will be stored in data.
 * @param dataCase4 > data is passed through every menu - here to enable automatic saving of binary result
 * @pre data must contain at least one binary 
 * @throw "ERROR: invalid user input, must be number!"
 */
void menuCalculateCase4( std::vector<BinaryNumber>& dataCase4 );





