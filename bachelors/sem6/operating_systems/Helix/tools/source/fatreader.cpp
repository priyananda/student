#include <cstdio>
#include <cstdlib>
#include <cstring>

struct FAT12
{
	unsigned char jmp[3];
	char oemName[8];
	unsigned short bytesPerSector;
	unsigned char sectorsPerCluster;
	unsigned short reservedSectors;
	unsigned char fatCopies;
	unsigned short rootEntries;
	unsigned short totalSectors;
	unsigned char  mediaDescType;
	unsigned short sectorsPerFat;
	unsigned short sectorsPerTrack;
	unsigned short numHeads;
	unsigned short hiddenSectors;

	// fat16
	unsigned short hiddenSectorHighWord;
	unsigned int   totalSectors16;
	unsigned char  logicalDriveNumber;
	unsigned char  currentHead;
	unsigned char  extendedSign;
	unsigned int   serialNumber;
	char volumeLabel[11];
	char fatType[8];
} __attribute__((packed));

static void printStr(const char str[], const char *name)
{
	char buffer[20];
	memcpy(buffer, str, sizeof(str));
	buffer[sizeof(str) + 1] = 0;

	printf("%s = %s\n", name, buffer);
}

int main(int argc, char *argv[])
{
	--argc;argv++;
	if (argc < 1) {
		printf("Need an argument: floppy image path");
		exit(-2);
	}

	FILE *fileIn = fopen(argv[0], "rb");
	if (fileIn == nullptr) {	
		printf("floppy image path is wrong");
		exit(-3);
	}

	struct FAT12 fat12br = {0};

	fread(&fat12br, sizeof(FAT12), 1, fileIn);

	printf("bytesPerSector = %hu\n", fat12br.bytesPerSector);
	printf("sectorsPerCluster = %hhu\n", fat12br.sectorsPerCluster);
	printf("reservedSectors = %hu\n", fat12br.reservedSectors);
	printf("fatCopies = %hhu\n", fat12br.fatCopies);
	printf("rootEntries = %hu\n", fat12br.rootEntries);
	printf("totalSectors = %hu\n", fat12br.totalSectors);
	printf("mediaDesc = %hhx\n", fat12br.mediaDescType);
	printf("sectorsPerFat = %hu\n", fat12br.sectorsPerFat);
	printf("sectorsPerTrack = %hu\n", fat12br.sectorsPerTrack);
	printf("numHeads = %hu\n", fat12br.numHeads);
	printf("hiddenSectors = %hu\n", fat12br.hiddenSectors);

	// fat16
	printf("hiddenSectorHighWord = %hu\n", fat12br.hiddenSectorHighWord);
    printf("totalSectors16 = %u\n", fat12br.totalSectors16);
    printf("logicalDriveNumber = %hhx\n", fat12br.logicalDriveNumber);
    printf("currentHead = %hhu\n", fat12br.currentHead);
    printf("extendedSign = %hhx\n", fat12br.extendedSign);
    printf("serialNumber = %u\n", fat12br.serialNumber);
    printStr(fat12br.volumeLabel, "volumeLabel");
    printStr(fat12br.fatType, "fatType");


	fclose(fileIn);
	return 0;
}
