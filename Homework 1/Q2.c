#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int  picture[n][n];
    int case_;
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int num;
            scanf("%d",&picture[i][j]);
     //       picture[i][j]=num;
            if(picture[i][j]==0){
                if(i==0 && j==0){
                    case_=0;
                }   
                else if(i==0){
                    case_=1;
                }
                else if(j==0){
                    case_=3;
                }
                else{
                    case_=2;
                }
            }
        }
    }
    if(case_==0){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                printf("%d ",picture[i][j]);
            }
            printf("\n");
        }
    }
    else if(case_==1){
        for(int i=n-1;i>=0;i--){
            for(int j=0;j<n;j++){
                printf("%d ",picture[j][i]);
            }
            printf("\n");
        }
    }
    else if(case_==2){
        for(int i=n-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                printf("%d ",picture[i][j]);
            }
            printf("\n");
        }
    }
    else{
        for(int i=0;i<n;i++){
            for(int j=n-1;j>=0;j--){
                printf("%d ",picture[j][i]);
            }
            printf("\n");
        }
    }

    return 0;
}