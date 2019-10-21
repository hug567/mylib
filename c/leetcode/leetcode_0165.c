/* leetcode 165: 比较版本号 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareVersion(char *version1, char *version2)
{
	int i = 0, j = 0;
	int num1 = 0, num2 = 0;

	while (i < strlen(version1) || j < strlen(version2)) {
		num1 = 0; num2 = 0;
		while (i < strlen(version1) && version1[i] != '.') {
			num1 = 10 * num1 + version1[i] - '0';
			i++;
		}
		while (j < strlen(version2) && version2[j] != '.') {
			num2 = 10 * num2 + version2[j] - '0';
			j++;
		}
		if (num1 > num2) {
			return 1;
		} else if (num1 < num2) {
			return -1;
		}
		i++;
		j++;
	}

	return 0;
}

int main()
{
	char *version1 = "1.1.23.456.789.8";
	char *version2 = "1.1.23.456.789.01";
	printf("result = %d\n", compareVersion(version1, version2));
	return 0;
}
