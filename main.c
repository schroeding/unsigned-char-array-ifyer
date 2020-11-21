#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printUsage() {

	printf("Usage: uca <filename> [<name of array>] [-o <output filename> ]\n" \
		" \t-o - Writes output to the specified file instead of stdout\n");
	return;

}

int main(int argc, char* argv[]) {

	if ((argc < 2) || (argc > 5)) {
		printUsage();
		return EXIT_FAILURE;
	}

	char* arrayName = NULL;
	char* outputFileName = NULL;

	if (argc >= 3) {
		if (strncmp(argv[2], "-o", sizeof("-o")) == 0) {
			if (argc < 4) {
				printf("No output file specified.\n\n");
				printUsage();
				return EXIT_FAILURE;
			}
			outputFileName = argv[3];
		} else {
			arrayName = argv[2];
			if ((argc >= 4) && strncmp(argv[3], "-o", sizeof("-o")) == 0) {
				if (argc < 5) {
					printf("No output file specified.\n\n");
					printUsage();
					return EXIT_FAILURE;
				}
				outputFileName = argv[4];
			}
		}
	}

	FILE* inputFile = fopen(argv[1], "rb");
	if (inputFile == NULL) {
		printf("Could not open input file.\n");
		return EXIT_FAILURE;
	}

	fseek(inputFile, 0L, SEEK_END);
	long inputSize = ftell(inputFile);
	if (inputSize <= 0L) {
		printf("Input file empty or invalid.\n");
		return EXIT_FAILURE;
	}

	fseek(inputFile, 0L, SEEK_SET);
	unsigned char* inputData = malloc(inputSize);
	if (!inputData) { printf("Memory allocation failed"); return EXIT_FAILURE; }
	long readBytes = fread(inputData, 1, inputSize, inputFile);
	if (readBytes != inputSize) {
		printf("Unable to read input file.\n");
		return EXIT_FAILURE;
	}
	fclose(inputFile);

	char* outputData = NULL;
	if (!arrayName) {
		outputData = malloc(sizeof("unsigned char data[] = { };\n") + (sizeof("0x00, ") * inputSize));
		if (!outputData) { printf("Memory allocation failed"); return EXIT_FAILURE; }
		strcpy(outputData, "unsigned char data[] = { ");
	} else {
		outputData = malloc(sizeof("unsigned char [] = { };\n") + strlen(arrayName) + (sizeof("0x00, ") * inputSize));
		if (!outputData) { printf("Memory allocation failed"); return EXIT_FAILURE; }
		strcpy(outputData, "unsigned char ");
		strcat(outputData, arrayName);
		strcat(outputData, "[] = { ");
	}

	char* charBuffer = malloc(sizeof("0x00, "));
	if (!charBuffer) { printf("Memory allocation failed"); return EXIT_FAILURE; }
	for (int i = 0; i < inputSize; i++) {
		sprintf(charBuffer, "0x%02X, ", inputData[i]);
		strcat(outputData, charBuffer);
	}
	free(charBuffer);
	free(inputData);
	strcat(outputData, "};\n");

	if (!outputFileName) {
		fwrite(outputData, 1, strlen(outputData), stdout);
		free(outputData);
		return EXIT_SUCCESS;
	} else {
		FILE* outputFile = fopen(outputFileName, "wb+");
		if (inputFile == NULL) {
			printf("Could not open / create output file.\n");
			return EXIT_FAILURE;
		}
		fwrite(outputData, 1, strlen(outputData), outputFile);
		free(outputData);
		fclose(outputFile);
		return EXIT_SUCCESS;
	}

}