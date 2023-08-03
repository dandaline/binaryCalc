/**
 * @file binaryMain.cpp
 * @author Laila Staschenuk
 * @version 0.1
 * @date 2021-02-17
 */

/**
 * Documentation Glossary 
 * binary - will ALWAYS refer to an object of the class "BinaryNumber"
 * data - will ALWAYS refer to the single vector in which ALL binaries are stored, declared in "int main()
 * A! - a part of the assignment is solved here
 */

#include "binaryMenu.hpp"

int main()
{
    try
    {
        std::vector<BinaryNumber> data;  // data vector to which all binaries will be stored this is the "memory" of this program
        char choice = 'b';
        main_menu( choice, data );
        while( choice > 'q' || choice < 'q' )
        {
            main_menu( choice, data );
        }      
    }catch(...){
        std::cout << "ERROR: unknown" << std::endl;
    }
}
