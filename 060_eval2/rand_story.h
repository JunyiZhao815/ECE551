#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>
#include <string.h>

#include "provided.h"
//any functions you want your main to use
void checkValid(FILE * f);
void printStory(FILE * f, catarray_t * cat);

int fill(char * temp, catarray_t * cats, char * pointer, int pointer_size);
#endif
