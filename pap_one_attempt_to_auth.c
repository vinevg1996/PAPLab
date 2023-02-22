#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum login_input 
{
    RAR_PLUS,
    RAR_MINUS,  
}INPUT;


typedef enum login_output
{
    SAA,
    SAN
    
}OUTPUT;

typedef enum program_state
{
    ACK,
    OPEN,
    CLOSE
}STATE;

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

    if(state == ACK && input == RAR_PLUS)
    {
        printf("\ni=%s\to=SAA\n\n", (input==RAR_PLUS)?"RAR+":"RAR-"); //OUTPUT
        state = OPEN;
    }
    else if(state == ACK && input == RAR_MINUS)
    {
        printf("\ni=%s\to=SAN\n\n", (input==RAR_PLUS)?"RAR+":"RAR-"); //OUTPUT
        state = CLOSE;
    }

    else if(state == CLOSE && input == RAR_PLUS)
    {
        printf("\ni=%s\to=SAN\n\n", (input==RAR_PLUS)?"RAR+":"RAR-"); //OUTPUT
        state = ACK;
    }
    else if(state == CLOSE && input == RAR_MINUS)
    {
        printf("\ni=%s\to=SAN\n\n", (input==RAR_PLUS)?"RAR+":"RAR-"); //OUTPUT
        state = CLOSE;
    }

    else if(state == OPEN && input == RAR_PLUS)
    {
        printf("\ni=%s\to=SAA\n\n", (input==RAR_PLUS)?"RAR+":"RAR-"); //OUTPUT
        state = OPEN;
    }
    else if(state == OPEN && input == RAR_MINUS)
    {
        printf("\ni=%s\to=SAN\n\n", (input==RAR_PLUS)?"RAR+":"RAR-"); //OUTPUT
        state = OPEN;
    }
    return state;
}

void pap_fsm() {
    char *user = NULL;
    char *password = NULL;
    size_t nu = 0, np = 0;
    //int number_of_states = 5;
    int state = 0;
    int input;

    int work_flag = 1;
    while (1) {
        printf("User: ");
        if(getline(&user, &nu, stdin) == -1)
            printf ("502 - Error readning standard input!\n");
        
        printf("Password: ");
        if(getline(&password, &np, stdin) == -1)
            printf ("502 - Error readning standard input!\n");
        
        int input = check_login(user, password);
        state = pap_fsm_next_state(state, input);
    }
}

int main() {
    pap_fsm();
    return 0;
}
