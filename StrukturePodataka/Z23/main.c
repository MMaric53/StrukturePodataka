#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define FILE_ERROR_OPEN -1
#define MALLOC_ERROR -2
#define SCANF_ERROR -3
#define MAX_BUFFER 1024
#define N 50

struct _person;
typedef struct _person* Position;

typedef struct _person {
	char name[N];
	char surname[N];
	int bYear;
	Position next;
} Person;

Position createPerson();
int addToFrontOfTheList(Position);
int addToEndOfTheList(Position);
int printPerson(Position);
int printList(Position);
Position findPerson(Position, char*);
int deletePerson(Position, char*);
int deleteList(Position);
int addAfter(Position, char*);
int addBefore(Position, char*);
int fileWrite(Position);
int _fileRead();
int fileRead(Position);

void main()
{
	char in = 0;
	FILE* fp = NULL;

	char surname[N];
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .bYear = 0 };
	Person headR = { .next = NULL, .name = {0}, .surname = {0}, .bYear = 0 }; // for reading from file

	printf("f - add person to front of the list\ne - add person to end of the list\na - add person after person with surname\nb - add person before person with surname\np - print list\ns - find person with surname\nd - delete person with surname\nw - write list into file\nr - read list from file\n0 - end program\n");

	do
	{
		printf("\nChoose action: ");
		if (scanf(" %c", &in) != 1) return SCANF_ERROR;

		switch (in)
		{
			case 'f':
				printf("Add to front of the list\n");
				addToFrontOfTheList(&head);
				break;
			case 'e':
				printf("Add to end of the list\n");
				addToEndOfTheList(&head);
				break;
			case 'a':
				printf("Add after person with surname: ");
				if (scanf(" %s", surname) != 1) return SCANF_ERROR;
				addAfter(&head, surname);
				break;
			case 'b':
				printf("Add before person with surname: ");
				if (scanf(" %s", surname) != 1) return SCANF_ERROR;
				addBefore(&head, surname);
				break;
			case 'p':
				printf("Printing list:\n");
				printList(head.next);
				break;
			case 's':
				printf("Find person with surname: ");
				if (scanf(" %s", surname) != 1) return SCANF_ERROR;
				findPerson(head.next, surname) ? 
					printPerson(findPerson(head.next, surname)) : printf("\tPerson with surname '%s' was not found.\n", surname);
				break;
			case 'd':
				printf("Delete person with surname: ");
				if (scanf(" %s", surname) != 1) return SCANF_ERROR;
				deletePerson(&head, surname);
				break;
			case 'w':
				printf("Writing list into file...\n");
				fileWrite(head.next);
				break;
			case 'r':
				printf("Reading list from file:\n");
				fileRead(&headR);
				printList(headR.next);
				break;
			case '0':
				break;
			default:
				printf("\tInvalid input. Try again.\n");
				break;
		}
	} while (in != '0');

	deleteList(&head);
	deleteList(&headR);

	return EXIT_SUCCESS;
}

Position createPerson()
{
	Position person = NULL;
	person = (Position)malloc(sizeof(Person));
	if (!person) return NULL;

	printf("\tName: ");
	if (scanf(" %s", person->name) != 1) return SCANF_ERROR;

	printf("\tSurname: ");
	if (scanf(" %s", person->surname) != 1) return SCANF_ERROR;

	printf("\tBirth year: ");
	if (scanf(" %d", &person->bYear) != 1) return SCANF_ERROR;

	return person;
}

int addToFrontOfTheList(Position head)
{
	Position newPerson = NULL;
	newPerson = createPerson();
	if (!newPerson) {
		printf("Malloc error!\n");
		return MALLOC_ERROR;
	}

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int addToEndOfTheList(Position head)
{
	Position newPerson = NULL;
	newPerson = createPerson();
	if (!newPerson) {
		printf("Malloc error!\n");
		return MALLOC_ERROR;
	}

	while (head->next != NULL)
		head = head->next;

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int printPerson(Position person)
{
	printf("\t%s %s, born in %d. \n", person->name, person->surname, person->bYear);
	return EXIT_SUCCESS;
}

int printList(Position current)
{
	if (current == NULL)
		printf("\tEmpty list!\n");

	while (current != NULL) {
		printPerson(current);
		current = current->next;
	}
	
	return EXIT_SUCCESS;
}

Position findPerson(Position current, char* sur)
{
	while (current != NULL && strcmp(current->surname, sur))
		current = current->next;

	return current;
}

Position findPersonPrev(Position current, char* sur)
{
	while (current->next != NULL && strcmp(current->next->surname, sur))
		current = current->next;

	if (current->next == NULL) return NULL;

	return current;
}

int deletePerson(Position head, char* sur)
{
	Position temp = NULL, prev = NULL;

	prev = findPersonPrev(head, sur);

	if (prev != NULL)
	{
		temp = prev->next;
		prev->next = temp->next;
		free(temp);

		printf("\tPerson deleted.\n");
	}
	else printf("\tPerson with surname '%s' was not found.\n", sur);

	return EXIT_SUCCESS;
}

int deleteList(Position head)
{
	Position temp = NULL;

	while (head->next != NULL)
	{
		temp = head->next;
		head->next = head->next->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

int addAfter(Position head, char* sur)
{
	Position newPerson = NULL, personWithSurname = NULL;

	personWithSurname = findPerson(head, sur);

	if (personWithSurname != NULL)
	{
		newPerson = createPerson();
		if (!newPerson) {
			printf("Malloc error!\n");
			return MALLOC_ERROR;
		}

		newPerson->next = personWithSurname->next;
		personWithSurname->next = newPerson;
	}
	else printf("\tPerson with surname '%s' was not found.\n", sur);

	return EXIT_SUCCESS;
}

int addBefore(Position head, char* sur)
{
	Position newPerson = NULL, personBeforeSurname = NULL;

	personBeforeSurname = findPersonPrev(head, sur);
	
	if (personBeforeSurname != NULL)
	{
		newPerson = createPerson();
		if (!newPerson) {
			printf("Malloc error!\n");
			return MALLOC_ERROR;
		}

		newPerson->next = personBeforeSurname->next;
		personBeforeSurname->next = newPerson;
	}
	else printf("\tPerson with surname '%s' was not found.\n", sur);
	
	return EXIT_SUCCESS;
}

int fileWrite(Position current)
{
	FILE* fp = NULL;
	fp = fopen("preson.txt", "w");

	if (fp == NULL) {
		printf("\nFile could not be opened.\n");
		return FILE_ERROR_OPEN;
	}

	while (current != NULL) {
		fprintf(fp, "%s %s %d\n", current->name, current->surname, current->bYear);
		current = current->next;
	}

	fclose(fp);

	printf("\tSuccess!\n");

	return EXIT_SUCCESS;
}

int _fileRead()
{
	char c = 0;
	FILE* fp = NULL;
	fp = fopen("persons.txt", "r");

	if (fp == NULL) {
		printf("File could not be opened.\n");
		return FILE_ERROR_OPEN;
	}

	c = getc(fp);
	while (c != EOF) {
		printf("%c", c);
		c = getc(fp);
	}
		
	fclose(fp);

	return EXIT_SUCCESS;
}

int fileRead(Position head)
{
	FILE* fp = NULL;
	fp = fopen("persons.txt", "r");

	if (!fp) {
		printf("File could not be opened.\n");
		return FILE_ERROR_OPEN;
	}


	Position prev = NULL, current = NULL;

	deleteList(head);
	prev = head;

	while (!feof(fp))
	{
		current = (Position)malloc(sizeof(Person));
		if (!current) {
			printf("Malloc error!\n");
			return MALLOC_ERROR;
		}
		if (fscanf(fp, " %s %s %d ", current->name, current->surname, &current->bYear) != 3)
			return SCANF_ERROR;

		
		current->next = prev->next;
		prev->next = current;

		prev = current;
	}

	fclose(fp);

	return EXIT_SUCCESS;
}