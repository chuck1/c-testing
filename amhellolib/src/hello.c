#include <config.h>
#include <stdio.h>

#include <hello.h>

int
hello (void)
{
  puts ("Hello World!");
  puts ("This is " PACKAGE_STRING ".");
  return 0;
}


