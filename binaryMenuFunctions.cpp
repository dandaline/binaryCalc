/**
 * @file binaryMenuFunctions.cpp
 * @author Laila Staschenuk
 * @version 0.1
 * @date 2021-02-17
 */

#include "binaryMenu.hpp"

void main_menu( char& c, std::vector<BinaryNumber>& data ) //Main menu, initially displayed in console
{
    std::cout << "------------- BINARY NUMBERS ------------ \n";
    std::cout << "--------------- MAIN MENU --------------- \n";
    std::cout << "select option: (1 load & save) (2 input & erase) (3 calculate) (d show data in memory) (q quit)\n: ";
    std::cin >> c;
    switch( c )
    {
        case 'q': //quit program
        {
            std::cout << "--------------- GOOD BYE ---------------" << std::endl;
        }
        break;

        case '1': //load & save
        {
            char choice1;
            menuLoadSave( choice1, data );
            while( choice1 > 'b' || choice1 < 'b' )
            {
                menuLoadSave( choice1, data );
            }
        }
        break;

        case '2': //input & erase
        {
            char choice2;
            menuInputErase( choice2, data );
            while( choice2 > 'b' || choice2 < 'b' )
            {
                menuInputErase( choice2, data );
            }
        }
        break;

        case '3': //calculate
        {
            char choice3;
            menuCalculate( choice3, data );
            while( choice3 > 'b' || choice3 < 'b')
            {
                menuCalculate( choice3, data );
            }
        }
        break;

        case 'd': //data to terminal
        {
            data_out( data );
        }
        break;

        default: //other than above was selected
        std::cout << "ERROR: no menu option found! please select an option displayed below" << std::endl;
        break;
        }
}

void data_out( std::vector<BinaryNumber>& dataOut ) //display data in terminal
{
    std::cout << std::setw(64) << "DATA" << std::setw(8) << "INDEX" << std::setw(23) << "DECIMAL" << std::endl;
    for(size_t i = 0; i < dataOut.size(); i++)
    {
        std::cout << std::setw(64) << dataOut.at(i).out_table();
        std::cout << std::setw(8) << i ;
        std::cout << std::setw(23) << dataOut.at(i).convert_to_decimal() << std::endl;
    }
}

void isEmpty(const std::vector<BinaryNumber>& dataE ) //checks empty vector
{
    if( dataE.empty() )
    {
        throw Error( "ERROR: no binaries found in data!" );
    }
}


void noIndex( const size_t& index, const std::vector<BinaryNumber>& dataNoIndex ) //checks allowed index for vector
{
    if( index > dataNoIndex.size() )
    {
        throw Error( "ERROR: no index in vector data!" );
    }
}

void menuLoadSave( char& c1, std::vector<BinaryNumber>& data ) //load & save( to files binaryIn.txt and binaryOut.txt )
{
    std::cout << "--------------- load & save ---------------" << std::endl;
    std::cout << "select option: (1 load from .txt file) (2 save to .txt file) (d show data in memory) (b back)" << std::endl;
    std::cin >> c1;
    switch( c1 )
    {
        case 'b':{} //back to main menu
        break;

        case '1': //load file
        {
            std::string fileNameIn;
            std::cout << "input file name including .txt extention: ";
            std::cin >> fileNameIn;
            std::ifstream inFile( fileNameIn );
            file_in( inFile, data );
            data_out( data );
        }
        break;

        case '2': //save file
        {
            std::string fileNameOut;
            std::cout << "input file name including .txt extention: ";
            std::cin >> fileNameOut;
            std::ofstream outFile( fileNameOut );
            file_out(outFile, data);
            std::cout << "...complete, check directory of binaryMain" << std::endl;
        }
        break;

        case 'd': //data to terminal
        {
            data_out( data );
        }
        break;

        default: //other than above was selected
        {
            std::cout << "ERROR: no menu option found! please select an option displayed below" << std::endl;
        }
        break;

    }
}

std::istream& operator>>( std::istream& in, BinaryNumber &obj ) //File input single line
{
    std::string temp;
    std::getline (in, temp);
    for( size_t i = 0; i < temp.size(); i++ )
    {
        if( temp.at(i) == '0' )
        {
            obj.bNumber.push_back( false );
        }
        else if( temp.at(i) == '1' )
        {
            obj.bNumber.push_back( true );
        }
    }
    return in;
}

void file_in( std::istream& in, std::vector<BinaryNumber>& dataLoad ) //File Input all lines
{
    while( in ) 
    {
        BinaryNumber d;
        in >> d; 
        if( in )
        {
            dataLoad.push_back( d );
        }
    }
}

std::ostream& operator<< ( std::ostream& out, BinaryNumber obj ) //File out single line
{
    std::string temp;
    for( size_t i = 0; i < obj.bNumber.size(); i++ )
    {
        if( obj.bNumber.at(i) == false )
        {
            temp.push_back( '0' );
        }
        else if( obj.bNumber.at(i) == true )
        {
            temp.push_back( '1' );
        }
    }
    out << temp;
    return out;
}


void file_out( std::ofstream& out, std::vector<BinaryNumber>& dataSave ) //File out all binaries to lines
{
    for(size_t i = 0; i < dataSave.size(); i++ )
    {
        out << dataSave.at(i);
        out << '\n';
    }
}

void menuInputErase( char& c2, std::vector<BinaryNumber>& data ) //input & erase ( to and from data)
{   
    std::cout << "--------------- input & erase ---------------" << std::endl;
    std::cout << "select option: (1 input binary Number) (2 erase binary Number) (3 erase entire memory) (d show data in memory) (b back)" << std::endl;
    std::cin >> c2;
    switch( c2 )
    {
        case 'b':{} //back to main menu
        break;

        case '1': //console Input
        {
            std::string consoleInput;
            std::cin >> consoleInput;
            try{
                consoleInput >> data;
            }catch(Error& e){
                std::cout << e.errText << std::endl;
                break;
            }
                data_out( data );
        }
        break;

        case '2': 
        {   
            try{
                index_erase( data );
            }catch(Error& e){
                std::cout << e.errText << std::endl;
                break;
            }
                data_out( data );    
        }
        break;

        case '3': //erase all data
        {
            try{
                erase_all( data );
            }catch(Error& e){
                std::cout << e.errText << std::endl;
                break;
            }
                data_out( data );
            
        }
        break;

        case 'd': //data to terminal
        {
            data_out( data ); 
        }
        break;

        default: //other than above was selected
        {
            std::cout << "ERROR: no menu option found! please select an option displayed below" << std::endl;
        }
        break;
    }
}

void operator>>( const std::string& console, std::vector<BinaryNumber>& dataCons ) //Console Input
{
    BinaryNumber obj;
    for( size_t i = 0; i < console.size(); i++ )
    {
        if( console.at(i) == '0' )
        {
            obj.bNumber.push_back( false );
        }
        else if( console.at(i) == '1' )
        {
            obj.bNumber.push_back( true );
        }
        else
        {
            throw Error( "ERROR: something other than 1 or 0 was entered!" );
        }
    }
    dataCons.push_back( obj );
}


void index_erase( std::vector<BinaryNumber>& dataErase )
{
    isEmpty( dataErase );
    std::cout << "type the index of the number you wish to erase: " << std::endl;
    unsigned int i = 0;
    std::cin >> i;
    if( !std::cin )
    {
        std::cin.clear();
        throw Error("ERROR: invalid user input, must be number!");
    }
    noIndex( i, dataErase );
    dataErase.erase(dataErase.cbegin() + i);
}

void erase_all( std::vector<BinaryNumber>& dataEraseAll)
{
    isEmpty( dataEraseAll );
    char eraseChoice;
    std::cout << "WARNING: You are about to erase all data in memory! Are you sure? (y / n): ";
    std::cin >> eraseChoice;
    switch( eraseChoice )
    {   
        case 'y':
        {
            dataEraseAll.clear();
        }
        break;

        case 'n':
        {
            std::cout << "that was close!" << std::endl;
        }
        break;

        default:
            std::cout << "Okay, any other key is fine too << std::endl"; 
        break;
    }
}







void menuCalculate( char& c3, std::vector<BinaryNumber>& data ) //calculate (extensive use of class BinaryNumber member functions)
{   
    std::cout << "--------------- calculate ---------------" << std::endl;
    std::cout << "select option: (1 logical, relational, division & subtraction) (2 NOT on one number) (3 concatenate) (4 parity) (d show data in memory) (b back)" << std::endl;
    std::cin >> c3;
    switch( c3 )
    {
        case 'b':{} //back to main menu
        break;

        case '1': //!, &, |, <, >, ==, !=, /, -,
        {
            try{
                menuCalculateCase1( data );  
            }catch(Error& e)
            {
                std::cout << e.errText << std::endl;
                break;
            }
        }
        break;

        case '2': //single !
        {
            try{
            menuCalculateCase2( data );
            }catch(Error& e){
                std::cout << e.errText << std::endl;
                break;
            }
        }
        break;

        case '3': //concatenate
        {
            try{
            menuCalculateCase3( data );
            }catch(Error& e){
                std::cout << e.errText << std::endl;
                break;
            }
        }
        break;

        case '4': //parity
        {
            try{
            menuCalculateCase4( data );
            }catch(Error& e){
                std::cout << e.errText << std::endl;
                break;
            }
        }
        break;

        case 'd': //data to terminal
        {
            data_out( data );
        }
        break;

        default: //other than above was selected
        {
            std::cout << "ERROR: no menu option found! please select an option displayed below" << std::endl;
        }
        break;
    }
}

void menuCalculateCase1( std::vector<BinaryNumber>& dataCase1 ) //Interface for !, &, |, <, >, ==, !=, /, -,
{
    isEmpty( dataCase1 );
    char NOTlhs;
    size_t iLHS;
    BinaryNumber tempLHS;
    std::cout << "input ! for optional NOT operator or press any key to continue without: ";
    std::cin >> NOTlhs;
    std::cout << "input index of LEFT HAND SIDE number: ";
    std::cin >> iLHS;
    if( !std::cin )
    {
        std::cin.clear();
        throw Error("ERROR: invalid user input, must be number!");
    }
    noIndex( iLHS, dataCase1 );
    switch( NOTlhs )
    {
        case '!': // ! yes, apply to
        {
            tempLHS = dataCase1.at( iLHS );
            !tempLHS;
        }
        break;

        default: // ! no, don't applay to
        {
            tempLHS = dataCase1.at( iLHS ); 
        }
        break;
    }
    char NOTrhs;
    size_t iRHS;
    BinaryNumber tempRHS;
    std::cout << "input ! for optional NOT operator or press any key to continue without: ";
    std::cin >> NOTrhs;
    std::cout << "input index of RIGHT HAND SIDE number: "; 
    std::cin >> iRHS; 
    if( !std::cin )
    {
        std::cin.clear();
        throw Error("ERROR: invalid user input, must be number!");
    }
    noIndex( iRHS, dataCase1 );
    switch( NOTrhs )
    {
        case '!': // ! yes, apply to
        {
            tempRHS = dataCase1.at( iRHS );
            !tempRHS;
        }
        break;

        default: // ! no, don't applay to
        {
            tempRHS = dataCase1.at( iRHS );
        }
        break;
    }
    BinaryNumber tempRESULT;
    char op;
    std::cout << "input operator (& AND) (| OR) (< smaller than) (> bigger than) (1 equal to (==) ) (0 not equal to (!=) \n(/ division) (- subtraction) ): ";
    std::cin >> op; 
    switch( op )
    {
        case '&':
        {
            tempRESULT = tempLHS & tempRHS;
        }
        break;

        case '|':
        {
            tempRESULT = tempLHS | tempRHS;
        }
        break;

        case '<':
        {
            tempRESULT.fill( 1, tempLHS < tempRHS );
        }
        break;

        case '>':
        {
            tempRESULT.fill( 1, tempLHS > tempRHS );
        }
        break;

        case '1':
        {
            tempRESULT.fill( 1, tempLHS == tempRHS );
        }
        break;

        case '0':
        {
            tempRESULT.fill( 1, tempLHS != tempRHS );
        }
        break;

        case '/':
        {
            tempRESULT = tempLHS / tempRHS;
        }
        break;

        case '-':
        {
            tempRESULT = tempLHS - tempRHS;
        }
        break;

        default: //other than above was selected
        {
            std::cout << "ERROR: no menu option found! please select an option displayed below" << std::endl; // ERROR Wont ask you to repeat
        }
        break;
    }
    std::cout << "= ";
    tempRESULT.out();
    std::cout << "result is automatically added to data" << std::endl;
    dataCase1.push_back( tempRESULT );  
}

void menuCalculateCase2( std::vector<BinaryNumber>& dataCase2 ) //Interface for ! single
{
    isEmpty( dataCase2 );
    size_t iNOT;
    BinaryNumber tempNOT;
    std::cout << "input index of number to apply NOT operator: ";
    std::cin >> iNOT;
    if( !std::cin )
    {
        std::cin.clear();
        throw Error("ERROR: invalid user input, must be number!");
    }
    noIndex(iNOT, dataCase2);
    tempNOT = dataCase2.at( iNOT );
    !tempNOT;
    std::cout << "= ";
    tempNOT.out();
    std::cout << "result is automatically added to data" << std::endl;
    dataCase2.push_back( tempNOT );  
}

void menuCalculateCase3( std::vector<BinaryNumber>& dataCase3 )//Interface for concatenate
{
    isEmpty( dataCase3 );
    BinaryNumber tempConcatenate;
    size_t iLHS;
    std::cout << "input index of first number: ";
    std::cin >> iLHS;
    size_t iRHS;
    std::cout << "input index of second number: ";
    std::cin >> iRHS;
    if( !std::cin )
    {
        std::cin.clear();
        throw Error("ERROR: invalid user input, must be number!");
    }
    noIndex( iLHS, dataCase3 );
    tempConcatenate = tempConcatenate.concatenate( dataCase3.at(iLHS), dataCase3.at(iRHS) );
    std::cout << "= ";
    tempConcatenate.out();
    dataCase3.push_back( tempConcatenate );
}

void menuCalculateCase4( std::vector<BinaryNumber>& dataCase4 ) //Interface for parity
{
    isEmpty( dataCase4 );
    BinaryNumber tempParity;
    size_t iParity;
    std::cout << "input index of number: ";
    std::cin >> iParity;
    if( !std::cin )
    {
        std::cin.clear();
        throw Error("ERROR: invalid user input, must be number!");
    }
    noIndex( iParity, dataCase4 );
    tempParity = tempParity.parity( dataCase4.at(iParity) );
    std::cout << "= ";
    tempParity.out();
    dataCase4.push_back( tempParity );
}

