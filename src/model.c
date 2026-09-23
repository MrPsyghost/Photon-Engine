#include "model.h"

Model* createModel(const char* file) {
    Model* model = malloc(sizeof(Model));

    const char* text = getFileContents(file);
    
    model->file = file;
    model->JSON = cJSON_Parse(text);

    model->data = getData(model);

    return model;
}

void Draw(Model* model, Shaders* shaders, Camera* cam) {
    
}

unsigned char* getData(Model* model) {
    cJSON* buffers = cJSON_GetObjectItem(model->JSON, "buffers");
    if (!cJSON_IsArray(buffers))
        return NULL;

    cJSON* buffer = cJSON_GetArrayItem(buffers, 0);
    if (!buffer)
        return NULL;

    cJSON* uri = cJSON_GetObjectItem(buffer, "uri");
    if (!cJSON_IsString(uri))
        return NULL;

    char path[1024];

    char* lastSlash = strrchr(model->file, '/');
    if (!lastSlash) {
        lastSlash = strrchr(model->file, '\\');
    }

    if (lastSlash)
    {
        size_t len = lastSlash - model->file + 1;
        strncpy(path, model->file, len);
        path[len] = '\0';
        strcat(path, uri->valuestring);
    }
    else
    {
        strcpy(path, uri->valuestring);
    }

    return getFileContents(path);
}

float* getFloats(Model* model, cJSON* accessor)
{
    unsigned int bufferViewInd = getUIntOrDefault(accessor, "bufferView", 1);
    unsigned int count = getUIntOrDefault(accessor, "count", 0);
    unsigned int accByteOffset = getUIntOrDefault(accessor, "byteOffset", 0);

    cJSON* typeItem = cJSON_GetObjectItem(accessor, "type");
    if (!cJSON_IsString(typeItem))
        return NULL;

    cJSON* bufferViews = cJSON_GetObjectItem(model->JSON, "bufferViews");
    cJSON* bufferView = cJSON_GetArrayItem(bufferViews, bufferViewInd);
    if (!bufferView)
        return NULL;

    unsigned int byteOffset = getUIntOrDefault(bufferView, "byteOffset", 0);

    unsigned int numPerVert;

    if (strcmp(typeItem->valuestring, "SCALAR") == 0)
        numPerVert = 1;
    else if (strcmp(typeItem->valuestring, "VEC2") == 0)
        numPerVert = 2;
    else if (strcmp(typeItem->valuestring, "VEC3") == 0)
        numPerVert = 3;
    else if (strcmp(typeItem->valuestring, "VEC4") == 0)
        numPerVert = 4;
    else
    {
        printf("Invalid accessor type.\n");
        return NULL;
    }

    unsigned int beginningOfData = byteOffset + accByteOffset;
    unsigned int numFloats = count * numPerVert;

    float* floatVec = malloc(numFloats * sizeof(float));
    if (!floatVec)
        return NULL;

    unsigned int j = 0;

    for (unsigned int i = beginningOfData;
         i < beginningOfData + numFloats * sizeof(float);
         i += sizeof(float))
    {
        memcpy(&floatVec[j++], &model->data[i], sizeof(float));
    }

    return floatVec;
}

GLuint* getIndices(Model* model, cJSON* accessor)
{
    unsigned int bufferViewInd = getUIntOrDefault(accessor, "bufferView", 1);
    unsigned int count = getUIntOrDefault(accessor, "count", 0);
    unsigned int accByteOffset = getUIntOrDefault(accessor, "byteOffset", 0);
    unsigned int componentType = getUIntOrDefault(accessor, "componentType", 0);

    cJSON* bufferViews = cJSON_GetObjectItem(model->JSON, "bufferViews");
    cJSON* bufferView = cJSON_GetArrayItem(bufferViews, bufferViewInd);
    if (!bufferView)
        return NULL;

    unsigned int byteOffset = getUIntOrDefault(bufferView, "byteOffset", 0);

    unsigned int beginningOfData = byteOffset + accByteOffset;

    GLuint* indices = malloc(count * sizeof(GLuint));
    if (!indices)
        return NULL;

    unsigned int j = 0;

    if (componentType == 5125) // UNSIGNED_INT
    {
        for (unsigned int i = beginningOfData;
             i < beginningOfData + count * sizeof(unsigned int);
             i += sizeof(unsigned int))
        {
            unsigned int value;
            memcpy(&value, &model->data[i], sizeof(unsigned int));
            indices[j++] = (GLuint)value;
        }
    }
    else if (componentType == 5123) // UNSIGNED_SHORT
    {
        for (unsigned int i = beginningOfData;
             i < beginningOfData + count * sizeof(unsigned short);
             i += sizeof(unsigned short))
        {
            unsigned short value;
            memcpy(&value, &model->data[i], sizeof(unsigned short));
            indices[j++] = (GLuint)value;
        }
    }
    else if (componentType == 5121) // UNSIGNED_BYTE
    {
        for (unsigned int i = beginningOfData;
             i < beginningOfData + count;
             i++)
        {
            indices[j++] = (GLuint)model->data[i];
        }
    }
    else
    {
        free(indices);
        printf("Unsupported index component type: %u\n", componentType);
        return NULL;
    }

    return indices;
}

vec2* groupFloatVec2(float* floatVec, unsigned int count) {
    vec2* vectors = malloc(count * sizeof(vec2));
    if (!vectors) { return NULL; }
    
    for (unsigned int i = 0, j = 0; i < count; j++, i += 2) {
        vectors[j][0] = floatVec[i];
        vectors[j][1] = floatVec[i+1];
    }
    
    return vectors;
}

vec3* groupFloatVec3(float* floatVec, unsigned int count) {
    vec3* vectors = malloc(count * sizeof(vec3));
    if (!vectors) { return NULL; }
    
    for (unsigned int i = 0, j = 0; i < count; j++, i += 3) {
        vectors[j][0] = floatVec[i];
        vectors[j][1] = floatVec[i+1];
        vectors[j][2] = floatVec[i+2];
    }

    return vectors;
}

vec4* groupFloatVec4(float* floatVec, unsigned int count) {
    vec4* vectors = malloc(count * sizeof(vec4));
    if (!vectors) { return NULL; }
    
    for (unsigned int i = 0, j = 0; i < count; j++, i += 4) {
        vectors[j][0] = floatVec[i];
        vectors[j][1] = floatVec[i+1];
        vectors[j][2] = floatVec[i+2];
        vectors[j][3] = floatVec[i+3];
    }

    return vectors;
}