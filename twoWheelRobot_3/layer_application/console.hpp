#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "serial.hpp"
#include "util.hpp"

#define DEFAULT_NEWLINE NEWLINE_LF

class Console;
class ConsoleCommand{
private:
	Console *console;
	int commandSetup(Console &console);
protected:
	int newLine(char value);
public:
	ConsoleCommand(Console &console){commandSetup(console);};
	virtual int commandCompare(char *command)=0;
	virtual int commandRequest(int argc,char **argv)=0;//1:sustain 0:unsustain
	virtual int commandCycle(){return 0;};
	virtual void consoleReadChar(char data){};
	void consolePrintf(char *pFormat, ...);
};

#define CONSOLE_DEFAULT_NEWLINE CONSOLE_NEWLINE_LF
#define NUMBER_OF_CONSOLE_COMMANDS 30
class Console:public SerialInterface{
public:
	enum{
		NEWLINE_LF,
		NEWLINE_CR,
		NEWLINE_CRLF
	};
	Console(Serial &serial);
	int setup(int baudrate);
	void cycle();

	int addCommand(ConsoleCommand &commandClass);
	int addCommand(ConsoleCommand *commandClass);
	int setNewLine(int newLine);
	void echo(bool value);
	void output(bool value);
	void setPrompt(char *value);
	int newLine(char value);

	void clear();
	void startRelative();
	void relative(int x,int y);
	void absolute(int x,int y);

	void serialVprintf(char *format,va_list arg);
	void serialReadChar(char data);
	void serialWriteChar(char value);
	void serialWriteString(char *value);

private:

	ConsoleCommand* command[NUMBER_OF_CONSOLE_COMMANDS];
	int commandCursor;
	int commandRunning;

	bool echoAvailable;
	bool outputAvailable;
	char *prompt;
	int newLineData;
	int newLineCount;

	int relativeCursorX;
	int relativeCursorY;

	int getString(char *value);
//	RingBuffer<char,SERIAL_BUFFER_LENGTH> buffer;



	int lf(char value){return (value=='\n');};
	int cr(char value){return (value=='\r');};
	int crlf(char value){
		static int flag=0;
		if(value=='\r')flag=1;
		else if(value=='\n'&&flag==1){
			flag=0;
			return 1;
		}else{
			flag=0;
		}
		return 0;
	};

	int toLF(char *value);
	int toCR(char *value);
	int toCRLF(char *value);

	int delOneChar(char *value,int num);
	int addOneChar(char *value,int num,char add);

	int setCommand(char ***argv,char *text);
	int deleteCommand(char ***argv);
	int noc(char *text);
};
#include "string.h"
class Echo:public ConsoleCommand{
public:
	Echo(Console &console):ConsoleCommand(console){};
	int commandCompare(char *str){/*consolePrintf((char*)"[Echo::commandCompare] %s\n",str);*/return (!strcmp(str,"echo"));};
	int commandRequest(int argc,char **argv){
		for(int i=1;i<argc;i++)consolePrintf(argv[i]);
		return 0;
	}
};

#endif//CONSOLE_HPP
