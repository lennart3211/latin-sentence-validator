#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "config.h"

char *toString(token_type type) {
    switch (type) {
        case TK_NOUN_STEM:
            return "NS";
        case TK_NOUN_END:
            return "NE";
        case TK_VERB_STEM:
            return "VS";
        case TK_VERB_END:
            return "VE";
        case TK_NOUN:
            return "N";
        case TK_VERB:
            return "V";
        case TK_SUBJECT:
            return "S";
        case TK_OBJECT:
            return "O";
        case TK_EOF:
            return "$";
        case TK_NONE:
            return "";
    }
}

void printInfo(token *stack, int top, token *input, int index) {
    printf("Stack: ");
    int i = 0;
    while (i < top) {
        printf("%s %d ", toString(stack[i].type), stack[i].state);
        i++;
    }
    printf("%s %d       Input: ", toString(stack[top].type), stack[i].state);
    i = index;
    while (input[i].type != TK_EOF) {
        printf("%s ", toString(input[i].type));
        i++;
    }
    printf("$\n");
}

int isNounStem(const char *word) {
    for (uint32_t i = 0; i < NUM_NOUNS; i++) {
        if (strcmp(word, nouns[i]._stem) == 0) return 1;
    }
    return 0;
}

int isVerbStem(const char *word) {
    for (uint32_t i = 0; i < NUM_VERBS; i++) {
        if (strcmp(word, verbs[i]._stem) == 0) return 1;
    }
    return 0;
}

int isNounEnding(const char *word) {
    for (uint32_t i = 0; i < 2; i++)
        for (uint32_t j = 0; j < 6; j++)
            for (uint32_t k = 0; k < 2; k++)
                if (strcmp(word, noun_endings[i][j][k]) == 0)
                    return (int) k + 1;

    return 0;
}

int isVerbEnding(const char *word) {
    for (uint32_t i = 0; i < 2; i++)
        for (uint32_t j = 0; j < 3; j++)
            for (uint32_t k = 0; k < 2; k++)
                if (strcmp(word, verb_endings[i][j][k]) == 0)
                    return (int) k + 1;
    return 0;
}

int isNominative(const char *word) {
    for (uint32_t i = 0; i < NUM_NOUNS; i++) {
        if (strcmp(nouns[i]._nom, word) == 0) return 1;
        char temp[32];
        strcpy(temp, nouns[i]._stem);
        strcpy(temp + strlen(nouns[i]._stem), noun_endings[nouns[i]._declension][CASE_NOM][1]);
        if (strcmp(word, temp) == 0) return 1;
    }
    return 0;
}

int isAccusative(const char *word) {
    uint32_t i = 0;
    while (word[i] != '\0') {
        if (word[i + 2] == '\0') {
            char ending[3];
            strcpy(ending, word + i);
            for (uint32_t j = 0; j < 2; j++) {
                if (strcmp(ending, noun_endings[j][CASE_ACC][0]) == 0 ||
                    strcmp(ending, noun_endings[j][CASE_ACC][1]) == 0 )
                    return 1;
            }
            return 0;
        }
        i++;
    }
    return 0;
}

int parse(token input[]) {
    token stack[32];
    int top = 0;
    int index = 0;

    stack[top].state = 0;
    stack[top].type = TK_NONE;

    while (1) {
        printInfo(stack, top, input, index);

        switch (table[stack[top].state][input[index].type]) {
        case R_0:
            if (top < 3 || stack[top].type != TK_VERB) return 0;

            break;
        case R_1:
            if (top < 1 || stack[top].type != TK_NOUN || !isNominative(stack[top].value)) return 0;
            stack[top].type = TK_SUBJECT;
            stack[top].state = table[stack[top - 1].state][stack[top].type] - G_0;
            break;
        case R_2:
            if (top < 1 || stack[top].type != TK_NOUN || !isAccusative(stack[top].value)) return 0;
            stack[top].type = TK_OBJECT;
            stack[top].state = table[stack[top - 1].state][stack[top].type] - G_0;
            break;
        case R_3:
            if (top < 2 || stack[top].type != TK_VERB_END || stack[top - 1].type != TK_VERB_STEM)
                return 0;
            top--;
            stack[top].type = TK_VERB;
            stack[top].state = table[stack[top - 1].state][stack[top].type] - G_0;
            strcpy(stack[top].value + strlen(stack[top].value), stack[top + 1].value);
            stack[top].number = stack[top + 1].number;
            break;
        case R_4:
            if (top < 2 || stack[top].type != TK_NOUN_END || stack[top - 1].type != TK_NOUN_STEM)
                return 0;
            top--;
            stack[top].type = TK_NOUN;
            stack[top].state = table[stack[top - 1].state][stack[top].type] - G_0;
            strcpy(stack[top].value + strlen(stack[top].value), stack[top + 1].value);
            stack[top].number = stack[top + 1].number;
            break;
        case R_5:
            if (top < 1 || stack[top].type != TK_NOUN_STEM || !isNominative(stack[top].value)) return 0;
            stack[top].type = TK_NOUN;
            stack[top].state = table[stack[top - 1].state][stack[top].type] - G_0;
            break;
        case S_3:
            stack[++top] = input[index++];
            stack[top].state = 3;
            break;
        case S_6:
            stack[++top] = input[index++];
            stack[top].state = 6;
            break;
        case S_8:
            stack[++top] = input[index++];
            stack[top].state = 8;
            break;
        case S_9:
            stack[++top] = input[index++];
            stack[top].state = 9;
            break;
        case NONE:
        case G_1:
        case G_2:
        case G_4:
        case G_5:
        case G_7:
            return 0;
        case ACCEPT:
            return top == 3
                && stack[top].type == TK_VERB
                && stack[top - 1].type == TK_OBJECT
                && stack[top - 2].type == TK_SUBJECT
                && stack[top].number == stack[top - 2].number;
        }
    }
}


token *tokenize(const char *input) {
    token *tokens = malloc(32 * sizeof(token));
    uint32_t index = 0;
    uint32_t i = 0;
    char currWord[32];
    currWord[i] = '\0';
    uint32_t length = 0;

    int inWord = 0;

    while (input[i] != '\0') {
        if (input[i] == ' ') {
            int number = isNounEnding(currWord);
            if (number) {
                tokens[index].type = TK_NOUN_END;
                strcpy(tokens[index].value, currWord);
                tokens[index].number = number;
                index++;
                inWord = 0;
            } else {
                number = isVerbEnding(currWord);
                if (number) {
                    tokens[index].type = TK_VERB_END;
                    strcpy(tokens[index].value, currWord);
                    tokens[index].number = number;
                    index++;
                    inWord = 0;
                }
            }
            length = 0;
            currWord[length] = '\0';
        } else {
            currWord[length++] = input[i];
            currWord[length] = '\0';


            if (!inWord && isNounStem(currWord)) {
                tokens[index].type = TK_NOUN_STEM;
                strcpy(tokens[index].value, currWord);
                index++;
                if (!isNominative(currWord)) inWord = 1;
                length = 0;
                currWord[length] = '\0';
            } else if (!inWord && isVerbStem(currWord)) {
                tokens[index].type = TK_VERB_STEM;
                strcpy(tokens[index].value, currWord);
                index++;
                length = 0;
                currWord[length] = '\0';
                inWord = 1;
            }
        }

        i++;
    }
    if (currWord[0] != '\0') {
        int number;
        number = isNounEnding(currWord);
        if (number) {
            tokens[index].type = TK_NOUN_END;
            strcpy(tokens[index].value, currWord);
            tokens[index].number = number;
            index++;

        } else {
            number = isVerbEnding(currWord);
            if (number) {
                tokens[index].type = TK_VERB_END;
                strcpy(tokens[index].value, currWord);
                tokens[index].number = number;
                index++;
            }
        }
    }
    tokens[index++].type = TK_EOF;
    return tokens;
}

int main(int argc, char **argv) {
    if (argc < 2) return 0;

    token *tokens = tokenize(argv[1]);

    printf("%d\n", parse(tokens));

    free(tokens);

    return 0;
}
