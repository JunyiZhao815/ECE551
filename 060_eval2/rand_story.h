#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "provided.h"
//any functions you want your main to use
void checkValid(char * argv1);
void printStory(char * argv1, catarray_t * cat);
int fill(char * temp, catarray_t * cats, char * pointer, int pointer_size);
void checking_colon(char * line);
void create_category(char * category, catarray_t * ans, char * replacement);
void freeAns(catarray_t * ans);
void step2convert(char * argv1);

#endif
