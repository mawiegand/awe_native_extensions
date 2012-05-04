#ifndef WackBattle_DataException_h
#define WackBattle_DataException_h

#include <exception>
#include <string>

class DataException : public std::exception {
public:
	DataException(const char* file, int line, const char* func, const char* message);
	virtual ~DataException() throw();
	
	virtual const char* what() const throw();
	
	std::string file;
	int line; 
	std::string func;
	std::string message;
};

#endif
