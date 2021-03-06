/* System includes */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


/* OpenCL includes */
#include <CL/cl.h>

void check(cl_int status) {

   if (status != CL_SUCCESS) {
      printf("OpenCL error (%d)\n", status);
      exit(-1);
   }
}

void printCompilerError(cl_program program, cl_device_id device) {
   cl_int status;

   size_t logSize;
   char *log;

   /* Get the log size */
   status = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
               0, NULL, &logSize);
   check(status);

   /* Allocate space for the log */
   log = (char*)malloc(logSize);
   if (!log) {
      exit(-1);
   }

   /* Read the log */
   status = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
               logSize, log, NULL);
   check(status);

   /* Print the log */
   printf("%s\n", log);
}

char* readFile(const char *filename) {

   FILE *fp;
   char *fileData;
   long fileSize;
   
   /* Open the file */
   fp = fopen(filename, "r");
   if (!fp) {
      printf("Could not open file: %s\n", filename);
      exit(-1);
   }

   /* Determine the file size */
   if (fseek(fp, 0, SEEK_END)) {
      printf("Error reading the file\n");
      exit(-1);
   }
   fileSize = ftell(fp);
   if (fileSize < 0) {
      printf("Error reading the file\n");
      exit(-1);
   }
   if (fseek(fp, 0, SEEK_SET)) {
      printf("Error reading the file\n");
      exit(-1);
   }

   /* Read the contents */
   fileData = (char*)malloc(fileSize + 1);
   if (!fileData) { 
      exit(-1); 
   }
   if (fread(fileData, fileSize, 1, fp) != 1) {
      printf("Error reading the file\n");
      exit(-1);
   }

   /* Terminate the string */
   fileData[fileSize] = '\0';

   /* Close the file */
   if (fclose(fp)) {
      printf("Error closing the file\n");
      exit(-1);
   }

   return fileData;
}


float *read_image(int size, const char* img_file)
{
	float *img;
	int channels = 3;

	img = new float [size*size*channels];

	FILE *fp = fopen(img_file, "r");
	
	if (fp == NULL)
	{
		std::cout<<"test image open failed!";
		exit(-1);
	}

	for(int channels=0; channels<3; channels++)
	{
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<size; j++)
				fscanf(fp, "%f\n", img + i*size + j + channels*(size*size));
		}
	}

	return img;
}
