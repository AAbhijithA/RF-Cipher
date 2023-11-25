#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DynamicString{
    int Cindex;
    char Carray[];
};

void Encrypt(){
    int n, levels, itr = 0, mov = 1;
    printf("Enter the size of transfer content you want to write: ");
    scanf("%d",&n);
    char transferText[n], cbuf;
    printf("Enter your text to transfer: ");
    scanf("%c",&cbuf);
    scanf("%[^\n]",transferText);
    printf("Enter the number of levels in the algorithm: ");
    scanf("%d",&levels);
    int LevelAccomodation[levels];
    for(int i=0;i<levels;i++) LevelAccomodation[i] = 0;
    for(int i=0;i<n;i++){
            LevelAccomodation[itr] += 1;
            if(mov == 1){
                if(itr == levels - 1){
                    itr--;
                    mov = 0;
                }
                else itr++;
            }
            else{
                if(itr == 0){
                    itr++;
                    mov = 1;
                }
                else itr--;
            }
    }
    struct DynamicString *RailwayFence[levels];
    for(int i=0;i<levels;i++){
            RailwayFence[i] = (struct DynamicString *)malloc(sizeof(struct DynamicString) + (LevelAccomodation[i]*sizeof(char)));
            RailwayFence[i]->Cindex = 0;
    }
    itr = 0;
    for(int i=0;i<n;i++){
            RailwayFence[itr]->Carray[RailwayFence[itr]->Cindex] = transferText[i];
            RailwayFence[itr]->Cindex += 1;
            if(mov == 1){
                if(itr == levels - 1){
                    itr--;
                    mov = 0;
                }
                else itr++;
            }
            else{
                if(itr == 0){
                    itr++;
                    mov = 1;
                }
                else itr--;
            }
    }
    printf("Encrypted Text is: ");
    char encryptedText[n];
    itr = 0;
    for(int i=0;i<levels;i++){
            for(int j=0;j<RailwayFence[i]->Cindex;j++){
                    encryptedText[itr] = RailwayFence[i]->Carray[j];
                    itr++;
            }
    }
    printf("%s",encryptedText);
    remove("encrypted.txt");
    FILE *fp = fopen("encrypted.txt","w");
    if(fp == NULL){
            printf("\nFile could not be opened program terminates...");
            return;
    }
    for(int i=0;i<n;i++) fputc(encryptedText[i],fp);
    fclose(fp);
    return;
}

void Decrypt(){
    int n = 0, itr = 0, mov = 1, Ti = 0;
    FILE *fp = fopen("encrypted.txt","r");
    if(fp == NULL){
        printf("File does not exist");
        return;
    }
    while(1){
            char c = fgetc(fp);
            if(feof(fp)) break;
            n++;
    }
    fclose(fp);
    char encryptedText[n];
    fp = fopen("encrypted.txt","r");
    while(1){
            char c = fgetc(fp);
            if(feof(fp)) break;
            encryptedText[itr] = c;
            itr++;
    }
    printf("Encrypted text is: %s\n",encryptedText);
    printf("Enter correct key to decrypt: ");
    int levels;
    scanf("%d",&levels);
    int LevelAccomodation[levels];
    itr = 0;
    for(int i=0;i<levels;i++) LevelAccomodation[i] = 0;
    for(int i=0;i<n;i++){
            LevelAccomodation[itr] += 1;
            if(mov == 1){
                if(itr == levels - 1){
                    itr--;
                    mov = 0;
                }
                else itr++;
            }
            else{
                if(itr == 0){
                    itr++;
                    mov = 1;
                }
                else itr--;
            }
    }
    struct DynamicString *RFDecrypt[levels];
    for(int i=0;i<levels;i++){
            RFDecrypt[i] = (struct DynamicString *)malloc(sizeof(struct DynamicString) + (LevelAccomodation[i]*sizeof(char)));
            RFDecrypt[i]->Cindex = 0;
    }
    itr = 0;
    while(Ti < n){
            while(RFDecrypt[itr]->Cindex < LevelAccomodation[itr]){
                    RFDecrypt[itr]->Carray[RFDecrypt[itr]->Cindex] = encryptedText[Ti];
                    RFDecrypt[itr]->Cindex += 1;
                    Ti += 1;
            }
            itr += 1;
    }
    char decryptedText[n];
    itr = 0;
    mov = 1;
    for(int i=0;i<levels;i++) RFDecrypt[i]->Cindex = 0;
    for(int i=0;i<n;i++){
            decryptedText[i] = RFDecrypt[itr]->Carray[RFDecrypt[itr]->Cindex];
            RFDecrypt[itr]->Cindex += 1;
            if(mov == 1){
                if(itr == levels - 1){
                    itr--;
                    mov = 0;
                }
                else itr++;
            }
            else{
                if(itr == 0){
                    itr++;
                    mov = 1;
                }
                else itr--;
            }
    }
    printf("Decrypted Text is: %s",decryptedText);
}

int main(){
    int choice;
    while(1){
            printf("\n--------------------------------------------------\n");
            printf("\nEnter 1 to Encrypt, 2 to Decrypt, 3 to Exit: ");
            scanf("%d",&choice);
            if( choice < 1 || choice > 3) printf("Invalid choice try again\n");
            if(choice == 1) Encrypt();
            else if(choice == 2) Decrypt();
            else if(choice == 3) break;
            printf("\n--------------------------------------------------\n");
    }
    printf("\n--------------------------------------------------\n");
    return 0;

}
