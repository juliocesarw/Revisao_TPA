### Trabalho de TPA (Teste de Conhecimento) - C++
<b>Enunciado:</b> Faça um programa que faça a leitura de um arquivo com dados de alunos em CSV.
Os dados devem ser armazenados em uma estrutura de lista duplamente encadeada.
Faça a opção de buscar por matricula e cpf.
Quando encontrar, ele deve mostrar os dados do aluno e também dar a opção de remover.

Na inserção não será permitido inserir CPFs nem matriculas iguais, então verifique se o cpf já nao existe antes de inserir outro aluno. A inserção deve ser ordenada por Nome no momento da inserção.

## Implementação da Tabela hash

<b>Enunciado:</b> Altere o programa da Atividade 1 para agora ter um vetor com 100 elementos da estrutura Alunos. E utilize os dois digitos verificadores do CPF para escolher em qual índice esse Alunos deve ser adicionado. Faça tudo utilizando e medindo métricas de tempo.

Coloque um comentário do tempo gasto para executar. Lembre que os alunos devem ser inseridos de forma ordenada pelo nome e você deve pesquisar se existem CPFs repetidos. Não precisa mais de verificar se a matrícula está repetida.

## Nova tarefa - Otimização do tempo

<b>Enunciado:</b> Crie mais 3 hashs de tamanhos distintos para o cpf, utilize alguma ideia sua para cada uma. (no lugar de usar os dois ultimos digitos do cpf). Faça uma com 1000 índices no vetor, 10000 índices e 100000 índices. Faça a analise do tempo de inserção de todos os elementos e veja o que ocorre.

Analise o impacto do tempo da busca por nome. Crie uma busca automática que busque por 10 nomes, e rode o tempo disso nos 4 hashs implementados.

Após isso, volte para a hash de 100, e mude a forma de ordenação na lista. Passe a ordenar por cpf, e após inserir tudo, rode um algoritmo de ordenação, de preferência o quicksort em cada lista da hash. Faça a comparação de tempo para inserir tudo entre essa forma e a forma inicial que é ordenando por nome.