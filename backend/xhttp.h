#ifndef xhttp_h
#define xhttp_h

#include <stdio.h>
#include <errno.h>
#include <string>
#include "xtime.h"

#define XHTTP_HOST_NAME "red.ctsu.ox.ac.uk/~cp/cjb/matrix"
#define XHTTP_HOST_PORT 80

extern std::string timebuf;
extern XTIME logtime;
extern FILE * logfile;

void xhttp_htmlspecialchars(char *out, char *in);

void smsspecialchars(char *out, char *in);

void xhttp_urlencode_url(char *out, char *in);

void xhttp_urlencode_string(char *out, char *in);

struct hostent* gethost(void);

int xhttp_send_request(char **response, char *request);

int xhttp_proxy_send_request(char **response, char *request);

int xhttp_get(char **response, const char *url);

int xhttp_post(char **response, char *url, char *content, char *contentType, char *host);

#endif
