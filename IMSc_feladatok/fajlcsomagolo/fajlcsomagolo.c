#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned size; //4 byte
    char name[256];
} FileEntry;

typedef struct {
    unsigned short file_count; //2 byte
    FileEntry *entries;
} Catalog;

void print_usage()
{
    printf("usage: program command\n");
    printf("commands:\n");
    printf("    pack <packed_file> <file_1> [<file_2> ...] Pack file_1, file_2, etc. into packed_file\n");
    printf("    list <packed_file> List the packed files in the archive\n");
    printf("    unpack <packed_file> <file_1> [<file_2> ...] Unpack the selected files\n");
    printf("    unpack <packed_file> Unpack all files\n");
}

long get_file_size(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);
    return size;
}

void pack_files(char *packed_file, int file_count, char *file_names[])
{
    FILE *output = fopen(packed_file, "wb");
    if (!output)
        return;

    Catalog catalog;
    catalog.file_count = file_count;
    if (file_count == 0)
    {
        fclose(output);
        return;
    }

    catalog.entries = malloc(file_count * sizeof(FileEntry));
    if (catalog.entries == NULL)
    {
        fclose(output);
        return;
    }

    fwrite(&catalog.file_count, sizeof(catalog.file_count), 1, output);

    for (int i = 0; i < file_count; i++)
    {
        FILE *input = fopen(file_names[i], "rb");
        if (!input)
            continue;
        
        catalog.entries[i].size = get_file_size(input);
        strncpy(catalog.entries[i].name, file_names[i], sizeof(catalog.entries[i].name));
        catalog.entries[i].name[sizeof(catalog.entries[i].name) - 1] = '\0';

        fwrite(&catalog.entries[i].size, sizeof(catalog.entries[i].size), 1, output);
        fwrite(catalog.entries[i].name, strlen(catalog.entries[i].name) + 1, 1, output);

        fclose(input);
    }

    for (int i = 0; i < file_count; i++)
    {
        FILE *input = fopen(file_names[i], "rb");
        if (!input)
            continue;
        
        char *buffer = malloc(catalog.entries[i].size);
        fread(buffer, 1, catalog.entries[i].size, input);
        fwrite(buffer, 1, catalog.entries[i].size, output);

        free(buffer);
        fclose(input);
    }

    free(catalog.entries);
    fclose(output);
    return;
}

void list_files(char *packed_file)
{
    FILE *input = fopen(packed_file, "rb");
    if (!input)
        return;
    
    Catalog catalog;
    fread(&catalog.file_count, sizeof(catalog.file_count), 1, input);
    catalog.entries = malloc(catalog.file_count * sizeof(FileEntry));

    for (int i = 0; i < catalog.file_count; i++)
    {
        fread(&catalog.entries[i].size, sizeof(catalog.entries[i].size), 1, input);
        int j = 0;
        while (j < 256)
        {
            fread(&catalog.entries[i].name[j], 1, 1, input);
            if (catalog.entries[i].name[j] == '\0')
                break;
            j++;
        }

        char *unit;
        double size = catalog.entries[i].size;
        if (size >= (1 << 30))
        {
            unit = "GiB";
            size /= (1 << 30);
        } 
        else if (size >= (1 << 20))
        {
            unit = "MiB";
            size /= (1 << 20);
        }
        else if (size >= (1 << 10))
        {
            unit = "KiB";
            size /= (1 << 10);
        }
        else
        {
            unit = "B";
        }

        printf("%s (%.0f %s)\n", catalog.entries[i].name, size, unit);
    }
    
    free(catalog.entries);
    fclose(input);
    return;
}

void unpack_files(char *packed_file, int file_count, char *file_names[])
{
    FILE *input = fopen(packed_file, "rb");
    if (!input)
        return;
    
    Catalog catalog;
    fread(&catalog.file_count, sizeof(catalog.file_count), 1, input);
    catalog.entries = malloc(catalog.file_count * sizeof(FileEntry));

    for (int i = 0; i < catalog.file_count; i++)
    {
        fread(&catalog.entries[i].size, sizeof(catalog.entries[i].size), 1, input);
        int j = 0;
        while (j < 256)
        {
            fread(&catalog.entries[i].name[j], 1, 1, input);
            if (catalog.entries[i].name[j] == '\0')
                break;
            j++;
        }
    }

    int *unpacked = calloc(catalog.file_count, sizeof(int));

    for (int i = 0; i < catalog.file_count; i++)
    {
        int unpack = (file_count == 0);
        for (int j = 0; j < file_count; j++)
            if (strcmp(catalog.entries[i].name, file_names[j]) == 0)
            {
                unpack = 1;
                break;
            }
        
        if (unpack == 1)
        {
            FILE *output = fopen(catalog.entries[i].name, "wb");
            if (!output)
                continue;
            
            char *buffer = malloc(catalog.entries[i].size);
            fread(buffer, 1, catalog.entries[i].size, input);
            fwrite(buffer, 1, catalog.entries[i].size, output);

            free(buffer);
            fclose(output);
            unpacked[i] = 1;   
        }
        else
        {
            fseek(input, catalog.entries[i].size, SEEK_CUR);
        }
    }

    for (int i = 0; i < file_count; i++)
    {
        int found = 0;
        for (int j = 0; j < catalog.file_count; j++) {
            if (strcmp(file_names[i], catalog.entries[j].name) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
            printf("Unable to unpack %s\n", file_names[i]);
    }

    free(catalog.entries);
    fclose(input);
    return;
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage();
        return 1;
    }

    if (strcmp(argv[1], "pack") == 0)
    {
        if (argc < 4)
        {
            print_usage();
            return 1;
        }
        pack_files(argv[2], argc - 3, &argv[3]);
    }
    else if (strcmp(argv[1], "list") == 0)
    {
        if (argc != 3)
        {
            print_usage();
            return 1;
        }
        list_files(argv[2]);
    }
    else if (strcmp(argv[1], "unpack") == 0)
    {
        if (argc < 3)
        {
            print_usage();
            return 1;
        }
        unpack_files(argv[2], argc - 3, &argv[3]);
    }
    else
    {
        print_usage();
        return 1;
    }

    return 0;
}



/*
int main()
{
    //pack_files("tesztpak.packed", 2, (char *[]){"test1.txt", "test2.txt"});
    //list_files("tesztpak.packed");
    //unpack_files("test.packed", 1, (char *[]){"test2.txt"});
    return 0;
}
*/