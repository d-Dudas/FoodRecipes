#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


typedef struct node{
    char titlu[100], descriere[1000], ingrediente[1000];
    struct node* next;
    int poz;
} node;

typedef struct list{
    struct node* head;
    struct node* last;
}list;

void set_color(int color_code) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}

void citire_fisier(list *l){
    FILE * fr;
    node *n;
    node *aux;
    char t[100], d[1000], i[1000];
    n = malloc(sizeof(node));
    aux = malloc(sizeof(node));
    int nr_retete;
    fr = fopen("retete.txt", "r");
    fscanf(fr, "%d", &nr_retete);
    fgets(t, 100, fr);
    for(int j = 1; j <= nr_retete; j++){
        fgets(t, 100, fr);
        fgets(d, 1000, fr);
        fgets(i, 1000, fr);
        if(l->head == NULL){
            l->head = malloc(sizeof(node));
            strcpy(l->head->titlu, t);
            strcpy(l->head->descriere, d);
            strcpy(l->head->ingrediente, i);
            l->head->poz = 1;
            l->head->next = NULL;
            l->last = l->head;
        }
        else{
            node *n;
            n = malloc(sizeof(node));
            strcpy(n->titlu, t);
            strcpy(n->descriere, d);
            strcpy(n->ingrediente, i);
            n->poz = l->last->poz + 1;
            l->last->next = n;
            n->next = NULL;
            l->last = n;
        }
    }
    fclose(fr);
}

void retete_de_baza(list *l){
    node *n;
    n = malloc(sizeof(node));
    strcpy(n->titlu, "Salata de oua cu avocado\n");
    strcpy(n->descriere, "Salata de oua cu avocado este foarte gustoasa si la indemana oricui, se pregateste repede si este potrivit atat pentru micul dejun cat si ca aperitiv. Mie mi-a placut foarte mult cu paine prajita, ceea ce va recomand si voua.\n");
    strcpy(n->ingrediente, "2 avocado, 2 oua fierte tari, 1 ceapa rosie mica, 100 ml iaurt grecesc, 1 lingura zeama lamaie, 1 lingura mustar, sare dupa gust\n");
    n->poz = 1;
    l->head = n;
    l->head->next = NULL;
    l->last = l->head;
    node *n2;
    n2 = malloc(sizeof(node));
    strcpy(n2->titlu, "Pasta de jumari\n");
    strcpy(n2->descriere, "Pentru ca in zona noastra nu se obisnuieste, sau cel putin nu auzisem eu, abia acum cativa ani am mancat pentru prima data pasta de jumari, la Brasov, la Bistro Del'Arte, si efectiv mi s-a parut fenomenala. Este incredibil cum dintr-un preparat atat de simplu, cum sunt jumarile, putem obtine ceva atat de minunat.  Senzationala pasta de jumari, cu un gust intens, usor picant, musai de servit cu paine proaspata de casa, si musai cu ceva tarie alaturi.\n");
    strcpy(n2->ingrediente, "500 g jumari, 2 linguri mustar picant, 1 ceapa rosie, 2 catei usturoi, sare, piper\n");
    n2->poz = 2;
    l->last->next = n2;
    n2->next = NULL;
    l->last = n2;
    node *n3;
    n3 = malloc(sizeof(node));
    strcpy(n3->titlu, "Quesadilla cu pui\n");
    strcpy(n3->descriere, "Quesadilla cu pui este o reteta mexicana de tip fast food, foaie de tortilla umpluta cu branzeturi, uneori carne condimente si in general  insotita de diverse sosuri. De regula mancarurile mexicane sunt foarte condimentate, de data asta insa eu am ales sa pregatesc o varianta mai prietenoasa, pe langa faptul ca nu este picanta am facut-o pe grill, iar ardeii i-am pus cruzi, fara sa ii gatesc in prealabil.\n");
    strcpy(n3->ingrediente, "4 foi tortilla, 500 gr piept pui, 2 ardei colorati, 4-5 fire ceapa verde, 200 gr cascaval, sare, piper\n");
    n3->poz = 3;
    l->last->next = n3;
    n3->next = NULL;
    l->last = n3;
}

void add_to_list(list *l){
    char t[100], d[1000], i[1000];
    set_color(6);
    printf("Titlu: ");
    set_color(7);
    fgets(t, sizeof(t), stdin);
    set_color(6);
    printf("Descriere: ");
    set_color(7);
    fgets(d, sizeof(d), stdin);
    set_color(6);
    printf("Ingrediente: ");
    set_color(7);
    fgets(i, sizeof(i), stdin);
    if(l->head == NULL){
        l->head = malloc(sizeof(node));
        strcpy(l->head->titlu, t);
        strcpy(l->head->descriere, d);
        strcpy(l->head->ingrediente, i);
        l->head->poz = 1;
        l->head->next = NULL;
        l->last = l->head;
    }
    else{
        node *n;
        n = malloc(sizeof(node));
        strcpy(n->titlu, t);
        strcpy(n->descriere, d);
        strcpy(n->ingrediente, i);
        n->poz = l->last->poz + 1;
        l->last->next = n;
        n->next = NULL;
        l->last = n;
    }
}

void print_list(list l){
    node *aux;
    aux = l.head;
    while(aux != NULL){
        printf("%s\n", aux->titlu);
        aux = aux->next;
    }
}

void search(list l){
    char ts[50], res = NULL;
    set_color(6);
    printf("Search: ");
    set_color(7);
    scanf("%s", &ts);
    node *aux;
    aux = l.head;
    while(aux != NULL){
        res = strstr(aux->titlu, ts);
        if(res != NULL){
            set_color(6);
            printf("(%d) ", aux->poz);
            set_color(7);
            printf("%s", aux->titlu);
        }
        aux = aux->next;
    }
    set_color(6);
    printf("Select a number: ");
    set_color(7);
    int nr_nod_cautat = 0;
    scanf("%d", &nr_nod_cautat);

    find_and_print_node(nr_nod_cautat, l);

    return 0;
}

void print_node(node *n){
    //printf("==============\nTitlu: %s\nDescriere: %s\nIngrediente: %s\n===============\n", n->titlu, n->descriere, n->ingrediente);
    set_color(6);
    printf("================\n");
    printf("Titlu: ");
    set_color(7);
    printf("%s\n", n->titlu);
    set_color(6);
    printf("Descriere: ");
    set_color(7);
    printf("%s\n", n->descriere);
    set_color(6);
    printf("Ingrediente: ");
    set_color(7);
    printf("%s\n", n->ingrediente);
    set_color(6);
    printf("================\n");
    int exit;
    set_color(12);
    printf("Press (c) to continue: ");
    set_color(7);
    scanf("%d", exit);
}

void find_and_print_node(int x, list l){
    node *aux;
    aux = malloc(sizeof(node));
    aux = l.head;
    while(aux != NULL){
        if((int)aux->poz == x){
            system("cls");
            print_node(aux);
            aux = l.last;
        }
        aux = aux->next;
    }
}

void delete_node(int delete_node_poz, list *l){
    node *aux_delete;
    node *free_this;
    int k = 0;
    free_this = malloc(sizeof(node));
    aux_delete = malloc(sizeof(node));
    aux_delete = l->head;
    if(aux_delete->next == NULL && delete_node_poz == 1){
        l->head = NULL;
        free(aux_delete);
        k = 1;
    }
    else
    if(aux_delete->poz == delete_node_poz){
        l->head = aux_delete->next;
        free(aux_delete);
    }
    else{
        while(aux_delete->next->poz != delete_node_poz) aux_delete = aux_delete->next;
        free_this = aux_delete->next;
        aux_delete->next = aux_delete->next->next;
        free(free_this);
    }
    if(k!=1){
    aux_delete = l->head;
    aux_delete->poz = 1;
    while(aux_delete->next != NULL){
        aux_delete->next->poz = aux_delete->poz + 1;
        aux_delete = aux_delete->next;
        l->last = aux_delete;
    }
    }
}

void edit_node(int edit_node_poz, list *l){
    char titlu_edit[100], di_edit[1000];
    node *aux_edit;
    aux_edit = malloc(sizeof(node));
    aux_edit = l->head;
    while(aux_edit->poz != edit_node_poz) aux_edit = aux_edit->next;
    char exit_edit = ' ', choose_edit = ' ';
    while(exit_edit != 'e'){
        choose_edit = ' ';
        system("cls");
        //printf("==============\nTitlu: %s\nDescriere: %s\nIngrediente: %s\n===============\n", aux_edit->titlu, aux_edit->descriere, aux_edit->ingrediente);
        printf("Titlu: ");
        set_color(7);
        printf("%s\n", aux_edit->titlu);
        set_color(6);
        printf("Descriere: ");
        set_color(7);
        printf("%s\n", aux_edit->descriere);
        set_color(6);
        printf("Ingrediente: ");
        set_color(7);
        printf("%s\n", aux_edit->ingrediente);
        set_color(6);
        //printf("Edit this:\n(t) Titlu\n(d) Descriere\n(i) Ingrediente\n(e) Exit edit\nInput:");
        printf("Edit this:\n");
        set_color(10);
        printf("(t) ");
        set_color(7);
        printf("Titlu\n");
        set_color(10);
        printf("(d) ");
        set_color(7);
        printf("Descriere\n");
        set_color(10);
        printf("(i) ");
        set_color(7);
        printf("Ingrediente\n");
        set_color(4);
        printf("(e) ");
        set_color(12);
        printf("Exit edit\n");
        set_color(6);
        printf("Input: ");
        set_color(7);
        scanf("%c", &choose_edit);
        exit_edit = choose_edit;
        switch(choose_edit){
            case 't':
                set_color(6);
                printf("Noul titlu: ");
                set_color(7);
                gets(titlu_edit);
                gets(titlu_edit);
                strncat(titlu_edit, "\n", 1);
                strcpy(aux_edit->titlu, titlu_edit);
                break;
            case 'd':
                set_color(6);
                printf("Noua descriere: ");
                set_color(7);
                gets(di_edit);
                gets(di_edit);
                strncat(di_edit, "\n", 1);
                strcpy(aux_edit->descriere, di_edit);
                break;
            case 'i':
                set_color(6);
                printf("Lista noua de ingrediente: ");
                set_color(7);
                gets(di_edit);
                gets(di_edit);
                strncat(di_edit, "\n", 1);
                strcpy(aux_edit->ingrediente, di_edit);
                break;
        }

    }
}

void salvare_fisier(list *l){
    FILE * fp;
    fp = fopen("retete.txt", "w");
    int nr_retete_out = l->last->poz;
    fprintf(fp, "%d", nr_retete_out);
    fputs("\n", fp);
    node * aux;
    aux = l->head;
    while(aux != NULL){
        fputs(aux->titlu, fp);
        fputs(aux->descriere, fp);
        fputs(aux->ingrediente, fp);
        aux = aux->next;
    }
    fclose(fp);
}

list l;

int main(){
    list *head = NULL;
    //retete_de_baza(&l);
    citire_fisier(&l);
    int show_list = 0;
    while(1){
        set_color(6);
        printf("=========================================\n");
        set_color(7);
        printf("Choose the character in parentheses\n");
        set_color(6);
        printf("=========================================\n");
        set_color(10);
        printf("(s) ");
        set_color(7);
        printf("Search\n");
        set_color(10);
        printf("(a) ");
        set_color(7);
        printf("Add\n");
        set_color(10);
        printf("(d) ");
        set_color(7);
        printf("Delete\n");
        set_color(10);
        printf("(e) ");
        set_color(7);
        printf("Edit node\n");
        set_color(10);
        printf("(l) ");
        set_color(7);
        if(show_list == 0) printf("Show list\n");
        else printf("Hide list\n");
        if(show_list == 1){
        node *aux;
        aux = l.head;
        set_color(6);
        if(aux != NULL) printf("\nRetetele culinare:\n\n");
        while(aux != NULL){
            set_color(10);
            printf("(%d) ", aux->poz);
            set_color(7);
            printf("%s",aux->titlu);
            aux = aux->next;
        }
        }
        set_color(6);
        printf("\n=========================================\n");
        set_color(7);
        char selected[3];
        printf("Your choice:");
        set_color(10);
        fgets(selected, sizeof(selected), stdin);
        set_color(7);
        selected[strcspn(selected, "\n")] = NULL;
        if(strcmp("d", selected) == 0){
            int node_poz;
            printf("Delete this node: ");
            scanf("%d", &node_poz);
            delete_node(node_poz, &l);

        }
        else
        if(strcmp("s", selected) == 0) search(l);
        else
        if(strcmp("l", selected) == 0) if(show_list == 1) show_list = 0; else show_list = 1;
        if(strcmp("e", selected) == 0) {
            printf("Edit this node:");
            int enp;
            scanf("%d", &enp);
            edit_node(enp, &l);
        }
        else
            if(strcmp("a", selected) == 0) add_to_list(&l);
            else{
                int selected_int;
                sscanf(selected, "%d", &selected_int);
                find_and_print_node(selected_int, l);
                selected_int = 0;
            }
        strcpy(selected, "x");

        system("cls");
        salvare_fisier(&l);
    }
}
