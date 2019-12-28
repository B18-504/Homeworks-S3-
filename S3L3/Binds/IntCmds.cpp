void InputInt(void ***argv)
{
    Input(*(int*)argv[0]);
}

void PrintInt(void ***argv)
{
    printf("%d\n", *(int*)argv[0]);
}

void FPrintInt(void ***argv)
{
    fprintf((FILE*)(*(argv[1])), "%d\n", *(int*)argv[0]);
}