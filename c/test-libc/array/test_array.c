



static int test_array_increment(void)
{
    int i;
    int array[10];

    for (i = 0; i < 10; i++) {
        array[i] = i;
        array[i]++;
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

int main(void)
{
    return 0;
}
