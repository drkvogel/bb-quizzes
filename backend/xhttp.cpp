#ifndef XHTTP_C_INCLUDED
#define XHTTP_C_INCLUDED

#ifndef __WIN32__

#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>

#define SOCKET_ERROR -1

#endif

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <errno.h>
#include <string.h>
#include "xhttp.h"
#include "xtime.h"
//#include "bbquiz.h"

#define DBG_LOGFILE logfile

#define DBG_PRINT(x)    fprintf(DBG_LOGFILE, "%s", x); fflush(logfile);
#define DBG_PRINT2(x,y) fprintf(DBG_LOGFILE, x, y); fflush(logfile);

void xhttp_htmlspecialchars(char *out, char *in) {

    while (*in != '\0') {
        // switch?
        if (*in == '<') {
            *out++ = '&';
            *out++ = 'l';
            *out++ = 't';
        } else if (*in == '>') {
            *out++ = '&';
            *out++ = 'g';
            *out++ = 't';
        } else if (*in == '&') {
            *out++ = '&';
            *out++ = 'a';
            *out++ = 'm';
            *out++ = 'p';
        } else if (*in == '"') {
            *out++ = '&';
            *out++ = 'q';
            *out++ = 'u';
            *out++ = 'o';
            *out++ = 't';
        } else if (*in == '\'') {
            *out++ = '&';
            *out++ = '#';
            *out++ = '0';
            *out++ = '3';
            *out++ = '9';
        } else if (*in == '\n') {
            *out++ = '<';
            *out++ = 'b';
            *out++ = 'r';
            *out++ = '>';
            *out++ = '\\';
            *out++ = 'n';
        } else {
            *out++ = *in;
        }
        *in++;
    }
    *out = '\0';
}

// url encode chars for http transmission and ignore non-sms compatible chars
void smsspecialchars(char *out, char *in) {

    char buf[10];

    while (*in != 0) {
        if (    (*in == '\x21')                     ||  // !
                (*in == '\x24')                     ||  // ??
                (*in >= '\x27' && *in <= '\x2b')    ||  // ' () * +
                (*in == '\x2d')                     ||  // -
                (*in >= '0' && *in <= '9')          ||  // 0-9
                (*in == '\x40')                     ||  // @ - different in gsm though
                (*in >= 'A' && *in <= 'Z')          ||  // A-Z
                (*in == '\x5f')                     ||  // _ - different in gsm
                (*in >= 'a' && *in <= 'z'))             // a-z
        {
            *out++ = *in++;
        } else {
            switch (*in) {
                case '\x0a':        // LF
                case '\x0d':        // CR
                case '\x20':        // SP
                case '\x22':        // "
                case '\x23':        // #
                case '\x25':        // %
                case '\x26':        // &
                case '\x2c':        // ,
                case '\x2e':        // .
                case '\x2f':        // /
                case '\x3a':        // :
                case '\x3b':        // ;
                case '\x3d':        // <
                case '\x3e':        // >
                case '\x3f':        // ?

                    sprintf(buf, "%%%2.2x", (int)*in);
                    memcpy(out, buf, strlen(buf));
                    out += strlen(buf);
                    *in++;
                    break;

                default:
                    *in++;
            }
        }
    }
    *out = 0;
}

// url encodes a whole url, preserving url special characters $&,/:;=?@
// n.b. does not preserve +, should use %20 for space instead
void xhttp_urlencode_url(char *out, char *in) {

    char buf[10];

    while (*in != 0) {
        if (   // url reserved characters
                (*in == '\x24')                     ||  // $
                (*in == '\x26')                     ||  // &
                (*in == '\x2c')                     ||  // ,
                (*in == '\x2f')                     ||  // /
                (*in == '\x3a')                     ||  // :
                (*in == '\x3b')                     ||  // ;
                (*in == '\x3d')                     ||  // =
                (*in == '\x3f')                     ||  // ?
                (*in == '\x40')                     ||  // @

                // other allowed characters
                (*in == '\x2d')                     ||  // -
                (*in == '\x2e')                     ||  // .
                (*in == '\x5f')                     ||  // _
                (*in >= '0' && *in <= '9')          ||  // 0-9
                (*in >= 'A' && *in <= 'Z')          ||  // A-Z
                (*in >= 'a' && *in <= 'z'))             // a-z
        {
                *out++ = *in++;
        } else {
            sprintf(buf, "%%%2.2x", (int)*in);
            memcpy(out, buf, 3);
            out += 3;
            *in++;
        }
    }
    *out = 0;
}



// url encodes a string BEFORE it is added to a url
void xhttp_urlencode_string(char *out, char *in) {

    // url encode chars for http transmission
    char buf[10];
    char *out_orig;

    //XXXout_orig = out;

    //printf("*in: %s,\nin: %d\n\n", in, in);

    *out = 0;     // for strcat

    while (*in != 0) {
        if (   (*in == '\x2d')                      ||  // -
                (*in == '\x2e')                     ||  // .
                (*in == '\x5f')                     ||  // _
                (*in >= '0' && *in <= '9')          ||  // 0-9
                (*in >= 'A' && *in <= 'Z')          ||  // A-Z
                (*in >= 'a' && *in <= 'z'))             // a-z
        {
            *out++ = *in++;
        } else {
            sprintf(buf, "%%%2.2x", (int)*in);
            memcpy(out, buf, strlen(buf));
            out += strlen(buf);
            *in++;
        }
    }
    *out = 0;
}

struct hostent* gethost(void) {
    static struct hostent* hst = NULL;

    if (!hst) {
        hst = gethostbyname(XHTTP_HOST_NAME);
    }

    return hst;
}

int xhttp_send_request(char **response, char *request) {
    char *obuf, *optr;
    char ibuf[1024], *iptr;
    int olen, sock, iret, ilen;
    struct hostent *hst;
    struct sockaddr_in name;

    olen = strlen(request);
    obuf = (char *)malloc(olen + 5);
    strcpy(obuf, request);

    // Get a socket for the connection
#ifdef __WIN32__
    WORD wVersionRequested;
    WSADATA wsaData;
    wVersionRequested = MAKEWORD( 2, 2 );
    int err = WSAStartup( wVersionRequested, &wsaData );
    if ( err != 0 ) {
        return 1;
    }
#endif

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == SOCKET_ERROR) {
#ifdef __WIN32__
        int sock_error = GetLastError();
        DBG_PRINT2("Socket error: code %d\n", sock_error);
#else
        DBG_PRINT("Socket error: couldn't get socket\n");
#endif
	    DBG_PRINT2("errno:%d", errno);
        free(obuf);
        return errno;
    };

    // Get the address of the host
    hst = gethost();
    if (!hst) {
        DBG_PRINT("Error: couldn't get host address\n")
        free(obuf);
	    DBG_PRINT2("errno:%d", errno);
        return errno;
    };

    // Set up connection info for the proxy
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = *(int *)hst->h_addr;
    name.sin_port = htons(XHTTP_HOST_PORT);

    // Connect to the http proxy
    iret = connect(sock, (struct sockaddr *)&name, sizeof(struct sockaddr));

    if (iret == SOCKET_ERROR) {
        DBG_PRINT("Socket error: couldn't connect to host\n");
        free(obuf);
	    DBG_PRINT2("errno:%d", errno);
        return errno;
    };
    //DBG_PRINT("no sock error\n");

    // Send our request
    optr = obuf;
    while (olen) {
        iret = send(sock, optr, olen, 0);

        if (iret == SOCKET_ERROR) {
            DBG_PRINT("Socket error: couldn't send request\n");
            free(obuf);
            DBG_PRINT2("errno:%d", errno);

            return errno;
        } else {
            optr += iret;
            olen -= iret;
        };
    };
    //DBG_PRINT("-sent");
    //DBG_PRINT2(" req:\n%s\n", obuf);

    // Loop on receive (receive flags a dropped connection by returning zero)
    ilen = 0;
    iret = recv(sock, ibuf, sizeof(ibuf), 0);

    //DBG_PRINT("-received");
    *response = (char *)malloc((iret + 1) * sizeof(char));
    while (iret > 0) {
        *response = (char *)realloc((void *)(*response), (ilen + iret + 1)*sizeof(char));
        iptr = *response;
        iptr += ilen;
        strncpy(iptr, ibuf, iret); // smsq_results becomes corrupted after this
        ilen += iret;
        iret = recv(sock, ibuf, sizeof(ibuf), 0);
    };

    // null terminate
    iptr = *response + ilen;
    *iptr = '\0';
    if (iret == SOCKET_ERROR) {
        DBG_PRINT2("Socket error on receiving response; errno: ", errno);
        //free(obuf);
        return errno;
    }

    // Shut and close socket
    iret = shutdown(sock, 1);
    if (iret == SOCKET_ERROR) {
        DBG_PRINT2("Socket error: errno:%d", errno); ;
        //free(obuf);
        return errno;
    }

#ifdef __WIN32__
    closesocket(sock);
#else
    close(sock);
#endif

    /* obuf and request should be freed in calling func */

    return (EXIT_SUCCESS);
}

int xhttp_proxy_send_request(char **response, char *request) {
    char *obuf, *optr;
    char ibuf[102400], *iptr;
    int olen, sock, iret, ilen;
    struct hostent *hst;
    struct sockaddr_in name;

    olen = strlen(request);
    obuf = (char *)malloc(olen + 1);
    strcpy(obuf, request);

    // Get a socket for the connection
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == SOCKET_ERROR) {
        DBG_PRINT("Socket error: couldn't get socket\n");
        free(obuf);
	    DBG_PRINT2("errno:%d", errno);
        return errno;
    };
    // Get the address of the http proxy
    //hst = gethostbyname(CTSU_PROXY_NAME);
    hst = gethost();
    if (!hst) {
        DBG_PRINT("Error: couldn't get proxy address\n")
        free(obuf);
	    DBG_PRINT2("errno:%d", errno);
        return errno;
    };
    //DBG_PRINT("Got address for " XHTTP_HOST_NAME "\n");
    // Set up connection info for the proxy
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = *(int *)hst->h_addr;
    name.sin_port = htons(XHTTP_HOST_PORT);

    // Connect to the http proxy
    iret = connect(sock, (struct sockaddr *)&name, sizeof(struct sockaddr));
    if (iret == SOCKET_ERROR) {
        DBG_PRINT("Socket error: couldn't connect to http proxy\n");
        free(obuf);
	    DBG_PRINT2("errno:%d", errno);
        return errno;
    };

    // Send our request
    optr = obuf;
    while (olen) {
        iret = send(sock, optr, olen, 0);
        if (iret == SOCKET_ERROR) {
            DBG_PRINT("Socket error: couldn't send request\n");
            free(obuf);
            DBG_PRINT2("errno:%d", errno);

            return errno;
        } else {
            optr += iret;
            olen -= iret;
        };
    };

    // Loop on receive (receive flags a dropped connection by returning zero)
    ilen = 0;
    iret = recv(sock, ibuf, sizeof(ibuf), 0);
    while (iret > 0) {
        *response = (char *)realloc((void *)(*response), (ilen + iret)*sizeof(char));
        iptr = *response;
        iptr += ilen;
        strncpy(iptr, ibuf, iret);
        ilen += iret;
        iret = recv(sock, ibuf, sizeof(ibuf), 0);
    };

    // null terminate
    iptr = *response + ilen;
    *iptr = '\0';
    if (iret == SOCKET_ERROR) {
        DBG_PRINT2("Socket error on receiving response; errno: ", errno);
        free(obuf);
        return errno;
    }

    // Shut and close socket
    iret = shutdown(sock, 1);
    if (iret == SOCKET_ERROR) {
        DBG_PRINT2("Socket error: errno:%d", errno);
        return errno;
    }

#ifdef __WIN32__
    closesocket(sock);
#else
    close(sock);
#endif
    //free(obuf);
    printf("");
    return (EXIT_SUCCESS);
}

int xhttp_get(char **response, const char *url) {
    int result;
    char *requestbuf;
    requestbuf = (char *)malloc((strlen("GET  HTTP/1.0\n\n") + strlen(url) + 50) * sizeof(char));
    sprintf(requestbuf, "GET %s HTTP/1.0\n\n", url);
    //DBG_PRINT2("REQUEST: %s\n\n", requestbuf);
    result = xhttp_send_request(response, requestbuf);
    //DBG_PRINT2("RESPONSE %s\n\n", *response); //???
    free(requestbuf);
    return result;
}

int xhttp_post(char **response, char *url, char *content, char *contentType, char *host) {
    int result;
    char *requestbuf;
    char *contentbuf;
    requestbuf = (char *)malloc((strlen("POST ") + strlen(url) +
                                + strlen (" HTTP/1.0\n\nContent-Type: \r") + strlen(contentType)
                                + strlen("Host: \r") + strlen(host)
                                + strlen("Content-Length: \n\n") + strlen(content) + 20) * sizeof(char));
    sprintf(requestbuf, "POST %s HTTP/1.0\rContent-Type: %s\rHost: %s\rContent-Length: %d\n\n%s",
            url, contentType, host, strlen(content), content);
    result = xhttp_send_request(response, requestbuf);
    free(requestbuf);
    return result;
}

#endif
