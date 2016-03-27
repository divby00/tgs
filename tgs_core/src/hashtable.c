#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "hashtable.h"


static uint16_t pearson_hash(char* str, size_t len) {
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

    uint8_t h = T[str[0] % 256];
    for (i = 1; i < len; i++) {
        h = T[h ^ str[i]];
    }
    return h;
}


static uint16_t bkdr_hash(char* str, size_t len) {
   uint16_t hash = 0;
   size_t i = 0;
   for(i=0; i<len; str++, i++) {
      hash = ((hash << 5) - hash) + (*str);
   }
   return hash;
}


static TGS_HASHTABLE_ENTRY* hashtable_entry_create(char* key, void* params_create, void* (*create)(void *params), void (*destroy)(void *params)) {
    TGS_HASHTABLE_ENTRY* entry = NULL;
    if (key != NULL) {
        entry = malloc(sizeof(TGS_HASHTABLE_ENTRY));
        if (entry != NULL) {
            memset(entry, 0, sizeof(TGS_HASHTABLE_ENTRY));
            entry->key = malloc(sizeof(char) * (strlen(key)+1));
            if (entry->key != NULL) {
                memset(entry->key, 0, sizeof(char) * (strlen(key)+1));
                strcpy(entry->key, key);
                entry->value = create(params_create);
                entry->destroy = destroy;
            }
            entry->next = NULL;
        }
    }
    return entry;
}


static void hashtable_remove(TGS_HASHTABLE* hashtable, char* key) {
    uint16_t hashcode = 0;
    TGS_HASHTABLE_ENTRY* entry = NULL;
    TGS_HASHTABLE_ENTRY* first = NULL;
    TGS_HASHTABLE_ENTRY* prev = NULL;

    if (hashtable != NULL && key != NULL) {

        hashcode = hashtable->hash(key, strlen(key));
        entry = hashtable->table[hashcode];
        first = entry;
        prev = entry;

        while(entry != NULL && entry->key != NULL && strcmp(key, entry->key) > 0) {
            prev = entry;
            entry = entry->next;
        }

        if (entry != NULL && entry->key != NULL && !strcmp(key, entry->key)) {
            /* It's a first node */
            if (entry == first) {
                first = entry->next;
                entry->destroy(entry->value);
                if (entry->key != NULL) {
                    free(entry->key);
                    entry->key = NULL;
                }
                free(entry);
                entry = NULL;
                hashtable->table[hashcode] = first;
            /* It's the last node */
            } else if (entry->next == NULL) {
                prev->next = NULL;
                entry->destroy(entry->value);
                if (entry->key != NULL) {
                    free(entry->key);
                    entry->key = NULL;
                }
                free(entry);
                entry = NULL;
            /* It's an intermediate node */
            } else {
                prev->next = entry->next;
                entry->destroy(entry->value);
                if (entry->key != NULL) {
                    free(entry->key);
                    entry->key = NULL;
                }
                free(entry);
                entry = NULL;
            }
        }
    }
}


static void hashtable_put(TGS_HASHTABLE* hashtable, char* key, void* params_create, void* (*create)(void *params), void (*destroy)(void *params)) {
    uint16_t hashcode = 0;
    TGS_HASHTABLE_ENTRY* entry = NULL;
    TGS_HASHTABLE_ENTRY* next = NULL;
    TGS_HASHTABLE_ENTRY* last = NULL;
    hashcode = hashtable->hash(key, strlen(key));
    next = hashtable->table[hashcode];

    while(next!=NULL && next->key!=NULL && strcmp(key, next->key) > 0) {
        last = next;
        next = next->next;
    }

    if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0) {
        free(next->value);
        next->value = create(params_create);
    } else {
        entry = hashtable_entry_create(key, params_create, create, destroy);
        hashtable->keys->add(hashtable->keys, key);
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


static void* hashtable_get(TGS_HASHTABLE* hashtable, char* key) {
    uint16_t hashcode = 0;
    TGS_HASHTABLE_ENTRY* entry = NULL;
    hashcode = hashtable->hash(key, strlen(key));

    entry = hashtable->table[hashcode];
    while (entry != NULL && entry->key != NULL && strcmp(key, entry->key) > 0) {
        entry = entry->next;
    }

    if (entry == NULL || entry->key == NULL || strcmp(key, entry->key) != 0) {
        return NULL;
    } else {
        return entry->value;
    }
}


static void* hashtable_string_create(void* params) {
    char* buffer = NULL;
    if (params != NULL) {
        buffer = malloc(sizeof(char) * (strlen(params) + 1));
        if (buffer != NULL) {
            memset(buffer, 0, sizeof(char) * (strlen(params) + 1));
            strcpy(buffer, params);
        }
    }
    return buffer;
}


static void hashtable_string_destroy(void* params) {
    if (params != NULL) {
        free(params);
        params = NULL;
    }
}


static uint8_t hashtable_contains(TGS_HASHTABLE* hashtable, char *key) {
    return (hashtable->get(hashtable, key) != NULL);
}


static TGS_HASHTABLE* hashtable_create(enum TGS_HASHTABLE_SIZE size) {
    TGS_HASHTABLE* hashtable = NULL;
    size_t i = 0;

    hashtable = malloc(sizeof(TGS_HASHTABLE));
    if (hashtable != NULL) {
        memset(hashtable, 0, sizeof(TGS_HASHTABLE));
        if (size == HT_SIZE_NORMAL) {
            hashtable->size = UINT16_MAX + 1;
            hashtable->hash = bkdr_hash;
        } else {
            hashtable->size = UINT8_MAX + 1;
            hashtable->hash = pearson_hash;
        }

        hashtable->keys = linkedlist_init(hashtable_string_create, hashtable_string_destroy);

        hashtable->table = malloc(sizeof(TGS_HASHTABLE_ENTRY*) * hashtable->size);
        if (hashtable->table != NULL) {
            memset(hashtable->table, 0, sizeof(TGS_HASHTABLE_ENTRY*) * hashtable->size);
            for (i=0; i < hashtable->size; i++) {
                hashtable->table[i] = NULL;
            }
        }

        hashtable->put = hashtable_put;
        hashtable->get = hashtable_get;
        hashtable->remove = hashtable_remove;
        hashtable->contains = hashtable_contains;
        hashtable->string_create = hashtable_string_create;
        hashtable->string_destroy = hashtable_string_destroy;
    }
    return hashtable;
}


TGS_HASHTABLE* hashtable_init_small(void) {
    return hashtable_create(HT_SIZE_SMALL);
}


TGS_HASHTABLE* hashtable_init(void) {
    return hashtable_create(HT_SIZE_NORMAL);
}


void hashtable_quit(TGS_HASHTABLE* hashtable) {
    TGS_HASHTABLE_ENTRY* entry = NULL;
    TGS_HASHTABLE_ENTRY* aux = NULL;
    size_t i = 0;

    if (hashtable != NULL) {
        for (i=0; i<hashtable->size; ++i) {
            entry = hashtable->table[i];
            while(entry != NULL) {
                aux = entry;
                entry = entry->next;
                aux->next = NULL;
                aux->destroy(aux->value);
                if (aux->key != NULL) {
                    free(aux->key);
                    aux->key = NULL;
                }
                free(aux);
                aux = NULL;
            }
        }

        linkedlist_quit(hashtable->keys);

        if (hashtable->table != NULL) {
            free(hashtable->table);
            hashtable->table = NULL;
        }
        free(hashtable);
        hashtable = NULL;
    }
}
