#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define ERROR_OF -1
#define BUFFER_SIZE 2048

position create_person(char* fname, char* lname, int birth_year);

int main() {

	person head = {.fname="", .lname="", .birth_year=0}
	return 0;
};

position create_person(char* fname, char* lname, int birth_year)
{
	position new_person = NULL;

	new_person = (position*)malloc(sizeof(person))
		if (!new_person) {
			printf("Malloc failed in function create_person");
			return NULL;
		}

	strcpy(new_person->fname, fname);
	strcpy(new_person->lname, lname);
	new_person->birth_year = birth_year;
	new_person->next = NULL;

	return new_person;
}

int prepend_list(position head, char* fname, char* lname, int birth_year)
{
	position new_person = NULL;

	new_person = create_person(fname, lname, birth_year);
	if (!new_person) {
		return -1;
	}
	new_person->next = head->next;
	head->next = new_person;

	return EXIT_SUCCESS;
}

int print_list(position first)
{
	position temp = first;
	while (temp) {
		printf("First name: %s\nLast name: %s\nBirth year: %i",temp->fname, temp->lname, temp->birth_year);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

position find_last(position head)
{
	position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;
}

int append_list(position head, char* fname, char* lname, int birth_year)
{
	position new_person = NULL, last = NULL;
	new_person = create_person(fname, lname, birth_year);
	if (!new_person) {
		return -1;
	}

	last = find_last(head);
	insert_after(last, new_person);

	return EXIT_SUCCESS;
}

position find_by_lname(position first, char* fname, char* lname, int birth_year)
{
	position temp = first;
	while (temp)
	{
		if (strcmp(temp->lname, lname) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

/*
toDelete=previous->next;
previous->next=toDelete->next;
free(toDelete);
*/