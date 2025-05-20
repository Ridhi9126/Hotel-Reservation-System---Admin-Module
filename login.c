#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"

void login() {
    const char adUname[] = "welcome";
    const char adPass[] = "abcde";
    char username[20], password[20];

    printf("Admin Login\nUsername: ");
    scanf("%19s", username);
    printf("Password: ");
    scanf("%19s", password);

    if (strcmp(username, adUname) == 0 && strcmp(password, adPass) == 0) {
        printf("Login Successful!\n");
    } else {
        printf("Invalid credentials. Exiting...\n");
        exit(0);
    }
}