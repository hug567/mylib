#include <stdio.h>
#include <stdlib.h>

int countCharacters(char **words, int wordsSize, char *chars)
{
	int i = 0, j = 0;
	int len = 0;
	int char_tab[26] = {0};
	int temp_tab[26] = {0};
	int word_len[wordsSize];

	while (chars[i] != '\0') {
		char_tab[chars[i]-'a']++;
		i++;
	}

	for (i = 0; i < wordsSize; i++) {
		word_len[i] = 0;
		while (words[i][word_len[i]] != '\0') {
			word_len[i]++;
		}
	}

	for (i = 0; i < wordsSize; i++) {
		for (j = 0; j < 26; j++) {
			temp_tab[j] = char_tab[j];
		}
		j = 0;
		while (words[i][j] != '\0') {
			if (temp_tab[words[i][j] - 'a'] == 0) {
				break;
			}
			temp_tab[words[i][j] - 'a']--;
			j++;
		}
		if (word_len[i] == j) {
			len += word_len[i];
		}
	}

	return len;
}

int main(void)
{
	char *words[] = {"cat", "bt" ,"hat", "tree"};
	char * chars = "attach";

	printf("len = %d\n", countCharacters(words, 4, chars));
	return 0;
}
