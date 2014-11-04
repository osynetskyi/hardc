#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *filename = "out.txt";
	FILE *conn = fopen(filename, "r+");
	int n = 19;
	char p = 'c';
	long double m = 12.09;
	int k = 0;
	char p1 = '\0';
	long double m1 = 0.0;
	fwrite(&n, sizeof(int), 1, conn);
	fwrite(&p, sizeof(char), 1, conn);
	fwrite(&m, sizeof(long double), 1, conn);
	rewind(conn);
	/*fclose(conn);
	conn = fopen(filename, "r");*/
	fread(&k, sizeof(int), 1, conn);
	fread(&p1, sizeof(char), 1, conn);
	fread(&m1, sizeof(long double), 1, conn);
	printf("k: %d\np: %c\nm: %llf\n", k, p1, m1);
	fclose(conn);

	return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fp;
  double d = 12.23;
  int i = 101;
  long l = 123023L;

  if((fp=fopen("test", "wb+"))==NULL) {
    printf("Ошибка при открытии файла.\n");
    exit(1);
  }

  fwrite(&d, sizeof(double), 1, fp);
  fwrite(&i, sizeof(int), 1, fp);
  fwrite(&l, sizeof(long), 1, fp);

  rewind(fp);

  fread(&d, sizeof(double), 1, fp);
  fread(&i, sizeof(int), 1, fp);
  fread(&l, sizeof(long), 1, fp);

  printf("%f %d %ld", d, i, l);

  fclose(fp);

  return 0;
}
*/
