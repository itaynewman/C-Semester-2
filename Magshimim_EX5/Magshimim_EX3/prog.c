/*********************************
* Class: MAGSHIMIM C2			 *
* Week:                			 *
* Name:                          *
* Credits:                       *
**********************************/

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    char type[30];
    char name[30];
    int age;
} Animal;

void printAnimal(Animal animal);
bool areSimilar(const Animal* animal1, const Animal* animal2);

int main() {
    Animal animal1, animal2;

    printf("Enter details for the first animal:\n");
    printf("Type: ");
    fgets(animal1.type, sizeof(animal1.type), stdin);
    printf("Name: ");
    fgets(animal1.name, sizeof(animal1.name), stdin);
    printf("Age: ");
    scanf("%d", &animal1.age);

    getchar();

    printf("\nEnter details for the second animal:\n");
    printf("Type: ");
    fgets(animal2.type, sizeof(animal2.type), stdin);
    printf("Name: ");
    fgets(animal2.name, sizeof(animal2.name), stdin);
    printf("Age: ");
    scanf("%d", &animal2.age);

    printf("\nMemory occupied by each animal struct: %d bytes\n", sizeof(Animal) * 2);

    printf("\nDetails of the first animal:\n");
    printAnimal(animal1);

    printf("\nDetails of the second animal:\n");
    printAnimal(animal2);

    if (areSimilar(&animal1, &animal2)) {
        printf("\nAnimals are similar.\n");
    }
    else {
        printf("\nAnimals are not similar.\n");
    }

    return 0;
}

void printAnimal(Animal animal) {
    printf("Type: %s", animal.type);
    printf("Name: %s", animal.name);
    printf("Age: %d\n", animal.age);
}

bool areSimilar(const Animal* animal1, const Animal* animal2) {
    if (strcmp(animal1->type, animal2->type) == 0 &&
        strcmp(animal1->name, animal2->name) == 0 &&
        animal1->age == animal2->age) {
        return true;
    }
    else {
        return false;
    }
}

