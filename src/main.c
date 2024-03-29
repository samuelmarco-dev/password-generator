#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define FALSE 0
#define TRUE 1 
#define VERYWEAK 1
#define WEAK 2
#define GOOD 3
#define STRONG 4
#define VERYSTRONG 5

#define VERYWEAK_MIN 1
#define VERYWEAK_MAX 4
#define WEAK_MIN 5
#define WEAK_MAX 7
#define GOOD_MIN 8
#define GOOD_MAX 9
#define STRONG_MIN 10
#define STRONG_MAX 11
#define VERYSTRONG_MIN 12
#define DEFAULT 25
#define VERYSTRONG_MAX 50
#define PASSWORD_MAX 50
#define MAX 100

typedef struct {
    int length;
    int numbers;
    int symbols;
    int uppercase;
    int lowercase;
} Password;

Password *createPassword();
void setLength(Password *password);
void setUppercase(Password *password);
void setLowercase(Password *password);
void setNumbers(Password *password);
void setSymbols(Password *password);

int verificationLength(int length);
int contains(int input);
int veryWeak(int lenght);
int weak(int lenght);
int good(int lenght);
int strong(int lenght);
int veryStrong(int lenght);

int passwordStrength(Password *password);
void generatePassword(Password *password);
void allowedCharacters(Password *password);

void noticeOfExit(Password *password);
int recommendation(Password *password);
void generateNewPassword(Password *password);

int main() { 
    setlocale(LC_ALL, "");
    printf("Seja Bem-vindo ao Gerador de Senhas!\n\n");

    Password *password = createPassword();
    generatePassword(password);
    noticeOfExit(password);

    if(recommendation(password)) {
        printf("Sua senha possui vulnerabilidades!\n");
        generateNewPassword(password);
    }

    free(password);
    return 0;
}

Password *createPassword() {
    Password *password = (Password *) malloc(sizeof(Password));

    setLength(password);
    setUppercase(password);
    setLowercase(password);
    setNumbers(password);
    setSymbols(password);

    return password;
}

void setLength(Password *password) {
    do {
        printf("Digite o tamanho da senha desejada: ");
        scanf("%d", &password->length);
        getchar(); 

        if(!verificationLength(password->length))
            printf("O tamanho da senha deve ser entre 1 e 50 caracteres!\n");
        else 
            break;
    } while(!verificationLength(password->length));
    printf("O tamanho da senha será de %d caracteres!\n", password->length);
}

void setUppercase(Password *password) {
    do {
        printf("\nDeseja que a senha contenha letras maiúsculas? (1 - Sim | 0 - Não): ");
        scanf("%d", &password->uppercase);
        getchar();

        if(password->uppercase < FALSE || password->uppercase > TRUE)
            printf("Opção inválida!\n");
        else if(password->uppercase)
            printf("A senha conterá letras maiúsculas!\n");
        else if(!password->uppercase)
            printf("A senha não conterá letras maiúsculas!\n");
        else 
            break;
    } while(!contains(password->uppercase));
}

void setLowercase(Password *password) {
    do {
        printf("\nDeseja que a senha contenha letras minúsculas? (1 - Sim | 0 - Não): ");
        scanf("%d", &password->lowercase);
        getchar();

        if(password->uppercase < FALSE || password->uppercase > TRUE)
            printf("Opção inválida!\n");
        else if(password->lowercase)
            printf("A senha conterá letras minúsculas!\n");
        else if(!password->lowercase)
            printf("A senha não conterá letras minúsculas!\n");
        else 
            break;
    } while(!contains(password->lowercase));
}

void setNumbers(Password *password) {
    do {
        printf("\nDejesa que a senha contenha números? (1 - Sim | 0 - Não): ");
        scanf("%d", &password->numbers);
        getchar();

        if(password->uppercase < FALSE || password->uppercase > TRUE)
            printf("Opção inválida!\n");
        else if(password->numbers)
            printf("A senha conterá números!\n");
        else if(!password->numbers)
            printf("A senha não conterá números!\n");
        else 
            break;
    } while(!contains(password->numbers));
}

void setSymbols(Password *password) {
    do {
        printf("\nDeseja que a senha contenha símbolos? (1 - Sim | 0 - Não): ");
        scanf("%d", &password->symbols);
        getchar();

        if(password->uppercase < FALSE || password->uppercase > TRUE)
            printf("Opção inválida!\n");
        else if(password->symbols)
            printf("A senha conterá símbolos!\n");
        else if(!password->symbols)
            printf("A senha não conterá símbolos!\n");
        else
            break;
    } while(!contains(password->symbols));
}

int verificationLength(int length) {
    return (length <= FALSE || length > PASSWORD_MAX) ? FALSE : TRUE;
}

int contains(int input) {
    return (input == TRUE || input == FALSE) ? TRUE : FALSE;
}

int veryWeak(int lenght) {
    return (lenght >= VERYWEAK_MIN && lenght <= VERYWEAK_MAX) ? TRUE : FALSE;
}

int weak(int lenght) {
    return (lenght >= WEAK_MIN && lenght <= WEAK_MAX) ? TRUE : FALSE;
}

int good(int lenght) {
    return (lenght >= GOOD_MIN && lenght <= GOOD_MAX) ? TRUE : FALSE;
}

int strong(int lenght) {
    return (lenght >= STRONG_MIN && lenght <= STRONG_MAX) ? TRUE : FALSE;
}

int veryStrong(int lenght) {
    return (lenght >= VERYSTRONG_MIN && lenght <= VERYSTRONG_MAX) ? TRUE : FALSE;
}

int passwordStrength(Password *password) {
    int strength;

    if(password == NULL) {
        fprintf(stderr, "Erro ao verificar força da senha!\n");
        exit(TRUE);
    }

    if(veryWeak(password->length))
        strength = VERYWEAK;
    else if(weak(password->length))
        strength = WEAK;
    else if(good(password->length))
        strength = GOOD;
    else if(strong(password->length))
        strength = STRONG;
    else if(veryStrong(password->length))
        strength = VERYSTRONG;
    else 
        strength = FALSE;
    
    return strength;
}

void generatePassword(Password *password) {
    if(password == NULL) {
        fprintf(stderr, "Erro ao gerar senha!\n");
        exit(TRUE);
    }

    allowedCharacters(password);
}   

void allowedCharacters(Password *password) {
    const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
    const char numbers[] = "0123456789";
    const char symbols[] = "!@#$%&*()_+=-{}[]:;?/|";

    char allowedCharacters[MAX] = "";

    if(password->uppercase)
        strcat(allowedCharacters, uppercase);
    if(password->lowercase)
        strcat(allowedCharacters, lowercase);
    if(password->numbers)
        strcat(allowedCharacters, numbers);
    if(password->symbols)
        strcat(allowedCharacters, symbols);

    printf("\n----------------------------------------\n");
    printf("Senha gerada: ");

    srand(time(NULL));
    for(int i = 0; i < password->length; i++) {
        int index = (int) (rand() % strlen(allowedCharacters));
        
        char aux = allowedCharacters[i];
        allowedCharacters[i] = allowedCharacters[index];
        allowedCharacters[index] = aux;
        
        printf("%c", allowedCharacters[i]);
    }
    printf("\n----------------------------------------\n");
}

void noticeOfExit(Password *password) {
    if(password == NULL) {
        fprintf(stderr, "Erro ao verificar força da senha!\n");
        exit(TRUE);
    }

    printf("\nResultado: ");
    if(passwordStrength(password) == VERYWEAK)
        printf("A senha gerada é muito fraca!\n");
    else if(passwordStrength(password) == WEAK)
        printf("A senha gerada é fraca!\n");
    else if(passwordStrength(password) == GOOD)
        printf("A senha gerada é boa!\n");
    else if(passwordStrength(password) == STRONG)
        printf("A senha gerada é forte!\n");
    else if(passwordStrength(password) == VERYSTRONG)
        printf("A senha gerada é muito forte!\n");
    else 
        printf("A senha gerada é inválida!\n");
}

int recommendation(Password *password) {
    if(password == NULL) {
        fprintf(stderr, "Erro ao verificar força da senha!\n");
        exit(TRUE);
    }

    return (passwordStrength(password) >= STRONG) ? FALSE : TRUE;
}

void generateNewPassword(Password *password) {
    int option;

    if(password == NULL) {
        fprintf(stderr, "Erro ao verificar força da senha!\n");
        exit(TRUE);
    }

    do {
        printf("\nDeseja gerar uma nova senha? (1 - Sim | 0 - Não): ");
        scanf("%d", &option);
        getchar();

        if(option < FALSE || option > TRUE)
            printf("Opção inválida!\n");
        else if(option) {
            printf("Gerando nova senha...\n");
            password->length = DEFAULT;
            generatePassword(password);
            noticeOfExit(password);
        }
        else 
            break;
    } while(!contains(option));
}
