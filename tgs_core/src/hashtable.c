#include <stdint.h>
#include "memory.h"
#include "hashtable.h"


TGS_HASHTABLE* hashtable_init(uint32_t size) {
    TGS_HASHTABLE* hashtable = NULL;
    if (size < 1) return NULL;
    hashtable = _memalloc(sizeof(TGS_HASHTABLE));
    if (hashtable != NULL) {
        hashtable->table = _memalloc(sizeof(TGS_HASHTABLE_ENTRY*) * size);
        if (hashtable->table != NULL) {
            for(uint32_t i=0; i < size; i++) {
                hashtable->table[i] = NULL;
            }
        }
        hashtable->size = size;
        hashtable->put = hashtable_put;
        hashtable->get = hashtable_get;
    }
    return hashtable;
}


static uint32_t pearson_hash(char* str, unsigned int len) {
    size_t i;
    static const unsigned char T[256] = {
        59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
        39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
        90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
        237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
        197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
        123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
        3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,
        133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
        98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
        183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,
        221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,
        154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
        189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
        61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
        43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239,
        238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110
    };

    unsigned char h = T[str[0] % 256];
    for (i = 1; i < len; i++) {
        h = T[h ^ str[i]];
    }
    return h;
}

/*
uint32_t bkdr_hash(TGS_HASHTABLE* hashtable, char* str, unsigned int len) {
   uint32_t hash = 0;
   uint32_t i = 0;
   for(i=0; i<len; str++, i++) {
      hash = ((hash << 5) - hash) + (*str);
   }
   return hash;
}
*/


TGS_HASHTABLE_ENTRY* hashtable_entry_create(char* key, char* value) {
    TGS_HASHTABLE_ENTRY* entry = NULL;
    if (key != NULL) {
        entry = _memalloc(sizeof(TGS_HASHTABLE_ENTRY));
        if (entry != NULL) {
            entry->key = _memalloc(sizeof(char)*strlen(key)+1);
            if (entry->key != NULL) {
                strcpy(entry->key, key);
                entry->value = _memalloc(sizeof(char)*strlen(value)+1);
                if (entry->value != NULL) {
                    strcpy(entry->value, value);
                }
            }
            entry->next = NULL;
        }
    }
    return entry;
}


void hashtable_put(TGS_HASHTABLE* hashtable, char* key, char* value) {
    uint32_t hashcode = 0;
    TGS_HASHTABLE_ENTRY* entry = NULL;
    TGS_HASHTABLE_ENTRY* next = NULL;
    TGS_HASHTABLE_ENTRY* last = NULL;
    hashcode = pearson_hash(key, strlen(key));
    next = hashtable->table[hashcode];

    while(next!=NULL && next->key!=NULL && strcmp(key, next->key) > 0) {
        last = next;
        next = next->next;
    }

    if( next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
        free(next->value);
        next->value = _memalloc(sizeof(char)*strlen(value)+1);
        if (next->value != NULL) {
            strcpy(next->value, value);
        }
    } else {
        entry = hashtable_entry_create(key, value);
        if (next == hashtable->table[hashcode]) {
            entry->next = next;
            hashtable->table[hashcode] = entry;
        } else if (next == NULL) {
            last->next = entry;
        } else  {
            entry->next = next;
            last->next = entry;
        }
    }
}


char* hashtable_get(TGS_HASHTABLE* hashtable, char* key) {
    uint32_t hashcode = 0;
    TGS_HASHTABLE_ENTRY* entry = NULL;
    hashcode = pearson_hash(key, strlen(key));

    entry = hashtable->table[hashcode];
    while(entry != NULL && entry->key != NULL && strcmp(key, entry->key) > 0) {
        entry = entry->next;
    }

    if(entry == NULL || entry->key == NULL || strcmp(key, entry->key) != 0) {
        return NULL;
    } else {
        return entry->value;
    }
}


void hashtable_quit(TGS_HASHTABLE* hashtable) {
    TGS_HASHTABLE_ENTRY* entry = NULL;
    TGS_HASHTABLE_ENTRY* aux = NULL;
    uint32_t i = 0;

    if (hashtable != NULL) {
        for (i=0; i<hashtable->size; ++i) {
            entry = hashtable->table[i];
            while(entry != NULL) {
                aux = entry;
                entry = entry->next;
                aux->next = NULL;
                _memfree(aux->value);
                _memfree(aux->key);
                _memfree(aux);
            }
        }
        _memfree(hashtable->table);
        _memfree(hashtable);
    }
}
