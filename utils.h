#ifndef _UTILS_
#define _UTILS_

// functie apelata cand primesc comanda enter_library
char* enter_func(int sockfd , char* message2 , char* response2, char* cookies);

// parseaza token-ul primit
char* tokens(char* tokens, char* str);

// parseaza cookie-ul primit
char* addCookies(char* cookies, char* str);

// functie apelata cand primeste comanda register
void register_func(char *username, char *pass, char * message ,
 char *response, char *loginData, int sockfd);

// functie apelata cand primeste comanda login
char* login_func(char *username, char *pass, char * message1 ,
 char *response1, char *loginData1, int sockfd);

// functie apelata cand primesc comanda get_books
void get_books_func(char* message3, int sockfd ,
 char* response3, char* mytoken, char* cookies);

// functie apelata cand primesc comanda get_book
void get_book_func(char* message4, int sockfd , char* response4, char* mytoken);

// functie apelata cand primesc comanda add_book
void add_book_func(int sockfd, char* namebook, char* author, char* genre, char* publisher,
 char* page_count, char* message6, char* response6, char* mytoken , char* loginData6);

// functie apelata cand primesc comanda delete_book
void delete_book_func(int sockfd, char* message, char* response, char* mytoken);

// functie apelata cand primesc comanda logout
void logout_func(int sockfd, char* message, char* response, char* cookies);


#endif