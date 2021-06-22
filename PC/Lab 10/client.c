#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include "requests.h"

int main(int argc, char *argv[])
{
    char *message;
    char *response;
    int sockfd;
    sockfd = open_connection("34.118.48.238", 8080, AF_INET, SOCK_STREAM, 0);
    char *test[25] = {"field1=value1", "field2=value2"};
    // Ex 1.1: GET dummy from main server
    message = compute_get_request("34.118.48.238:8080", "/api/v1/dummy", NULL, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("%s\n", response);
    
    // Ex 1.2: POST dummy and print response from main server
    message = compute_post_request("34.118.48.238:8080", "/api/v1/dummy", "application/x-www-form-urlencoded", test, 2, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("%s\n", response);
    // Ex 2: Login into main server
    char *login[25] = {"username=student", "password=student"};
    message = compute_post_request("34.118.48.238:8080", "/api/v1/auth/login", "application/x-www-form-urlencoded", login, 2, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("%s\n", response);
    // Ex 3: GET weather key from main server
    char key[150];
    char *dataKey;
    dataKey = strtok(memcpy(key, &response[291], 150), ".");
    // Ex 4: GET weather data from OpenWeather API
    char data[255] = "lat=43.700111&lon=-79.416298&appid={";
    strcat(data, dataKey);
    strcat(data, "}");
    printf("%s\n", data);
    int sockfd2 = open_connection("188.166.16.132", 80, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("188.166.16.132:80", "/data/2.5/weather", data, NULL, 0);
    send_to_server(sockfd2, message);
    response = receive_from_server(sockfd2);
    printf("%s\n", response);
    // Ex 5: POST weather data for verification to main server
    // Ex 6: Logout from main server
    message = compute_get_request("34.118.48.238:8080", "/api/v1/auth/logout", NULL, NULL, 0);
    send_to_server(sockfd, message);
    response = receive_from_server(sockfd);
    printf("%s", response);
    // BONUS: make the main server return "Already logged in!"
    // free the allocated data at the end!

    return 0;
}
