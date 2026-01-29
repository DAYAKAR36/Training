#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GET_TOKEN strtok(NULL, "{}\"[]");

void main()
{
    char word[50], buffer[2000], command[200], meaning[1000], audio[200];
    int audio_found = 0;
    while (1)
    {
        printf(">> ");
        scanf("%s", word);
        if (strchr(word, '.') != NULL)
        {
            return;
        }
        sprintf(command, "curl -s \"https://api.dictionaryapi.dev/api/v2/entries/en/%s\"", word);
        FILE *fp_meaning = popen(command, "r");
        fread(buffer, sizeof(buffer), 1, fp_meaning);
        pclose(fp_meaning);
        char *token = strtok(buffer, "{}\"[]");
        while (token != NULL)
        {
            if (strcmp(token, "audio") == 0)
            {
                GET_TOKEN;
                token = GET_TOKEN;
                strcpy(audio, token);
            }
            if (strcmp(token, "definition") == 0)
            {
                GET_TOKEN;
                token = GET_TOKEN;
                strcpy(meaning, token);
                break;
            }
            token = GET_TOKEN;
        }
        if (strlen(audio) > 0)
        {
            sprintf(command, "vlc --intf dummy --play-and-exit \"%s\"", audio);
            system(command);
        }
        printf("Definition of %s: %s.\n", word, meaning);
    }
}
