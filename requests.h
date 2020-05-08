#ifndef _REQUESTS_
#define _REQUESTS_

// calculeaza si returneaza un string GET request 
char *compute_get_request(char *host, char *url, char *query_params,
							char *cookies, char *token);

// calculeaza si returneaza un string POST request 
char *compute_post_request(char *host, char *url, char* content_type, char *body_data,
							char* cookies,char *token);

// calculeaza si returneaza un string DELETE request 
char *compute_delete_request(char *host, char *url, char *query_params,
                            char *cookies, char *token);

#endif
