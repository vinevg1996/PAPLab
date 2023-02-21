#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *strtrim(char *s) {
    char *end = (char*)(s + strlen(s) - 1);
    
    while(s <= end && isspace(*s))  
        s++;
    
    while(s <= end && isspace(*end))
        end--;
    *(end + 1) = '\0';
    
    return s;
}

int check_login(char *login, char *password) {

    FILE *fp = NULL;
    char *db_info = NULL;
    ssize_t res;
    size_t n = 0;
    char *access_str = NULL, *logint = NULL, *passwordt = NULL;
    int result = 1;

    logint = strtrim(login);
    passwordt = strtrim(password);

    access_str = (char*)malloc(sizeof(char) * (2 + strlen(logint) +strlen(passwordt)));

    sprintf(access_str, "%s %s", logint, passwordt); 


    fp = fopen("./users.db", "r");
    if(!fp)
    {
        printf("501- Error opening users' database!\n");
        exit(501);
    }
    
    while((res = getline(&db_info, &n, fp)) != -1)
        if(!strcmp(strtrim(db_info), access_str))
        {
            result = 0;
            break;
        }
    
    fclose(fp);
    return result;
}

int pap_fsm_next_state(int state, int input) {
    int next_state;

    if(state == 0 && input == 0)
    {
        printf("\ni=%s\to=SAA\n\n", (input==0)?"RAR+":"RAR-"); //OUTPUT
        next_state = 1;
    }
    else if(state == 0 && input == 1)
    {
        printf("\ni=%s\to=SAN\n\n", (input==0)?"RAR+":"RAR-"); //OUTPUT
        next_state = 2;
    }

    else if(state == 2 && input == 0)
    {
        printf("\ni=%s\to=SAN\n\n", (input==0)?"RAR+":"RAR-"); //OUTPUT
        next_state = 2;
    }
    else if(state == 2 && input == 1)
    {
        printf("\ni=%s\to=SAN\n\n", (input==0)?"RAR+":"RAR-"); //OUTPUT
        next_state = 2;
    }
    else 
    {
        next_state = -1;
    }
    return next_state;
}

void pap_fsm() {
    char *user = NULL;
    char *password = NULL;
    size_t nu = 0, np = 0;
    //int number_of_states = 5;
    int state = 0;
    int input;
    int next_state;

    int i = 0;
    // while (i <= 40) {
    int work_flag = 1;
    while (1) {
        printf("User: ");
        if(getline(&user, &nu, stdin) == -1)
            printf ("502 - Error readning standard input!\n");
        
        printf("Password: ");
        if(getline(&password, &np, stdin) == -1)
            printf ("502 - Error readning standard input!\n");
        
        int input = check_login(user, password);
        //int input = rand() % 2;
        state = pap_fsm_next_state(state, input);
        if ((state == 1) && (next_state == 1) && (state == 4) && (next_state == 4)) {
            work_flag = 0;
        }
    }
}

int pap_attempt(int input, int tries) {
    int success = 0;
    if((input == 1) && (tries >= 0) && (tries < 3))
    {
        printf("\ni=%s\to=SAN\n\n", (input==0)?"RAR+":"RAR-"); //OUTPUT
    }
    else if(input == 0 && (tries >= 0) && (tries < 3))
    {
        printf("\ni=%s\to=SAA\n\n", (input==0)?"RAR+":"RAR-"); //OUTPUT
        success = 1;
    }
    else if ((input>=0) && (input<=1) && (tries>=0) && (tries<3))
    {
        printf("\ni=%s\to=SAN\n\n", (input==0)?"RAR+":"RAR-"); //OUTPUT
    }
    return success;
}

int pap()
{
    char *user = NULL;
    char *password = NULL;
    size_t nu = 0, np = 0;
    //int success = 0, tries = 0;
    int success = 0;
    int tries = 0;
    int input;
    
    while((tries <= 3) && (success == 0))
    {
        /*
        printf("User: ");
        if(getline(&user, &nu, stdin) == -1)
            printf ("502 - Error readning standard input!\n");
        printf("Password: ");
        if(getline(&password, &np, stdin) == -1)
            printf ("502 - Error readning standard input!\n");
        input = check_login(user, password); 
        */
        input = rand() % 2;
        success = pap_attempt(input, tries);
        tries = tries + 1;

    }
    free(user); 
    free(password);
    
    return 0;

}

int main() {
    pap_fsm();
    //pap();
    return 0;
}
