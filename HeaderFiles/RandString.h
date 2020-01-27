char *rand_string(size_t size)
{
    // reserves a place for NULL
    char *str = malloc((size + 1) * sizeof(char));
    const char charset[] =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < size; i++)
    {
        int key = rand() % (sizeof(charset) / sizeof(char) - 1);
        str[i] = charset[key];
    }
    str[size] = '\0';
    return str;
}
