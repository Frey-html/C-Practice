#include <stdio.h>
#include "skiplist.h"

void showInfo(void);

int main(){
    //show information of operate method
    showInfo();
    //create skiplist
    SkipList *list = createList();
    char command;
    int key;
    double value;
    Node *node;
    int judge;
    //command
    while(1){
        //read in command
        scanf("%c", &command);
        switch (command){
            //insert
            case 'i':;case 'I':
                scanf("%d %lf", &key, &value);
                judge = insertKey(list, key, value);
                if(judge == 1) printf("insert success\n");
                else printf("insert failed\n");
            break;
            //delete
            case 'd':;case 'D':
                scanf("%d", &key);
                judge = deleteKey(list, key);
                if(judge == 1) printf("delete success\n");
                else printf("delete failed\n");
            break;
            //search
            case 's':;case 'S':
                scanf("%d", &key);
                node = search(list, key);
                if(node == NULL) printf("can't find key %d in skiplist\n", key);
                else printf("value is %.3lf\n", node->value);
            break;
            //print skiplist
            case 'p':;case 'P':
                printList(list);
            break;
            //show information
            case 'h':;case 'H':
                showInfo();
            break;
            //quit
            case 'q':;case 'Q':
                return 0;
            break;
            default:break;
        }
    }
    return 0;
}

void showInfo(void){
    printf("This is a test program for skiplist\n"
            "----------------------------------------\n"
            "I:insert D:delete S:search\n"
            "----------------------------------------\n"
            "P:print skiplist Q:quit  H:help\n"
            "----------------------------------------\n"
            "example:i 1 2.0 insert a node whose key is 1 and value is 2.0\n");
}