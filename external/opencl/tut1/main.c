#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <CL/cl.h>

#define NUM_FILE (1)
#define MAX_SOURCE_SIZE (0x100000)

#include "universe.h"

float timestep = 100.0;
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
	char const * fileName[NUM_FILE] = {"./hello.cl"};
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
	ret = clBuildProgram(
			program,
			1,
			&device_id,
			"-I.",
			NULL, NULL);
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
int		get_device_info(cl_device_id device_id)
{
	cl_int ret;

	cl_uint max_compute_units;
	size_t max_work_group_size;
	cl_uint max_work_item_dimensions;
	size_t max_work_item_sizes[16];
	cl_ulong local_mem_size;

	ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &max_compute_units, NULL);
	ret = clGetDeviceInfo(device_id, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &local_mem_size, NULL);
	ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &max_work_group_size, NULL);
	ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &max_work_item_dimensions, NULL);
	ret = clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, max_work_item_dimensions * sizeof(size_t), &max_work_item_sizes, NULL);

	printf("gpu:\n");
	printf("%32s = %i\n", "max_compute_units", max_compute_units);
	printf("%32s = %i\n", "local_mem_size", (int)local_mem_size);
	printf("%32s = %i\n", "max_work_group_size", (int)max_work_group_size);
	printf("%32s = %i\n", "max_work_item_dimensions", max_work_item_dimensions);
	for(int i = 0; i < max_work_item_dimensions; i++)
	{
		printf("%29s[%i] = %i\n", "max_work_item_sizes", i, (int)max_work_item_sizes[i]);
	}

	printf("problem:\n");
	printf("%32s = %i\n", "num bodies", NUM_BODIES);
	printf("%32s = %i\n", "num groups", NUM_GROUPS);
	printf("%32s = %i\n", "bodies per group", NUM_BODIES / NUM_GROUPS);
	printf("%32s = %i\n", "bodies per work item", NUM_BODIES / NUM_GROUPS / LOCAL_SIZE);
	printf("%32s = %i\n", "sizeof(Body)", (int)sizeof(Body));
	printf("%32s = %i\n", "sizeof(Pair)", (int)sizeof(Pair));
	printf("%32s = %i\n", "sizeof(Map)", (int)sizeof(Map));
}

int main()
{
	puts("Create Universe");

	Universe* u = (Universe*)malloc(sizeof(Universe));
	u->alloc(NUM_BODIES, NUM_STEPS);
	u->random(mass);

	//printf("x = %f %f %f\n", u->bodies[0].x[0], u->bodies[0].x[1], u->bodies[0].x[2]);

	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;

	cl_mem memobj_bodies = NULL;
	cl_mem memobj_pairs = NULL;
	cl_mem memobj_map = NULL;
	cl_mem memobj_flag_multi_coll = NULL;

	cl_program program = NULL;

	cl_kernel kernel_pairs = NULL;
	cl_kernel kernel_bodies = NULL;
	cl_kernel kernel_collisions = NULL;
	cl_kernel kernel_clear_bodies_num_collisions = NULL;

	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;


	/* Get Platform and Device Info */
	puts("Get Platform and Device Info");
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	check(__LINE__, ret);

	/* Get Device Info */
	ret = get_device_info(device_id);

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
	memobj_map      = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(Map), NULL, &ret);
	memobj_flag_multi_coll = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(unsigned int), NULL, &ret);
	check(__LINE__, ret);

	unsigned int flag_multi_coll = 0;

	/* Write to buffers */
	puts("write buffers");
	ret = clEnqueueWriteBuffer(command_queue, memobj_bodies,   CL_TRUE, 0, u->num_bodies_ * sizeof(Body),	 u->b(0), 0, NULL, NULL); check(__LINE__, ret);
	ret = clEnqueueWriteBuffer(command_queue, memobj_pairs,    CL_TRUE, 0, u->num_pairs_ * sizeof(Pair),	 u->pairs, 0, NULL, NULL); check(__LINE__, ret);
	ret = clEnqueueWriteBuffer(command_queue, memobj_map,      CL_TRUE, 0, sizeof(Map),	                 &u->map, 0, NULL, NULL); check(__LINE__, ret);
	ret = clEnqueueWriteBuffer(command_queue, memobj_flag_multi_coll, CL_TRUE, 0, sizeof(unsigned int), &flag_multi_coll, 0, NULL, NULL); check(__LINE__, ret);
	//ret = clEnqueueWriteBuffer(command_queue, memobj_dt,       CL_TRUE, 0, sizeof(float),                    &timestep, 0, NULL, NULL); check(__LINE__, ret);
	check(__LINE__, ret);

	/* Create Kernel Program from the source */
	program = create_program_from_file(context, device_id);

	/* Create OpenCL Kernel */
	kernel_pairs = clCreateKernel(program, "step_pairs", &ret); check(__LINE__, ret);
	kernel_bodies = clCreateKernel(program, "step_bodies", &ret); check(__LINE__, ret);
	kernel_collisions = clCreateKernel(program, "step_collisions", &ret); check(__LINE__, ret);
	kernel_clear_bodies_num_collisions = clCreateKernel(program, "clear_bodies_num_collisions", &ret); check(__LINE__, ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel_pairs, 0, sizeof(cl_mem), (void *)&memobj_bodies);
	ret = clSetKernelArg(kernel_pairs, 1, sizeof(cl_mem), (void *)&memobj_pairs);
	check(__LINE__, ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel_collisions, 0, sizeof(cl_mem), (void *)&memobj_bodies);
	ret = clSetKernelArg(kernel_collisions, 1, sizeof(cl_mem), (void *)&memobj_pairs);
	ret = clSetKernelArg(kernel_collisions, 2, sizeof(cl_mem), (void *)&memobj_flag_multi_coll);
	check(__LINE__, ret);

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel_bodies, 0, sizeof(cl_mem), (void *)&memobj_bodies);
	ret = clSetKernelArg(kernel_bodies, 1, sizeof(cl_mem), (void *)&memobj_pairs);
	ret = clSetKernelArg(kernel_bodies, 2, sizeof(cl_mem), (void *)&memobj_map);
	ret = clSetKernelArg(kernel_bodies, 3, sizeof(float), (void *)&timestep); check(__LINE__, ret);

	ret = clSetKernelArg(kernel_clear_bodies_num_collisions, 0, sizeof(cl_mem), (void *)&memobj_bodies);

	/* Execute OpenCL Kernel */

	puts("execute");

	size_t global_size = GLOBAL_SIZE;
	size_t local_size = LOCAL_SIZE;

	auto program_time_start = std::chrono::system_clock::now();

	for(int t = 1; t < NUM_STEPS; t++)
	{
		if((t % (NUM_STEPS / 100)) == 0) printf("t = %5i\n", t);

		/* Execute "step_pairs" kernel */

		ret = clEnqueueNDRangeKernel(command_queue, kernel_pairs, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
		check(__LINE__, ret);
		if(ret) break;

		clFinish(command_queue);
		check(__LINE__, ret);

		/* Execute "step_bodies" kernel */
		ret = clEnqueueNDRangeKernel( command_queue, kernel_bodies, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
		check(__LINE__, ret);
		if(ret) break;

		clFinish(command_queue);
		check(__LINE__, ret);

		/* Execute "step_collisions" kernel */
		ret = clEnqueueNDRangeKernel(command_queue, kernel_collisions, 1, NULL, &global_size, &local_size, 0, NULL, NULL);

		check(__LINE__, ret);
		if(ret) break;

		clFinish(command_queue); check(__LINE__, ret);

		/* Read flag_multi_coll */
		ret = clEnqueueReadBuffer(command_queue, memobj_flag_multi_coll, CL_TRUE, 0, sizeof(unsigned int), &flag_multi_coll, 0, NULL, NULL); check(__LINE__, ret);
		clFinish(command_queue); check(__LINE__, ret);

		/* Execute "clear_bodies_num_collisions" kernel */
		ret = clEnqueueNDRangeKernel(command_queue, kernel_clear_bodies_num_collisions, 1, NULL, &global_size, &local_size, 0, NULL, NULL);
		check(__LINE__, ret);
		if(ret) break;

		clFinish(command_queue); check(__LINE__, ret);

		if(flag_multi_coll)
		{
			puts("resolve multi_coll");

			/* Execute "step_collisions" kernel on a single thread to resolve bodies with multiple collisions */
			global_size = 1;
			local_size = 1;

			ret = clEnqueueNDRangeKernel(command_queue, kernel_collisions, 1, NULL, &global_size, &local_size, 0, NULL, NULL);

			check(__LINE__, ret);
			if(ret) break;

			clFinish(command_queue); check(__LINE__, ret);

			global_size = GLOBAL_SIZE;
			local_size = LOCAL_SIZE;
		}

		/* Reset flag_multi_coll */
		flag_multi_coll = 0;

		ret = clEnqueueWriteBuffer(command_queue, memobj_flag_multi_coll, CL_TRUE, 0, sizeof(unsigned int), &flag_multi_coll, 0, NULL, NULL); check(__LINE__, ret);
		clFinish(command_queue); check(__LINE__, ret);


		/* Store data for timestep */
		ret = clEnqueueReadBuffer(command_queue, memobj_bodies, CL_TRUE, 0, u->num_bodies_ * sizeof(Body), u->b(t), 0, NULL, NULL);
		check(__LINE__, ret);
		if(ret) break;

		clFinish(command_queue); check(__LINE__, ret);
	}

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - program_time_start);

	printf("duration = %i milliseconds\n", (int)duration.count());

	/* Finalization */
	ret = clFlush(command_queue);check(__LINE__, ret);
	ret = clFinish(command_queue);check(__LINE__, ret);

	ret = clReleaseKernel(kernel_pairs);check(__LINE__, ret);
	ret = clReleaseKernel(kernel_bodies);check(__LINE__, ret);

	ret = clReleaseProgram(program);check(__LINE__, ret);

	ret = clReleaseMemObject(memobj_bodies);check(__LINE__, ret);
	ret = clReleaseMemObject(memobj_pairs);check(__LINE__, ret);

	ret = clReleaseCommandQueue(command_queue);check(__LINE__, ret);
	ret = clReleaseContext(context);check(__LINE__, ret);

	/* Display Universe Data */
	/*
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
	   */
	puts("Write");
	u->write();

	u->free();

	return 0;
}
