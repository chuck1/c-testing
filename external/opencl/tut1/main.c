#include <stdio.h>
#include <stdlib.h>

#include <CL/cl.h>

#define NUM_FILE (1)
#define MAX_SOURCE_SIZE (0x100000)

#include "universe.h"

float timestep = 200.0;
float mass = 1e6;

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
	u->alloc(NUM_BODIES, NUM_STEPS);
	u->random(mass);

	printf("x = %f %f %f\n",
			u->bodies[0].x[0],
			u->bodies[0].x[1],
			u->bodies[0].x[2]);

	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	
	cl_mem memobj_bodies = NULL;
	cl_mem memobj_bodymaps = NULL;
	cl_mem memobj_pairs = NULL;
	
	cl_program program = NULL;

	cl_kernel kernel_pairs = NULL;
	cl_kernel kernel_bodies = NULL;

	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;


	/* Get Platform and Device Info */
	puts("hello");
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	check(__LINE__, ret);

	cl_uint max_compute_units;
	ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &max_compute_units, NULL);

	printf("gpu:\n");
	printf("max_compute_units = %i\n", max_compute_units);

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
	memobj_bodies   = clCreateBuffer(context, CL_MEM_READ_WRITE, u->num_bodies_ * sizeof(Body), NULL, &ret);
	memobj_pairs    = clCreateBuffer(context, CL_MEM_READ_WRITE, u->num_pairs_ * sizeof(Pair), NULL, &ret);
	memobj_bodymaps = clCreateBuffer(context, CL_MEM_READ_WRITE, u->num_bodies_ * sizeof(BodyMap), NULL, &ret);
	check(__LINE__, ret);
	
	/* Write to buffers */
	puts("write buffers");
	ret = clEnqueueWriteBuffer(command_queue, memobj_bodies,   CL_TRUE, 0, u->num_bodies_ * sizeof(Body),	 u->b(0), 0, NULL, NULL); check(__LINE__, ret);
	ret = clEnqueueWriteBuffer(command_queue, memobj_pairs,    CL_TRUE, 0, u->num_pairs_ * sizeof(Pair),	 u->pairs, 0, NULL, NULL); check(__LINE__, ret);
	ret = clEnqueueWriteBuffer(command_queue, memobj_bodymaps, CL_TRUE, 0, u->num_bodies_ * sizeof(BodyMap), u->bodymaps, 0, NULL, NULL); check(__LINE__, ret);
	//ret = clEnqueueWriteBuffer(command_queue, memobj_dt,       CL_TRUE, 0, sizeof(float),                    &timestep, 0, NULL, NULL); check(__LINE__, ret);
	check(__LINE__, ret);
	
	/* Create Kernel Program from the source */
	program = create_program_from_file(context, device_id);

	/* Create OpenCL Kernel */
	kernel_pairs = clCreateKernel(program, "step_pairs", &ret);
	check(__LINE__, ret);
	kernel_bodies = clCreateKernel(program, "step_bodies", &ret);
	check(__LINE__, ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel_pairs, 0, sizeof(cl_mem), (void *)&memobj_bodies);
	ret = clSetKernelArg(kernel_pairs, 1, sizeof(cl_mem), (void *)&memobj_pairs);
	check(__LINE__, ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel_bodies, 0, sizeof(cl_mem), (void *)&memobj_bodies);
	ret = clSetKernelArg(kernel_bodies, 1, sizeof(cl_mem), (void *)&memobj_pairs);
	ret = clSetKernelArg(kernel_bodies, 2, sizeof(cl_mem), (void *)&memobj_bodymaps);
	ret = clSetKernelArg(kernel_bodies, 3, sizeof(float), (void *)&timestep);
	check(__LINE__, ret);

	/* Execute OpenCL Kernel */

	puts("execute");

	size_t global_size = 2;
	size_t local_size = 1;

	for(int t = 1; t < NUM_STEPS; t++)
	{
		if((t % (NUM_STEPS / 10)) == 0) printf("t = %5i\n", t);
		
		//cl_event event;
		ret = clEnqueueNDRangeKernel(
				command_queue,
				kernel_pairs,
				1,
				NULL,
				&global_size,
				&local_size,
				0,
				NULL,
				NULL);//&event);
		check(__LINE__, ret);
		if(ret) break;

		//clWaitForEvents(1, &event);

		/* Execute "step_bodies" kernel */

		clFinish(command_queue);

		ret = clEnqueueNDRangeKernel(
				command_queue,
				kernel_bodies,
				1,
				NULL,
				&global_size,
				&local_size,
				0,
				NULL,
				NULL);//&event);
		check(__LINE__, ret);
		if(ret) break;

		clFinish(command_queue);

		/* Store data for timestep */
		ret = clEnqueueReadBuffer(
				command_queue,
				memobj_bodies,
				CL_TRUE,
				0,
				u->num_bodies_ * sizeof(Body),
				u->b(t),
				0,
				NULL,
				NULL);
		check(__LINE__, ret);
		if(ret) break;

		clFinish(command_queue);
	}

	//clWaitForEvents(1, &event);


	/* Copy results from the memory buffer */
	/* Finalization */
	ret = clFlush(command_queue);check(__LINE__, ret);
	ret = clFinish(command_queue);check(__LINE__, ret);

	ret = clReleaseKernel(kernel_pairs);check(__LINE__, ret);
	ret = clReleaseKernel(kernel_bodies);check(__LINE__, ret);

	ret = clReleaseProgram(program);check(__LINE__, ret);

	ret = clReleaseMemObject(memobj_bodies);
	ret = clReleaseMemObject(memobj_pairs);
	ret = clReleaseMemObject(memobj_bodymaps);

	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	/* Display Universe Data */
	printf("u = %f %f %f\n",
			u->pairs[0].u[0],
			u->pairs[0].u[1],
			u->pairs[0].u[2]);
	printf("f = %f\n",
			u->pairs[0].f);
	printf("x = %f %f %f\n",
			u->b(NUM_STEPS - 1, 0).x[0],
			u->b(NUM_STEPS - 1, 0).x[1],
			u->b(NUM_STEPS - 1, 0).x[2]);


	u->write();

	u->free();

	return 0;
}
