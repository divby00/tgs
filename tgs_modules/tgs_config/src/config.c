#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "memory.h"
#include "stringutils.h"
#include "json.h"
#include "config.h"


static void config_read(TGS_CONFIG* config, const char* filename) {
    char* buffer = NULL;
    uint64_t size = 0;
    FILE* f = NULL;

    if (!str_is_empty(filename)) {
        f = fopen(filename, "rt");
        if (f != NULL) {
            fseek(f, 0, SEEK_END);
            size = ftell(f);
            fseek(f, 0, SEEK_SET);
            buffer = memalloc(size);
            if (buffer != NULL) {
                fread(buffer, size, 1, f);
                config->json = cJSON_Parse(buffer);

                if (config->json != NULL) {
                    char* b = cJSON_Print(config->json);
                    free(b);
                }
                memfree(buffer);
            }
            fclose(f);
        }
    }
}


static void* field_data_add(void* params) {
    TGS_CONFIG_FIELD_DATA* field_params = params;
    TGS_CONFIG_FIELD_DATA* field_data = NULL;

    if (!str_is_empty(field_params->field_name) && !str_is_empty(field_params->field_value)) {
        field_data = memalloc(sizeof(TGS_CONFIG_FIELD_DATA));
        if (field_data != NULL) {
            field_data->field_name = memalloc(sizeof(char) * (strlen(field_params->field_name) + 1));
            if (field_data->field_name != NULL) {
                strcpy(field_data->field_name, field_params->field_name);
            }
            field_data->field_value = memalloc(sizeof(char) * (strlen(field_params->field_value) + 1));
            if (field_data->field_value != NULL) {
                strcpy(field_data->field_value, field_params->field_value);
            }
            field_data->field_type = field_params->field_type;
        }
    }
    return field_data;
}


static void field_data_remove(void* params) {
    struct TGS_CONFIG_FIELD_DATA* field_params = params;
    if (field_params != NULL) {
        memfree(field_params->field_name);
        memfree(field_params->field_value);
        memfree(field_params);
    }
}


static void* section_add(void* params) {
    TGS_LINKED_LIST* list = NULL;
    params = NULL;
    list = linkedlist_init(field_data_add, field_data_remove);
    return list;
}


static void section_remove(void* params) {
    linkedlist_quit(params);
}


static void config_add_field(TGS_CONFIG* config, char* section_name, char* field_name, char* field_value, enum TGS_CONFIG_TYPES field_type) {
    TGS_HASHTABLE* sections = NULL;
    TGS_LINKED_LIST* list = NULL;
    TGS_CONFIG_FIELD_DATA field_data;

    if (config != NULL && !str_is_empty(section_name) && !str_is_empty(field_name) && !str_is_empty(field_value)) {
        sections = config->sections;
        if (!sections->contains(sections, section_name)) {
            sections->put(sections, section_name, "", section_add, section_remove);
        }
        list = sections->get(sections, section_name);
        field_data.field_name = field_name;
        field_data.field_value = field_value;
        field_data.field_type = field_type;
        list->add(list, &field_data);
    }
}


static void config_save(TGS_CONFIG* config, const char* filename) {
    FILE* file = NULL;
    TGS_LINKED_LIST* keylist = config->sections->keys;
    TGS_LINKED_LIST* datalist = NULL;
    TGS_LINKED_LIST_NODE* node = NULL;
    TGS_LINKED_LIST_NODE* datanode = NULL;
    TGS_CONFIG_FIELD_DATA* field_data = NULL;
    cJSON* root = NULL;
    cJSON* first = NULL;
    char* key = NULL;
    char* buffer = NULL;
    double number = 0;
    uint8_t boolean = 0;

    root = cJSON_CreateObject();
    if (root != NULL) {
        node = keylist->node;

        while(node != NULL) {
            key = (char*)node->object;
            first = cJSON_CreateObject();
            cJSON_AddItemToObject(root, key, first);
            datalist = config->sections->get(config->sections, key);
            datanode = datalist->node;

            while(datanode != NULL) {
                field_data = datanode->object;
                if (field_data->field_type == CFG_TYPE_STRING) {
                    cJSON_AddItemToObject(first, field_data->field_name, cJSON_CreateString(field_data->field_value));
                } else if (field_data->field_type == CFG_TYPE_NUMBER) {
                    number = strtod(field_data->field_value, NULL);
                    cJSON_AddItemToObject(first, field_data->field_name, cJSON_CreateNumber(number));
                } else if (field_data->field_type == CFG_TYPE_BOOLEAN) {
                    boolean = (!strcmp(field_data->field_value, "true")) ? 1: 0;
                    cJSON_AddItemToObject(first, field_data->field_name, cJSON_CreateBool(boolean));
                }
                datanode = datanode->next;
            }
            node = node->next;
        }

        buffer = cJSON_Print(root);
        if (buffer != NULL) {
            file = fopen(filename, "wt");
            fwrite(buffer, sizeof(char)*(strlen(buffer)), 1, file);
            fflush(file);
            fclose(file);
            memfree(buffer);
        }
        cJSON_Delete(root);
    }
}


TGS_CONFIG* config_init() {
    TGS_CONFIG* config = NULL;
    config = memalloc(sizeof(TGS_CONFIG));
    if (config != NULL) {
        config->read = config_read;
        config->save = config_save;
        config->add_field = config_add_field;
        config->sections = hashtable_init();
    }
    return config;
}


void config_quit(TGS_CONFIG* config) {
    if (config != NULL) {
        if (config->json != NULL) {
            cJSON_Delete(config->json);
            config->json = NULL;
        }
        hashtable_quit(config->sections);
        memfree(config);
    }
}
