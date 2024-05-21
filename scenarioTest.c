#include "scenarioTest.h"
/* 
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
                // (*scenarios)[sce_idx].decision.question[sizeof((*scenarios)[sce_idx].decision.question) - 1] = '\0';  // Ensure null-termination

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
                        strncpy((*scenarios)[sce_idx].decision.options[option_idx].narra_bf, narrative_bf->valuestring,
                                sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_bf) - 1);
                        strncpy((*scenarios)[sce_idx].decision.options[option_idx].narra_af, narrative_af->valuestring,
                                sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_af) - 1);

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
*/
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
            (*scenarios)[sce_idx].name[sizeof((*scenarios)[sce_idx].name) - 1] = '\0'; // Ensure null-termination

            strncpy((*scenarios)[sce_idx].description, description->valuestring, sizeof((*scenarios)[sce_idx].description) - 1);
            (*scenarios)[sce_idx].description[sizeof((*scenarios)[sce_idx].description) - 1] = '\0'; // Ensure null-termination

            cJSON* option_num = cJSON_GetObjectItemCaseSensitive(decision, "option_num");
            cJSON* decision_question = cJSON_GetObjectItemCaseSensitive(decision, "decision_question");
            cJSON* options = cJSON_GetObjectItemCaseSensitive(decision, "options");

            if (cJSON_IsNumber(option_num) && cJSON_IsString(decision_question) && cJSON_IsArray(options)) {
                (*scenarios)[sce_idx].decision.option_num = option_num->valueint;
                strncpy((*scenarios)[sce_idx].decision.question, decision_question->valuestring,
                        sizeof((*scenarios)[sce_idx].decision.question) - 1);
                (*scenarios)[sce_idx].decision.question[sizeof((*scenarios)[sce_idx].decision.question) - 1] = '\0'; // Ensure null-termination

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
                        (*scenarios)[sce_idx].decision.options[option_idx].response[sizeof((*scenarios)[sce_idx].decision.options[option_idx].response) - 1] = '\0'; // Ensure null-termination

                        strncpy((*scenarios)[sce_idx].decision.options[option_idx].narra_bf, narrative_bf->valuestring,
                                sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_bf) - 1);
                        (*scenarios)[sce_idx].decision.options[option_idx].narra_bf[sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_bf) - 1] = '\0'; // Ensure null-termination

                        strncpy((*scenarios)[sce_idx].decision.options[option_idx].narra_af, narrative_af->valuestring,
                                sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_af) - 1);
                        (*scenarios)[sce_idx].decision.options[option_idx].narra_af[sizeof((*scenarios)[sce_idx].decision.options[option_idx].narra_af) - 1] = '\0'; // Ensure null-termination

                        int enemy_idx = 0;
                        cJSON* enemy_json = NULL;
                        cJSON_ArrayForEach(enemy_json, enemies) {
                            if (enemy_idx >= MAX_ENEMIES)
                                break;

                            cJSON* enemy_name = cJSON_GetObjectItemCaseSensitive(enemy_json, "enemy_name");
                            cJSON* atk = cJSON_GetObjectItemCaseSensitive(enemy_json, "atk");
                            cJSON* hp = cJSON_GetObjectItemCaseSensitive(enemy_json, "hp");
                            cJSON* def = cJSON_GetObjectItemCaseSensitive(enemy_json, "def");
                            cJSON* skills = cJSON_GetObjectItemCaseSensitive(enemy_json, "skills");

                            if (cJSON_IsString(enemy_name) && cJSON_IsNumber(atk) && cJSON_IsNumber(hp) &&
                                cJSON_IsNumber(def) && cJSON_IsArray(skills)) {
                                Enemy *enemy = &(*scenarios)[sce_idx].decision.options[option_idx].enemies[enemy_idx];
                                strncpy(enemy->name, enemy_name->valuestring, sizeof(enemy->name) - 1);
                                enemy->name[sizeof(enemy->name) - 1] = '\0'; // Ensure null-termination
                                enemy->atk = atk->valueint;
                                enemy->hp = hp->valueint;
                                enemy->def = def->valueint;

                                int skill_idx = 0;
                                cJSON* skill_json = NULL;
                                cJSON_ArrayForEach(skill_json, skills) {
                                    if (skill_idx >= MAX_SKILL)
                                        break;

                                    cJSON* skill_id = cJSON_GetObjectItemCaseSensitive(skill_json, "skill_id");
                                    cJSON* description = cJSON_GetObjectItemCaseSensitive(skill_json, "description");
                                    cJSON* type = cJSON_GetObjectItemCaseSensitive(skill_json, "type");
                                    cJSON* duration = cJSON_GetObjectItemCaseSensitive(skill_json, "duration");
                                    cJSON* skill_atk = cJSON_GetObjectItemCaseSensitive(skill_json, "atk");
                                    cJSON* skill_hp = cJSON_GetObjectItemCaseSensitive(skill_json, "hp");
                                    cJSON* skill_def = cJSON_GetObjectItemCaseSensitive(skill_json, "def");

                                    if (cJSON_IsString(skill_id) && cJSON_IsString(description) && cJSON_IsString(type) && cJSON_IsNumber(duration)
                                        && cJSON_IsNumber(skill_atk) && cJSON_IsNumber(skill_hp) && cJSON_IsNumber(skill_def)) {
                                        Skill *skill = &enemy->skills[skill_idx];
                                        strncpy(skill->name, skill_id->valuestring, sizeof(skill->name) - 1);
                                        skill->name[sizeof(skill->name) - 1] = '\0'; // Ensure null-termination
                                        strncpy(skill->description, description->valuestring, sizeof(skill->description) - 1);
                                        skill->description[sizeof(skill->description) - 1] = '\0'; // Ensure null-termination
                                        strncpy(skill->type, type->valuestring, sizeof(skill->type) - 1);
                                        skill->type[sizeof(skill->type) - 1] = '\0'; // Ensure null-termination
                                        skill->duration = duration->valueint;
                                        skill->atk = skill_atk->valueint;
                                        skill->hp = skill_hp->valueint;
                                        skill->def = skill_def->valueint;

                                        skill_idx++;
                                    }
                                }
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
