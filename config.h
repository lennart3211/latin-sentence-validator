//
// Created by mclen on 14/10/2024.
//

#ifndef LATIN_SENTENCE_VALIDATOR_CONFIG_H
#define LATIN_SENTENCE_VALIDATOR_CONFIG_H

/*
    SE -> S O V
    S -> N
    O -> N
    V -> VS VE
    N -> NS NE
    N -> NS
*/

#include "validator.h"

#define NUM_NOUNS 26
#define NUM_VERBS 14



const noun nouns[] = {
        (noun) {"nauta", "naut", DECL_FIRST, MASC},             // 0
        (noun) {"poeta", "poet", DECL_FIRST, MASC},             // 1
        (noun) {"patria", "patri", DECL_FIRST, FEM},            // 2
        (noun) {"poena", "poen", DECL_FIRST, FEM},              // 3
        (noun) {"philosophia", "philosophi", DECL_FIRST, FEM},  // 4
        (noun) {"fama", "fam", DECL_FIRST, FEM},                // 5
        (noun) {"forma", "form", DECL_FIRST, FEM},              // 6
        (noun) {"fortuna", "fortun", DECL_FIRST, FEM},          // 7
        (noun) {"ira", "ir", DECL_FIRST, FEM},                  // 8
        (noun) {"porta", "port", DECL_FIRST, FEM},              // 9
        (noun) {"puella", "puell", DECL_FIRST, FEM},            // 10
        (noun) {"pecunia", "pecuni", DECL_FIRST, FEM},          // 11
        (noun) {"rosa", "ros", DECL_FIRST, FEM},                // 12
        (noun) {"sententia", "sententi", DECL_FIRST, FEM},      // 13
        (noun) {"vita", "vit", DECL_FIRST, FEM},                // 14
        (noun) {"ager", "agr", DECL_SECOND, MASC},              // 15
        (noun) {"agricola", "agricol", DECL_FIRST, MASC},       // 16
        (noun) {"amica", "amic", DECL_FIRST, MASC},             // 17
        (noun) {"femina", "femin", DECL_FIRST, FEM},            // 18
        (noun) {"filia", "fili", DECL_FIRST, FEM},              // 19
        (noun) {"filius", "fili", DECL_SECOND, MASC},           // 20
        (noun) {"numerus", "numer", DECL_SECOND, MASC},         // 21
        (noun) {"populus", "popul", DECL_SECOND, MASC},         // 22
        (noun) {"puer", "puer", DECL_SECOND, MASC},             // 23
        (noun) {"sapientia", "sapienti", DECL_FIRST, FEM},      // 24
        (noun) {"vir", "vir", DECL_SECOND, MASC},               // 25
};

const char *noun_endings[3][6][2] =
{

        { // first declension
            {"a", "ae"},
            {"ae", "arum"},
            {"ae", "is"},
            {"am", "as"},
            {"a", "is"},
            {"a", "ae"},
        },
        { // second declension
            {"us", "i"},
            {"i", "orum"},
            {"o", "is"},
            {"um", "os"},
            {"o", "is"},
            {"us", "i"},
        },
};

const verb verbs[] = {
        (verb) {"amare", "am", CONJ_FIRST},             // 0
        (verb) {"cogitare", "cogit", CONJ_FIRST},       // 1
        (verb) {"debere", "deb", CONJ_SECOND},          // 2
        (verb) {"dare", "d", CONJ_FIRST},               // 3
        (verb) {"errare", "err", CONJ_FIRST},           // 4
        (verb) {"laudare", "laud", CONJ_FIRST},         // 5
        (verb) {"monere", "mon", CONJ_SECOND},          // 6
        (verb) {"salvere", "salv", CONJ_SECOND},        // 7
        (verb) {"servare", "serv", CONJ_FIRST},         // 8
        (verb) {"conservare", "conserv", CONJ_FIRST},   // 9
        (verb) {"terrere", "terr", CONJ_SECOND},        // 10
        (verb) {"valere", "val", CONJ_SECOND},          // 11
        (verb) {"videre", "vid", CONJ_SECOND},          // 12
        (verb) {"vocare", "voc", CONJ_FIRST},           // 13
};

const char *verb_endings[3][3][2] =
{
        { // first conjugation
            {"o", "amus"},
            {"as", "atis"},
            {"at", "ant"},
        },
        { // second conjugation
            {"eo", "emus"},
            {"es", "etis"},
            {"et", "ent"},
        },
        { // third conjugation
            {"o", "imus"},
            {"is", "itis"},
            {"it", "unt"},
        }
};

instruction table[10][10] = {
        {NONE, NONE, S_3, NONE, NONE, NONE, G_1, NONE, NONE, G_2},
        {NONE, NONE, S_3, NONE, NONE, NONE, NONE, G_4, NONE, G_5},
        {NONE, NONE, R_1, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {R_5, NONE, R_5, S_6, NONE, NONE, NONE, NONE, NONE, NONE},
        {S_8, NONE, NONE, NONE, NONE, NONE, NONE, NONE, G_7, NONE},
        {R_2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {R_4, NONE, R_4, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {NONE, NONE, NONE, NONE, ACCEPT, NONE, NONE, NONE, NONE, NONE},
        {NONE, S_9, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
        {NONE, NONE, NONE, NONE, R_3, NONE, NONE, NONE, NONE, NONE}};

#endif//LATIN_SENTENCE_VALIDATOR_CONFIG_H
