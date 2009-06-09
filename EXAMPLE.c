/*
   This software is in the public domain, furnished "as is", without
   technical support, and with no warranty, express or implied, as to its
   usefulness for any purpose.

   gcc -w -std=c99 -g3 -ggdb -o scrobsub-example -I. EXAMPLE.c -lcrypto -lxml2 -lcurl
*/
#define SCROBSUB_NO_RELAY 1
#define SCROBSUB_CLIENT_ID "ass"

#include "scrobsub.c"
#include "auth-libxml2.c"
#include "http-curl.c"
#include "md5.c"
#include "persistence-simple.c"
#include <unistd.h>


static void callback(int e, const char* s)
{
    if (e == SCROBSUB_AUTH_REQUIRED)
    {
        char url[110];
        scrobsub_auth(url);
        printf("Please visit\n%s\nto authorize scrobbling and then press enter to continue.\n", url);
        char c = getc(stdin);
    }
}


int main()
{
    scrobsub_init(callback);
    scrobsub_start("Max Howell", "Is Fucking Awesome", 60, "Audioscrobbler EXAMPLE", 0, "");
    printf("Fake track is playing for 60 seconds...\n");
    sleep(60);
    scrobsub_stop();
    return 0;
}
