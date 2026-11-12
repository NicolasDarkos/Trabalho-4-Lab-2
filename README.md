TRABALHO 4 - PILHAS E FILAS

Alunos: Bruno Bellinasso Brasil, Nícolas Focking da Rosa, Vinicius Morais Vilar

ARQUIVOS
- main.c / menu.c / menu.h : menu principal e funcoes de interface (opcoes 1, 4, 5 e 6)
- restaurante.c / .h       : struct Restaurante (matriz de mesas, pilha e fila), criacao e liberacao
- mesa.c / mesa.h          : struct Mesa, chegada de clientes, liberacao de mesa e impressao das mesas
- prato.c / prato.h        : pilha de pratos limpos (lista encadeada)
- filaDeEspera.c / .h      : fila de espera de grupos (lista encadeada, com senha unica)

O QUE FOI FEITO
1) Abrir restaurante: o usuario informa linhas e colunas; a matriz de mesas e alocada
   dinamicamente; todas as mesas abrem livres e arrumadas (4 pratos). A pilha de pratos
   abre com um estoque inicial de 4 pratos por mesa.
2) Chegada de clientes: o grupo ocupa quantas mesas livres forem necessarias (ate 4 pessoas
   por mesa, sem exigir adjacencia). Quem nao conseguir mesa vai para a fila de espera com
   uma senha unica. Cada mesa ocupada recebe uma comanda. Grupos diferentes nao compartilham
   mesas. Os pratos excedentes da mesa sao retirados e devolvidos a pilha; se a mesa tiver
   menos pratos que pessoas, tenta-se completar com pratos da pilha.
3) Finalizar refeicao/liberar mesa: o usuario informa o numero da mesa. Os pratos da mesa
   voltam para a pilha e a mesa e arrumada novamente com 4 pratos (ou com o que houver na
   pilha, se nao houver pratos suficientes). Em seguida os grupos da fila sao chamados; se o
   grupo for grande, senta apenas parte dele e permanece na fila com a MESMA senha e a
   quantidade de pessoas atualizada.
4) Desistir de esperar: o usuario informa a senha e o grupo sai da fila de espera.
5) Repor pratos: o usuario informa quantos pratos adicionar na pilha, a qualquer momento.
6) Imprimir: mesa por numero, ocupacao de todas as mesas, fila de espera (grupos, senhas e
   total de pessoas), pilha de pratos (quantidade) ou tudo.
- Structs alocadas dinamicamente, sem variaveis globais, uso de funcoes com passagem de
  parametros e liberacao de toda a memoria ao sair.

DECISOES DE PROJETO
- Cada mesa ocupada gera uma comanda propria (um grupo de 2 mesas tem 2 comandas).
- Os pratos de uma mesa liberada voltam limpos para a pilha antes de a mesa ser arrumada.
