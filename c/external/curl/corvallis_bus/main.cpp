#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SIZE 2000

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	char** memp = (char**)userp;
	
	//*memp = (char*)malloc(realsize);
	
	if(*memp == NULL) {
		/* out of memory! */ 
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(*memp, contents, realsize);


	return realsize;
}



int main(int ac, char** av)
{
	CURL *curl;
	CURLcode res;

	int routeno = atoi(av[1]);

	char * p = (char*)malloc(SIZE);

	char str_routeno[20];
	sprintf(str_routeno, "RouteNo=\"%i\"", routeno);

	curl = curl_easy_init();
	if(!curl) exit(1);


	char const * url = "http://www.corvallistransit.com/rtt/public/utility/file.aspx?contenttype=SQLXML&Name=RoutePositionET.xml&PlatformTag=311";

	curl_easy_setopt(curl, CURLOPT_URL, url);

	/* example.com is redirected, so we tell libcurl to follow redirection */ 
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);


	/* send all data to this function  */ 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

	/* we pass our 'chunk' struct to the callback function */ 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&p);


	/* Perform the request, res will get the return code */ 
	res = curl_easy_perform(curl);

	/* Check for errors */ 
	if(res != CURLE_OK)
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(res));

	char * a = strstr(p, str_routeno);

	if(a == NULL) {
		fprintf(stderr, "route not found\n");
		fprintf(stderr, "%s\n", p);
		exit(1);
	}

	char * b = strstr(a, "ETA=\"");

	if(b == NULL) {
		fprintf(stderr, "ETA not found\n");
		exit(1);
	}

	b += 5;

	char * c = strchr(b, '"');

	if(c == NULL) {
		fprintf(stderr, "parse error\n");
		exit(1);
	}

	*c = 0;

	printf("%s\n", b);

	/* always cleanup */ 
	curl_easy_cleanup(curl);

	return 0;
}

