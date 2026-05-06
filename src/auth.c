#include <stdio.h>
#include <string.h>
#include "auth.h"

int login() {
    char user[50], pass[50];
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(user, "admin") == 0 && strcmp(pass, "1234") == 0) {
        printf("Login successful\n");
        return 1;
    } else {
        printf("Invalid credentials\n");
        return 0;
    }
}
