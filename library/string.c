#include "string.h"

int strcmp(char* str1, char* str2){
	int index = 0;
	while((str1[index] != '\0') && (str1[index] == str2[index])){
		index++;
	}
	//while (*str1 && *str1==*str2){
	//	str1++, str2++;
	//}
	//return *str1 - *str2;
	return str1[index] - str2[index];
}

size_t strlen(const char *str){
	size_t count = 0;
	while(str[count] != '\0'){
		count++;
	}
	return count;
}
