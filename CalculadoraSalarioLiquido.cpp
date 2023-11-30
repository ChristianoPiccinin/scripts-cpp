#include <stdio.h>

int main() {
    
    double valorHora;
    int horasTrabalhadas;
    
    //exercicio 1
    printf("Digite o valor da hora em reais: ");
    scanf("%lf", &valorHora);
    
    //exercicio 2
    printf("Digite a quantidade de horas trabalhadas: ");
    scanf("%d", &horasTrabalhadas);
    
    //exercicio 3
    //calcular salario bruto 
    double salarioBruto = horasTrabalhadas * valorHora * 5.25;
    
    //exercicio 4
    //calcular o desconto de INSS
    double descontoINSS;
    if(salarioBruto <= 1751.81) {
        descontoINSS = salarioBruto * 0.08;
    }else if(salarioBruto <= 2919.72){
        descontoINSS = salarioBruto * 0.09;
    }else if(salarioBruto <= 5839.45){
         descontoINSS = salarioBruto * 0.11;
    }else {
        descontoINSS = 642.34;
    }
    
    //exercicio 5
    //Calcular o desconto de IRRF
    double descontoIRRF;
    if(salarioBruto <= 1903.98){
        descontoIRRF = 0.0;
    }else if(salarioBruto <= 2826.65){
        descontoIRRF = salarioBruto * 0.075;
    }else if(salarioBruto <= 3751.05){
        descontoIRRF = salarioBruto * 0.15;
    }else if(salarioBruto <= 4664.68){
        descontoIRRF = salarioBruto * 0.225;
    }else{
        descontoIRRF = salarioBruto * 0.275;
    }
    
    //exercicio 6 
    //Calcular salario liquido
    double salarioLiquido = salarioBruto - descontoINSS - descontoIRRF;
    
    
    //exercicio 7
    //Exibir a folha de pagamento
    
    printf("\n Folha de Pagamento:\n");
    printf("Valor da hora de trabalho: R$ %.2lf\n",valorHora);
    printf("Quantidade de horas semanais: %d horas\n", horasTrabalhadas );
    printf("Salário bruto (sem desconto): R$ %.2lf\n", salarioBruto);
    printf("Desconto de INSS: R$ %.2lf\n", descontoINSS);
    printf("Desconto de IRRF: R$ %.2lf\n", descontoIRRF);
    printf("Total de descontos (INSS + IRFF): R$ %.2lf\n", descontoINSS + descontoIRRF);
    printf("Salário líquido (depositado):  R$ %.2lf\n", salarioLiquido);
    
    
    return 0;
}