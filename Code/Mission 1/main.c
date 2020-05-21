#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// For dynamic string lists
struct TextNode{
	char text[14];
	struct TextNode *next;
};

// Dynamic list of strings
struct TextList{
	struct TextNode *head, *tail;
};

// Agent information
struct Agent{
	int ID;
    char name[30];
    char lastName [30];
    int age;
    struct TextList actives;
    struct TextList missions;
};

// For dynamic list of agents
struct AgentNode{
	struct Agent agent;
	struct AgentNode *next;
};

// Dynamic list of agents
struct AgentList{
	struct AgentNode *head;
	struct AgentNode *tail;
};

struct AgentList agents;
int currentID = 0;

// Insert agent to list 
void insertAgent(struct Agent agent) {
	struct AgentNode *newAgentNode, *tmp;

	newAgentNode = (struct AgentNode*)malloc(sizeof(struct AgentNode));
	
	newAgentNode->agent = agent;
	newAgentNode->next = NULL;

	if(agents.head == NULL) {
		agents.head = newAgentNode;
		agents.tail = newAgentNode;
	}
	else {
		agents.tail->next = newAgentNode;
		agents.tail = agents.tail->next;
	}
}

// Insert validated active string
void insertActive(struct Agent *agent, char active[14]) {
	struct TextNode *newActiveNode, *tmp;

	newActiveNode = (struct TextNode*)malloc(sizeof(struct TextNode));
	
	strncpy(newActiveNode->text, active, 14);
	newActiveNode->text[13] = '\0';
	newActiveNode->next = NULL;
	
	if(agent->actives.head == NULL) {
		agent->actives.head = newActiveNode;
		agent->actives.tail = newActiveNode;
	}
	else {
		agent->actives.tail->next = newActiveNode;
		agent->actives.tail = agent->actives.tail->next;
	}
}

// Insert mission active string
void insertMission(struct Agent *agent, char mission[14]) {
	struct TextNode *newActiveNode, *tmp;
	
	newActiveNode = (struct TextNode*)malloc(sizeof(struct TextNode));
	
	strncpy(newActiveNode->text, mission, 14);
	newActiveNode->text[13] = '\0';
	newActiveNode->next = NULL;
	
	if(agent->missions.head == NULL) {
		agent->missions.head = newActiveNode;
		agent->missions.tail = newActiveNode;
	}
	else {
		agent->missions.tail->next = newActiveNode;
		agent->missions.tail = agent->missions.tail->next;
	}
}

void printEncrypted(char* message, bool encrypted) {
    if(!encrypted) {
        printf("%s", message);
    } 
    else {
        int i = 0;
        while(message[i] != '\0') {
            if(message[i] == '\n'){
                printf("\n");
            }
            else if(message[i] == '\t'){
                printf("\t");
            }
            else {
                printf("%c", message[i]+5);
            }
            i++;
        }
    }
}

// Print any general dynamic string list
void printTextList(struct TextList list, bool encrypted) {
	struct TextNode *currentTextNode = list.head;
    char temp [20];
	while (currentTextNode != NULL) {
        snprintf(temp, 20, "\t %s \n", currentTextNode->text);
        printEncrypted(temp, encrypted);
		currentTextNode = currentTextNode->next;
	}
	
}

// Print agent information
void printAgent(struct Agent agent, bool encrypted) {
    char temp[100];

	printEncrypted("\nAgent: \n", encrypted);

    snprintf(temp, 100, "ID: %d\n", agent.ID);
	printEncrypted(temp, encrypted);

    snprintf(temp, 100, "Name: %s\n", agent.name);
	printEncrypted(temp, encrypted);

    snprintf(temp, 100, "Last name: %s\n", agent.lastName);
	printEncrypted(temp, encrypted);

    snprintf(temp, 100, "Age: %d\n", agent.age);
	printEncrypted(temp, encrypted);
    
	printEncrypted("Actives:\n", encrypted);
	if(agent.actives.head == NULL) {
		printEncrypted("\tNo se registraron activos para este agente.\n", encrypted);
	}
	else {
		printTextList(agent.actives, encrypted);
	}

    printEncrypted("Missions:\n", encrypted);
	if(agent.missions.head == NULL) {
		printEncrypted("\tNo se registraron misiones para este agente.\n", encrypted);
	}
	else {
		printTextList(agent.missions, encrypted);
	}
}

// Print complete list of agents
void printAgents(bool encrypted) {
	struct AgentNode *currentAgentNode = agents.head;
	
	printf("\n");

	if(currentAgentNode == NULL) {
		printEncrypted("No hay agentes registrados.", encrypted);
		return;
	}

	while(currentAgentNode != NULL) {
		printAgent(currentAgentNode->agent, encrypted);
		currentAgentNode = currentAgentNode->next;
	}
}

// Validate mission string
bool validateMission(char mission[13]) {
	for(int i = 0; i < 12; i++) {
		if( i < 3) {
			if(mission[i] < 'A' || mission[i] > 'Z' &&
                mission[i] < 'a' || mission[i] > 'z') {
					return false;
			}
		}
        else if (mission[i] < '0' || mission[i] > '9') {
			return false;
		}
	}
	if(mission[12] != '\0') {
		return false;
	}
	
	return true;
}

// Validate active string
bool validateActive(char active[14]) {
    for(int i = 0; i < 13; i++) {
		if( i < 4) {
			if(active[i] < 'A' || active[i] > 'Z' && 
			    active[i] < 'a' || active[i] > 'z') {
					return false;
				}
		} else if (active[i] < '0' || active[i] > '9') {
			return false;
		}
	}
	if(active[13] != '\0') {
		return false;
	}
	
	return true;
}

// Delete agent by given ID
bool deleteAgentByID(int id) {
	struct AgentNode *agentToDelete, *tmp;

	if(agents.head->agent.ID == id) {
		agentToDelete = agents.head;
		agents.head = agents.head->next;
		free(agentToDelete);
		return true;
	}

	agentToDelete = agents.head;

	while(agentToDelete->next != NULL && agentToDelete->next->agent.ID != id) {
		agentToDelete = agentToDelete->next;
	}

	if(agentToDelete->next != NULL) {
		tmp = agentToDelete->next;
		agentToDelete->next = agentToDelete->next->next;
		free(tmp);
		return true;
	}

	return false;
}

bool foundInTextList(struct TextList list, char query[30]){
    struct TextNode *currentNode = list.head;

    while(currentNode != NULL) {
        if(strcmp(currentNode->text, query) == 0) {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

void findAgent(char query[30], bool encrypted){
    bool found = false,  exit = false, keepAsking = true, keepInputing = true;
    int option;
    char temp[20], question;
    struct AgentNode *agentToFind;
    struct Agent *agent;

    agentToFind = agents.head;

    while(agentToFind != NULL){
        if(strcmp(agentToFind->agent.lastName, query)==0 || foundInTextList(agentToFind->agent.actives, query)){
            found = true;
            agent = &agentToFind->agent;
        }
        
        agentToFind = agentToFind->next;
    }

    if(!found) {
        printEncrypted("No se encontró al agente\n", encrypted);
        return;
    }

    printAgent(*agent, encrypted);
    while(!exit){
        printEncrypted("\nDesea borrarlo(1), editarlo(2) o regresar al menu principal(3)?\n", encrypted);
        scanf(" %s", temp);

        option = atoi(temp);

        switch (option) {
        case 1:
            deleteAgentByID(agent->ID);
            printEncrypted("El agente nunca existió.\n Regresando al menu principal... \n", encrypted);
            exit = true;
            break;
        
        case 2:
                printEncrypted("\nIngrese el nombre nuevo del agente: ", encrypted);
                scanf(" %s", agent->name);
                
                printEncrypted("Ingrese el apellido nuevo del agente: ", encrypted);
                scanf(" %s", agent->lastName);
                
                printEncrypted("Ingrese la edad nueva del agente: ", encrypted);
                scanf(" %s", temp);
                agent->age = atoi(temp);

                // Validate age
                while(agent->age <= 0) {
                    printEncrypted("Edad invalida, ingrese de nuevo: ", encrypted);
                    scanf(" %s", temp);
                    agent->age = atoi(temp);
                }

                keepAsking = true;
                while (keepAsking) {
                    printEncrypted("Desea ingresar un activo nuevo? (Y/N) ", encrypted);
                    scanf(" %c", &question);
                    switch (question) {
                        case 'y':
                        case 'Y':
                            keepInputing = true;
                            keepAsking = false;
                            break;
                        case 'n':
                        case 'N':
                            keepInputing = false;
                            keepAsking = false;
                            break;
                        default:
                            printEncrypted("Opcion invalida, intente nuevamente.\n", encrypted);
                            break;
                    }
                }
                
                while (keepInputing) {
                    printEncrypted("Ingrese el activo: ", encrypted);
                    scanf(" %s", temp);
                    while(!validateActive(temp)) {
                        printEncrypted("Activo invalido, intente nuevamente (Formato: 4 caracteres y 9 digitos): ", encrypted);
                        scanf(" %s", temp);
                    }

                    insertActive(agent, temp);
                    printEncrypted("Activo agregado correctamente, ", encrypted);

                    keepAsking = true;
                    while (keepAsking) {
                        printEncrypted(" desea agregar otro activo? (Y/N) ", encrypted);
                        scanf(" %c", &question);
                        switch (question) {
                            case 'y':
                            case 'Y':
                                keepAsking = false;
                                break;
                            case 'n':
                            case 'N':
                                keepInputing = false;
                                keepAsking = false;
                                break;
                            default:
                                printEncrypted("Opcion invalida, intente nuevamente.", encrypted);
                                break;
                        }
                    }
                }

                keepAsking = true;
                while (keepAsking) {
                    printEncrypted("Desea ingresar una mision nueva? (Y/N) ", encrypted);
                    scanf(" %c", &question);
                    switch (question) {
                        case 'y':
                        case 'Y':
                            keepInputing = true;
                            keepAsking = false;
                            break;
                        case 'n':
                        case 'N':
                            keepInputing = false;
                            keepAsking = false;
                            break;
                        default:
                            printEncrypted("Opcion invalida, intente nuevamente.\n", encrypted);
                            break;
                    }
                }
                
                while (keepInputing) {
                    printEncrypted("Ingrese la mision: ", encrypted);
                    scanf(" %s", temp);
                    while(!validateMission(temp)) {
                        printEncrypted("Mision invalida, intente nuevamente (Formato: 3 caracteres y 9 digitos): ", encrypted);
                        scanf(" %s", temp);
                    }

                    insertMission(agent, temp);
                    printEncrypted("Mision agregada correctamente, ", encrypted);

                    keepAsking = true;
                    while (keepAsking) {
                        printEncrypted(" desea agregar otra mision? (Y/N) ", encrypted);
                        scanf(" %c", &question);
                        switch (question) {
                            case 'y':
                            case 'Y':
                                keepAsking = false;
                                break;
                            case 'n':
                            case 'N':
                                keepInputing = false;
                                keepAsking = false;
                                break;
                            default:
                                printEncrypted("Opcion invalida, intente nuevamente.", encrypted);
                                break;
                        }
                    }
                }

                printEncrypted("El agente se edito exitosamente.\n", encrypted);
                exit = true;
        case 3:
          printEncrypted("Regresando al menú principal", encrypted);
          exit = true;

        default:
            printEncrypted("Opcion invalida, intente nuevamente. ", encrypted);
            break;
        }
    }
    
    
}

int main() {
  bool exit = false, keepInputing, keepAsking,  encrypt = true;
	int option, id;
	char question, temp[30];
	struct Agent *agent;
	agents.head = NULL;

    printEncrypted("Bienvenido al sistema, agente.\n", encrypt);

    while(!exit) {
		printEncrypted("\n\nSelecciona una opcion:\n", encrypt);
		printEncrypted("1. Registrar a un agente nuevo.\n", encrypt);
		printEncrypted("2. Desaparecer a un agente.\n", encrypt);
		printEncrypted("3. Revelar las identidades de los agentes.\n", encrypt);
		printEncrypted("4. Revelar la identidad de un agente.\n", encrypt);
		printEncrypted("5. Salir del sistema.\n\n", encrypt);
		
		scanf(" %s", temp);

        if(strcmp("DEncrypt", temp) == 0) {
            encrypt = false;
            printEncrypted("Autenticado correctamente. Bienvenido Agente\n", encrypt);
        } else {
            option = atoi(temp);

            switch (option)
            {
            case 1:
                agent = (struct Agent*)malloc(sizeof(struct Agent));
                agent->actives.head = NULL;
                agent->actives.tail = NULL;
                agent->missions.head = NULL;
                agent->missions.tail = NULL;

                printEncrypted("\nIngrese el nombre del agente: ", encrypt);
                scanf(" %s", agent->name);
                
                printEncrypted("Ingrese el apellido del agente: ", encrypt);
                scanf(" %s", agent->lastName);
                
                printEncrypted("Ingrese la edad del agente: ", encrypt);
                scanf(" %s", temp);
                agent->age = atoi(temp);

                // Validate age
                while(agent->age <= 0) {
                    printEncrypted("Edad invalida, ingrese de nuevo: ", encrypt);
                    scanf(" %s", temp);
                    agent->age = atoi(temp);
                }

                keepAsking = true;
                while (keepAsking) {
                    printEncrypted("Desea ingresar un activo? (Y/N) ", encrypt);
                    scanf(" %c", &question);
                    switch (question) {
                        case 'y':
                        case 'Y':
                            keepInputing = true;
                            keepAsking = false;
                            break;
                        case 'n':
                        case 'N':
                            keepInputing = false;
                            keepAsking = false;
                            break;
                        default:
                            printEncrypted("Opcion invalida, intente nuevamente.\n", encrypt);
                            break;
                    }
                }
                
                while (keepInputing) {
                    printEncrypted("Ingrese el activo: ", encrypt);
                    scanf(" %s", temp);
                    while(!validateActive(temp)) {
                        printEncrypted("Activo invalido, intente nuevamente (Formato: 4 caracteres y 9 digitos): ", encrypt);
                        scanf(" %s", temp);
                    }

                    insertActive(agent, temp);
                    printEncrypted("Activo agregado correctamente, ", encrypt);

                    keepAsking = true;
                    while (keepAsking) {
                        printEncrypted(" desea agregar otro activo? (Y/N) ", encrypt);
                        scanf(" %c", &question);
                        switch (question) {
                            case 'y':
                            case 'Y':
                                keepAsking = false;
                                break;
                            case 'n':
                            case 'N':
                                keepInputing = false;
                                keepAsking = false;
                                break;
                            default:
                                printEncrypted("Opcion invalida, intente nuevamente.", encrypt);
                                break;
                        }
                    }
                }

                keepAsking = true;
                while (keepAsking) {
                    printEncrypted("Desea ingresar una mision? (Y/N) ", encrypt);
                    scanf(" %c", &question);
                    switch (question) {
                        case 'y':
                        case 'Y':
                            keepInputing = true;
                            keepAsking = false;
                            break;
                        case 'n':
                        case 'N':
                            keepInputing = false;
                            keepAsking = false;
                            break;
                        default:
                            printEncrypted("Opcion invalida, intente nuevamente.\n", encrypt);
                            break;
                    }
                }
                
                while (keepInputing) {
                    printEncrypted("Ingrese la mision: ", encrypt);
                    scanf(" %s", temp);
                    while(!validateMission(temp)) {
                        printEncrypted("Mision invalida, intente nuevamente (Formato: 3 caracteres y 9 digitos): ", encrypt);
                        scanf(" %s", temp);
                    }

                    insertMission(agent, temp);
                    printEncrypted("Mision agregada correctamente, ", encrypt);

                    keepAsking = true;
                    while (keepAsking) {
                        printEncrypted(" desea agregar otra mision? (Y/N) ", encrypt);
                        scanf(" %c", &question);
                        switch (question) {
                            case 'y':
                            case 'Y':
                                keepAsking = false;
                                break;
                            case 'n':
                            case 'N':
                                keepInputing = false;
                                keepAsking = false;
                                break;
                            default:
                                printEncrypted("Opcion invalida, intente nuevamente.", encrypt);
                                break;
                        }
                    }
                }

                agent->ID = currentID++;
                insertAgent(*agent);
                printEncrypted("\nAgente agregado exitosamente.\n", encrypt);

                break;
            case 2:
                keepAsking = true;
                while (keepAsking) {
                    printEncrypted("Ingresa el ID del agente a desaparecer (-1 para cancelar): ", encrypt);
                    scanf("%d", &id);
                    if(id == -1){
                        keepAsking = false;
                        keepInputing = false;
                    }
                    else {
                        keepAsking = false;
                        keepInputing = true;
                    }
                }
                
                if(keepInputing) {
                    bool deleted = deleteAgentByID(id);
                    if(deleted) {
                        printEncrypted("\nEl agente nunca existio.\n", encrypt);
                    }
                    else {
                        printEncrypted("\nNo se encontro el agente.\n", encrypt);
                    }
                } else {
                    printEncrypted("\nCancelando opcion.\n", encrypt);
                }

                break;
            case 3:
                printAgents(encrypt);
                break;
            case 4:
                printEncrypted("Ingresa el apellido o un activo del agente a buscar: ", encrypt);
                scanf(" %s", temp);
                findAgent(temp, encrypt);
                break;
            case 5:
                printEncrypted("Saliendo del sistema, adios agente.", encrypt);
                exit = true;
                break;
            default:
                printEncrypted("Opcion invalida, intente de nuevo agente.\n", encrypt);
                break;
            }
        }
    }
	return 0;
}