#ifndef MODEL_H
#define MODEL_H

#include <stdlib.h>
#include "cglm/cglm.h"
#include "cjson.h"
#include "mesh.h"
#include "shaders.h"

typedef struct {
    const char* file;
    unsigned char* data;
    cJSON* JSON;
} Model;

unsigned int getUIntOrDefault(cJSON* object, const char* key, unsigned int def) {
    cJSON* item = cJSON_GetObjectItem(object, key);
    return cJSON_IsNumber(item) ? (unsigned int)item->valuedouble : def;
}

Model* createModel(const char* file);

void Draw(Model* model, Shaders* shaders, Camera* cam);

unsigned char* getData(Model* model);

float* getFloats(Model* model, cJSON* accessor);
GLuint* getIndices(Model* model, cJSON* accessor);

vec2* groupFloatVec2(float* floatVec, unsigned int count);
vec3* groupFloatVec3(float* floatVec, unsigned int count);
vec4* groupFloatVec4(float* floatVec, unsigned int count);

#endif