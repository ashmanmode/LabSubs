#include <stdio.h>
#include <stdlib.h>
int RowEvaluation(char a,char b,char c, char y);
int CalculateBoardValue(char d[3][3]);
void GetBestPosition();
int CheckWin(char d[3][3]);
int Evaluation(char a,char b,char c);
int GetBest(char a,int y);
int Get4Worst();
int Get3Best();
int Get2Worst();
int Get1Best();
void GameTTT();
void ContinueTTT();
void PrintGameGrid();
int UserChanceToWin();
int TriodCheck(char a,char b, char c);
void GameOver();

char e[3][3];
int best1,worst2,best3,worst4,init4,init3,init2,init1,pos_best;// global variables are declared

int main(){
    int i=0,j=0,x;
    GameTTT();
}


int Get4Worst(){              ///find the worst of the fourth layer
    int i,j,tempworst,pos_worst;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(e[i][j]==' '){
                if(init4==1){
                    e[i][j]='o';
                    tempworst=CalculateBoardValue(e);
                    worst4=tempworst;
                    init4=0;
                    e[i][j]=' ';
                }else{
                    e[i][j]='o';
                    tempworst=CalculateBoardValue(e);
                    if(tempworst<worst4){
                        worst4=tempworst;
                    }
                    e[i][j]=' ';
                }
            }
          }
        }
            return worst4;
}

int Get3Best(){               ///find the best in the third layer from values calculated in fourth layer
    int i,j,tempbest,pos_best;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(e[i][j]==' '){
                if(init3==1){
                    e[i][j]='x';
                    init4=1;
                    tempbest=Get4Worst();
                    best3=tempbest;
                    init3=0;
                    e[i][j]=' ';
                }else{
                    e[i][j]='x';
                    init4=1;
                    tempbest=Get4Worst();
                    if(tempbest>best3){
                        best3=tempbest;
                    }
                    e[i][j]=' ';
                }
            }
        }
    }
    return best3;
}


int Get2Worst(){                  ///find the worst in 2nd layer from best in third layer
    int i,j,tempworst;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(e[i][j]==' '){
                if(init2==1){
                    e[i][j]='o';
                    init3=1;
                    tempworst=Get3Best();
                    worst2=tempworst;
                    init2=0;
                    e[i][j]=' ';
                }else{
                    e[i][j]='o';
                    init3=1;
                    tempworst=Get3Best();
                    if(tempworst<worst2){
                        worst2=tempworst;
                    }
                    e[i][j]=' ';
                }
            }
          }
        }
            return worst2;

}

int Get1Best(){                   /// find the position of best in 1st layer
    int i,j,tempbest;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(e[i][j]==' '){
                if(init1==1){
                    e[i][j]='x';
                    init2=1;
                    tempbest=Get2Worst();
                    pos_best=i+10*j;
                    best1=tempbest;
                    init1=0;
                    e[i][j]=' ';
                }else{
                    e[i][j]='x';
                    init2=1;
                    tempbest=Get2Worst();
                    if(tempbest>best1){
                        pos_best=i+10*j;
                        best1=tempbest;
                    }
                    e[i][j]=' ';
                }
            }
        }
    }
    return pos_best;
}


int RowEvaluation(char a,char b,char c, char y){     /// function return 0 if there is a chance of triode of char opposite to y
    int count;                                      /// this will be used for calculation of  value of matrix
    if(a==y || b==y || c==y)
        return(0);
    else if(a==' ' && b==' ' && c==' '){
        return(0);
    }else{
        return(1);}
}

int CalculateBoardValue(char d[3][3]){                      /// calculate value of matrix
        int countx=0,counto=0;
        countx=countx+RowEvaluation(d[0][0],d[0][1],d[0][2],'o');
        countx=countx+RowEvaluation(d[1][0],d[1][1],d[1][2],'o');
        countx=countx+RowEvaluation(d[2][0],d[2][1],d[2][2],'o');
        countx=countx+RowEvaluation(d[0][0],d[1][0],d[2][0],'o');
        countx=countx+RowEvaluation(d[0][1],d[1][1],d[2][1],'o');
        countx=countx+RowEvaluation(d[0][2],d[1][2],d[2][2],'o');
        countx=countx+RowEvaluation(d[0][0],d[1][1],d[2][2],'o');
        countx=countx+RowEvaluation(d[2][0],d[1][1],d[0][2],'o');

        counto=counto+RowEvaluation(d[0][0],d[0][1],d[0][2],'x');
        counto=counto+RowEvaluation(d[1][0],d[1][1],d[1][2],'x');
        counto=counto+RowEvaluation(d[2][0],d[2][1],d[2][2],'x');
        counto=counto+RowEvaluation(d[0][0],d[1][0],d[2][0],'x');
        counto=counto+RowEvaluation(d[0][1],d[1][1],d[2][1],'x');
        counto=counto+RowEvaluation(d[0][2],d[1][2],d[2][2],'x');
        counto=counto+RowEvaluation(d[0][0],d[1][1],d[2][2],'x');
        counto=counto+RowEvaluation(d[2][0],d[1][1],d[0][2],'x');

        return(countx - counto);
}




int CheckWin(char d[3][3]){                                   /// will check if anybody had won i.e. anybody has a triode
    int countx=0;                                           /// return greater than 100 if computer wins
        countx=countx+Evaluation(d[0][0],d[0][1],d[0][2]); ///return greater than 10 if user wins
        countx=countx+Evaluation(d[1][0],d[1][1],d[1][2]); ///return less than 10 if nobody wins
        countx=countx+Evaluation(d[2][0],d[2][1],d[2][2]);
        countx=countx+Evaluation(d[0][0],d[1][0],d[2][0]);
        countx=countx+Evaluation(d[0][1],d[1][1],d[2][1]);
        countx=countx+Evaluation(d[0][2],d[1][2],d[2][2]);
        countx=countx+Evaluation(d[0][0],d[1][1],d[2][2]);
        countx=countx+Evaluation(d[2][0],d[1][1],d[0][2]);

        return countx;


}

int Evaluation(char a,char b,char c){  ///return 100 if triode of 'x'
        if(a=='x' && b=='x' && c=='x'){     ///return 10 if triode of 'o'
            return 100;
        }else if(a=='o' && b=='o' && c=='o')
            return 10;
        else if(a=='o'||a=='x' && b=='o'||b=='x' && c=='o'||c=='x')///return 1 if nobody has triode
            return 1;
        else
            return 0;                                               ///return 0 if empty matrix
}


void ContinueTTT(){                         /// continue game after one turn of each player is over
    int i,j,a,val,b;
    char c;

    printf("Its your turn Enter the co-ordinates:\n");
    printf("\nEnter x co-ordinate: ");
    scanf("%d",&i);
    printf("\nEnter y co-ordinate: ");
    scanf("%d",&j);
    e[i][j]='o';
    PrintGameGrid();
    GameOver();

    init1=1;
    if(UserChanceToWin()){
        b=UserChanceToWin();
        printf("\n computer machine turn : %d\n",b);
        i=(b%10)-1;
        j=(b/10)-1;
        e[i][j]='x';
        printf("\n\n\n");
        PrintGameGrid();
    }else{
    a=Get1Best();
    printf("\n best value is %d\n",a);
    i=a%10;
    j=a/10;
    e[i][j]='x';
    printf("\n\n\n");
    PrintGameGrid();
    }
    GameOver();

ContinueTTT();

}

void GameTTT(){ //initializing the game with empty matrix
e[0][0]=' ';
e[0][1]=' ';
e[0][2]=' ';
e[1][0]=' ';
e[1][1]=' ';
e[1][2]=' ';
e[2][0]=' ';
e[2][1]=' ';
e[2][2]=' ';
PrintGameGrid();
    ContinueTTT();
}

void PrintGameGrid(){               /// PrintGameGrid matrix
    int i;
    printf("\n     ===================   \n");
    for(i=0;i<3;i++){
        printf("     I  %c  I  %c  I  %c  I\n", e[i][0],e[i][1],e[i][2]);
        printf("     ===================   \n");
    }
}

int TriodCheck(char a,char b, char c){           // check if three char of triode are given
    if(a=='x' || b=='x' || c=='x')                //return 0 if no triode is possible for user
        return(0);                                //return 1 if first char is space and other 2 are 'o'
    else if(b=='o'&&c=='o' )                       //return 2 middle char is space and other are 'o'
        return 1;                                   // return 3 if last is space and other are 'o'
    else if(a=='o'&&c=='o')
        return 2;
    else if(a=='o'&&b=='o')
        return 3;
    else
        return 0;
}

int UserChanceToWin(){              /// check if in next turn user is winning i.e. 2 'o' and 1 ' '(space) in any triode
    int i,j;
    for(i=0;i<3;i++){
        if(TriodCheck(e[i][0],e[i][1],e[i][2])){
            return(i+1+10*(TriodCheck(e[i][0],e[i][1],e[i][2])));
        }
    }
    for(j=0;j<3;j++){
        if(TriodCheck(e[0][j],e[1][j],e[2][j])){
            return((TriodCheck(e[0][j],e[1][j],e[2][j]))+10*(j+1));
        }
    }
    if((TriodCheck(e[0][0],e[1][1],e[2][2])))
        return((TriodCheck(e[0][0],e[1][1],e[2][2]))+10*(TriodCheck(e[0][0],e[1][1],e[2][2])));
    else if((TriodCheck(e[0][2],e[1][1],e[2][0])))
        return(10*(4-(TriodCheck(e[0][2],e[1][1],e[2][0])))+(TriodCheck(e[0][2],e[1][1],e[2][0])));
    else
        return(0);
}

void GameOver(){                   /// check if game is finished
    int val;                            /// after game is over if new game to start or not
    char c;
    val=CheckWin(e);
    if(val>=100){
        printf("You Lost this game\n \n ");
        printf("Do you want to play again:  ");
        scanf("%s",&c);
        if(c=='y')
            GameTTT();
        else
            printf("\n \n Please close the window to exit \n \n ");
            scanf("%s",&c);
    }
    else if(val>=10){
        printf("Congratulation! You Win \n");
        printf("Do you want to play again:  ");
        scanf("%s",&c);
        if(c=='y')
            GameTTT();
        else
            printf("\n \n Please close the window to exit \n \n ");
            scanf("%s",&c);

    }else if(val>=8){
        printf("Game Draw\n\n");
        printf("Do you want to play again:  ");
        scanf("%s",&c);
        if(c=='y')
            GameTTT();
        else
            printf("\n \n Please close the window to exit \n \n ");
            scanf("%s",&c);
    }
}