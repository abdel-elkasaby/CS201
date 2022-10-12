#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
//#define NDEBUG
#include <assert.h>

extern size_t vstrlen(const char *);
extern char *vstrcpy(char *, const char *);
extern char *vstrcat(char *, const char *);

int main (void) {

#ifdef ARRAY
    printf("testing using array syntax\n");
#else //ARRAY
    printf("testing using pointer syntax\n");
#endif //ARRAY

    // vstrlen tests
    {
        char str0[5] = "";
        char str1[] = "123456789";
        char str2[50] = "123456";

        assert(vstrlen(str0) == strlen(str0));
        assert(vstrlen(str1) == strlen(str1));
        assert(vstrlen(str2) == strlen(str2));
        assert(vstrlen("abc") == strlen("abc"));
    }
    printf("vstrlen passes all tests\n");

    //vstrcpy tests
    {
        char str0[5] = "";
        char str1[50] = "123456";
        char str2[50] = "123456";

        assert(strcmp(vstrcpy(str1, str0), strcpy(str2, str0)) == 0);
        assert(strcmp(str1, str2) == 0);
    }

    {
        char str0[50] = "";
        char str1[50] = "";
        char str2[50] = "123456";

        assert(strcmp(vstrcpy(str0, str2), strcpy(str1, str2)) == 0);
        assert(strcmp(str0, str1) == 0);
    }

    {
        char str0[] = "123456789";
        char str1[50] = "abcdef";
        char str2[50] = "abcdef";

        assert(strcmp(vstrcpy(str1, str0), strcpy(str2, str0)) == 0);
        assert(strcmp(str1, str2) == 0);
    }

    {
        char str1[50] = "";
        char str2[50] = "";

        assert(strcmp(vstrcpy(str1, "abc"), strcpy(str2, "abc")) == 0);
        assert(strcmp(str1, str2) == 0);
    }
    printf("vstrcpy passes all tests\n");

    //vstrcat tests
    {
        char str0[] = "123456789";
        char str1[50] = "abcdef";
        char str2[50] = "abcdef";

        assert(strcmp(vstrcat(str1, str0), strcat(str2, str0)) == 0);
        assert(strcmp(str1, str2) == 0);
    }

    { 
        char str0[5] = "";
        char str1[50] = "123456";
        char str2[50] = "123456";
        
        assert(strcmp(vstrcat(str1, str0), strcat(str2, str0)) == 0);
        assert(strcmp(str1, str2) == 0);
    }

    {
        char str1[50] = "123456";
        char str2[50] = "123456";

        assert(strcmp(vstrcat(str1, "a"), strcat(str2, "a")) == 0);
        assert(strcmp(str1, str2) == 0);
    }

    {
        char str1[50] = "abcdef";
        char str2[50] = "abcdef";

        assert(strcmp(vstrcat(str1, "123456789"), strcat(str2, "123456789")) == 0);
        assert(strcmp(str1, str2) == 0);
    }

    printf("vstrcat passes all tests\n");

    return EXIT_SUCCESS;
}