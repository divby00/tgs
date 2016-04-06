#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include "memory.h"
#include "stringutils.h"
#include "fileutils.h"
#include "json.h"
#include "config.h"


static void config_read(TGS_CONFIG* config, const char* filename) {
    char* buffer = NULL;

    if (!str_is_empty(filename)) {
        buffer = file_read(filename);
        if (buffer != NULL) {
            config->json = cJSON_Parse(buffer);

            if (config->json != NULL) {
                uint8_t error = 0;
                char* key = NULL;
                TGS_LINKED_LIST* keylist = config->sections->keys;
                TGS_LINKED_LIST* datalist = NULL;
                TGS_LINKED_LIST_NODE* node = NULL;
                TGS_LINKED_LIST_NODE* datanode = NULL;
                TGS_CONFIG_FIELD_DATA* field_data = NULL;

                node = keylist->node;

                while (node != NULL) {
                    key = (char*)node->object;
                    cJSON* section = cJSON_GetObjectItem(config->json, key);
                    if (section != NULL) {
                        datalist = config->sections->get(config->sections, key);
                        datanode = datalist->node;

                        while (datanode != NULL) {
                            field_data = datanode->object;
                            cJSON* obj = cJSON_GetObjectItem(section, field_data->field_name);
                            if (obj == NULL) {
                                error = 1;
                            }
                            datanode = datanode->next;
                        }
                    }
                    node = node->next;
                }

                if (error) {
                    cJSON_Delete(config->json);
                    config->json = NULL;
                }
            }
            memfree(buffer);
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


static cJSON* config_get_json_from_hashtable(TGS_CONFIG* config) {
    TGS_LINKED_LIST* keylist = config->sections->keys;
    TGS_LINKED_LIST* datalist = NULL;
    TGS_LINKED_LIST_NODE* node = NULL;
    TGS_LINKED_LIST_NODE* datanode = NULL;
    TGS_CONFIG_FIELD_DATA* field_data = NULL;
    cJSON* root = NULL;
    cJSON* first = NULL;
    char* key = NULL;
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
    }
    return root;
}


static void config_save(TGS_CONFIG* config, const char* filename) {
    FILE* file = NULL;
    cJSON* root = NULL;
    char* buffer = NULL;

    if (config->json == NULL) {
        root = config_get_json_from_hashtable(config);
    } else {
        root = config->json;
    }

    if (root != NULL) {
        buffer = cJSON_Print(root);
        if (buffer != NULL) {
            file = fopen(filename, "wt");
            fwrite(buffer, sizeof(char)*(strlen(buffer)), 1, file);
            fflush(file);
            fclose(file);
            memfree(buffer);
        }
        cJSON_Delete(root);
        config->json = NULL;
        root = NULL;
    }
}


static cJSON* get_json_object(TGS_CONFIG* config, const char* section, const char* field) {
    cJSON* object = NULL;
    if (config->json != NULL) {
        cJSON* obj = cJSON_GetObjectItem(config->json, section);
        if (obj != NULL) {
            cJSON* sect = cJSON_GetObjectItem(obj, field);
            if (sect != NULL) {
                object = sect;
            }
        }
    }
    return object;
}


static uint8_t config_get_boolean(TGS_CONFIG* config, const char* section, const char* field) {
    uint8_t result = 0;
    cJSON* obj = get_json_object(config, section, field);
    if (obj != NULL) {
        result = obj->valueint;
    }
    return result;
}


static char* config_get_string(TGS_CONFIG* config, const char* section, const char* field) {
    char* result = NULL;
    cJSON* obj = get_json_object(config, section, field);
    if (obj != NULL) {
        result = obj->valuestring;
    }
    return result;
}


static double config_get_number(TGS_CONFIG* config, const char* section, const char* field) {
    double result = 0;
    cJSON* obj = get_json_object(config, section, field);
    if (obj != NULL) {
        result = obj->valuedouble;
    }
    return result;
}


static void config_set_boolean(TGS_CONFIG* config, const char* section, const char* field, uint8_t value) {
    cJSON* obj = get_json_object(config, section, field);
    if (obj != NULL) {
        obj->valueint = value;
    }
}


static void config_set_number(TGS_CONFIG* config, const char* section, const char* field, double value) {
    cJSON* obj = get_json_object(config, section, field);
    if (obj != NULL) {
        obj->valuedouble = value;
    }
}


static void config_set_string(TGS_CONFIG* config, const char* section, const char* field, char* value) {
    char* buffer = NULL;
    cJSON* obj = get_json_object(config, section, field);

    if (obj != NULL) {
        memfree(obj->valuestring);
        buffer = memalloc(sizeof(char) * (strlen(value) + 1));
        strcpy(buffer, value);
        obj->valuestring = buffer;
    }
}


TGS_CONFIG* config_init() {
    TGS_CONFIG* config = NULL;
    config = memalloc(sizeof(TGS_CONFIG));
    if (config != NULL) {
        config->read = config_read;
        config->save = config_save;
        config->add_field = config_add_field;
        config->sections = hashtable_init_small();
        config->get_string = config_get_string;
        config->get_boolean = config_get_boolean;
        config->get_number = config_get_number;
        config->set_boolean = config_set_boolean;
        config->set_number = config_set_number;
        config->set_string = config_set_string;
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
