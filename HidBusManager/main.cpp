#include <iostream>
#include <cstring>
#include <fstream>

struct Arg_Aunc_Pair
{
	char * arg;
	int argSize = 0;
	void (*func)(const char*);
};

void PRINT_HELP(const char*)
{
	std::cout<<"Usage: HidBusManager [options]"<<std::endl;
	std::cout<<"options:"<<std::endl;
	std::cout<<"\t-h || --help\t\tdisplay help and exit"<<std::endl;
	std::cout<<"\t-p <file name>\t\tunit to write data"<<std::endl;
	std::cout<<"\t--rawfile\t\t\tfile with data to send"<<std::endl;
	std::cout<<"\t--data\t\t\tdata to send"<<std::endl;
	std::cout<<"\t--cmdsfile <filename>\tfile with commands"<<std::endl;
	std::cout<<"\t-I\t\t\tstart interactive mode"<<std::endl;
};

Arg_Aunc_Pair prgArgs[]=
{
	// {"", nullptr},
	{"-h",			sizeof("-h")-1, 		PRINT_HELP},
	{"--help",		sizeof("--help")-1,		PRINT_HELP},
	{"-p",			sizeof("-p")-1,			nullptr},
	{"--rawfile",	sizeof("--rawfile")-1,	nullptr},
	{"--data",		sizeof("--data")-1,		nullptr},
	{"--cmdsfile",	sizeof("--cmdsfile")-1,	nullptr},
	{"-I",			sizeof("-I")-1,			nullptr}
};

int main(int argc, char const *argv[])
{
	// if ( argc <= 1 || ( memcmp(argv[1], "-h", 2) == 0 ) | ( memcmp(argv[1], "--help", 6) == 0 ) )
	// {
	// 	// std::cout<<""<<std::endl;
	// 	std::cout<<"Usage: HidBusManager [options]"<<std::endl;
	// 	std::cout<<"options:"<<std::endl;
	// 	std::cout<<"\t-h || --help\t\tdisplay help and exit"<<std::endl;
	// 	std::cout<<"\t-p <file name>\t\tunit to write data"<<std::endl;
	// 	std::cout<<"\t--rawfile\t\t\tfile with data to send"<<std::endl;
	// 	std::cout<<"\t--data\t\t\tdata to send"<<std::endl;
	// 	std::cout<<"\t--cmdsfile <filename>\tfile with commands"<<std::endl;
	// 	std::cout<<"\t-I\t\t\tstart interactive mode"<<std::endl;
	// };

	for (int givenArgsCounter = 1; givenArgsCounter < argc; ++givenArgsCounter)
	{
		for (int programArgsCounter = 0; programArgsCounter < sizeof(prgArgs); ++programArgsCounter)
		{
			if( memcmp(argv[givenArgsCounter],
					   prgArgs[programArgsCounter].arg,
					   prgArgs[programArgsCounter].argSize) == 0 )
			{
				prgArgs[programArgsCounter].func(argv[givenArgsCounter]);
				break;
			} //else
			// {
			// 	std::cout<<"Error:"<<argv[givenArgsCounter]<<" is unknown arg!"<<std::endl;
			// };
		};
	};
	return 0;
};