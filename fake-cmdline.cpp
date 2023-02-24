// Small sample of command line parsing in C
// This is really stupid don't look

#include <stdio.h>
#include <string.h>

constexpr char *Help = R"Help(

FakeCmdline finds duplicate files within a directory.

  FakeCmdline.exe [directory] [flags] 

Directory can be relative path or absolute path to a directory (not file).

Flags:
  /R - recurse into subdirectories

)Help";


int main( int argc, char **argv )
{
	if ( argc != 2 && argc != 3 )
	{
		fprintf( stderr, Help );
		return( -1 );
	}
	const char* pDirectoryArg = argv[1];

	bool Recurse = false;
	if ( argc == 3 && !strcmp( argv[2], "/R" ) )
		Recurse = true;

    printf( "Dir: %s. Recurse? %s\n", pDirectoryArg, Recurse ? "Y" : "N");
	
    return( 0 );
}
