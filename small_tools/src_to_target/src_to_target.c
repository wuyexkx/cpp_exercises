#include <stdio.h>
#include <string.h>

#define MAX_COUNT_PER_LINE  (4096)

int main(int argc, char**argv)
{
    // 读写文件。如果文件不存在，则会创建一个新文件。读取会从文件的开头开始，写入则只能是追加模式。
    char target_format[4] = {"a+"};
    char source_format[4] = {"a+"};
    if(argc > 1){
        // 打印帮助信息
        if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0){
            printf("\n-------------- xxx.exe remove '\\n' from string ---------------\n");
            printf("'source.txt' same directory as 'xxx.exe', \n");
            printf("    auto generate no '\\n' files 'target.txt' same directory.\n");
            printf("    default append to new line to 'target.txt'.\n");
            printf("\n1. Parameter 'cls a' will clean 'target.txt' and 'source.txt':\n");
            printf("Ex: xxx.exe cls a\n");
            printf("\n2. Parameter 'cls s' will clean 'source.txt':\n");
            printf("Ex: xxx.exe cls s\n");
            printf("\n3. Parameter 'cls t' will clean 'target.txt':\n");
            printf("Ex: xxx.exe cls t\n");
            printf("---------------------------------------------------------------\n");
            getchar();
        }
        else if(strcmp(argv[1], "cls") == 0 && strcmp(argv[2], "s") == 0){
            FILE *f_read = fopen("./source.txt", "w");
            if(f_read == NULL){
                printf("fail to read './source.txt.'\n");
                return 0;
            }
            fclose(f_read);
        }
        else if(strcmp(argv[1], "cls") == 0 && strcmp(argv[2], "t") == 0){
            FILE *f_write = fopen("./target.txt", "w");
            if(f_write == NULL){
                printf("fail to read './target.txt.'\n");
                return 0;
            }
            fclose(f_write);
        }
        else if(strcmp(argv[1], "cls") == 0 && strcmp(argv[2], "a") == 0){
            FILE *f_read = fopen("./source.txt", "w");
            if(f_read == NULL){
                printf("fail to read './source.txt.'\n");
                return 0;
            }
            fclose(f_read);
            FILE *f_write = fopen("./target.txt", "w");
            if(f_write == NULL){
                printf("fail to read './target.txt.'\n");
                return 0;
            }
            fclose(f_write);
            return 0;
        }
        return 0;
    }
    

    // a 表示打开文件追加内容，无则创建
    FILE *f_read = fopen("./source.txt", source_format);
    if(f_read == NULL){
        printf("fail to read './source.txt.'\n");
        return 0;
    }
    // 允许读写，target文件，没有则自动创建，读从头开始，写则追加
    FILE *f_write = fopen("./target.txt", target_format); 
    if(f_write == NULL){
        printf("fail to write './target.txt.'\n");
        return 0;
    }    

    // 替换'\n'
    char buff[MAX_COUNT_PER_LINE];
    int line_length, num_line=0, flag=0;
    while(fgets(buff, MAX_COUNT_PER_LINE, f_read) != NULL){
        line_length = strlen(buff);

        // 存在单词 - 换行的情况
        if(((buff[line_length - 2] == '-') && buff[line_length - 1] == '\n')){
            buff[line_length - 2] = '\0';
            buff[line_length - 1] = '\0';
        }
        // 存在分段的情况 ".\n" 
        if(((buff[line_length - 2] == '.' || buff[line_length - 2] == ':') && 
             buff[line_length - 1] == '\n')){
            flag = 1;
        }
        // 替换掉末尾的'\n'
        if (buff[line_length - 1] == '\n'){
            buff[line_length - 1] = ' ';
        }
        // 段落换行
        fputs(buff, f_write);
        if(flag){
            fputs("\n", f_write);
            flag = 0;
        }
        
        ++num_line;
        printf("line:%d(%d char) %s\n", num_line, line_length-1, buff);
    }
    // 一次完成需要换行
    if(buff[0] != '\n')
        fputs("\n", f_write);

    fclose(f_read);
    fclose(f_write);

    return 0;
}