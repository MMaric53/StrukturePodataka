#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define N 20
#define MAX_BUFFFER 1024
#define MAX_POINTS 100
#define EXIT_SUCCESS 0
#define FILE_ERROR_OPEN -1
#define MALLOC_ERROR -2
#define SCANF_ERROR -3

typedef struct _student {
	char name[N];
	char surname[N];
	double points;
} Student;

int RowNum()
{
	int c = 0;
	char buffer[MAX_BUFFFER] = { 0 };

	FILE* fp = NULL;
	fp = fopen("student.txt", "r");
	if (!fp) {
		printf("File not opened!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(fp)) {
		fgets(buffer, MAX_BUFFFER, fp);
		c++;
	}

	fclose(fp);

	return c;
}

int main()
{
	int i = 0, rc = 0;
	rc = RowNum();

	if (rc > 0)
	{
		FILE* fp = NULL;
		fp = fopen("student.txt", "r");
		if (!fp) {
			printf("File not opened!\n");
			return FILE_ERROR_OPEN;
		}

		Student* o = NULL;
		o = (Student*)malloc(rc * sizeof(Student));
		if (o == NULL) {
			printf("Malloc error!\n");
			return MALLOC_ERROR;
		}

		for (i = 0; i < rc; i++) {
			if (fscanf(fp, " %s %s %lf ", o[i].name, o[i].surname, &o[i].points) != 3)
				return SCANF_ERROR;
		}

		for (i = 0; i < rc; i++) {
			printf("%s %s %d %.2lf \n", o[i].name, o[i].surname, (int)o[i].points, o[i].points / MAX_POINTS * 100);
		}

		fclose(fp);
		free(o);
	}

	return EXIT_SUCCESS;
}