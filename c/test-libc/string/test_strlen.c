#include <stdio.h>
#include <string.h>

int string_main()
{
    char *str = "1234567890";
    printf("strlen(\"%s\") = %d\n", str, (int)strlen(str));
    return 0;
}
