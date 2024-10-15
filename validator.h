//
// Created by mclen on 15/10/2024.
//

#ifndef LATIN_SENTENCE_VALIDATOR_VALIDATOR_H
#define LATIN_SENTENCE_VALIDATOR_VALIDATOR_H

typedef enum {
    MASC,
    FEM,
    NEUT,
} gender;

typedef enum {
    DECL_FIRST,
    DECL_SECOND,
} declension;

typedef enum {
    CONJ_FIRST,
    CONJ_SECOND,
} conjugation;

typedef enum {
    CASE_NOM,
    CASE_GEN,
    CASE_DAT,
    CASE_ACC,
    CASE_ABL,
    CASE_VOC,
} case_;

typedef struct {
    char _nom[32];
    char _stem[32];
    declension _declension;
    gender _gender;
} noun;

typedef struct {
    char _inf[32];
    char _stem[32];
    conjugation _conjugation;
} verb;

typedef enum {
    TK_NOUN_STEM = 2,
    TK_NOUN_END = 3,
    TK_VERB_STEM = 0,
    TK_VERB_END = 1,
    TK_NOUN = 9,
    TK_VERB = 8,
    TK_SUBJECT = 6,
    TK_OBJECT = 7,
    TK_EOF = 4,
    TK_NONE,
} token_type;

typedef struct {
    token_type type;
    char value[32];
    uint32_t state;
    uint32_t number;
} token;

typedef enum {
    NONE = 0,
    R_0 = 1,
    R_1 = 2,
    R_2 = 3,
    R_3 = 4,
    R_4 = 5,
    R_5 = 6,
    S_0 = 4,
    S_3 = 7,
    S_6 = 10,
    S_8 = 12,
    S_9 = 13,
    G_0 = 13,
    G_1 = 14,
    G_2 = 15,
    G_4 = 17,
    G_5 = 18,
    G_7 = 20,
    ACCEPT,
} instruction;

// returns a string representing the type
char *toString(token_type type);

// prints the stack and the input array
void printInfo(token *stack, int top, token *input, int index);

// checks if word is part of the noun_stems array
int isNounStem(const char *word);

// checks if word is part of the ver_stems array
int isVerbStem(const char *word);

// checks if word is a noun ending
// returns 1 for singular and 2 for plural
int isNounEnding(const char *word);

// checks if word is a verb ending
// returns 1 for singular and 2 for plural
int isVerbEnding(const char *word);

// checks if word is in the nominative
int isNominative(const char *word);

// checks if word is in the accusative
int isAccusative(const char *word);

// LR(1) parser
// returns 1 if the input is valid
int parse(token input[]);

// takes an input string and returns an array of tokens
token *tokenize(const char *input);

#endif//LATIN_SENTENCE_VALIDATOR_VALIDATOR_H
