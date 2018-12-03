#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
/*Atividade Prática Supervisionada
Objetivo: Calcular a constante de molas
Autores: Alexsandro Stepheson Paes Mendes, Deborah Silva Pires e Eduardo Candido Milani*/

int estatico()
{
    int j;
    int teste;
    printf("Quantos testes deseja relizar: ");
    scanf("%i",&teste);
    double vetor_massa[teste];
    double vetor_newton[teste];
    double vetor_variacao[teste];
    double soma_x=0;
    double soma_xx=0;
    double soma_xy=0;
    double soma_y=0;
    double cont_teorica;
    double por_erro;
    double a;//coef. linear
    double b;//coef. angular
    char escolha;
    char arquivo[100]="C:\\Users\\Alex\\Desktop\\arq.txt";
    char arquivo2[100]="C:\\Users\\Alex\\Desktop\\scr.txt";
    printf("Digite as massas (em kilogramas e em ordem crescente): \n");
    for(j=0;j<teste;j++){
        printf("%i° massa: ",j+1);
        scanf("%lf",&vetor_massa[j]);
        fflush(stdin);
    }
    printf("Digite as variacoes de comprimento (em metros e em ordem crescente): \n");
    for(j=0;j<teste;j++){
        printf("%i° variacao: ",j+1);
        scanf("%lf",&vetor_variacao[j]);
        fflush(stdin);
        soma_x+=vetor_variacao[j];
        soma_xx+=(vetor_variacao[j]*vetor_variacao[j]);
    }
    for(j=0;j<teste;j++){
        vetor_newton[j]=vetor_massa[j]*9.81;
        soma_y+=vetor_newton[j];
        soma_xy+=(vetor_variacao[j]*vetor_newton[j]);
    }
    a=(((soma_y*soma_xx)-(soma_x*soma_xy))/((teste*soma_xx)-pow(soma_x,2)));
    b=(((teste*soma_xy)-(soma_y*soma_x))/((teste*soma_xx)-pow(soma_x,2)));
    FILE *fd=NULL;
    if((fd=fopen(arquivo,"w"))==NULL){
        printf("ERRO!");
        exit(1);
    }
    fprintf(fd,"#EixoX \t\t #EixoY\n");
    for(j=0;j<teste;j++){
        fprintf(fd,"%7.3lf \t %7.3lf",vetor_variacao[j],vetor_newton[j]);
        fprintf(fd,"\n");
    }
    fclose(fd);
    FILE *fl=NULL;
    if((fl=fopen(arquivo2,"w"))==NULL){
        printf("ERRO!");
        exit(1);
    }
    fprintf(fl,"#Roteiro \n");
    fprintf(fl,"reset \n");
    fprintf(fl,"set xrange [0:25] \n");
    fprintf(fl,"set yrange [0:25] \n");
    fprintf(fl,"set grid \n");
    fprintf(fl,"plot f(x)=%7.3lf+%7.3lfx",a,b);
    fclose(fl);
    system("C:\\Users\\Alex\\Desktop\\gnuplot\\bin\\gnuplot -p C:\\Users\\Alex\\Desktop\\scr.txt");
    printf("\nA contante elástica da mola testada e %7.3lf. \n",b);
    printf("Gostaria de calcular o erro? \n");
    printf("S) Sim.\n");
    printf("N) Nao.\n");
    scanf("%c",&escolha);
    switch(escolha){
        case 's':
        case 'S':
            printf("Digite o valor que a constante deveria ter: ");
            scanf("%lf",&cont_teorica);
            fflush(stdin);
            por_erro=((b-cont_teorica)/cont_teorica)*100;
            por_erro=sqrt(pow(por_erro,2));
            printf("O erro foi de %7.3lf %%\n",por_erro);
        break;
        case 'n':
        case 'N':
        break;
        default:
            printf("Opcao invalida!\n");
        break;
    }
}
int dinamico()
{
    int coluna;
    int linha;
    int i,j;
    double media;
    double pi = 3.1415926;
    double constante;
    double soma_x=0;
    double soma_xx=0;
    double soma_xy=0;
    double soma_y=0;
    double a;
    double a1;
    double a2;
    double b;
    double b1;
    double b2;
    double cont_teorica;
    double por_erro;
    char escolha;
    char arquivo[100]="C:\\Users\\Alex\\Desktop\\arq.txt";
    char arquivo2[100]="C:\\Users\\Alex\\Desktop\\scr.txt";
    printf("Digite o numero de analises que deseja realizar: ");
    scanf("%i",&coluna);
    fflush(stdin);
    printf("Digite o numero de massas que deja usar: ");
    scanf("%i",&linha);
    fflush(stdin);
    double tabela[linha][coluna+2];
    double dados[linha][2];
    for(i=0;i<linha;i++){
        for(j=0;j<coluna+2;j++){
            if(j==0){
                printf("Digite a %i° massa: ",i+1);
                scanf("%lf",&tabela[i][j]);
                fflush(stdin);
            }else{
                if(j!=coluna+1){
                    printf("Digite o %i° periodo referente a %i° massa: ",j,i+1);
                    scanf("%lf",&tabela[i][j]);
                    fflush(stdin);
                    media=media+tabela[i][j];
                }else{
                    tabela[i][j]=media/(coluna);
                    media=0;
                }
            }
        }
    }
    for(i=0;i<linha;i++){
        for(j=0;j<2;j++){
            if(j==0){
                dados[i][j]=log10(tabela[i][0]);
                soma_x+=dados[i][j];
                soma_xx+=(dados[i][j]*dados[i][j]);
            }else{
                dados[i][j]=log10(tabela[i][coluna+1]);
                soma_y+=dados[i][j];
            }
        }
    }
    for(i=0;i<linha;i++){
        soma_xy+=(dados[i][0]*dados[i][1]);
    }
    a1=((soma_y*soma_xx)-(soma_x*soma_xy));
    a2=((linha*soma_xx)-pow(soma_x,2));
    a=a1/a2;
    b1=((linha*soma_xy)-(soma_y*soma_x));
    b2=((linha*soma_xx)-pow(soma_x,2));
    b=b1/b2;
    FILE *fd=NULL;
    if((fd=fopen(arquivo,"w"))==NULL){
        printf("ERRO!");
        exit(1);
    }
    fprintf(fd,"#EixoX \t #EixoY\n");
    for(j=0;j<10;j++){
        fprintf(fd,"%7.3lf \t %7.3lf",dados[j][0],dados[j][1]);
        fprintf(fd,"\n");
    }
    fclose(fd);
      FILE *fl=NULL;
    if((fl=fopen(arquivo2,"w"))==NULL){
        printf("ERRO!");
        exit(1);
    }
    fprintf(fl,"#Roteiro \n");
    fprintf(fl,"reset \n");
    fprintf(fl,"set grid \n");
    fprintf(fl,"set xrange [0:25] \n");
    fprintf(fl,"set yrange [0:25] \n");
    fprintf(fl,"plot f(x)=%7.3lf+%7.3lfx",a,b);
    fclose(fl);
    system("C:\\Users\\Alex\\Desktop\\gnuplot\\bin\\gnuplot -p C:\\Users\\Alex\\Desktop\\scr.txt");
    constante=pow(10,a);
    constante=2*pi/constante;
    constante=pow(constante,2);
    printf("A contante elastica da mola testada e %7.3lf. \n",constante);
    printf("Gostaria de calcular o erro? \n");
    printf("S) Sim.\n");
    printf("N) Nao.\n");
    scanf("%c",&escolha);
    switch(escolha){
        case 's':
        case 'S':
            printf("Digite o valor que a constante deveria ter: ");
            scanf("%lf",&cont_teorica);
            fflush(stdin);
            por_erro=((constante-cont_teorica)/cont_teorica)*100;
            por_erro=sqrt(pow(por_erro,2));
            printf("O erro foi de %7.3lf %%\n",por_erro);
        break;
        case 'n':
        case 'N':
        break;
        default:
            printf("Opcao invalida!\n");
        break;
    }
}
int main()
{
    int opcao;
    char escolha;
    do{
        printf("MENU: \n");
        printf("1)Calculo da constante da mola. \n");
        printf("2)Sair do programa. \n");
        scanf("%i",&opcao);
        fflush(stdin);
        switch(opcao){
            case 1:
                printf("Calculo da constante da mola: \n");
                printf("\tA)Metodo estatico. \n");
                printf("\tB)Metodo dinamico. \n");
                printf("\tC)Voltar para o menu anterior. \n\t");
                scanf("%c",&escolha);
                fflush(stdin);
                switch(escolha){
                    case 'A':
                    case 'a':
                        estatico();
                    break;
                    case 'B':
                    case 'b':
                        dinamico();
                    break;
                    case 'C':
                    case 'c':
                    break;
                    default:
                        printf("Opcao invalida!\n");
                    break;
            }
            break;
            case 2:
                printf("Tchau!");
            break;
            default:
                printf("Opcao invalida!\n");
            break;
        }
    }while(opcao!=2);
    return 0;
}
