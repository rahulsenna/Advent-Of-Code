#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct CITIES CITIES;

typedef struct
{
	CITIES *to;
	int dist;
} CITY_EDGE;

struct CITIES
{
    char city[MAX_SIZE];
	int idx;
    CITIES* next;
};

CITIES *CreateCityNode(const char *city)
{
    CITIES *newNode = (CITIES *) malloc(sizeof(CITIES));
    strcpy(newNode->city, city);
    newNode->next = NULL;
    return newNode;
}

void InsertCityAlphabetically(CITIES **head, const char *city_name, int *city_count)
{
	CITIES **cursor = head;

    while (*cursor != NULL && strcmp((*cursor)->city, city_name) < 0)
        cursor = &(*cursor)->next;
	
    if (*cursor != NULL && strcmp((*cursor)->city, city_name) == 0) // Disallowing duplicates
        return;

    CITIES *city = CreateCityNode(city_name);
	city->idx = (*city_count)++;
	city->next = *cursor;
	*cursor = city;
}



int main() {
    FILE* file = fopen("input.txt", "r");
    CITIES* cities = NULL;

	int adjacencyMatrix[MAX_SIZE][MAX_SIZE];

    // Initialize adjacency matrix with infinity
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            adjacencyMatrix[i][j] = -1;
        }
    }

    char line[MAX_SIZE];
    char src[MAX_SIZE], to[MAX_SIZE], dest[MAX_SIZE], eq[MAX_SIZE];
    int dist;
	
	int city_count = 0;

    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%s %s %s %s %d", src, to, dest, eq, &dist);
        InsertCityAlphabetically(&cities, src, &city_count);
        InsertCityAlphabetically(&cities, dest, &city_count);
    }
    fclose(file);

    // Print the cities
    CITIES* current = cities;
    printf("Cities:\n");
    while (current != NULL)
    {
        printf("%s\n", current->city);
        current = current->next;
    }

	printf("city_count: %d\n", city_count);

    return 0;
}
