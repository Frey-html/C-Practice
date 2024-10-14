#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MaxWordsInFile 1000
#define MaxLengthofWord 20

typedef struct WordCDT * Word;
struct WordCDT{
    int times;
    char word[MaxLengthofWord];
};

typedef struct DocumentCDT * Document;
struct DocumentCDT{
    char id[10];
    Word content[MaxWordsInFile];
    int numofwords;
};

Document NewDoc(char * filename){
    Document doc = (Document)malloc(sizeof(struct DocumentCDT));
    doc->numofwords = 0;
    strcpy(doc->id, filename);
    return doc;
}

Word NewWord(char * word){
    Word newword = (Word)malloc(sizeof(struct WordCDT));
    newword->times = 1;
    strcpy(newword->word, word);
    return newword;
}

int Find(Document doc, char * newword){
    for(int i = 0;i < doc->numofwords;i++){
        if(strcmp(doc->content[i]->word, newword) == 0){
            doc->content[i]->times++;
            return 1;
        }
    }
    doc->content[doc->numofwords++] = NewWord(newword);
}

double Product(Document a, Document b){
    double result = 0;
    for(int i = 0;i < a->numofwords;i++){
        for(int j = 0;j < b->numofwords;j++){
            if(strcmp(a->content[i]->word, b->content[j]->word) == 0)
                result += a->content[i]->times * b->content[j]->times;
        }
    }
    return result;
}

double Distance(Document a, Document b){
    double result;
    result = Product(a, b)/(sqrt(Product(a, a))*sqrt(Product(b, b)));
    return result;
}

//bounus
void Stem(char * word){
    int length = strlen(word);
    for(int i = 0;i < length;i++){
        word[i] += 32;
    }
    if(strcmp(word+length-3, "ing") == 0) word[length - 3] = 0;
    else if(strcmp(word+length-3, "ies") == 0) word[length - 3] = 0;
    else if(strcmp(word+length-2, "es") == 0) word[length - 2] = 0;
    else if(strcmp(word+length-2, "ed") == 0) word[length - 2] = 0;

    return;
} 

int main(){
    int n;
    scanf("%d", &n);
    Document files[100];
    char word[MaxLengthofWord];
    int i = 0;
    while(i < n){
        //read in a new file
        scanf("%s", word);
        files[i] = NewDoc(word);
        
        //read in words
        scanf("%s", word);
        while(word[0] != '#'){
            Stem(word);
            Find(files[i], word);
            scanf("%s", word);
        }
        i++;
    }
    
    int querytimes;
    scanf("%d", &querytimes);
    char file1[10], file2[10];
    int index1, index2;
    
    for(int i = 0;i < querytimes;i++){
        scanf("%s %s", file1, file2);
        //find the index of file1 and file 2 in files
        for(int i = 0;i < n;i++){
            if(strcmp(file1, files[i]->id) == 0){
                index1 = i;
                break;
            }
        }
        for(int i = 0;i < n;i++){
            if(strcmp(file2, files[i]->id) == 0){
                index2 = i;
                break;
            }
        }
        printf("Case %d: %.3f\n", i+1, acos(Distance(files[index1], files[index2])) );
    }
    
}