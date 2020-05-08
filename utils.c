#include <stdlib.h> /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "utils.h"
#include "helpers.h"
#include "parson.h"
#include "requests.h"
#define HOST_IP "3.8.116.10"

// parseaza cookie-ul primit
char* addCookies(char* cookies, char* str) {
    char* p = strstr(str, "connect.sid");
    strtok(p, ";");
    return p;
}
// parseaza token-ul primit
char* tokens(char* tokens, char* str) {
    char* p = strstr(str, "eyJ");
    strtok(p, "\"");
    return p;
}
void register_func(char* username, char* pass,
    char* message, char* response, char* loginData, int sockfd) {
    // citesc username-ul si parola
    printf("username=");
    scanf("%s", username);
    printf("password=");
    scanf("%s", pass);
    // deschid conexiunea
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);

    JSON_Value* root_value = json_value_init_object();
    JSON_Object* root_object = json_value_get_object(root_value);
    // creez payload-ul
    json_object_set_string(root_object, "username", username);
    json_object_set_string(root_object, "password", pass);
    loginData = json_serialize_to_string_pretty(root_value);
    // creez mesajul
    message = compute_post_request(HOST_IP,
     "/api/v1/tema/auth/register", "application/json", loginData, NULL, NULL);
    // il trimit la server
    send_to_server(sockfd, message);
    printf("%s\n", message);
    // primesc mesajul de la server
    response = receive_from_server(sockfd);
    // daca nu am primit niciun mesaj
    if (response == NULL) {
        // deschid iar conexiunea
        sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
        // trimit iar mesajul
        send_to_server(sockfd, message);
        printf("%s\n", message);
        response = receive_from_server(sockfd);
    }
    // afisez mesajul primit
    printf("%s\n", response);
    puts("");
    // eliberez memoria folosita
    free(response);
    free(message);
    free(loginData);
}

char* login_func(char* username, char* pass, char* message1,
    char* response1, char* loginData1, int sockfd) {
    // citesc username-ul si parola
    printf("username=");
    scanf("%s", username);
    printf("password=");
    scanf("%s", pass);
    // deschid conexiunea
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
    JSON_Value* root_value1 = json_value_init_object();
    JSON_Object* root_object1 = json_value_get_object(root_value1);
    // creez payload-ul
    json_object_set_string(root_object1, "username", username);
    json_object_set_string(root_object1, "password", pass);
    loginData1 = json_serialize_to_string_pretty(root_value1);
    // creez mesajul
    message1 = compute_post_request(HOST_IP, "/api/v1/tema/auth/login",
    "application/json", loginData1, NULL, NULL);
    // il trimit la server
    send_to_server(sockfd, message1);
    printf("%s\n", message1);
    // primesc mesajul de la server
    response1 = receive_from_server(sockfd);
    // daca nu am primit niciun mesaj
    if (response1 == NULL) {
        // deschid iar conexiunea
        sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
        // trimit iar mesajul
        send_to_server(sockfd, message1);
        printf("%s\n", message1);
        response1 = receive_from_server(sockfd);
    }
    // afisez mesajul primit
    printf("%s\n", response1);
    puts("");
    // eliberez memoria folosita
    free(loginData1);
    free(message1);
    free(username);
    free(pass);
    return response1;
}
char* enter_func(int sockfd, char* message2, char* response2, char* cookies) {
    // deschid conexiunea
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
    // creez mesajul
    message2 = compute_get_request(HOST_IP, "/api/v1/tema/library/access",
    NULL, cookies, NULL);
    // il trimit la server
    send_to_server(sockfd, message2);
    printf("%s\n", message2);
    // primesc mesajul de la server
    response2 = receive_from_server(sockfd);
    // daca nu am primit niciun mesaj
    if (response2 == NULL) {
        // deschid iar conexiunea
        sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
        // trimit iar mesajul
        send_to_server(sockfd, message2);
        printf("%s\n", message2);
        response2 = receive_from_server(sockfd);
    }
    // afisez mesajul primit
    printf("%s\n", response2);
    puts("");
    // eliberez memoria folosita
    free(message2);
    return response2;
}
void get_books_func(char* message3, int sockfd, char* response3,
    char* mytoken, char* cookies) {
    // deschid conexiunea
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
    // creez mesajul
    message3 = compute_get_request(HOST_IP, "/api/v1/tema/library/books",
    NULL, cookies, mytoken);
    // il trimit la server
    send_to_server(sockfd, message3);
    printf("%s\n", message3);
    // primesc mesajul de la server
    response3 = receive_from_server(sockfd);
    // daca nu am primit niciun mesaj
    if (response3 == NULL) {
        // deschid iar conexiunea
        sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
        // trimit iar mesajul
        send_to_server(sockfd, message3);
        printf("%s\n", message3);
        response3 = receive_from_server(sockfd);
    }
    // afisez mesajul primit
    printf("%s\n", response3);
    puts("");
    // eliberez memoria folosita
    free(response3);
    free(message3);
}
void get_book_func(char* message4, int sockfd, char* response4, char* mytoken) {
    // deschid conexiunea
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
    char* bookIdstr = (char*)calloc(10, sizeof(char));
    char* str = (char*)calloc(1000, sizeof(char));
    // citesc id-ul si il adaug la url
    printf("id=");
    scanf("%s", bookIdstr);
    strcpy(str, " /api/v1/tema/library/books/");
    strcat(str, bookIdstr);
    // creez mesajul
    message4 = compute_get_request(HOST_IP, str, NULL, NULL, mytoken);
    // il trimit la server
    send_to_server(sockfd, message4);
    printf("%s\n", message4);
    // primesc mesajul de la server
    response4 = receive_from_server(sockfd);
    // daca nu am primit niciun mesaj
    if (response4 == NULL) {
        // deschid iar conexiunea
        sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
        // trimit iar mesajul
        send_to_server(sockfd, message4);
        printf("%s\n", message4);
        response4 = receive_from_server(sockfd);
    }
    // afisez mesajul primit
    printf("%s\n", response4);
    puts("");
    // eliberez memoria folosita
    free(response4);
    free(message4);
    free(bookIdstr);
    free(str);
}
void add_book_func(int sockfd, char* namebook, char* author, char* genre, char* publisher,
    char* page_count, char* message6, char* response6, char* mytoken, char* loginData6) {
    JSON_Value* root_value6 = json_value_init_object();
    JSON_Object* root_object6 = json_value_get_object(root_value6);
    // citesc datele despre carte
    printf("title=");
    scanf("%s", namebook);
    printf("author=");
    scanf("%s", author);
    printf("genre=");
    scanf("%s", genre);
    printf("publisher=");
    scanf("%s", publisher);
    printf("page_count=");
    scanf("%s", page_count);
    int page_count1 = atoi(page_count);
    // creez payload-ul
    json_object_set_string(root_object6, "title", namebook);
    json_object_set_string(root_object6, "author", author);
    json_object_set_string(root_object6, "genre", genre);
    json_object_set_number(root_object6, "page_count", page_count1);
    json_object_set_string(root_object6, "publisher", publisher);
    loginData6 = json_serialize_to_string_pretty(root_value6);
    // deschid conexiunea
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
    // creez mesajul
    message6 = compute_post_request(HOST_IP, "/api/v1/tema/library/books/",
    "application/json", loginData6, NULL, mytoken);
    printf("%s\n", message6);
    // il trimit la sever
    send_to_server(sockfd, message6);
    // primesc mesajul de la server
    response6 = receive_from_server(sockfd);
    // daca nu am primit niciun mesaj
    if (response6 == NULL) {
        // deschid iar conexiunea
        sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
        // trimit iar mesajul la server
        send_to_server(sockfd, message6);
        printf("%s\n", message6);
        response6 = receive_from_server(sockfd);
    }
    // afisez mesajul primit
    printf("%s\n", response6);
    puts("");
    // eliberez memoria folosita
    free(response6);
    free(message6);
    free(loginData6);
    free(namebook);
    free(author);
    free(genre);
    free(publisher);
    free(page_count);
}
void delete_book_func(int sockfd, char* message, char* response, char* mytoken) {
    char* str = (char*)calloc(1000, sizeof(char));
    // deschid conexiunea
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
    char* bookIdstr1 = (char*)calloc(10, sizeof(char));
    // citesc id-ul cartii si il adaug la url
    printf("id=");
    scanf("%s", bookIdstr1);
    strcpy(str, " /api/v1/tema/library/books/");
    strcat(str, bookIdstr1);
    // creez mesajul
    message = compute_delete_request(HOST_IP, str, NULL, NULL, mytoken);
    // il trimit la server
    send_to_server(sockfd, message);
    printf("%s\n", message);
    // primesc mesajul de la server
    response = receive_from_server(sockfd);
    // daca nu am primit niciun mesaj
    if (response == NULL) {
        // deschid iar conexiunea
        sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
        // trimit iar mesajul la server
        send_to_server(sockfd, message);
        printf("%s\n", message);
        response = receive_from_server(sockfd);
    }
    // afisez mesajul primit
    printf("%s\n", response);
    puts("");
    // eliberez memoria folosita
    free(response);
    free(message);
    free(bookIdstr1);
    free(str);
}
void logout_func(int sockfd, char* message, char* response, char* cookies) {
    // deschid conexiunea
    sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
    // creez mesajul
    message = compute_get_request(HOST_IP,
    "/api/v1/tema/auth/logout", NULL, cookies, NULL);
    // trimit mesajul la server
    send_to_server(sockfd, message);
    printf("%s\n", message);
    // primesc mesajul de la server
    response = receive_from_server(sockfd);
    // daca nu am primit niciun mesaj
    if (response == NULL) {
        // deschid iar conexiunea
        sockfd = open_connection(HOST_IP, 8080, AF_INET, SOCK_STREAM, 0);
        // trimit iar mesajul la server
        send_to_server(sockfd, message);
        printf("%s\n", message);
        response = receive_from_server(sockfd);
    }
    // afisez mesajul primit
    printf("%s\n", response);
    puts("");
    // eliberez memoria folosita
    free(response);
    free(message);
}