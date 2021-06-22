#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <ctype.h>      /* isdigit*/
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"
#include "parson.h"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;
    char request[20];
    char username[25];
    char password[25];
    char title[45];
    char author[30];
    char genre[20];
    char publisher[30];
    char id[10];
    int page_count;
    char key[150];
    char tmpToken[300];
    char *token;
    char *dataKey = NULL;

    while(1){
        scanf("%s", request);
        if(strcmp(request, "register") == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            printf("username="); 
            scanf("%s", username);
            printf("password="); 
            scanf("%s", password);
            JSON_Value *root_value = json_value_init_object();
            JSON_Object *root_object = json_value_get_object(root_value);
            char *serialized_string = NULL;
            json_object_set_string(root_object, "username", username);
            json_object_set_string(root_object, "password", password);
            serialized_string = json_serialize_to_string_pretty(root_value);
            message = compute_post_request("34.118.48.238:8080", "/api/v1/tema/auth/register", "application/json", &serialized_string, 1, NULL, 0, NULL);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            char tmpCode[10];
            memcpy(tmpCode, &response[8], 4);
            int code = atoi(tmpCode);
            if(code == 201) {
                printf("%d OK\n",code);
                printf("Registered successfully\n");
            } else if(code == 400) {
                char err[100];
                memcpy(err, &response[544], 40 + strlen(username));
                printf("%d\n%s\n", code, err);
            } else if(code == 429) {
                printf("%d\nToo many requests, please try again later.", code);
            }
            printf("\n");
            // puts(response);
            json_free_serialized_string(serialized_string);
            json_value_free(root_value);
        } else if (strcmp(request, "login") == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            printf("username="); 
            scanf("%s", username);
            printf("password="); 
            scanf("%s", password);
            JSON_Value *root_value = json_value_init_object();
            JSON_Object *root_object = json_value_get_object(root_value);
            char *serialized_string = NULL;
            json_object_set_string(root_object, "username", username);
            json_object_set_string(root_object, "password", password);
            serialized_string = json_serialize_to_string_pretty(root_value);
            message = compute_post_request("34.118.48.238:8080", "/api/v1/tema/auth/login", "application/json", &serialized_string, 1, NULL, 0, NULL);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            char tmpCode[10];
            memcpy(tmpCode, &response[8], 4);
            int code = atoi(tmpCode);
            if(code == 200) {
                printf("%d OK\n",code);
                printf("Logged in successfully\n");
                dataKey = strtok(memcpy(key, &response[277], 200), ";");
            } else if(code == 400) {
                char err[100];
                memcpy(err, &response[469], 45);
                printf("%d\n%s\n", code, err);
            } else if(code == 429) {
                printf("%d\nToo many requests, please try again later.", code);
            }
            printf("\n");
            // puts(response);
            json_free_serialized_string(serialized_string);
            json_value_free(root_value);
        } else if (strcmp(request, "enter_library") == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            message = compute_get_request("34.118.48.238:8080", "/api/v1/tema/library/access", NULL, &dataKey, 1, NULL);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            char tmpCode[10];
            memcpy(tmpCode, &response[8], 4);
            int code = atoi(tmpCode);
            if(code == 200) {
                memcpy(tmpToken, &response[472], 281);
                token = strtok(tmpToken, "\"");
                printf("%d OK\n",code);
                printf("You have successfully entered the library.\n");
                printf("Your token: %s\n", token);
            } else if(code == 401) {
                char err[100];
                memcpy(err, &response[470], 45);
                printf("%d\n%s\n", code, err);
            } else if(code == 429) {
                printf("%d\nToo many requests, please try again later.", code);
            }
            printf("\n");
            // puts(response);
            
        } else if (strcmp(request, "get_books") == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            message = compute_get_request("34.118.48.238:8080", "/api/v1/tema/library/books", NULL, NULL, 1, token);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            char tmpCode[10];
            memcpy(tmpCode, &response[8], 4);
            int code = atoi(tmpCode);
            if(code == 200) {
                printf("%d OK\n",code);
                printf("Your books:\n");
                char books[1000];
                memcpy(books, &response[460], strlen(response) - 456);
                printf("%s\n", books);
            } else if(code == 500) {
                char err[100];
                memcpy(err, &response[479], 45);
                printf("%d\n%s\n", code, err);
            } else if(code == 429) {
                printf("%d\nToo many requests, please try again later.\n", code);
            }
            printf("\n");
            //puts(response);
        } else if (strcmp(request, "add_book") == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            printf("title="); 
            scanf("%s", title);
            printf("author="); 
            scanf("%s", author);
            printf("genre="); 
            scanf("%s", genre);
            printf("publisher="); 
            scanf("%s", publisher);
            printf("page_count="); 
            scanf("%d", &page_count);
            if(page_count <= 0 || page_count > 10000) {
                printf("Wrong format!\n\n");
                continue;
            }
            JSON_Value *root_value = json_value_init_object();
            JSON_Object *root_object = json_value_get_object(root_value);
            char *serialized_string = NULL;
            json_object_set_string(root_object, "title", title);
            json_object_set_string(root_object, "author", author);
            json_object_set_string(root_object, "genre", genre);
            json_object_set_number(root_object, "page_count", page_count);
            json_object_set_string(root_object, "publisher", publisher);
            serialized_string = json_serialize_to_string_pretty(root_value);
            message = compute_post_request("34.118.48.238:8080", "/api/v1/tema/library/books", "application/json", &serialized_string, 1, NULL, 0, token);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            char tmpCode[10];
            memcpy(tmpCode, &response[8], 4);
            int code = atoi(tmpCode);
            if(code == 200) {
                printf("%d OK\n",code);
                printf("You have added the book: %s\n", title);

            } else if(code == 403) {
                char err[100];
                memcpy(err, &response[545], 50);
                printf("%d\n%s\n", code, err);
            } else if(code == 429) {
                printf("%d\nToo many requests, please try again later.\n", code);
            }
            printf("\n");
            // puts(response);
            json_free_serialized_string(serialized_string);
            json_value_free(root_value);
        } else if(strcmp(request, "get_book") == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            printf("id=");
            scanf("%s", id);
            char url[100];
            strcpy(url, "/api/v1/tema/library/books/");
            strcat(url, id);
            message = compute_get_request("34.118.48.238:8080", url, NULL, NULL, 0, token);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            char tmpCode[10];
            memcpy(tmpCode, &response[8], 4);
            int code = atoi(tmpCode);
            if(code == 200) {
                printf("%d OK\n",code);
                printf("Your book:\n");
                printf("%s\n", &response[460]);
            } else if(code == 403) {
                printf("%d\n", code);
                printf("%s\n", &response[467]);
            } else if(code == 404) {
                printf("%d\n", code);
                printf("%s\n", &response[467]);
            } else if(code == 429) {
                printf("%d\nToo many requests, please try again later.\n", code);
            }
            printf("\n");
            // puts(response);
        } else if(strcmp(request, "delete_book") == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            printf("id=");
            scanf("%s", id);
            char url[100];
            strcpy(url, "/api/v1/tema/library/books/");
            strcat(url, id);
            message = compute_delete_request("34.118.48.238:8080", url, NULL, NULL, 0, token);
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            char tmpCode[10];
            memcpy(tmpCode, &response[8], 4);
            int code = atoi(tmpCode);
            if(code == 200) {
                printf("%d OK\n",code);
                printf("You have deleted the book with this ID: %s\n", id);
            } else if(code == 403) {
                printf("%d\n", code);
                printf("%s\n", &response[467]);
            } else if(code == 404) {
                printf("%d\n", code);
                printf("%s\n", &response[467]);
            } else if(code == 429) {
                printf("%d\nToo many requests, please try again later.\n", code);
            }
            printf("\n");
            // puts(response);
        } else if(strcmp(request, "logout") == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            char url[100];
            strcpy(url, "/api/v1/tema/auth/logout");
            if(dataKey != NULL) {
                message = compute_get_request("34.118.48.238:8080", url, NULL, &dataKey, 1, NULL);
            } else {
                message = compute_get_request("34.118.48.238:8080", url, NULL, NULL, 0, NULL); 
            }
            send_to_server(sockfd, message);
            response = receive_from_server(sockfd);
            dataKey = NULL;
            token = NULL;
            char tmpCode[10];
            memcpy(tmpCode, &response[8], 4);
            int code = atoi(tmpCode);
            if(code == 200) {
                printf("%d OK\n",code);
                printf("Logged out successfully\n");
            } else if(code == 400) {
                printf("%d\n", code);
                printf("%s\n", &response[469]);
            } else if(code == 429) {
                printf("%d\nToo many requests, please try again later.\n", code);
            }
            printf("\n");
            // puts(response);
        }
        
        else if (strncmp(request, "exit", 4) == 0) {
            sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
            printf("Exiting program\n");
            close(sockfd);
            break;
        }
    }
    return 0;
}
