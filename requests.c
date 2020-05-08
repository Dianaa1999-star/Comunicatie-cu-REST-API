#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "utils.h"

char *compute_get_request(char *host, char *url, char *query_params,
                            char *cookies, char *token) {
	// aloc memorie
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // scriu url-ul , implicit query_params daca exista
    if (query_params != NULL) {
        sprintf(line,  "GET %s?%s HTTP/1.1", url, query_params);
    } else {
        sprintf(line, "GET %s HTTP/1.1", url);
    }
    compute_message(message, line);

    // adaug sursa
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
    // daca exista un cookie, il scriu
    if (cookies != NULL) {
        sprintf(line, "Cookie: ");
        sprintf(line + strlen(line), " %s", cookies);

        compute_message(message, line);
    }
    // daca exista un token , il scriu
    if (token!= NULL) {
        sprintf(line, "Authorization: Bearer");
        sprintf(line + strlen(line), " %s", token);

        compute_message(message, line);
    }

    // adaug o linie goala la final
    compute_message(message, "");
    return message;
}

char *compute_delete_request(char *host, char *url, char *query_params,
                            char *cookies, char *token) {
	// aloc memorie
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));
	
	// scriu url-ul   
    sprintf(line, "DELETE %s HTTP/1.1", url);
    compute_message(message, line);

    // adaug sursa
    sprintf(line, "Host: %s", host);
    compute_message(message, line);
     // daca exista un token , il scriu
     if (token!= NULL) {
        sprintf(line, "Authorization: Bearer");
        sprintf(line + strlen(line), " %s", token);
        compute_message(message, line);
    }

    // adaug o linie goala la final
    compute_message(message, "");
    return message;
}


char *compute_post_request(char *host, char *url, char* content_type, char *body_data,
                            char *cookies, char *token) {
	// aloc memorie
    char *message = calloc(BUFLEN, sizeof(char));
    char *line = calloc(LINELEN, sizeof(char));

    // scriu url-ul
    sprintf(line, "POST %s HTTP/1.1", url);
    compute_message(message, line);

    // adaug sursa
    sprintf(line, "Host: %s", host);
    compute_message(message, line);

    // scriu tipul mesajului
    sprintf(line, "Content-Type: %s", content_type);
    compute_message(message, line);

    // scriu lungimea mesajului
    sprintf(line, "Content-Length: %ld", strlen(body_data));
    compute_message(message, line);
    // daca exista un cookie, il scriu
    if (cookies != NULL) {
        sprintf(line, "Cookie: %s", cookies);
        compute_message(message, line);
    }
    // daca exista un token , il scriu
    if (token != NULL) {
        sprintf(line, "Authorization: Bearer %s",token);
        compute_message(message, line);
    }

    // adaug o linie goala la final
    compute_message(message, "");

    // adaug payload-ul
    compute_message(message, body_data);
    return message;
}

