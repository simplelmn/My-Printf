#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "limits.h"

void my_putchar(char c){
    write(1,&c,1);
}
//--------------------
int my_putstr(char * s){
    int i =0;
    while(s[i]){
        my_putchar(s[i++]);
    }
    return i;
}
//--------------------
char* convertIntToString(int n, int o){
    int arr[10000];
    int arr_ind = 0;
    int neg=0;
    if(n < 0){
        n = n*(-1);
        neg++;
    }
    while(n > 0){
        arr[arr_ind] = n % 10;
        n = n / 10;
        arr_ind++;
    }
    char *res;
    res = malloc(arr_ind);
    char * negres;
    negres = malloc(arr_ind+1);
    int res_ind = 0;
    for(int i = arr_ind - 1; i >= 0; i--){
        res[res_ind] = arr[i] + '0';
        res_ind++;
    }
    if(neg > 0){
        if(o == 0){
            negres[0]= '-';
            for(int i = 0 ; i < strlen(res); i++ ){
                negres[i+1] = res[i] ;
            }
        return negres;
        }
        else{
        return res;
        }
    }
    return res;
}
char* sendaddress(unsigned long int x, int col){
    unsigned long int firstnum = x;
    unsigned int len = 0;
    char* result = NULL;
    unsigned long int temp_n;

    firstnum = firstnum > 0 ? firstnum : -(firstnum);
    while(x){
        x = x/col;
        len++;
    } 
    if(!(result = (char*)malloc(sizeof(char) * len + 1))){
        return NULL;
    }
    *(result + len) = '\0';
    len--;
    while(firstnum > 0){
        temp_n = firstnum % col;
        if(temp_n < 10)
            *(result + len) = temp_n + '0';
        else 
            *(result + len) = ((temp_n)-10 + 97);
        firstnum = firstnum / col;
        len--;
    }
    return result;
}
//-----------------------
int my_printf(char* s, ...){
    va_list list;
    va_start(list, s);
    int x;
    int len;
    intptr_t value_p;
    char ch;
    char* str;
    int j = 0;
    void* p;
    char* string = NULL;
    char buffer[10000];
    for(int i =0 ; i < strlen(s); i++){
        if(s[i] == '%'){
            i++;
            switch (s[i]) {
                //10-digit number system
                case 'd':                             
                    x=va_arg(list, int);    //my_printf("%d", x)
                    if(x == 0){
                        char zero = x + '0';
                        my_putchar(zero);
                        j++;
                    }
                    else{
                        my_putstr(convertIntToString(x,0));
                        j = j + strlen(convertIntToString(x,0));
                    }
                break;
                case 'u': 
                    x=va_arg(list, int);
                    if(x == 0){
                        char zero = x + '0';
                        my_putchar(zero);
                        j++;
                    }
                    else{
                        my_putstr(convertIntToString(x,1));
                        j = j + strlen(convertIntToString(x,1));
                    }
                break;

                case 'o':
                    x = va_arg(list, int);
                    char octalNumber[10000], i = 0;
                    while (x != 0){
                        octalNumber[i++] = x % 8 + '0';
                        x = x / 8;
                        j++;
                    }
                    for(int i =strlen(octalNumber)-1 ; i >= 0; i--){
                        my_putchar(octalNumber[i]);
                    }
                break;
                case 'x':
                    x = va_arg(list, int);
                    int remainder;
                    int ind = 0;
                    char hexadecimalnum[100];

                    while (x != 0)
                    {
                        j++;
                        remainder = x % 16;
                        if (remainder < 10)
                            hexadecimalnum[ind++] = 48 + remainder;
                        else
                            hexadecimalnum[ind++] = 55 + remainder;
                        x = x / 16;
                    }
                    my_putstr(hexadecimalnum);
                break;
                case 'p':
                    value_p = va_arg(list, intptr_t);
                    string = sendaddress(value_p, 16);
                    write(1, "0x", 2);
                    len = my_putstr(string);
                    j += len+2;
                break; 
                
                case 's':
                    str = (char*)va_arg(list, char*);
                    j+=my_putstr(str);
                break;
 
                case 'c':
                    ch = (char)va_arg(list, int); 
                    my_putchar(ch);
                    j++;
                break;
            }
        }//it is for increment
        else{
            my_putchar(s[i]);
            j++;
        }
    }
    return j;
}
// ----------------
// int main()
// {
//    int x = 987654356, j =0;
//    j = my_printf("%u\n", -10000);
//     //my_printf("%d", j);
//     return 0;
// }