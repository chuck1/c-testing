#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

#define NUM_FILE (1)
#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)

#define NUM_BODIES (100)

#include "universe.h"

float timestep = 100.0;

void check(int line, int ret)
{
	if(ret)
	{
		printf("%i: %i\n", line, ret);
		//exit(1);
	}
}

cl_program create_program_from_file(cl_context context, cl_device_id device_id)
{

	cl_program program = NULL;
	cl_int ret;
	

	FILE *fp;
	char const * fileName[] = {"./hello.cl","./body.h"};
	char *source_str[NUM_FILE];
	size_t source_size[NUM_FILE];
	
	/* Load the source code containing the kernel*/

	for(int i = 0; i < NUM_FILE; i++)
	{
		fp = fopen(fileName[i], "r");
		if (!fp) {
			fprintf(stderr, "Failed to load kernel.\n");
			exit(1);
		}
		source_str[i] = (char*)malloc(MAX_SOURCE_SIZE);
		source_size[i] = fread(source_str[i], 1, MAX_SOURCE_SIZE, fp);

		fclose(fp);
	}

	program = clCreateProgramWithSource(
			context,
			NUM_FILE,
			(const char **)source_str,
			(const size_t *)source_size, &ret);
	check(__LINE__, ret);




	free(source_str[0]);

	/* Build Kernel Program */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	//eck(__LINE__, ret);

	cl_build_status status;
	size_t logSize;
	char* programLog;

	// build failed
	if (ret != CL_SUCCESS) {

		// check build error and build status first
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_STATUS,
				sizeof(cl_build_status), &status, NULL);

		// check build log
		clGetProgramBuildInfo(program, device_id,
				CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
		programLog = (char*) calloc (logSize+1, sizeof(char));
		clGetProgramBuildInfo(program, device_id,
				CL_PROGRAM_BUILD_LOG, logSize+1, programLog, NULL);
		printf("Build failed; error=%d, status=%d, programLog:nn%s",
				ret, status, programLog);
		free(programLog);

	}


	return program;
}


int main()
{
	puts("hello");

	Universe* u = (Universe*)malloc(sizeof(Universe));
	universe_alloc(u, NUM_BODIES);
	universe_random(u);

	printf("x = %f %f %f\n",
			u->bodies[0].x[0],
			u->bodies[0].x[1],
			u->bodies[0].x[2]);

	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memobj0 = NULL;
	cl_mem memobj1 = NULL;
	cl_mem memobj2 = NULL;
	cl_mem memobj3 = NULL;
	cl_mem memobj4 = NULL;
	cl_program program = NULL;

	cl_kernel kernel0 = NULL;
	cl_kernel kernel1 = NULL;

	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	char string[MEM_SIZE];

	/* Get Platform and Device Info */
	puts("hello");
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	check(__LINE__, ret);

	/* Create OpenCL context */
	puts("create context");
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	check(__LINE__, ret);

	/* Create Command Queue */
	puts("create queue");
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	check(__LINE__, ret);

	/* Create Memory Buffer */
	puts("create buffer");
	memobj0 = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);
	memobj1 = clCreateBuffer(context, CL_MEM_READ_WRITE, u->num_bodies_ * sizeof(Body), NULL, &ret);
	memobj2 = clCreateBuffer(context, CL_MEM_READ_WRITE, u->num_pairs_ * sizeof(Pair), NULL, &ret);
	memobj3 = clCreateBuffer(context, CL_MEM_READ_WRITE, 1 * sizeof(int), NULL, &ret);
	memobj4 = clCreateBuffer(context, CL_MEM_READ_WRITE, 1 * sizeof(float), NULL, &ret);
	check(__LINE__, ret);
	
	/* Write to buffers */
	puts("write buffers");
	ret = clEnqueueWriteBuffer(command_queue, memobj1, CL_TRUE, 0, u->num_bodies_ * sizeof(Body), u->bodies, 0, NULL, NULL);
	check(__LINE__, ret);
	ret = clEnqueueWriteBuffer(command_queue, memobj2, CL_TRUE, 0, u->num_pairs_ * sizeof(Pair), u->pairs, 0, NULL, NULL);
	check(__LINE__, ret);
	ret = clEnqueueWriteBuffer(command_queue, memobj3, CL_TRUE, 0, sizeof(int), &u->num_pairs_, 0, NULL, NULL);
	check(__LINE__, ret);
	ret = clEnqueueWriteBuffer(command_queue, memobj4, CL_TRUE, 0, sizeof(float), &timestep, 0, NULL, NULL);
	check(__LINE__, ret);

	/* Create Kernel Program from the source */
	program = create_program_from_file(context, device_id);

	/* Create OpenCL Kernel */
	kernel0 = clCreateKernel(program, "hello", &ret);
	check(__LINE__, ret);
	kernel1 = clCreateKernel(program, "step_bodies", &ret);
	check(__LINE__, ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel0, 0, sizeof(cl_mem), (void *)&memobj0);
	ret = clSetKernelArg(kernel0, 1, sizeof(cl_mem), (void *)&memobj1);
	ret = clSetKernelArg(kernel0, 2, sizeof(cl_mem), (void *)&memobj2);
	ret = clSetKernelArg(kernel0, 3, sizeof(cl_mem), (void *)&memobj3);
	check(__LINE__, ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel1, 0, sizeof(cl_mem), (void *)&memobj1);
	ret = clSetKernelArg(kernel1, 1, sizeof(cl_mem), (void *)&memobj2);
	ret = clSetKernelArg(kernel1, 2, sizeof(cl_mem), (void *)&memobj4);
	check(__LINE__, ret);

	/* Execute OpenCL Kernel */

	puts("execute");

	size_t global_size = 2;
	size_t local_size = 1;

	//cl_event event;
	ret = clEnqueueNDRangeKernel(
			command_queue,
			kernel0,
			1,
			NULL,
			&global_size,
			&local_size,
			0,
			NULL,
			NULL);//&event);
	check(__LINE__, ret);

	//clWaitForEvents(1, &event);

	/* Execute "step_bodies" kernel */

	clFinish(command_queue);

	if(1)
	{
		ret = clEnqueueNDRangeKernel(
				command_queue,
				kernel1,
				1,
				NULL,
				&global_size,
				&local_size,
				0,
				NULL,
				NULL);//&event);
		check(__LINE__, ret);
	}

	//clWaitForEvents(1, &event);

	clFinish(command_queue);

	/* Copy results from the memory buffer */
	puts("read");
	ret = clEnqueueReadBuffer(
			command_queue,
			memobj0,
			CL_TRUE,
			0,
			MEM_SIZE * sizeof(char),
			string,
			0,
			NULL,
			NULL);
	check(__LINE__, ret);


	ret = clEnqueueReadBuffer(
			command_queue,
			memobj1,
			CL_TRUE,
			0,
			u->num_bodies_ * sizeof(Body),
			u->bodies,
			0,
			NULL,
			NULL);
	check(__LINE__, ret);

	ret = clEnqueueReadBuffer(
			command_queue,
			memobj2,
			CL_TRUE,
			0,
			u->num_pairs_ * sizeof(Pair),
			u->pairs,
			0,
			NULL,
			NULL);
	check(__LINE__, ret);

	/* Finalization */
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);

	ret = clReleaseKernel(kernel0);
	ret = clReleaseKernel(kernel1);

	ret = clReleaseProgram(program);

	ret = clReleaseMemObject(memobj0);
	ret = clReleaseMemObject(memobj1);
	ret = clReleaseMemObject(memobj2);
	ret = clReleaseMemObject(memobj3);
	ret = clReleaseMemObject(memobj4);

	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	/* Display Result */
	puts(string);

	/* Display Universe Data */
	printf("u = %f %f %f\n",
			u->pairs[0].u[0],
			u->pairs[0].u[1],
			u->pairs[0].u[2]);
	printf("f = %f\n",
			u->pairs[0].f);
	printf("x = %f %f %f\n",
			u->bodies[0].x[0],
			u->bodies[0].x[1],
			u->bodies[0].x[2]);


	universe_free(u);

	return 0;
}
