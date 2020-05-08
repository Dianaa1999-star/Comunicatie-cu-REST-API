#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "utils.h"


int main(int argc, char* argv[]) {
    // mesajul care va fi trimis
    char *message;
    message = (char*)calloc(100, sizeof(char));
    // mesajul care va fi primit
    char *response;
    int sockfd = 0;
    // variabile pentru declararea unui cont
    char* username = (char*)calloc(100, sizeof(char));
    char* pass = (char*)calloc(100, sizeof(char));
    // comanda citita
    char* task = (char*)calloc(100, sizeof(char));
    // token-ul care demonstreaza accesul la biblioteca
    char* mytoken;
    // mesajul creeat
    char* loginData ;
    // le initializez cu NULL
    mytoken = NULL; 
    loginData = NULL;
    response = NULL;
    // variabile pentru declararea unei carti
    char* page_count = (char*)calloc(100, sizeof(char));
    char* namebook = (char*)calloc(100, sizeof(char));
    char* author = (char*)calloc(100, sizeof(char));
    char* genre = (char*)calloc(100, sizeof(char));
    char* publisher = (char*)calloc(100, sizeof(char));
   
    // variabila de oprire
    int ok = 1;
    // cooki-ul care demonstreaza inregistrarea
    // in cont
    char* cookies;
    cookies = NULL;
    while (ok == 1) {
        // citesc comanda de la tastatura
        scanf("%s", task);
        // in caz ca primeste comanda exit iese din bucla
        if (!strcmp(task, "exit")) {
            ok = 0;
            break;
        } else {
            if (strcmp(task, "register") == 0) {
                // functie apelata cand primeste comanda register
                register_func(username, pass, message, response, loginData, sockfd);
            } else if (strcmp(task, "login") == 0) {
                // functie apelata cand primeste comanda login
                response = login_func(username, pass, message, response, loginData, sockfd);
                // pastrez cookie-ul pentru a dovedi ca sunt intregistrata
                // in cont
                cookies = addCookies(cookies,response);   
                free(response);
            } else if (strcmp(task, "enter_library") == 0) {
                // functie apelata cand primesc comanda enter_library
                response = enter_func(sockfd, message, response, cookies);
                // pastrez token-ul pentru a dovedi accesul la biblioteca
                mytoken = tokens(mytoken, response);
                free(response);
            } else if (strcmp(task, "get_books") == 0) {
                // functie apelata cand primesc comanda get_books
                get_books_func(message, sockfd, response, mytoken, cookies);
            } else if (strcmp(task, "get_book") == 0) {
                // functie apelata cand primesc comanda get_book
                get_book_func(message, sockfd, response, mytoken);
            } else if (strcmp(task, "add_book") == 0) {
                // functie apelata cand primesc comanda add_book
                add_book_func(sockfd, namebook, author, genre, publisher,
                page_count, message, response, mytoken, loginData);

            } else if (strcmp(task, "delete_book") == 0) {
                // functie apelata cand primesc comanda delete_book
                delete_book_func(sockfd, message, response, mytoken);
                
            } else if (strcmp(task, "logout") == 0) {
                // functie apelata cand primesc comanda logout
                logout_func(sockfd, message, response, cookies);
            }
        }
    }
    // eliberez spatiul alocat
    free(page_count);
    free(publisher);
    free(namebook);
    free(author);
    free(genre);
    free(username);
    free(pass);
    free(response);
    free(message);
    // inchid conexiunea
    close_connection(sockfd);

    return 0;
}
