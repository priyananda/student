#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
	--argc;argv++;
	
	const char *inFilePath = argv[0];
	const char *outFilePath = argv[1];
	
	FILE *fileIn = fopen(inFilePath, "rb");
	FILE *fileOut = fopen(outFilePath, "wt");
	
	fprintf(fileOut, "db ");
	
	unsigned char buffer[1];
	bool writeComma = false;
	while (fread(buffer, 1, 1, fileIn)) {
		if (writeComma)
			fprintf(fileOut, ", ");
		writeComma = true;
		fprintf(fileOut, "0x%hhx", buffer[0]);
	}
	
	fprintf(fileOut, "\n");
	
	fclose(fileIn);
	fclose(fileOut);
	
	return 0;
}
