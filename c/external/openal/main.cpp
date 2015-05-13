#include <AL/al.h>
#include <AL/alc.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_BUFFERS 3
#define BUFFER_SIZE 4096


/*
void print(void* v, int size) {

	unsigned char* b = (unsigned char*)v;
	unsigned char* c = (unsigned char*)v;

	for(; c < (b + size); ++c) {
		printf("'%c'", *c);
	}
	printf("\n");
}
*/

class AL
{
	public:

		AL() {

			/* First the standard open-device, create-context, set-context.. */
			dev = alcOpenDevice(NULL);
			if(!dev)
			{
				fprintf(stderr, "Oops\n");
				exit(1);
			}

			ctx = alcCreateContext(dev, NULL);
			alcMakeContextCurrent(ctx);
			if(!ctx)
			{
				fprintf(stderr, "Oops2\n");
				exit(1);
			}


		}
		~AL() {

			/* All done. Close OpenAL and exit. */
			alcMakeContextCurrent(NULL);
			alcDestroyContext(ctx);
			alcCloseDevice(dev);


		}



		ALCdevice *dev;
		ALCcontext *ctx;

} g_al;

class Source
{
	public:

		void OpenFile(char const * filename) {
			struct stat statbuf;

			/* Here's where our magic begins. First, we want to call stat on the
			 * filename since mplayer will just silently exit if it tries to play a
			 * non-existant file **/
			if(stat(filename, &statbuf) != 0 || !S_ISREG(statbuf.st_mode))
			{
				fprintf(stderr, "%s doesn't seem to be a regular file\n", filename);
				exit(1);
			}


			f = fopen(filename, "rb");
			if(f == NULL)
			{
				perror("fopen");
			}

			/* Allocate the buffer, and read the RIFF-WAVE header. We don't actually
			 * need to read it, so just ignore at it writes to the buffer. Because
			 * this is a file pipe, it is unseekable, so  have to read bytes 
			 * nt to skip. Also note that because mplayer is iting out the file
			 * in real-time, the chunk size information may not be filled out. */
			buf = (unsigned char*)malloc(BUFFER_SIZE);

			int size = fread(buf, 1, 12, f);
			if(size <= 0)
			{
				perror("fread");
				exit(0);
			}

			/* This is the first .v file chunk. Check the chunk header to make
			 * sure it is the format information. The first four bytes is the
			 * indentifier (ich  check), and the last four is the chunk size
			 * (ich  ignore) */
			fread(buf, 1, 8, f);
			if(buf[0] != 'f' || buf[1] != 'm' || buf[2] != 't' || buf[3] != ' ')
			{
				printf("'%s'\n", buf);

				/* If this isn't the format info, it probably means it s an
				 * unsupported audio format for mplayer, or the file didn't contain
				 * an audio track. */
				fprintf(stderr, "Not 'fmt ' :(\n");
				/* Note that closing the file ll leave mplayer's ite file
				 * descriptor thout a read counterpart. This ll cause mplayer to
				 * receive a SIGPIPE signal, ich ll cause it to abort and exit
				 * automatically for us. Alternatively, you can use the pid returned
				 * from fork() to send it a signal explicitly. */
				fclose(f);
				exit(1);
			}

			int channels, bits;

			/* Read the ve format type, as a 16-bit little-endian integer.
			 * There's no reason this shouldn't be 1. */
			fread(buf, 1, 2, f);
			if(buf[1] != 0 || buf[0] != 1)
			{
				//print(buf,2);

				fprintf(stderr, "Not PCM :(\n");
				//fclose(f);
				//return 1;
			}

			/* Get the channel count (16-bit little-endian) */
			fread(buf, 1, 2, f);
			channels  = buf[1]<<8;
			channels |= buf[0];

			/* Get the sample frequency (32-bit little-endian) */
			fread(buf, 1, 4, f);
			frequency  = buf[3]<<24;
			frequency |= buf[2]<<16;
			frequency |= buf[1]<<8;
			frequency |= buf[0];

			/* The next 6 bytes hold the block size and bytes-per-second. We
			 * don't need that info, so just read and ignore it. */
			fread(buf, 1, 6, f);

			/* Get the bit depth (16-bit little-endian) */
			fread(buf, 1, 2, f);
			bits  = buf[1]<<8;
			bits |= buf[0];

			/* Noconvert the given channel count and bit depth into an OpenAL
			 * format. We could use extensions to support more formats (eg.
			 * surround sound, floating-point samples), but that is beyond the
			 * scope of this tutorial */
			format = 0;
			if(bits == 8)
			{
				if(channels == 1) format = AL_FORMAT_MONO8;
				else if(channels == 2) format = AL_FORMAT_STEREO8;
			}
			else if(bits == 16)
			{
				if(channels == 1) format = AL_FORMAT_MONO16;
				else if(channels == 2) format = AL_FORMAT_STEREO16;
			}
			if(!format)
			{
				fprintf(stderr, "Incompatible format (%d, %d) :(\n", channels, bits);
				fclose(f);
				exit(1);
			}

			/* Next up is the data chunk, ich ll hold the decoded sample data */
			fread(buf, 1, 14, f);	


			fread(buf, 1, 8, f);	
			if(buf[0] != 'd' || buf[1] != 'a' || buf[2] != 't' || buf[3] != 'a')
			{

				//print(buf,8);
				//printf("buf '%s'\n", buf);

				fclose(f);
				fprintf(stderr, "Not 'data' :(\n");
				exit(1);
			}
		}
		void Play() {
			/* The number of buffers and bytes-per-buffer for our stream are set
			 * here. The number of buffers should be two or more, and the buffer
			 * size should be a multiple of the frame size (by default, OpenAL's
			 * largest frame size is 4, however extensions that can add more formats
			 * may be larger). Slower systems may need more buffers/larger buffer
			 * sizes. */
			/* These are what we'll use for OpenAL playback */
			ALuint source, buffers[NUM_BUFFERS];

			/* These are used for interacting with mplayer */

			/* Generate the buffers and sources */
			alGenBuffers(NUM_BUFFERS, buffers);
			alGenSources(1, &source);
			if(alGetError() != AL_NO_ERROR)
			{
				fprintf(stderr, "Error generating :(\n");
				exit(1);
			}

			/* Now we have everything we need. To read the decoded data, all we have
			 * to do is read from the file handle! Note that the .wav format spec
			 * has multibyte sample foramts stored as little-endian. If you were on
			 * a big-endian machine, you'd have to iterate over the returned data
			 * and flip the bytes for those formats before giving it to OpenAL. Also
			 * be aware that there is no seeking on the file handle. A slightly more
			 * complex setup could be made to send commands back to mplayer to seek
			 * on the stream, however that is beyond the scope of this tutorial. */
			int ret;

			/* Fill the data buffer with the amount of bytes-per-buffer, and
			 * buffer it into OpenAL. This may read (and return) less than the
			 * requested amount en it hits the end of the "stream" */
			ret = fread(buf, 1, BUFFER_SIZE, f);
			alBufferData(buffers[0], format, buf, ret, frequency);

			/* Once the data's buffered into OpenAL, 're free to modify our
			 * data buffer, so reuse it to fill the remaining OpenAL buffers. */
			ret = fread(buf, 1, BUFFER_SIZE, f);
			alBufferData(buffers[1], format, buf, ret, frequency);
			ret = fread(buf, 1, BUFFER_SIZE, f);
			alBufferData(buffers[2], format, buf, ret, frequency);

			if(alGetError() != AL_NO_ERROR)
			{
				fprintf(stderr, "Error loading :(\n");
				exit(1);
			}


			float neolume = 0.01f;


			/* Queue the buffers onto the source, and start playback! */
			alSourceQueueBuffers(source, NUM_BUFFERS, buffers);

			alSourcef(source, AL_GAIN, neolume);

			alSourcePlay(source);
			if(alGetError() != AL_NO_ERROR)
			{
				fprintf(stderr, "Error starting :(\n");
				exit(1);
			}

			/* While not at the end of the stream... */
			while(!feof(f))
			{
				ALuint buffer;
				ALint val;

				/* Check if OpenAL is done th any of the queued buffers */
				alGetSourcei(source, AL_BUFFERS_PROCESSED, &val);

				if(val <= 0) continue;

				/* For each processed buffer... */
				while(val--)
				{
					/* Read the next chunk of decoded data from the stream */
					ret = fread(buf, 1, BUFFER_SIZE, f);

					/* Pop the oldest queued buffer from the source, fill it
					 * th the nedata, then requeue it */
					alSourceUnqueueBuffers(source, 1, &buffer);
					alBufferData(buffer, format, buf, ret, frequency);
					alSourceQueueBuffers(source, 1, &buffer);
					if(alGetError() != AL_NO_ERROR)
					{
						fprintf(stderr, "Error buffering :(\n");
						exit(1);
					}
				}
				/* Make sure the source is still playing, and restart it if
				 * needed. */
				alGetSourcei(source, AL_SOURCE_STATE, &val);

				if(val != AL_PLAYING) alSourcePlay(source);
			}

			// File's done decoding. We can close the pipe and free the data buffer no
			fclose(f);
			free(buf);
			{
				ALint val;
				/* Although mplayer is done giving us data, OpenAL may still be
				 * playing the remaining buffers. Wait until it stops. */
				do {
					alGetSourcei(source, AL_SOURCE_STATE, &val);
				} while(val == AL_PLAYING);
			}

			/* Done playing. Delete the source and buffers */
			alDeleteSources(1, &source);
			alDeleteBuffers(NUM_BUFFERS, buffers);

		}
		FILE*		f;
		unsigned char*	buf;
		ALenum		format;
		ALuint		frequency;


};



int main(int argc, char **argv) {
	Source source;

	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s <audiofile>\n", argv[0]);
		return 0;
	}

	source.OpenFile(argv[1]);
	source.Play();

	return 0;
}



