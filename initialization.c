# include "game.h"
# include "initialization.h"


char* readFile (const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Failed in opening file\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek (fp, 0, SEEK_SET);

    char* content = (char*)malloc(len+1);
    if (content)
    {
        fread(content, 1, len, fp);
        content[len] ='\0';
    }
    fclose(fp);
    return content;
}


# if 0
void loadScenario (const char*jsonString, Scenario** scenarios, int *num_sce)
{
    cJSON *json = cJSON_Parse (jsonString);
    if (json == NULL)
    {
        printf ("Failed in opening json fiel\n");
        return;
    }

    cJSON* scenarios_json = cJSON_GetObjectItemCaseSensitive (json, "scenarios");
    if (!cJSON_IsArray(scenarios_json))
    {
        printf("Invalid format\n");
        cJSON_Delete(json);
        return;
    }

    // allocate memory space
    *num_sce = cJSON_GetArraySize (scenarios_json);
    *scenarios = (Scenario*)malloc ((*num_sce) * sizeof(Scenario));

    // Reading data
    cJSON* scenario_json = NULL;
    int sce_idx = 0;
    cJSON_ArrayForEach(scenario_json, scenarios_json)
    {
        if (sce_idx >= SCE_NUM)
            break;
        cJSON *scenario_id = cJSON_GetObjectItemCaseSensitive (scenario_json, "scenario_id");
        cJSON *description = cJSON_GetObjectItemCaseSensitive (scenario_json, "description");
        cJSON *decisions = cJSON_GetObjectItemCaseSensitive (scenario_json, "decisions");

        if (cJSON_IsString(scenario_id) && cJSON_IsString(description) && cJSON_IsArray(decisions))
        {
            strncpy((*scenarios)[sce_idx].name, scenario_id->valuestring, sizeof((*scenarios)[sce_idx].name) -1);
            strncpy((*scenarios)[sce_idx].description, description->valuestring, sizeof((*scenarios)[sce_idx].description) -1);
        }

        int decision_idx = 0;
        cJSON* decision_json = NULL;
        cJSON_ArrayForEach(decision_json, decisions)
        {
            if (decision_idx >= 2)
                break;

            cJSON* decision_id = cJSON_GetObjectItemCaseSensitive (decision_json, "decision_id");
            cJSON* decision_question = cJSON_GetObjectItemCaseSensitive(decision_json, "decision_question");
            cJSON* options = cJSON_GetObjectItemCaseSensitive(decision_json, "options");

            if (cJSON_IsNumber(decision_id) && cJSON_IsObject(options) && cJSON_IsString(decision_question))
            {
                (*scenarios)[sce_idx].decisions[decision_idx].option_num = decision_id->valueint;
                cJSON* responses = cJSON_GetObjectItemCaseSensitive (options, "response");
                cJSON* narrative_bf = cJSON_GetObjectItemCaseSensitive(options, "narra_bf");
                cJSON* narrative_af = cJSON_GetObjectItemCaseSensitive(options, "narra_af");
                cJSON* enemies = cJSON_GetObjectItemCaseSensitive(options, "enemies");

                if (cJSON_IsString(responses) && cJSON_IsString(narrative_bf) && cJSON_IsArray(enemies) && cJSON_IsString(narrative_af))
                {
                    strncpy((*scenarios)[sce_idx].decisions[decision_idx].options.response, responses->valuestring,
                    sizeof((*scenarios)[sce_idx].decisions[decision_idx].options.response) -1);

                    strncpy((*scenarios)[sce_idx].decisions[decision_idx].options.narra_bf, narrative_bf->valuestring,
                    sizeof((*scenarios)[sce_idx].decisions[decision_idx].options.narra_bf) -1);

                    strncpy((*scenarios)[sce_idx].decisions[decision_idx].options.narra_af, narrative_af->valuestring,
                    sizeof((*scenarios)[sce_idx].decisions[decision_idx].options.narra_af) -1);

                    int enemy_idx = 0;
                    cJSON* enemy = NULL;
                    cJSON_ArrayForEach(enemy, enemies)
                    {
                        if (enemy_idx >= MAX_ENEMIES)
                            break;
                        if (cJSON_IsString(enemy))
                        {
                            strncpy((*scenarios)[sce_idx].decisions[decision_idx].options.enemies[enemy_idx], enemy->valuestring,
                            MAX_CHAR_NAME -1);
                            enemy_idx++; 
                        }
                    }                    
                }
                
            }
            decision_idx++;     
        }
           
    }sce_idx++; 
    cJSON_Delete(json);  
}

# endif


void loadScenario(const char* jsonString, Scenario** scenarios, int* num_sce) {
    cJSON *json = cJSON_Parse(jsonString);
    if (json == NULL) {
        printf("Failed to parse JSON\n");
        return;
    }

    cJSON* scenarios_json = cJSON_GetObjectItemCaseSensitive(json, "scenarios");
    if (!cJSON_IsArray(scenarios_json)) {
        printf("Invalid scenarios format\n");
        cJSON_Delete(json);
        return;
    }

    *num_sce = cJSON_GetArraySize(scenarios_json);
    *scenarios = (Scenario*)malloc((*num_sce) * sizeof(Scenario));
    if (*scenarios == NULL) {
        printf("Failed to allocate memory\n");
        cJSON_Delete(json);
        return;
    }

    int sce_idx = 0;
    cJSON* scenario_json = NULL;
    cJSON_ArrayForEach(scenario_json, scenarios_json) {
        cJSON *scenario_id = cJSON_GetObjectItemCaseSensitive(scenario_json, "scenario_id");
        cJSON *description = cJSON_GetObjectItemCaseSensitive(scenario_json, "description");
        cJSON *decisions = cJSON_GetObjectItemCaseSensitive(scenario_json, "decisions");

        if (cJSON_IsString(scenario_id) && cJSON_IsString(description) && cJSON_IsArray(decisions)) {
            strncpy((*scenarios)[sce_idx].name, scenario_id->valuestring, sizeof((*scenarios)[sce_idx].name) - 1);
            strncpy((*scenarios)[sce_idx].description, description->valuestring, sizeof((*scenarios)[sce_idx].description) - 1);
        }

        int decision_idx = 0;
        cJSON* decision_json = NULL;
        cJSON_ArrayForEach(decision_json, decisions) {
            if (decision_idx >= MAX_DECISION)
                break;

            cJSON* decision_id = cJSON_GetObjectItemCaseSensitive(decision_json, "decision_id");
            cJSON* decision_question = cJSON_GetObjectItemCaseSensitive(decision_json, "decision_question");
            cJSON* options = cJSON_GetObjectItemCaseSensitive(decision_json, "options");

            if (cJSON_IsNumber(decision_id) && cJSON_IsString(decision_question) && cJSON_IsObject(options)) {
                (*scenarios)[sce_idx].decisions[decision_idx].option_num = decision_id->valueint;

                cJSON* responses = cJSON_GetObjectItemCaseSensitive(options, "response");
                cJSON* narrative_bf = cJSON_GetObjectItemCaseSensitive(options, "narra_bf");
                cJSON* narrative_af = cJSON_GetObjectItemCaseSensitive(options, "narra_af");
                cJSON* enemies = cJSON_GetObjectItemCaseSensitive(options, "enemies");

                if (cJSON_IsString(responses) && cJSON_IsString(narrative_bf) && cJSON_IsString(narrative_af) && cJSON_IsArray(enemies)) {
                    strncpy((*scenarios)[sce_idx].decisions[decision_idx].options.response, responses->valuestring,
                            sizeof((*scenarios)[sce_idx].decisions[decision_idx].options.response) - 1);
                    strncpy((*scenarios)[sce_idx].decisions[decision_idx].options.narra_bf, narrative_bf->valuestring,
                            sizeof((*scenarios)[sce_idx].decisions[decision_idx].options.narra_bf) - 1);
                    strncpy((*scenarios)[sce_idx].decisions[decision_idx].options.narra_af, narrative_af->valuestring,
                            sizeof((*scenarios)[sce_idx].decisions[decision_idx].options.narra_af) - 1);

                    int enemy_idx = 0;
                    cJSON* enemy = NULL;
                    cJSON_ArrayForEach(enemy, enemies) {
                        if (enemy_idx >= MAX_ENEMIES)
                            break;
                        if (cJSON_IsString(enemy)) {
                            strncpy((*scenarios)[sce_idx].decisions[decision_idx].options.enemies[enemy_idx], enemy->valuestring,
                                    MAX_CHAR_NAME - 1);
                            enemy_idx++;
                        }
                    }
                }
            }
            decision_idx++;
        }
        sce_idx++;
    }
    cJSON_Delete(json);
}

