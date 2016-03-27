#ifndef __TGS_CONFIG_H__
#define __TGS_CONFIG_H__


#include "json.h"
#include "hashtable.h"
#include "linkedlist.h"


enum TGS_CONFIG_TYPES {
    CFG_TYPE_BOOLEAN,
    CFG_TYPE_NUMBER,
    CFG_TYPE_STRING,
};


typedef struct TGS_CONFIG_FIELD_DATA {
    char* field_name;
    char* field_value;
    enum TGS_CONFIG_TYPES field_type;
} TGS_CONFIG_FIELD_DATA;


typedef struct TGS_CONFIG {
    cJSON* json;
    TGS_HASHTABLE* sections;
    void (*read)(struct TGS_CONFIG*, const char* filename);
    void (*save)(struct TGS_CONFIG*, const char* filename);
    void (*add_field)(struct TGS_CONFIG*, char* section_name, char* field_name, char* field_value, enum TGS_CONFIG_TYPES field_type);
} TGS_CONFIG;


TGS_CONFIG* config_init();
void config_quit(TGS_CONFIG* config);


#endif
