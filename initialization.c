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

// Load Scenario JSON file
void scenarioInit(const char* jsonString, Scenario** scenarios, int* num_sce) {
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
        cJSON *decision = cJSON_GetObjectItemCaseSensitive(scenario_json, "decision");

        if (cJSON_IsString(scenario_id) && cJSON_IsString(description) && cJSON_IsObject(decision)) {
            strncpy((*scenarios)[sce_idx].name, scenario_id->valuestring, sizeof((*scenarios)[sce_idx].name) - 1);
            //(*scenarios)[sce_idx].name[sizeof((*scenarios)[sce_idx].name) - 1] = '\0';  // Ensure null-termination

            strncpy((*scenarios)[sce_idx].description, description->valuestring, sizeof((*scenarios)[sce_idx].description) - 1);
            //(*scenarios)[sce_idx].description[sizeof((*scenarios)[sce_idx].description) - 1] = '\0';  // Ensure null-termination

            cJSON* option_num = cJSON_GetObjectItemCaseSensitive(decision, "option_num");
            cJSON* decision_question = cJSON_GetObjectItemCaseSensitive(decision, "decision_question");
            cJSON* options = cJSON_GetObjectItemCaseSensitive(decision, "options");

            if (cJSON_IsNumber(option_num) && cJSON_IsString(decision_question) && cJSON_IsArray(options)) {
                (*scenarios)[sce_idx].decision.option_num = option_num->valueint;
                strncpy((*scenarios)[sce_idx].decision.question, decision_question->valuestring,
                        sizeof((*scenarios)[sce_idx].decision.question) - 1);
                (*scenarios)[sce_idx].decision.question[sizeof((*scenarios)[sce_idx].decision.question) - 1] = '\0';  // Ensure null-termination

                int option_idx = 0;
                cJSON* option_json = NULL;
                cJSON_ArrayForEach(option_json, options) {
                    if (option_idx >= MAX_DECISION)
                        break;

                    cJSON* response = cJSON_GetObjectItemCaseSensitive(option_json, "response");
                    cJSON* narrative_bf = cJSON_GetObjectItemCaseSensitive(option_json, "narra_bf");
                    cJSON* narrative_af = cJSON_GetObjectItemCaseSensitive(option_json, "narra_af");
                    cJSON* enemies = cJSON_GetObjectItemCaseSensitive(option_json, "enemies");

                    if (cJSON_IsString(response) && cJSON_IsString(narrative_bf) && cJSON_IsString(narrative_af) && cJSON_IsArray(enemies)) {
                        strncpy((*scenarios)[sce_idx].decision.options[option_idx].response, response->valuestring,
                                sizeof((*scenarios)[sce_idx].decision.options[option_idx].response) - 1);
                        //(*scenarios)[sce_idx].decision.options[option_idx].response[sizeof((*scenarios)[sce_idx].decision.options[option_idx].response) - 1] = '\0';  // Ensure null-termination

                        strncpy((*scenarios)[sce_idx].decision.options[option_idx].narra_bf, narrative_bf->valuestring,
                                sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_bf) - 1);
                        //(*scenarios)[sce_idx].decision.options[option_idx].narra_bf[sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_bf) - 1] = '\0';  // Ensure null-termination

                        strncpy((*scenarios)[sce_idx].decision.options[option_idx].narra_af, narrative_af->valuestring,
                                sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_af) - 1);
                        //(*scenarios)[sce_idx].decision.options[option_idx].narra_af[sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_af) - 1] = '\0';  // Ensure null-termination

                        int enemy_idx = 0;
                        cJSON* enemy = NULL;
                        cJSON_ArrayForEach(enemy, enemies) {
                            if (enemy_idx >= MAX_ENEMIES)
                                break;
                            if (cJSON_IsString(enemy)) {
                                strncpy((*scenarios)[sce_idx].decision.options[option_idx].enemies[enemy_idx], enemy->valuestring,
                                        sizeof((*scenarios)[sce_idx].decision.options[option_idx].enemies[enemy_idx]) - 1);
                                (*scenarios)[sce_idx].decision.options[option_idx].enemies[enemy_idx][sizeof((*scenarios)[sce_idx].decision.options[option_idx].enemies[enemy_idx]) - 1] = '\0';  // Ensure null-termination
                                enemy_idx++;
                            }
                        }
                    }
                    option_idx++;
                }
            }
        }
        sce_idx++;
    }
    cJSON_Delete(json);
}


// Initialize skills
void characterInit (const char* jsonString, Character** players, int* num_charac)
{
    cJSON *json = cJSON_Parse(jsonString);
    if (json == NULL) 
    {
        printf("Failed to parse JSON\n");
        return;
    }

    cJSON* players_json = cJSON_GetObjectItemCaseSensitive(json, "characters");
    if (!cJSON_IsArray(players_json)) 
        {
            printf("Invalid characters format\n");
            cJSON_Delete(json);
            return;
        }
        //
        *num_charac = cJSON_GetArraySize (players_json);
        *players = (Character*)malloc((*num_charac) * sizeof(Character));
        if (*players == NULL) {
            printf("Failed to allocate memory\n");
            cJSON_Delete(json);
            return;
        }
        
        int player_idx = 0;
        cJSON* player_json = NULL;
        cJSON_ArrayForEach(player_json, players_json)
        {
            if (player_idx >= MAX_CHARACTS)
                break;
            cJSON *characters_name = cJSON_GetObjectItemCaseSensitive (player_json, "characters_name");
            cJSON *hp = cJSON_GetObjectItemCaseSensitive (player_json, "hp");
            cJSON *atk = cJSON_GetObjectItemCaseSensitive (player_json, "atk");
            cJSON *def = cJSON_GetObjectItemCaseSensitive (player_json, "def");
            cJSON *skills = cJSON_GetObjectItemCaseSensitive (player_json, "skills");

            if (cJSON_IsString (characters_name) && cJSON_IsNumber(hp) && cJSON_IsNumber(atk) &&
                cJSON_IsNumber(def) && cJSON_IsArray (skills))
                {
                    strncpy((*players)[player_idx].name, characters_name->valuestring, sizeof((*players)[player_idx].name) -1);
                    (*players)[player_idx].atk = atk->valueint;
                    (*players)[player_idx].def = def->valueint;
                    (*players)[player_idx].hp = hp->valueint;
                }
            int skill_idx = 0;
            cJSON* skill_json = NULL;
            cJSON_ArrayForEach(skill_json, skills) 
            {
                if (skill_idx >= MAX_SKILL)
                    break;
                cJSON *skill_name = cJSON_GetObjectItemCaseSensitive(skill_json, "skill_name");
                cJSON *description = cJSON_GetObjectItemCaseSensitive(skill_json, "description");
                cJSON *type = cJSON_GetObjectItemCaseSensitive(skill_json, "type");
                cJSON *duration = cJSON_GetObjectItemCaseSensitive(skill_json, "duration");
                cJSON *atk = cJSON_GetObjectItemCaseSensitive(skill_json, "atk");
                cJSON *hp = cJSON_GetObjectItemCaseSensitive(skill_json, "hp");
                cJSON *def = cJSON_GetObjectItemCaseSensitive(skill_json, "def");

                if (cJSON_IsString(skill_name) && cJSON_IsString(description) && cJSON_IsNumber(type) && cJSON_IsNumber(duration)
                    && cJSON_IsNumber(atk) && cJSON_IsNumber(hp) && cJSON_IsNumber(def)) 
                {
                    strncpy((*players)[player_idx].skills[skill_idx].name, skill_name->valuestring, sizeof((*players)[player_idx].skills[skill_idx].name) -1);
                    strncpy((*players)[player_idx].skills[skill_idx].description, description->valuestring, sizeof((*players)[player_idx].skills[skill_idx].description) -1);
                    (*players)[player_idx].skills[skill_idx].type = type->valueint;
                    (*players)[player_idx].skills[skill_idx].duration = duration->valueint;
                    (*players)[player_idx].skills[skill_idx].atk = atk->valueint;
                    (*players)[player_idx].skills[skill_idx].hp = hp->valueint;
                    (*players)[player_idx].skills[skill_idx].def = def->valueint;
                    skill_idx++;
                }
            }
        player_idx++;
        }
    cJSON_Delete(json);
}


void enemyInit (const char* jsonString, Enemy** enemies, int* num_enemy)
{
    cJSON *json = cJSON_Parse(jsonString);
    if (json == NULL) 
    {
        printf("Failed to parse JSON\n");
        return;
    }

    cJSON* enemies_json = cJSON_GetObjectItemCaseSensitive(json, "enemies");
    if (!cJSON_IsArray(enemies_json)) 
    {
        printf("Invalid enemy format\n");
        cJSON_Delete(json);
        return;
    }

    *num_enemy = cJSON_GetArraySize(enemies_json);
    *enemies = (Enemy*)malloc((*num_enemy) * sizeof(Enemy));
    if (*enemies == NULL) {
        printf("Failed to allocate memory\n");
        cJSON_Delete(json);
        return;
    }

    int enemy_idx = 0;
    cJSON* enemy_json = NULL;
    cJSON_ArrayForEach (enemy_json, enemies_json)
    {
        if (enemy_idx >= *num_enemy)
            break;
        cJSON *enemy_name = cJSON_GetObjectItemCaseSensitive (enemy_json, "enemy_name");
        cJSON *atk = cJSON_GetObjectItemCaseSensitive (enemy_json, "atk");
        cJSON *hp = cJSON_GetObjectItemCaseSensitive (enemy_json, "hp");
        cJSON *def = cJSON_GetObjectItemCaseSensitive (enemy_json, "def");
        cJSON *skills = cJSON_GetObjectItemCaseSensitive (enemy_json, "skills");
        
        if (cJSON_IsString (enemy_name) && cJSON_IsNumber(hp) && cJSON_IsNumber(atk) &&
            cJSON_IsNumber(def) && cJSON_IsArray (skills))
            {
                strncpy ((*enemies)[enemy_idx].name, enemy_name->valuestring, sizeof ((*enemies)[enemy_idx].name) -1);
                (*enemies)[enemy_idx].atk = atk->valueint;
                (*enemies)[enemy_idx].hp = hp->valueint;
                (*enemies)[enemy_idx].def = def->valueint;
            }

        int skill_idx = 0;
        cJSON* skill_json = NULL;
        cJSON_ArrayForEach(skill_json, skills) {
            if (skill_idx >= MAX_SKILL)
                break;
            cJSON *skill_name = cJSON_GetObjectItemCaseSensitive(skill_json, "skill_id");
            cJSON *description = cJSON_GetObjectItemCaseSensitive(skill_json, "description");
            cJSON *type = cJSON_GetObjectItemCaseSensitive(skill_json, "type");
            cJSON *duration = cJSON_GetObjectItemCaseSensitive(skill_json, "duration");
            cJSON *atk = cJSON_GetObjectItemCaseSensitive(skill_json, "atk");
            cJSON *hp = cJSON_GetObjectItemCaseSensitive(skill_json, "hp");
            cJSON *def = cJSON_GetObjectItemCaseSensitive(skill_json, "def");

            if (cJSON_IsString(skill_name) && cJSON_IsString(description) && cJSON_IsNumber(type) && cJSON_IsNumber(duration)
                && cJSON_IsNumber(atk) && cJSON_IsNumber(hp) && cJSON_IsNumber(def)) 
            {
                strncpy((*enemies)[enemy_idx].skills[skill_idx].name, skill_name->valuestring, sizeof((*enemies)[enemy_idx].skills[skill_idx].name) -1);
                strncpy((*enemies)[enemy_idx].skills[skill_idx].description, description->valuestring, sizeof((*enemies)[enemy_idx].skills[skill_idx].description) -1);
                (*enemies)[enemy_idx].skills[skill_idx].type = type->valueint;
                (*enemies)[enemy_idx].skills[skill_idx].duration = duration->valueint;
                (*enemies)[enemy_idx].skills[skill_idx].atk = atk->valueint;
                (*enemies)[enemy_idx].skills[skill_idx].hp = hp->valueint;
                (*enemies)[enemy_idx].skills[skill_idx].def = def->valueint;
                skill_idx++;
            }
        }
        enemy_idx++;
    }
    cJSON_Delete(json);
}