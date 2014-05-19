#include <string>
#include <stdexcept>

#define TESTING
#ifndef TESTING

#include <iostream>
#include <fstream>

class FileError : public std::runtime_error {
public:

    FileError( const std::string &fileName ) :
        m_fileName( fileName ),
        std::runtime_error( "" ) {
    }

    virtual const char *what() const throw () {
        return m_message.c_str( );
    }

    virtual ~FileError( ) throw () {

    }

protected:
    std::string m_fileName;
    std::string m_message;
};

class FileOpenError : public FileError {
public:

    FileOpenError( const std::string &fileName ) : FileError( fileName ) {
        m_message = "Error: unable to open the file " + m_fileName;
    }
};

class FileReadError : public FileError {
public:

    FileReadError( const std::string &fileName ) : FileError( fileName ) {
        m_message = "Error: unable to read the file " + m_fileName;
    }
};

class FileWriteError : public FileError {
public:

    FileWriteError( const std::string &fileName ) : FileError( fileName ) {
        m_message = "Error: unable to write the file " + m_fileName;
    }
};

#endif

class LogicError : public std::logic_error {
public:

    LogicError( ) : std::logic_error( "" ) {

    }

    virtual const char *what( ) const throw () {
        return m_message.c_str( );
    }

    virtual ~LogicError( ) throw () {

    }

protected:
    std::string m_message;
};

class EmptyArgument : public LogicError {
public:

    EmptyArgument( ) {
        m_message = "Error: empty argument";
    }
};

class BadArgument : public LogicError {
public:

    BadArgument( const std::string &argument ) {
        m_message = "Error: bad argument " + argument;
    }
};

#ifndef TESTING

void readData( const std::string &fileName,
               std::string &firstNumber,
               std::string &secondNumber,
               std::string &thirdNumber ) throw( FileOpenError, FileReadError );

void writeResult( const std::string &fileName,
                  const std::string &result) throw( FileOpenError, FileWriteError );

std::string theLagestNumber( std::string firstNumber,
                             std::string secondNumber,
                             std::string thirdNumber ) throw( EmptyArgument, BadArgument );

int main() {

    std::string fileNameIn = "input.txt";
    std::string firstNumber;
    std::string secondNumber;
    std::string thirdNumber;

    // Read input data from the file
    try {
        readData( fileNameIn, firstNumber, secondNumber, thirdNumber );
    } catch( const FileError &e ) {
        std::cerr << e.what( ) << std::endl;
    } catch( ... ) {
        std::cerr << "Error: unknown exception" << std::endl;
    }

    // Data processing
    std::string result;
    try {
        result = theLagestNumber( firstNumber, secondNumber, thirdNumber );
    } catch( const LogicError &e ) {
        std::cerr << e.what( ) << std::endl;
    } catch ( ... ) {
        std::cerr << "Error unknown excetion" << std::endl;
    }

    // Write output data to the file
    try {

    } catch( const FileError &e ) {
        std::cerr << e.what( ) << std::endl;
    } catch( ... ) {
        std::cerr << "Error: unknown exception" << std::endl;
    }

    return 0;
}

void readData( const std::string &fileName,
               std::string &firstNumber,
               std::string &secondNumber,
               std::string &thirdNumber ) throw ( FileOpenError, FileReadError ) {
    // Open the input file
    std::ifstream file;
    file.open( fileName.c_str( ) );
    if ( file.fail( ) ) {
        throw FileOpenError( fileName );
    }

    // Read data from the file
    if ( !( file >> firstNumber >> secondNumber >> thirdNumber ) ) {
        throw FileReadError( fileName );
    }
}

void writeResult( const std::string &fileName,
                  const std::string &result) throw ( FileOpenError, FileWriteError ) {
    // Open the output file
    std::ofstream file;
    file.open( fileName.c_str( ) );
    if ( file.fail( ) ) {
        throw FileOpenError( fileName );
    }

    // Write data to the file
    if ( !( file << result ) ) {
        throw FileWriteError( fileName );
    }
}

#endif

std::string theLagestNumber( std::string firstNumber,
                             std::string secondNumber,
                             std::string thirdNumber ) throw( EmptyArgument, BadArgument ) {

}
