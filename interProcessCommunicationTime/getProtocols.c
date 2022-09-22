#include <netdb.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    struct protoent *search;

    search = getprotobyname(argv[1]);
    endprotoent();

    printf("%s:%d\n", search->p_name, search->p_proto);

    return 0;
}
